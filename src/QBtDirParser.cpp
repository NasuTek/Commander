/*****************************************************************************
 * NasuTek Commander
 * Copyright (C) 2012 NasuTek Enterprises <mmanley@nasutek.com>
 * Copyright (C) 2005-2008 Piotr Pszczolkowski <piotr@beesoft.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtDirParser.h"
#include "QBtShared.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QtDebug>


//*******************************************************************
// cancel                                                     PUBLIC
//*******************************************************************
void QBtDirParser::cancel()
{
   break_ = true;
}
// end of cancel

//*******************************************************************
// run                                                        PUBLIC
//*******************************************************************
void QBtDirParser::run( const QString& in_dir_path,
                        const QString& in_fname_muster,
                        const bool     in_file_filter )
{
   fname_muster_ = in_fname_muster;
   file_filter_ = in_file_filter;
   break_ = false;
   do_it( in_dir_path );
   emit finished();
}
// end of run

//*******************************************************************
// do_it                                                     PRIVATE
//*******************************************************************
void QBtDirParser::do_it( const QString& in_path )
{
   QBtShared::idle();
   if( break_ ) return;

   const QFileInfo fi( in_path );
   
   if( fi.isDir() ) {
      if( fi.isExecutable() && fi.isReadable() ) {
         emit change_dir( in_path );
         parse_dir( in_path );
         if( remove_ ) remove_dir( in_path );
      }
      else {
         emit cant_read_dir( in_path );
      }
   }
   else {
      emit current_item( in_path );
      if( remove_ ) remove_file( in_path );
   }
}
// end of do_it

//*******************************************************************
// parse_dir                                                 PRIVATE
//*******************************************************************
void QBtDirParser::parse_dir( const QString& in_dir_path )
{
   QBtShared::idle();
   if( break_ ) return;

   QDir dir( in_dir_path );
   QDir::Filters filter = QDir::AllDirs | QDir::Files | QDir::NoSymLinks;
   if( !file_filter_ ) filter |= QDir::Hidden;
   dir.setFilter ( filter );
   dir.setNameFilters( fname_muster_.split( ';', QString::SkipEmptyParts ) );
   const QFileInfoList data = dir.entryInfoList();

   QFileInfoList::const_iterator it = data.begin();
   const QFileInfoList::const_iterator end = data.end();
   while( !break_ && ( it != end ) ) {
      if( QBtShared::is_regular_file( it->fileName() ) ) {
         do_it( it->absoluteFilePath() );
      }
      ++it;
   }
}
// end of parse_dir

//*******************************************************************
// remove_file                                               PRIVATE
//*******************************************************************
void QBtDirParser::remove_file( const QString& in_file_path )
{
   if( break_ ) return;
   
   if( !QFile::remove( in_file_path ) ) {
      emit cant_remove_file( in_file_path );
   }
}
// end of current_item

//*******************************************************************
// remove_dir                                                PRIVATE
//*******************************************************************
void QBtDirParser::remove_dir( const QString& in_dir_path )
{
   if( break_ ) return;

   QDir dir( in_dir_path );
   const QString dir_name = dir.dirName();
   if( dir.cdUp() ) {
      if( !dir.rmdir( dir_name ) ) {
         emit cant_remove_dir( in_dir_path );
      }
   }
}
// end of remove_dir

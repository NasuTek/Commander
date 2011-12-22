/*****************************************************************************
 * NasuTek Commander
 * Copyright © 2012 NasuTek Enterprises <mmanley@nasutek.com>
 * Copyright © 2005-2008 Piotr Pszczolkowski <piotr@beesoft.org>
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
#include "QBtDirWorkedThread.h"
#include "QBtFileInfo.h"
#include "QBtShared.h"
#include "QBtConfig.h"
#include <QDir>
#include <QFileInfo>
#include <QVariant>
#include <QDebug>


//*******************************************************************
// QBtDirWorkedThread                                    CONSTRUCTOR
//*******************************************************************
QBtDirWorkedThread::QBtDirWorkedThread( QObject* const in_parent ) : QBtWorkedThread( in_parent )
{}
// end of QBtDirWorkedThread

//*******************************************************************
// update                                                     PUBLIC
//*******************************************************************
void QBtDirWorkedThread::update( const QString& in_path )
{
   path_ = in_path;
   start();
}
// end of update

//*******************************************************************
// run                                           PROTECTED inherited
//*******************************************************************
void QBtDirWorkedThread::run()
{
   QDir dir( path_ );
   if( dir.exists() && dir.isReadable() ) {
      //-------------------------------
      const quint32 filter_state = 
         QBtConfig::instance()->filter()
         ? ( QDir::AllDirs | QDir::Files )
         : ( QDir::AllDirs | QDir::Files | QDir::Hidden );
      dir.setFilter( static_cast< QDir::Filters >( filter_state ) );
      dir.setSorting( QDir::Name | QDir::DirsFirst | QDir::IgnoreCase );
      const QFileInfoList data = dir.entryInfoList();
      //-------------------------------
      emit work_started();
      const qint32 n = data.size();
      emit items_count( n - ( dir.isRoot() ? 2 : 1 ) );
      //-------------------------------
      for( qint32 i = 0, row = 0; i < n; ++i ) {
         const QBtFileInfo fi( QFileInfo( data.at( i ) ) );
         
         if( "." == fi.full_name() ) continue;
         if( ( ".." == fi.full_name() ) && ( path_ == QDir::rootPath() ) ) continue;

         QStringList data;
         if( ".." == fi.full_name() ) {
            data << fi.full_name();
         }
         else
         {
            QString name   = fi.name();
            QString ext    = fi.ext();
            if( name.isEmpty() ) {
               name = '.' + ext;
               ext.clear();
            }
            const QString access = QBtShared::access( fi );
            const QString size   = QBtShared::num2str( fi.size() );
            const QString date   = fi.lastmod().date().toString( "dd-MM-yyyy" );
            const QString time   = fi.lastmod().time().toString( "hh:mm:ss" );
            const QString owner  = fi.owner();
            const QString group  = fi.group();
            data << name << ext << access << size << date << time << owner << group;
         }
         emit item_info( row++, QVariant::fromValue( fi ), data );
      }
      emit work_finished( path_ );
   }
}
// end of run

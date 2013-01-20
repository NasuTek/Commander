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
#include "QBtConfig.h"
#include "QBtDirModel.h"
#include "QBtShared.h"
#include "QBtEventsController.h"
#include "QBtViewItem.h"
#include "QBtViewStandardItem.h"
#include "QBtDirWorkedThread.h"
#include "QBtFileInfo.h"
#include <QApplication>
#include <QDateTime>
#include <QDir>


//*******************************************************************
// QBtDirModel                                           CONSTRUCTOR
//*******************************************************************
QBtDirModel::QBtDirModel( QObject* const in_parent ) : QBtViewModel( in_parent )
{
   thread_ = new QBtDirWorkedThread( this );
   connect( thread_, SIGNAL( work_started      () ),
            this   , SLOT  ( work_started_slot () ) );
   connect( thread_, SIGNAL( items_count       ( qint32 ) ),
            this   , SLOT  ( items_count_slot  ( qint32 ) ) );
   connect( thread_, SIGNAL( item_info         ( qint32, QVariant, QStringList ) ),
            this   , SLOT  ( item_info_slot    ( qint32, QVariant, QStringList ) ) );
   connect( thread_, SIGNAL( work_finished     ( const QString ) ),
            this   , SLOT  ( work_finished_slot( const QString ) ) );
}
// end of QBtDirModel

//*******************************************************************
// QBtDirModel                                           CONSTRUCTOR
//*******************************************************************
QBtDirModel::~QBtDirModel()
{
   delete dynamic_cast<QBtDirWorkedThread*>( thread_ );
   thread_ = 0;
}
// end of ~QBtDirModel

//*******************************************************************
// update                                          PUBLIC inherited
//*******************************************************************
void QBtDirModel::update( const QString& in_path )
{
   thread_->update( in_path );
}
void QBtDirModel::update( const QModelIndex& in_index )
{
   const QBtViewItem* const it = head_item( in_index );
   if( it ) {
      if( valid_dir_name( it->finfo().full_name() ) ) {
         thread_->update( it->finfo().path() );
      }
   }
}
// end of update

//*******************************************************************
// refresh                                          PUBLIC inherited
//*******************************************************************
void QBtDirModel::refresh()
{
   update( current_path_ );
}
// end of refresh

//*******************************************************************
// is_dir                                                     PUBLIC
//*******************************************************************
bool QBtDirModel::is_dir( const QModelIndex& in_index )
{
   const QBtViewItem* const it = head_item( in_index );
   return ( it ) ? it->finfo().is_dir() : false;
}
// end of is_dir

//*******************************************************************
// is_readable                                                PUBLIC
//*******************************************************************
bool QBtDirModel::is_readable( const QModelIndex& in_index )
{
   const QBtViewItem* const it = head_item( in_index );
   return ( it ) ? it->finfo().is_readable() : false;
}
// end of is_dir

//*******************************************************************
// cdup                                                       PUBLIC
//*******************************************************************
void QBtDirModel::cdup()
{
   QDir dir( current_path_ );
   if( !dir.isRoot() && dir.cdUp() ) {
      update( dir.absolutePath() );
   }
}
// end of cdup

//*******************************************************************
// append_row                                                PRIVATE
//*******************************************************************
void QBtDirModel::append_row( const qint32 in_row,
                              const QBtFileInfo& in_finfo,
                              const QStringList& in_data )
{
   const bool is_parent_dir = ( PARENT_DIR == in_data[ 0 ] );
   QStandardItem* const root_it = invisibleRootItem();

   {  // Nazwa pliku
      QBtViewItem* const it = new QBtViewItem;
      if( is_parent_dir ) {
         it->setIcon( QIcon( DIR_ICON ) );
      }
      else {
         if( in_finfo.is_dir() ) {
            const QIcon icon = QIcon( in_finfo.is_readable() ? DIR_ICON : NOREADABLE_ICON );
            it->setIcon( icon );
            ++dir_count_;
         }
         else {
            ++file_count_;
         }
      }
      it->finfo( in_finfo );
      it->setText( in_data[ 0 ] );
      root_it->setChild( in_row, 0, it );
   }

   if( is_parent_dir ) return;
   
   {  // Rozszerzenie
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setTextAlignment( Qt::AlignLeft );
      item->setText( in_data[ 1 ] );
      root_it->setChild( in_row, 1, item );
   }
   {  // Prawa dostepu
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setTextAlignment( Qt::AlignLeft );
      item->setText( in_data[ 2 ] );
      root_it->setChild( in_row, 2, item );
   }
   {  // Rozmiar pliku
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setTextAlignment( Qt::AlignRight );
      item->setText( in_data[ 3 ] );
      root_it->setChild( in_row, 3, item );
   }
   {  // Data
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setText( in_data[ 4 ] );
      root_it->setChild( in_row, 4, item );
   }
   {  // Czas
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setText( in_data[ 5 ] );
      root_it->setChild( in_row, 5, item );
   }
   {  // Nazwa wlasciciela
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setText( in_data[ 6 ] );
      root_it->setChild( in_row, 6, item );
   }
   {  // Nazwa grupy
      QBtViewStandardItem* const item = new QBtViewStandardItem;
      item->setText( in_data[ 7 ] );
      root_it->setChild( in_row, 7, item );
   }
}
// end of append_row

//###################################################################
//#                                                                 #
//#                   P R I V A T E   S L O T S                     #
//#                                                                 #
//###################################################################

//*******************************************************************
// work_started_slot                                    PRIVATE slot
//*******************************************************************
void QBtDirModel::work_started_slot()
{
   QApplication::setOverrideCursor( Qt::WaitCursor );      
   busy_ = true;
   file_count_ = dir_count_ = qint32();
   selections_.clear();
   invisibleRootItem()->removeRows( 0, invisibleRootItem()->rowCount() );
}
// end of work_started_slot

//*******************************************************************
// items_count_slot                                     PRIVATE slot
//*******************************************************************
void QBtDirModel::items_count_slot( const qint32 in_row_count )
{
   invisibleRootItem()->setColumnCount( columnCount() );
   invisibleRootItem()->setRowCount( in_row_count );
}
// end of items_count_slot

//*******************************************************************
// item_info_slot                                       PRIVATE slot
//*******************************************************************
void QBtDirModel::item_info_slot( const qint32 in_row, QVariant in_fi, QStringList in_data )
{
   append_row( in_row, in_fi.value<QBtFileInfo>(), in_data );
}
// end of item_info_slot

//*******************************************************************
// work_finished_slot                                   PRIVATE slot
//*******************************************************************
void QBtDirModel::work_finished_slot( const QString in_path )
{
   current_path_ = in_path;
   QApplication::restoreOverrideCursor();
   emit update_finished();
   busy_ = false;
}
// end of work_finished_slot

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
#include "QBtDeleteQuest.h"
#include "QBtShared.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QHeaderView>
#include <QFileInfo>

/*------- constants:
-------------------------------------------------------------------*/
const char* const QBtDeleteQuest::CAPTION = QT_TR_NOOP( "Delete files/directories" );
const char* const QBtDeleteQuest::WIPE    = QT_TR_NOOP( "&Wipe files" );
const char* const QBtDeleteQuest::ACCEPT  = QT_TR_NOOP( "&Accept" );
const char* const QBtDeleteQuest::CANCEL  = QT_TR_NOOP( "&Cancel" );
const char* const QBtDeleteQuest::HEAD    = QT_TR_NOOP( "Name of file/directory" );


//*******************************************************************
// QBtDeleteQuest                                        CONSTRUCTOR
//*******************************************************************
QBtDeleteQuest::QBtDeleteQuest( QWidget* const in_parent ) : QDialog( in_parent )
, view_   ( new QTreeWidget )
, wipe_   ( new QCheckBox  ( tr( WIPE   ) ) )
, accept_ ( new QPushButton( tr( ACCEPT ) ) )
, cancel_ ( new QPushButton( tr( CANCEL ) ) )
{
   setWindowTitle( tr( CAPTION ) );

   view_->setSortingEnabled( false );
   view_->setAlternatingRowColors( true );
   view_->setRootIsDecorated( false );
   view_->setEditTriggers( QTreeView::NoEditTriggers );
   view_->setColumnCount( 1 );
   view_->setHorizontalScrollMode( QTreeWidget::ScrollPerPixel );

   QTreeWidgetItem* const itm = new QTreeWidgetItem;
   itm->setText( 0, tr( HEAD ) );
   view_->setHeaderItem( itm );

   QVBoxLayout* const view_layout = new QVBoxLayout;
   view_layout->addWidget( view_ );
   view_layout->addWidget( wipe_ );

   QVBoxLayout* const btn_layout = new QVBoxLayout;
   btn_layout->addStretch( 100 );
   btn_layout->addWidget( accept_ );
   btn_layout->addWidget( cancel_ );
   
   QHBoxLayout* const main_layout = new QHBoxLayout;
   main_layout->addLayout( view_layout );
   main_layout->addLayout( btn_layout );
   setLayout( main_layout );

   connect( accept_, SIGNAL( clicked() ), this, SLOT( accept() ) );
   connect( cancel_, SIGNAL( clicked() ), this, SLOT( reject() ) );
}
// end of QBtDeleteQuest

//*******************************************************************
// showEvent                                       PRIVATE inherited
//*******************************************************************
void QBtDeleteQuest::showEvent( QShowEvent* const in_event )
{
   QDialog::showEvent( in_event );
   
   QTreeWidgetItem* const root = view_->invisibleRootItem();
   view_->setCurrentItem( root->child( 0 ) );
   accept_->setDefault( true );
   accept_->setFocus( Qt::OtherFocusReason );
}
// end of showEvent

//*******************************************************************
// set_files                                                  PUBLIC
//*******************************************************************
void QBtDeleteQuest::set_files( const SelectionsSet& in_data )
{
   SelectionsSet::const_iterator it = in_data.begin();
   const SelectionsSet::const_iterator end = in_data.end();
   while( it != end ) {
      QTreeWidgetItem* const itm = new QTreeWidgetItem( view_ );
      itm->setText( 0, QFileInfo( *it ).fileName() );
      ++it;
   }
   view_->resizeColumnToContents( 0 );
}
// end of set_files

//*******************************************************************
// to_wipe                                                    PUBLIC
//*******************************************************************
bool QBtDeleteQuest::to_wipe() const
{
   return wipe_->isChecked();
}
// end of to_wipe

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
 ------------------------------------------------------------------*/
 #include "QBtDirSelector.h"
 #include "QBtShared.h"
 #include <QVBoxLayout>
 #include <QHBoxLayout>
 #include <QPushButton>
 #include <QTreeView>
 #include <QDirModel>
 #include <QDir>
 #include <QHeaderView>
 #include <QtDebug>

 /*------- constants:
 ------------------------------------------------------------------*/
const char* const QBtDirSelector::Caption = QT_TR_NOOP( "Directories tree" );
const char* const QBtDirSelector::Select  = QT_TR_NOOP( "&Select" );
const char* const QBtDirSelector::Close   = QT_TR_NOOP( "&Close" );


//*******************************************************************
// QBtDirSelector                                        CONSTRUCTOR
//*******************************************************************
QBtDirSelector::QBtDirSelector( QWidget* const in_parent, const QString& in_path )
: QDialog( in_parent )
, view_       ( new QTreeView )
, select_btn_ ( new QPushButton( tr( Select ) ) )
, cancel_btn_ ( new QPushButton( tr( Close  ) ) )
, model_      ( new QDirModel( QStringList(), QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase ) )
, path_       ( in_path )
{
   setWindowTitle( tr( Caption ) );
   cancel_btn_->setDefault( true );

   model_->setReadOnly( true );
   view_->setModel( model_ );
   view_->setColumnHidden( 1, true );
   QHeaderView* const hdr = view_->header();
   hdr->setStretchLastSection( true );
   hdr->setSortIndicator( 0, Qt::AscendingOrder );
   hdr->setSortIndicatorShown( true );
   hdr->setClickable( true );
   
   QHBoxLayout* const btn_layout = new QHBoxLayout;
   btn_layout->addStretch();
   btn_layout->addWidget( select_btn_ );
   btn_layout->addWidget( cancel_btn_ );

   QVBoxLayout* const main_layout = new QVBoxLayout;
   main_layout->addWidget( view_ );
   main_layout->addLayout( btn_layout );
   setLayout( main_layout );

   connect( cancel_btn_, SIGNAL( clicked() ), this, SLOT( reject() ) );
   connect( select_btn_, SIGNAL( clicked() ), this, SLOT( accept() ) );
}
// end of QBtDirSelector

//*******************************************************************
// showEvent                                       PRIVATE inherited
//*******************************************************************
void QBtDirSelector::showEvent( QShowEvent* const in_event )
{
   QDialog::showEvent( in_event );
   QBtShared::resize( this, 35, 50 );

   const QModelIndex index = model_->index( path_ );
   view_->expand( index );
   view_->scrollTo( index, QTreeView::PositionAtCenter );
   view_->setCurrentIndex( index );
   view_->resizeColumnToContents( 0 );
   view_->resizeColumnToContents( 2 ); // kolumna nr.1 jest ukryta
   view_->setAllColumnsShowFocus( true );
}
// end of showEvent

//*******************************************************************
// path                                                       PUBLIC
//*******************************************************************
QString QBtDirSelector::path()
{
   const QModelIndex idx = view_->currentIndex();
   return ( idx.isValid() ?  model_->filePath( idx ) : QString() );
}
// end of path

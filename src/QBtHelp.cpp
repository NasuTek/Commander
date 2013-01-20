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
#include "QBtHelp.h"
#include "QBtShared.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QMessageBox>
#include <QShowEvent>
#include <QApplication>

/*------- constants:
-------------------------------------------------------------------*/
const char* const QBtHelp::CAPTION            = QT_TR_NOOP( "Help"    );
const char* const QBtHelp::CANCEL             = QT_TR_NOOP( "&Cancel" );
const char* const QBtHelp::NOT_FOUND_CAPTION  = QT_TR_NOOP( "File not found" );
const char* const QBtHelp::NOT_FOUND_MESSAGE  = QT_TR_NOOP( "The help file not found:\n%1" );

//*******************************************************************
// QBtHelp                                               CONSTRUCTOR
//*******************************************************************
QBtHelp::QBtHelp( QWidget* const in_parent ) : QDialog( in_parent )
, browser_ ( new QTextBrowser )
, cancel_  ( new QPushButton( tr( CANCEL ) ) )
{
   setWindowTitle( tr( CAPTION ) );

   QHBoxLayout* const btn_layout = new QHBoxLayout;
   btn_layout->addStretch();
   btn_layout->addWidget( cancel_ );

   QVBoxLayout* const main_layout = new QVBoxLayout;
   main_layout->addWidget( browser_ );
   main_layout->addLayout( btn_layout );
   setLayout( main_layout );

   connect( cancel_, SIGNAL( clicked() ), this, SLOT( accept() ) );
}
// end of QBtHelp

//*******************************************************************
// showEvent                                       PRIVATE inherited
//*******************************************************************
void QBtHelp::showEvent( QShowEvent* const in_event )
{
   QString fpath = QApplication::applicationDirPath();
   if( !fpath.endsWith( QDir::separator() ) ) fpath += QDir::separator();
   fpath += "help.en.html";

   QFile file( fpath );
   if( file.open( QIODevice::ReadOnly ) ) {
      QTextStream in( &file );
      browser_->insertHtml( in.readAll() );
      file.close();
   }
   else {
      QMessageBox::critical( this, tr( NOT_FOUND_CAPTION ), tr( NOT_FOUND_MESSAGE ).arg( fpath ) );
   }

   QBtShared::resize( this, 50, 50 );
   QDialog::showEvent( in_event );
}
// end of showEvent

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
#include "QBtMainWindow.h"
#include "QBtShared.h"
#include "QBtConfig.h"
#include "QBtEventsController.h"
#include <QVariant>
#include <QApplication>
#include <QIcon>

//*******************************************************************
// main
//*******************************************************************
int main( int in_argc, char** in_argv )
{
   Q_INIT_RESOURCE( nc );

   QCoreApplication::setOrganizationName  ( QBtShared::ORGANISATION );
   QCoreApplication::setOrganizationDomain( QBtShared::ORGANISATION );
   QCoreApplication::setApplicationName   ( QBtShared::PROGRAM_NAME );

   QApplication bsc( in_argc, in_argv );
   bsc.setWindowIcon( QIcon( ":/img/nc.png" ) );

   QBtConfig::instance();
   QBtEventsController::instance();
   qRegisterMetaType<QVariant>( "QVariant" );
   
   
   QBtMainWindow window;
   window.show();
   
   return bsc.exec();
}
// end of main

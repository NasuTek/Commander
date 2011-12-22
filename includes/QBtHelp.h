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

#ifndef INCLUDED_QBtHelp_h
#define INCLUDED_QBtHelp_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTextBrowser;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtHelp : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtHelp( QWidget* = 0 );
private:
   QBtHelp( const QBtHelp& );
   QBtHelp& operator=( const QBtHelp& );

//******* CONSTANTS ********
private:
   static const char* const CAPTION;
   static const char* const CANCEL;
   static const char* const NOT_FOUND_CAPTION;
   static const char* const NOT_FOUND_MESSAGE;

//******* MEMBERS *******
private:
   QTextBrowser* const browser_;
   QPushButton*  const cancel_;

//******* METHODS *******
private:
   void showEvent( QShowEvent* );
};

#endif // INCLUDED_QBtHelp_h

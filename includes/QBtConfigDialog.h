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

#ifndef INCLUDED_QBtConfigDialog_h
#define INCLUDED_QBtConfigDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTabBar;
class QStackedWidget;
class QPushButton;
class QBtConfigPanels;
class QBtConfigButtons;
class QBtConfigApps;
class QBtConfigExtensions;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtConfigDialog : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtConfigDialog( QWidget* = 0 );
private:
   QBtConfigDialog( const QBtConfigDialog& );
   QBtConfigDialog& operator=( const QBtConfigDialog& );

//******* CONSTANTS ********
private:
   enum {
      PANELS_IDX = 0,
      BUTTONS_IDX,
      CONSOLE_IDX,
      EXTENSIONS_IDX
   };
   static const char* const CAPTION;
   static const char* const PANELS;
   static const char* const BUTTONS;
   static const char* const CONSOLE;
   static const char* const EXTENSIONS;
   static const char* const APPLY;
   static const char* const EXIT;

//******* MEMBERS *******
private:
   QTabBar*             const tbar_;
   QStackedWidget*      const wstack_;
   QPushButton*         const apply_;
   QPushButton*         const exit_;
   QBtConfigPanels*     const panels_;
   QBtConfigButtons*    const buttons_;
   QBtConfigApps*       const apps_;
   QBtConfigExtensions* const extensions_;

//******* METHODS *******
private slots:
   void tab_changed( int );
   void apply      ();
};

#endif // INCLUDED_QBtConfigDialog_h

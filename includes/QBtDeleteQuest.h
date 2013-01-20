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

#ifndef INCLUDED_QBtDeleteQuest_h
#define INCLUDED_QBtDeleteQuest_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>
#include "BtTypes.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTreeWidget;
class QPushButton;
class QCheckBox;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDeleteQuest : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDeleteQuest( QWidget* = 0 );
private:
   QBtDeleteQuest( const QBtDeleteQuest& );
   QBtDeleteQuest& operator=( const QBtDeleteQuest& );

//******* CONSTANTS *******
private:
   static const char* const CAPTION;
   static const char* const WIPE;
   static const char* const ACCEPT;
   static const char* const CANCEL;
   static const char* const HEAD;

//******* MEMBERS *******
private:
   QTreeWidget* const view_;
   QCheckBox*   const wipe_;
   QPushButton* const accept_;
   QPushButton* const cancel_;

//******* METHODS *******
public:
   void set_files( const SelectionsSet& );
   bool to_wipe  () const;
private:
   void showEvent( QShowEvent* );
};

#endif // INCLUDED_QBtDeleteQuest_h

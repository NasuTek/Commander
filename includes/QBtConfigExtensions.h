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

#ifndef INCLUDED_QBtConfigExtensions_h
#define INCLUDED_QBtConfigExtensions_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QWidget>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTreeWidget;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtConfigExtensions : public QWidget
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtConfigExtensions( QWidget* = 0 );
private:
   QBtConfigExtensions( const QBtConfigExtensions& );
   QBtConfigExtensions& operator=( const QBtConfigExtensions& );

//******* CONSTANTS ********
private:
   static const char* const REMOVE;
   static const char* const ADD;
   static const char* const EDIT;
   static const char* const EXT;
   static const char* const PRG;
   static const char* const PAR;
   
//******* MEMBERS *******
private:
   QTreeWidget* const table_;
   QPushButton* const remove_;
   QPushButton* const add_;
   QPushButton* const edt_;

//******* METHODS *******
private:
   void add_item( const QString&, const QString&, const QString& );
   void restore ();
private slots:
   void remove  ();
   void add     ();
   void edit    ();
public:
   void save    ();
};

#endif // INCLUDED_QBtConfigExtensions_h

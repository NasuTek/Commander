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

#ifndef INCLUDED_QBtDeleter_h
#define INCLUDED_QBtDeleter_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>
#include "BtTypes.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QFrame;
class QPushButton;
class QBtInfoField;
class QBtDirParser;
class QBtWiper;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDeleter : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDeleter( QWidget* = 0 );
private:
   QBtDeleter( const QBtDeleter& );
   QBtDeleter& operator=( const QBtDeleter& );

//******* CONSTANTS *******
private:
   static const char* const CAPTION;
   static const char* const RUN;
   static const char* const CANCEL;
   static const char* const BREAK;
   static const char* const DIR_ERROR;
   static const char* const CANT_DEL_FILE;
   static const char* const CANT_DEL_DIR;

//******* MEMBERS *******
private:
   QBtInfoField*           const info_;
   QFrame*                 const line_;
   QPushButton*            const run_;
   QPushButton*            const cancel_;
   QBtDirParser*           const parser_;
   QBtWiper*                     wiper_;
   bool                          break_;
   bool                          runned_;
   bool                          wipe_;
   SelectionsSet                 data_;
   SelectionsSet::const_iterator it_;
   SelectionsSet::const_iterator end_;

//******* METHODS *******
public:
   void set_data( const SelectionsSet&, bool );
private:
   void showEvent         ( QShowEvent* );
   void keyPressEvent     ( QKeyEvent* );
private slots:
   void run               ();
   void cancel            ();
   void current_item      ( const QString& );
   void finished          ();
   void read_dir_error    ( const QString& );
   void remove_dir_error  ( const QString& );
   void remove_file_error ( const QString& );
   void progress          ( const QString& );
};

#endif // INCLUDED_QBtDeleter_h 

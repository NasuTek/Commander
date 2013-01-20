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

#ifndef INCLUDED_QBtCanOverwrite_h
#define INCLUDED_QBtCanOverwrite_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QLabel;
class QCheckBox;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtCanOverwrite : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtCanOverwrite( QWidget*, const QString& );
private:
   QBtCanOverwrite( const QBtCanOverwrite* );
   QBtCanOverwrite& operator=( const QBtCanOverwrite& );

//******* CONSTANTS *******
public:
   enum {
      CANCEL_FILE = -1,
      SKIP_FILE = 1,
      OVERWRITE_FILE,
      UPDATE_FILE,
      RENAME_FILE
   };
   static const char* const CAPTION;
   static const char* const MESSAGE;
   static const char* const SKIP;
   static const char* const OVERWRITE;
   static const char* const UPDATE;
   static const char* const RENAME;
   static const char* const DONT_ASK_AGAIN;
   static const char* const CANCEL;
   

//******* MEMBERS *******
private:
   QCheckBox*   const dont_ask_;
   QPushButton* const skip_;
   QPushButton* const overwrite_;
   QPushButton* const update_;
   QPushButton* const rename_;
   QPushButton* const cancel_;
   QLabel*      const path_;

//******* METHODS *******
public:
   bool ask_again() const;
private:
   void showEvent( QShowEvent* );
private slots:
   void skip     ();
   void overwrite();
   void update   ();
   void rename   ();
   void cancel   ();
};

#endif // INCLUDED_QBtCanOverwrite_h

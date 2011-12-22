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

#ifndef INCLUDED_QBtFileEditor_h
#define INCLUDED_QBtFileEditor_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTextEdit;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtFileEditor : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtFileEditor( QWidget*, const QString& );
private:
   QBtFileEditor( const QBtFileEditor& );
   QBtFileEditor& operator=( const QBtFileEditor& );

//******* CONSTANTS ********
private:
   static const char* const CAPTION;
   static const char* const RELOAD;
   static const char* const SAVE;
   static const char* const CANCEL;
   static const char* const NOTEXT_FILE;
   static const char* const READ_ERROR;
   static const char* const SAVE_ERROR;

//******* MEMBERS *******
private:
   QString             path_;
   QTextEdit*    const editor_;
   QPushButton*  const reload_;
   QPushButton*  const save_;
   QPushButton*  const cancel_;

//******* METHODS *******
private:
   void showEvent  ( QShowEvent* );
   void load_file  ();
private slots:
   void reload_file();
   void save_file  ();
};

#endif // INCLUDED_QBtFileEditor_h

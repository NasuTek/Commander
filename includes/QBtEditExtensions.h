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

#ifndef INCLUDED_QBtEditExtensions_h
#define INCLUDED_QBtEditExtensions_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QLineEdit;
class QLabel;
class QPushButton;
class QGroupBox;
class QTextBrowser;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtEditExtensions : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtEditExtensions( QWidget*, const QString& = QString(), const QString& = QString(), const QString& = QString() );
private:
   QBtEditExtensions( const QBtEditExtensions& );
   QBtEditExtensions& operator=( const QBtEditExtensions& );   

//******* CONSTANTS *******
private:
   static const char* const CAPTION;
   static const char* const INFO_CAPTION;
   static const char* const EXTENSION;
   static const char* const APPLICATION;
   static const char* const PARAMETERS;
   static const char* const ACCEPT;
   static const char* const CANCEL;
   static const char* const HELP;
   static const char* const EXT_IS_EMPTY;
   static const char* const PRG_IS_EMPTY;
   static const char* const PRG_NOT_FOUND;
   static const char* const PAR_IS_EMPTY;
   static const char* const IS_NOT_PRG;
   static const char* const SELECT;
   static const char* const FILTER;

//******* MEMBERS *******
private:
   QLabel*       const ext_prompt_;
   QLabel*       const prg_prompt_;
   QLabel*       const par_prompt_;
   QLineEdit*    const ext_;
   QLineEdit*    const prg_;
   QLineEdit*    const par_;
   QPushButton*  const path_;
   QPushButton*  const accept_;
   QPushButton*  const cancel_;
   QGroupBox*    const info_;
   QLabel*       const help_;

//******* METHODS *******
public:
   void data      ( QString&, QString&, QString& );
private:
   void showEvent ( QShowEvent* );
   bool is_ext_ok ();
   bool is_prg_ok ();
   bool is_par_ok ();
private slots:
   void accept    ();
   void select    ();
};

#endif // INCLUDED_QBtEditExtensions_h

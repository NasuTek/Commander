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

#ifndef INCLUDED_QBtAttrDialog_h
#define INCLUDED_QBtAttrDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QCheckBox;
class QPushButton;
class QLabel;

/*------- class declarations:
-------------------------------------------------------------------*/
class QBtAttrDialog : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtAttrDialog( QWidget*, const SelectionsSet& );
private:
   QBtAttrDialog( const QBtAttrDialog& );
   QBtAttrDialog& operator=( const QBtAttrDialog& );

//******* CONSTANTS *******
private:
   static const char* const CAPTION;
   static const char* const FILE_NAME;
   static const char* const RECURSIVE;
   static const char* const ACCEPT;
   static const char* const CLOSE;
#if !_WIN32
   static const char* const USER;
   static const char* const GROUP;
   static const char* const OTHER;
   static const char* const READ;
   static const char* const WRITE;
   static const char* const EXECUTE;
#else
   static const char* const READONLY;
   static const char* const HIDDEN;
   static const char* const ARCHIVE;
   static const char* const SYSTEM;
#endif

//******* MEMBERS *******
private:
   SelectionsSet      data_;
   QLabel*      const path_;
   QCheckBox*   const recursive_;
#if !_WIN32
   QCheckBox*   const user_read_;
   QCheckBox*   const user_write_;
   QCheckBox*   const user_exec_;
   QCheckBox*   const group_read_;
   QCheckBox*   const group_write_;
   QCheckBox*   const group_exec_;
   QCheckBox*   const other_read_;
   QCheckBox*   const other_write_;
   QCheckBox*   const other_exec_;
#else
   QCheckBox*   const readonly_;
   QCheckBox*   const hidden_;
   QCheckBox*   const archive_;
   QCheckBox*   const system_;
#endif
   QPushButton* const close_;
   QPushButton* const accept_;

//******* METHODS *******
private:
   void    set_info();
   QString get_info() const;
   bool    are_dirs() const;
   void    execute ( const QString& ) const;
private slots:
   void    accept  ();
};

#endif // INCLUDED_QBtAttrDialog_h

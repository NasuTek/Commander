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

#ifndef INCLUDED_QBtDirCopyDialog_h
#define INCLUDED_QBtDirCopyDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtCopyDialog.h"
#include "QBtSystemCall.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QFileInfo;
class QBtDirParser;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDirCopyDialog : public QBtCopyDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDirCopyDialog( QWidget* = 0 );
private:
   QBtDirCopyDialog( const QBtDirCopyDialog& );
   QBtDirCopyDialog& operator=( const QBtDirCopyDialog& );

//******* CONSTANTS *******
private:
   enum {
      BLOCK_SIZE = 8192
   };
   static const char* const CAPTION;
   static const QString     CHOWN;

//******* MEMBERS *******
private:
   char block_ [ BLOCK_SIZE ];
   QBtSystemCall sc_;

//******* METHODS *******
private:
   void copy_next  ( const QString&, const QString& );
   void copy_file  ( const QString&, const QString& );
   void copy_dir   ( const QString&, const QString& );
   bool can_update ( const QString&, const QString& ) const;
   void remove_dir ( const QString& );
private slots:
   void start();
};

#endif // INCLUDED_QBtDirCopyDialog_h

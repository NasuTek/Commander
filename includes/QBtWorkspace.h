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

#ifndef INCLUDED_QBtWorkspace_h
#define INCLUDED_QBtWorkspace_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QWidget>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QSplitter;
class QBtPanel;
class QBtView;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtWorkspace : public QWidget
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtWorkspace( QWidget* = 0 );
   ~QBtWorkspace();
private:
   QBtWorkspace( const QBtWorkspace& );
   QBtWorkspace& operator=( const QBtWorkspace& );

//******* CONSTANTS *******
public:
   enum {
      LEFT_PANEL_ID = 0,
      RIGHT_PANEL_ID
   };
   static const char* const InputCaption;
   static const char* const InputPrompt;
   static const char* const CompareFiles;
   static const char* const NoFiles;
   static const char* const FilesJoining;
   static const char* const EnterFileName;
   static const char* const NoWritableDir;
   static const char* const CanOverwrite;
   static const char* const Md5;
   static const char* const SyncNoDirs;
   static const char* const CmpNoDirs;
   static const char* const UserError;
   static const QString     Md5Create;
   static const QString     Md5Check;

//******* MEMBERS *******
private:
   QSplitter* const splitter_;
   QBtPanel*        left_panel_;
   QBtPanel*        right_panel_;

//******* METHODS *******
private:
   void keyPressEvent   ( QKeyEvent* );
   void customEvent     ( QEvent* );
   void save            ();
   void restore         ();
   void switch_panels   ();
   bool src_and_dst_view( QBtView*&, QBtView*&      ) const;
   bool get_selections  ( QBtView* , SelectionsSet& ) const;
   void copy            ();
   void pack            ();
   void compare_files   ();
   void compare_dirs    ();
   void sync_dirs       ();
   void diff            ( const QString&, const QString& ) const;
   void join_files      ();
   void dir_tree        ();
   void md5_create      ();
   void md5_check       ();
   void date_time       ();
};

#endif // INCLUDED_QBtWorkspace_h

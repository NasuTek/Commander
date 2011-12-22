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

#ifndef INCLUDED_QBtView_h
#define INCLUDED_QBtView_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QTreeView>
#include <stack>
#include <queue>


/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtViewModel;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtView : public QTreeView
{
   Q_OBJECT

//******** TYPES *******
private:
   enum {
      UNKNOWN = 0,
      INITIAL_FILE_SELECT,
      RESIZE_COLUMNS,
      GOTO_TOP,
      REFRESH,
   };

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtView( const QString&, QWidget* = 0 );
   ~QBtView();
private:
   QBtView( const QBtView& );
   QBtView& operator=( const QBtView& );
   
//****** MEMBERS *******
private:
   QBtViewModel*         model_;
   std::queue< qint32 >  requests_;
   std::stack< QString > initial_file_stack_;

//******* CONSTANTS *******
private:
   static const char* const MKDIR_CAPTION;
   static const char* const MKDIR_PROMPT;
   static const char* const MKDIR_ERROR;
   static const char* const RENAME_CAPTION;
   static const char* const RENAME_PROMPT;
   static const char* const RENAME_ERROR;

//******* METHODS *******
public:
   QString  selected_file_full_name  () const;
   QString  selected_file_path       () const;
   void           set_initial_file_request ( const QString& );
   void           set_initial_file         ();
   void           update                   ( const QString& );
   const QString& current_path             () const;
   void           goto_top                 ();
   const SelectionsSet&  get_selected_items() const;
   void           refresh                  ( const QString& = QString());
   void           unselect_all             ();
   void           one_level_up             ();
private:
   void    settings          ();
   void    keyPressEvent     ( QKeyEvent* );
   void    customEvent       ( QEvent* );
   void    find              ();
   void    enter_key         ();
   void    jump_to_home      ();
   void    resize_columns    ();
   void    select            ();
   void    select_mask       ();
   void    deselect_mask     ();
   void    revert_selection  ();
   void    select_all        ();
   void    remove_selected   ();
   void    access_permissions();
   void    mkdir             ();
   void    rename            ();
   void    view              ();
   void    edit              ();
   void    console_start     () const;
   bool    is_ext_declared   ( const QString&, QString&, QString& ) const;
private slots:
   void    enter            ( const QModelIndex& );
signals:
   void    dir_count        ( qint32 );
   void    file_count       ( qint32 );
   void    select_count     ( qint32 );
   void    path_changed     ( const QString& );
private slots:
   void    request_finished();
};

#endif // INCLUDED_QBtView_h

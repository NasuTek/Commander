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

#ifndef INCLUDED_QBtViewModel_h
#define INCLUDED_QBtViewModel_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QStandardItemModel>
#include <vector>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtViewItem;
class QBtWorkedThread;
class QBtFileInfo;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtViewModel : public QStandardItemModel
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtViewModel( QObject* = 0 );
private:
   QBtViewModel( const QBtViewModel& );
   QBtViewModel& operator=( const QBtViewModel& );

//******* CONSTANTS *******
protected:
   static const QString     THIS_DIR;
   static const QString     PARENT_DIR;
private:
   static const char* const HDR_NAME;
   static const char* const HDR_EXT;
   static const char* const HDR_ACCESS;
   static const char* const HDR_SIZE;
   static const char* const HDR_DATE;
   static const char* const HDR_TIME;
   static const char* const HDR_OWNER;
   static const char* const HDR_GROUP;
   static const char* const MASK_SELECTION_CAPTION;
   static const char* const MASK_SELECTION_PROMPT;
   static const char* const MASK_DESELECTION_PROMPT;
public:
   static const char* const DIR_ICON;
   static const char* const NOREADABLE_ICON;

//******* MEMEBERS *******
protected:
   QString          current_path_;
   qint32           file_count_;
   qint32           dir_count_;
   bool             busy_;
   QBtWorkedThread* thread_;
   SelectionsSet    selections_;

//******* METHODS *******
public:
   virtual void   update      ( const QString&     ) = 0;
   virtual void   update      ( const QModelIndex& ) = 0;
   virtual void   refresh     ()                     = 0;
   virtual bool   is_dir      ( const QModelIndex& ) = 0;
   virtual bool   is_readable ( const QModelIndex& ) = 0;
   virtual void   cdup        ()                     = 0;
   //--------------------------------------------
   const QString&        current_path      () const;
   QString               file_full_name    ( const QModelIndex& ) const;
   QString               file_path         ( const QModelIndex& ) const;
   QModelIndex           search_file       ( const QString& );
   QBtViewItem*          head_item         ( const QModelIndex& ) const;
   QBtViewItem*          head_item         ( qint32 ) const;
   QModelIndex           head_item_index   ( qint32 ) const;
   bool                  select            ( const QModelIndex& );
   void                  select_mask       ( bool, QWidget* = 0 );
   void                  revert_selections ();
   void                  clear_selections  ();
   void                  select_all        ();
   const SelectionsSet&  get_selected_items() const;
   //--------------------------------------------
   qint32                dir_count         () const { return dir_count_;         }
   qint32                file_count        () const { return file_count_;        }
   qint32                select_count      () const { return selections_.size(); }
   bool                  busy              () const { return busy_;              }
private:
   void                  select_this_item  ( bool, QBtViewItem* );
protected:
   bool                  valid_dir_name    ( const QString& );
signals:
   void                  update_finished   ();
};

#endif // INCLUDED_QBtViewModel_h

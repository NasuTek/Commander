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

#ifndef INCLUDED_QBtViewItem_h
#define INCLUDED_QBtViewItem_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QStandardItem>
#include "QBtFileInfo.h"

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtViewItem : public QStandardItem
{
//******* TYPES *******
public:
//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtViewItem() : QStandardItem()
   , selected_ ( false )
   , finfo_    ( QBtFileInfo() )
   {}
private:
   QBtViewItem( const QBtViewItem& rhs ) : QStandardItem( rhs )
   , selected_ ( rhs.selected_ )
   , finfo_    ( rhs.finfo_     )
   {}
   QBtViewItem& operator=( const QBtViewItem& rhs )
   {
      if( this != &rhs ) {
         QStandardItem::operator=( rhs );
         selected_ = rhs.selected_;
         finfo_    = rhs.finfo_;
      }
      return *this;
   }

//******* METHODS *******
public:
   bool               selected () const                        { return selected_;        }
   void               selected ( const bool in_selected )      { selected_ = in_selected; }
   const QBtFileInfo& finfo    () const                        { return finfo_;           }
   void               finfo    ( const QBtFileInfo& in_finfo ) { finfo_ = in_finfo;       }
//******* MEMBERS *******
private:
   bool        selected_;
   QBtFileInfo finfo_;
};

#endif // INCLUDED_QBtViewItem_h

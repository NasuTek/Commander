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

#ifndef INCLUDED_QBtSystemInfo_h
#define INCLUDED_QBtSystemInfo_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QStackedWidget;
class QTabBar;
class QTreeWidget;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtSystemInfo : public QDialog
{
   Q_OBJECT

// ******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtSystemInfo( QWidget* = 0 );
private:
   QBtSystemInfo( const QBtSystemInfo& );
   QBtSystemInfo& operator=( const QBtSystemInfo& );

// ******* CONSTANTS *******
private:
   enum {
      DISK_IDX = 0,
      MEMORY_IDX,
      
      DSK_FS_IDX = 0,
      DSK_TYPE_IDX,
      DSK_SIZE_IDX,
      DSK_USED_IDX,
      DSK_AVAIL_IDX,
      DSK_USE_IDX,
      DSK_MOUNT_IDX,
      DSK_COL_COUNT,

      MEM_EMPTY_IDX = 0,
      MEM_TOTAL_IDX,
      MEM_USED_IDX,
      MEM_FREE_IDX,
      MEM_SHARED_IDX,
      MEM_BUFFERS_IDX,
      MEM_CACHED_IDX,
      MEM_COL_COUNT,
   };
   static const char* const CAPTION;
   static const char* const DISKS;
   static const char* const MEMORY;
   static const char* const CLOSE;
   static const char* const DSK_FS;
   static const char* const DSK_TYPE;
   static const char* const DSK_SIZE;
   static const char* const DSK_USED;
   static const char* const DSK_AVAIL;
   static const char* const DSK_USE;
   static const char* const DSK_MOUNT;
   static const char* const MEM_EMPTY;
   static const char* const MEM_TOTAL;
   static const char* const MEM_USED;
   static const char* const MEM_FREE;
   static const char* const MEM_SHARED;
   static const char* const MEM_BUFFERS;
   static const char* const MEM_CACHED;
   
// ******* MEMBERS *******
private:
   QStackedWidget* const wstack_;
   QTabBar*        const tbar_;
   QTreeWidget*    const disk_view_;
   QTreeWidget*    const memory_view_;
   QPushButton*    const close_;

// ******* METHODS *******
private:
   void showEvent     ( QShowEvent* );
   void read_dsk_data ();
   void read_mem_data ();
   void add_dsk_item  ( const QStringList& );
   void add_mem_item  ( const QStringList& );
private slots:
   void tab_changed   ( int );
};

#endif // INCLUDED_QBtSystemInfo_h

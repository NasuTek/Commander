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

#ifndef INCLUDED_QBtDirModel_h
#define INCLUDED_QBtDirModel_h

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtViewModel.h"

/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtFileInfo;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDirModel : public QBtViewModel
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDirModel( QObject* = 0 );
   ~QBtDirModel();
private:
   QBtDirModel( const QBtDirModel& );
   QBtDirModel& operator=( const QBtDirModel& );

//******* METHODS *******
public:
   void update              ( const QString& );
   void update              ( const QModelIndex& );
   void refresh             ();
   bool is_dir              ( const QModelIndex& );
   bool is_readable         ( const QModelIndex& );
   void cdup                ();
private:
   void append_row          ( qint32, const QBtFileInfo&, const QStringList& );
private slots:
   void work_started_slot   ();
   void items_count_slot    ( qint32 );
   void item_info_slot      ( qint32, QVariant, QStringList );
   void work_finished_slot  ( QString );
};

#endif // INCLUDED_QBtDirModel_h

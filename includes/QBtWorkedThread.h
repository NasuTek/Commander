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

#ifndef INCLUDED_QBtWorkedThred_h
#define INCLUDED_QBtWorkedThred_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QThread>
#include <QVariant>
#include <QStringList>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtWorkedThread : public QThread
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtWorkedThread( QObject* = 0 );
private:
   QBtWorkedThread( const QBtWorkedThread& );
   QBtWorkedThread& operator=( const QBtWorkedThread& );

//******* MEMBERS *******
protected:
   QString path_;

//******* METHODS *******
public:
   virtual void update( const QString& ) = 0;
protected:
   virtual void run() = 0;
signals:
   void work_started  ();
   void items_count   ( qint32 );
   void item_info     ( qint32, QVariant, QStringList );
   void work_finished ( const QString );   
};

#endif // INCLUDED_QBtWorkedThred_h

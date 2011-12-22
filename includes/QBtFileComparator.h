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

#ifndef INCLUDED_QBtFileComparator_h
#define INCLUDED_QBtFileComparator_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtFileComparator : public QObject
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtFileComparator( QObject* = 0 );
private:
   QBtFileComparator( const QBtFileComparator& );
   QBtFileComparator& operator=( const QBtFileComparator& );

//******* TYPES *******
public:
   enum {
      BUFFER_SIZE = 4096,
      EQUAL = 0,
      NOT_EQUAL,
      IO_ERROR,
   };

//******* MEMBERS *******
private:
   bool loop_;
   
//******* METHODS *******
public:
   void  stop    ();
   qint32 compare( const QString&, const QString& );
signals:
   void init_progress ( qint64 );
   void progress      ( qint64 );
};

#endif // INCLUDED_QBtFileComparator_h

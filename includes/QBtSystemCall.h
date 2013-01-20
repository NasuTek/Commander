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

#ifndef INCLUDED_QBtSystemCall_h
#define INCLUDED_QBtSystemCall_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>
#include <QProcess>
#include <QByteArray>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtSystemCall : public QObject
{
//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtSystemCall( QObject* in_parent = 0 ) : QObject( in_parent )
   {}
private:
   QBtSystemCall( const QBtSystemCall& );
   QBtSystemCall& operator=( const QBtSystemCall& );

//******* MEMBERS *******
private:
   QByteArray buffer_;

//******* METHODS ********
public:
   void    run   ( const QString& );
   QString result() const;
};

#endif // INCLUDED_QBtSystemCall_h

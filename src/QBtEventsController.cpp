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

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtEventsController.h"
#include <QApplication>
#include <QMutexLocker>
#include <QtDebug>
using namespace std;

//*******************************************************************
// QBtEventsController                           CONSTRUCTOR private
//*******************************************************************
QBtEventsController::QBtEventsController() : QObject()
{
   setParent( qApp );
}
// end of EventsControler

//*******************************************************************
// ~EventsContoller                               DESTRUCTOR private
//*******************************************************************
QBtEventsController::~QBtEventsController()
{
   QMutexLocker locker( &mutex_ );
   evreg_.clear();
}
// end of ~QBtEventsController

//*******************************************************************
// instance                                                   PUBLIC
//*******************************************************************
QBtEventsController* QBtEventsController::instance()
{
   static QBtEventsController* instance = 0;
   if( !instance ) instance = new QBtEventsController;
   return instance;
}
// end of instance

//*******************************************************************
// append                                                     PUBLIC
//-------------------------------------------------------------------
// Zarejestrowanie chetnego do odbierania wskazanego sygnalu.
//*******************************************************************
bool QBtEventsController::append( QObject* const in_receiver, const qint32 in_event_id )
{
   QMutexLocker locker( &mutex_ );
   bool retval = true;

   // Jesli taka pozycja juz istnieje to nie zapamietujemy jej ponownie.
   if( exists( in_receiver, in_event_id ) ) {
      retval = false;
   }
   // Jesli nie ma takiej pozycji to ja zapamietujemy w rejestrze.
   else {
      EventsRegister::iterator it = evreg_.find( in_event_id );
      if( it != evreg_.end() ) {
         retval = it->second.insert( in_receiver ).second;
         //print();
      }
   }
   return retval;
}
// end of append

//*******************************************************************
// remove                                                     PUBLIC
//*******************************************************************
void QBtEventsController::remove( QObject* const in_receiver )
{
   QMutexLocker locker( &mutex_ );

   if( !evreg_.empty() ) {
      EventsRegister::iterator it = evreg_.begin();
      const EventsRegister::iterator end = evreg_.end();
      while( it != end ) {
         it->second.erase( in_receiver );
         ++it;
      }
   }
   //print();
}
// end of remove

//*******************************************************************
// exists                                                    PRIVATE
//*******************************************************************
bool QBtEventsController::exists( QObject* const in_receiver, const qint32 in_event_id )
{
   bool retval = false;

   const EventsRegister::const_iterator it = evreg_.find( in_event_id );
   if( it != evreg_.end() ) {
      if( it->second.find( in_receiver ) != it->second.end() ) {
         retval = true;
      }
   }
   else {
      // Dopisuje do rejestru TYLKO identyfikator sygnalu (nie obiekt).
      evreg_.insert( EventsRegister::value_type( in_event_id, Objects() ) );
   }
   return retval;
}
// end of exists

//*******************************************************************
// send_event                                                 PUBLIC
//*******************************************************************

// WERSJA BEZ DANYCH
void QBtEventsController::send_event( const qint32 in_event_id )
{
   QMutexLocker locker( &mutex_ );

   const EventsRegister::const_iterator rit = evreg_.find( in_event_id );
   if( rit != evreg_.end() ) {
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         QApplication::postEvent( *it, new QBtEvent( in_event_id ) );
         ++it;
      }
   }
}
// WERSJA Z 1 DANA
void QBtEventsController::send_event(  const qint32 in_event_id,
                                       const QVariant in_val )
{
   QMutexLocker locker( &mutex_ );

   const EventsRegister::const_iterator rit = evreg_.find( in_event_id );
   if( rit != evreg_.end() ) {
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         QApplication::postEvent( *it, new QBtEvent( in_event_id, in_val ) );
         ++it;
      }
   }
}
// WERSJA Z 2 DANYMI
void QBtEventsController::send_event(  const qint32 in_event_id,
                                       const QVariant in_val1,
                                       const QVariant in_val2 )
{
   QMutexLocker locker( &mutex_ );

   const EventsRegister::const_iterator rit = evreg_.find( in_event_id );
   if( rit != evreg_.end() ) {
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         QApplication::postEvent( *it, new QBtEvent( in_event_id, in_val1, in_val2 ) );
         ++it;
      }
   }
}
// WERSJA Z 3 DANYMI
void QBtEventsController::send_event(  const qint32 in_event_id,
                                       const QVariant in_val1,
                                       const QVariant in_val2,
                                       const QVariant in_val3 )
{
   QMutexLocker locker( &mutex_ );

   const EventsRegister::const_iterator rit = evreg_.find( in_event_id );
   if( rit != evreg_.end() ) {
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         QApplication::postEvent( *it, new QBtEvent( in_event_id, in_val1, in_val2, in_val3 ) );
         ++it;
      }
   }
}
// WERSJA Z 4 DANYMI
void QBtEventsController::send_event(  const qint32 in_event_id,
                                       const QVariant in_val1,
                                       const QVariant in_val2,
                                       const QVariant in_val3,
                                       const QVariant in_val4 )
{
   QMutexLocker locker( &mutex_ );

   const EventsRegister::const_iterator rit = evreg_.find( in_event_id );
   if( rit != evreg_.end() ) {
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         QApplication::postEvent( *it, new QBtEvent( in_event_id, in_val1, in_val2, in_val3, in_val4 ) );
         ++it;
      }
   }
}
// end of send_event


//*******************************************************************
// print                                                     PRIVATE
//*******************************************************************
/*
void QBtEventsController::print()
{
   qDebug() << "=======================================================";
   EventsRegister::const_iterator rit = evreg_.begin();
   const EventsRegister::const_iterator rend = evreg_.end();
   while( rit != rend ) {
      qDebug() << rit->first;
      Objects::const_iterator it = rit->second.begin();
      const Objects::const_iterator end = rit->second.end();
      while( it != end ) {
         qDebug() << "\t" << *it;
         ++it;
      }
      ++rit;
   }
}
*/
// end of print

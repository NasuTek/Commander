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
#include "QBtFileComparator.h"
#include <QFile>

//*******************************************************************
// QBtFileComparator                                     CONSTRUCTOR
//*******************************************************************
QBtFileComparator::QBtFileComparator( QObject* const in_parent )
: QObject( in_parent )
, loop_  ( true )
{
}
// end of QBtFileComparator

//*******************************************************************
// stop                                                       PUBLIC
//*******************************************************************
void QBtFileComparator::stop()
{
   loop_ = false;
}
// end of stop   

//*******************************************************************
// compare                                                    PUBLIC
//*******************************************************************
qint32 QBtFileComparator::compare(  const QString& in_fname1,
                                    const QString& in_fname2 )
{
   qint32 retval                  = IO_ERROR;
   char   buffer1[ BUFFER_SIZE ] = { 0 };
   char   buffer2[ BUFFER_SIZE ] = { 0 };
   
   QFile in1( in_fname1 );
   QFile in2( in_fname2 );  
   emit init_progress( in1.size() );

   if( in1.size() != in2.size() ) {
      emit progress( in1.size() );
      return NOT_EQUAL;
   }

   qint64 total = qint64();
   if( in1.open( QIODevice::ReadOnly ) ) {
      if( in2.open( QIODevice::ReadOnly ) ) {
         while( loop_ && !in1.atEnd() && !in2.atEnd() ) {
            const quint32 n1 = in1.read( buffer1, BUFFER_SIZE );
            const quint32 n2 = in2.read( buffer2, BUFFER_SIZE );
            retval = ( n1 == n2 ) ? memcmp( buffer1, buffer2, n1 ) : NOT_EQUAL;
            if( EQUAL != retval ) break;
            total += n1;
            emit progress( total );
         }
         in2.close();
      }
      in1.close();
   }
   return retval; 
}
// end of compare

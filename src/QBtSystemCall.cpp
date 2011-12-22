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
#include "QBtSystemCall.h"
#include <QtDebug>

//*******************************************************************
// run                                                        PUBLIC
//*******************************************************************
void QBtSystemCall::run( const QString& in_cmd )
{
   buffer_.clear();
   QProcess process;
   process.start( in_cmd );
   while( process.waitForReadyRead() ) {
      buffer_ += process.readAll();
   }
}
// end of run

//*******************************************************************
// result                                                     PUBLIC
//*******************************************************************
QString QBtSystemCall::result() const
{
   return QString::fromLocal8Bit( buffer_ );
}
// end of result

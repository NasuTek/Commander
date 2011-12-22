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
#include "QBtSettings.h"

//*******************************************************************
// save                                                       PUBLIC
//*******************************************************************
bool QBtSettings::save( const QString& in_ident, const QVariant& in_data )
{
   setValue( in_ident, in_data );
   return ( NoError == status() );
}
// end of save

//*******************************************************************
// read                                                PUBLIC static
//*******************************************************************
bool QBtSettings::read( const QString& in_ident, QVariant& out_data )
{
   bool retval = contains( in_ident );
   if( retval ) {
      out_data = value( in_ident );
      retval = ( NoError == status() );
   }
   return retval;
}
// end of read

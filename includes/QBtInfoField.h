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

#ifndef INCLUDED_QBtInfoField_h
#define INCLUDED_QBtInfoField_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QLineEdit>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtInfoField : public QLineEdit
{
public:
   QBtInfoField( QWidget* const in_parent = 0 ) : QLineEdit( in_parent )
   {
      setReadOnly( true );
      setFrame( false );
      setAlignment( Qt::AlignLeft );
      setFocusPolicy( Qt::NoFocus );
      //setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
   }
private:
   QBtInfoField( const QBtInfoField& );
   QBtInfoField& operator=( const QBtInfoField& );
};

#endif // INCLUDED_QBtInfoField_h

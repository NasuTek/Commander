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

#ifndef INCLUDED_QBtInfoLabel_h
#define INCLUDED_QBtInfoLabel_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QLabel>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtInfoLabel : public QLabel
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtInfoLabel( QWidget* = 0 );
private:
   QBtInfoLabel( const QBtInfoLabel& );
   QBtInfoLabel& operator=( const QBtInfoLabel& );

//******* CONSTANTS *******
private:
   static const QString Spacer;
   static const QString Slash;
   
//******* METHODS *******
public:
   void setText( const QString& );
private:
   void    paintEvent( QPaintEvent* );
   QString elide     ( int ) const;
};

#endif //INCLUDED_QBtInfoLabel_h

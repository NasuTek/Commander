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

#ifndef INCLUDED_QBtViewDelegate_h
#define INCLUDED_QBtViewDelegate_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QItemDelegate>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtView;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtViewDelegate : public QItemDelegate
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtViewDelegate( QBtView* = 0 );
private:
   QBtViewDelegate( const QBtViewDelegate& );
   QBtViewDelegate& operator=( const QBtViewDelegate& );

//******* MEMBERS *******
private:
   const QBtView* const view_;

private:
   void paint( QPainter*, const QStyleOptionViewItem&, const QModelIndex& ) const;
};

#endif // INCLUDED_QBtViewDelegate_h

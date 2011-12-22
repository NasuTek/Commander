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

#ifndef INCLUDED_QBtTabBar_h
#define INCLUDED_QBtTabBar_h

/*------- include files:
------------------------------------------------------------------*/
#include <QTabBar>

/*------- class declarations:
------------------------------------------------------------------*/
class QBtTabBar : public QTabBar
{
    Q_OBJECT
    
//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtTabBar( QWidget* in_parent = 0 ) : QTabBar( in_parent )
   {}
private:
   void mousePressEvent( QMouseEvent* in_event ) {
      QTabBar::mousePressEvent( in_event );
      emit mouse_event();
   }
signals:
   void mouse_event();
 };

#endif // INCLUDED_QBtTabBar_h 

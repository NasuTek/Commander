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

#ifndef INCLUDED_QBtColorDemo_h
#define INCLUDED_QBtColorDemo_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QLineEdit>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QColor;
class QFont;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtColorDemo : public QLineEdit
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtColorDemo( bool = false, QWidget* = 0 );
private:
   QBtColorDemo( const QBtColorDemo& );
   QBtColorDemo& operator=( const QBtColorDemo& );

//******* CONSTANTS *******
private:
   static const int HEIGHT;
   static const char* const TEXT;

//******* METHODS *******
public:
   void   background ( const QColor& );
   QColor background () const;
   void   color      ( const QColor& );
   QColor color      () const;
   void   fonts      ( const QFont& );
   QFont  fonts      () const;

public slots:
   void   select_bkg ();
   void   select_clr ();
};
 
#endif // INCLUDED_QBtColorDemo_h

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
#include "QBtColorDemo.h"
#include <QColor>
#include <QColorDialog>

/*------- constants:
-------------------------------------------------------------------*/
const int         QBtColorDemo::HEIGHT = 14;
const char* const QBtColorDemo::TEXT   = QT_TR_NOOP( "Text example" );

//*******************************************************************
// QBtColorDemo                                          CONSTRUCTOR
//*******************************************************************
QBtColorDemo::QBtColorDemo( const bool in_with_text, QWidget* const in_parent )
: QLineEdit( in_parent )
{
   if( in_with_text ) {
      setText( tr( TEXT ) );
      setAlignment( Qt::AlignHCenter );
   }
   else {
      setMinimumHeight( HEIGHT );
      setMaximumHeight( HEIGHT );
   }
  
   setReadOnly( true );
   setFocusPolicy( Qt::NoFocus );
}
// end of QBtColorDemo

//*******************************************************************
// background                                                 PUBLIC
//*******************************************************************
void QBtColorDemo::background( const QColor& in_color )
{
   QPalette p = palette();
   p.setColor( backgroundRole(), in_color );
   setPalette( p );
}
//-----------------------------------------------
QColor QBtColorDemo::background() const
{
   return palette().color( backgroundRole() );
}
// end of background

//*******************************************************************
// color                                                      PUBLIC
//*******************************************************************
void QBtColorDemo::color( const QColor& in_color )
{
   QPalette p = palette();
   p.setColor( foregroundRole(), in_color );
   setPalette( p );
}
//-----------------------------------------------
QColor QBtColorDemo::color() const
{
   return palette().color( foregroundRole() );
}
// end of color

//*******************************************************************
// font                                                       PUBLIC
//*******************************************************************
void QBtColorDemo::fonts( const QFont& in_font )
{
   setFont( in_font );
}
//-----------------------------------------------
QFont QBtColorDemo::fonts() const
{
   return font();
}
// end of font

//###################################################################
//#                                                                 #
//#                           S L O T S                             #
//#                                                                 #
//###################################################################


//*******************************************************************
// select_bkg                                           PRIVATE slot
//*******************************************************************
void QBtColorDemo::select_bkg()
{
   const QColor current_color = background();
   const QColor new_color = QColorDialog::getColor( current_color, this );
   if( new_color.isValid() ) {
      if( new_color != current_color ) {
         background( new_color );
      }
   }
}
// end of select_bkg

//*******************************************************************
// select_clr                                           PRIVATE slot
//*******************************************************************
void QBtColorDemo::select_clr()
{
   const QColor current_color = color();
   const QColor new_color = QColorDialog::getColor( current_color, this );
   if( new_color.isValid() ) {
      if( new_color != current_color ) {
         color( new_color );
      }
   }
}
// end of select_clr

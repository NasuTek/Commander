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
#include "QBtButtonSpace.h"
#include "QBtEventsController.h"
#include "QBtSettings.h"
#include "QBtConfig.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QtDebug>

/*------- constants:
-------------------------------------------------------------------*/
const char* const QBtButtonSpace::LABEL[] = {
   QT_TR_NOOP( "Help"   ),
#if !_WIN32
   QT_TR_NOOP( "Access" ),
#else
   QT_TR_NOOP( "Attributes" ),
#endif
   QT_TR_NOOP( "View"   ),
   QT_TR_NOOP( "Edit"   ),
   QT_TR_NOOP( "Copy"   ),
   QT_TR_NOOP( "Rename" ),
   QT_TR_NOOP( "MkDir"  ),
   QT_TR_NOOP( "Delete" ),
   QT_TR_NOOP( "Pack"   ),
   QT_TR_NOOP( "Quit"   )
};

//*******************************************************************
// QBtButtonSpace                                        CONSTRUCTOR
//*******************************************************************
QBtButtonSpace::QBtButtonSpace( QWidget* const in_parent ) : QWidget( in_parent )
{
   QSignalMapper* const mapper = new QSignalMapper( this );
   connect( mapper, SIGNAL( mapped( int ) ), this, SLOT( clicked( int ) ) );

   QHBoxLayout* const hbt = new QHBoxLayout( this );
   hbt->setMargin( 0 );

   for( qint32 i = F1; i < BUTTONS_COUNT; ++i ) {
      button_[ i ] = new QPushButton;
      button_[ i ]->setFocusPolicy( Qt::NoFocus );
      hbt->addWidget( button_[ i ] );
      connect( button_[ i ], SIGNAL( clicked() ), mapper, SLOT( map() ) );
      mapper->setMapping( button_[ i ], i );
   }
}
// end of QBtButtonSpace

//*******************************************************************
// retranslate                                                PUBLIC
//*******************************************************************
void QBtButtonSpace::retranslate()
{
   QBtConfig* const cfg = QBtConfig::instance();
   const int   mode = cfg->btn_mode();;
   const QFont font = cfg->btn_font();
   
   for( qint32 i = F1; i < BUTTONS_COUNT;  ++i ) {
      const QString number = QString::number( i + 1 );
      const QString label  = tr( LABEL[ i ] );
      QString text = "";

      switch( mode ) {
         case ONLY_FN:
            text = "F" + number;
            break;
         case ONLY_TEXT:
            text = label;
            break;
         case FULL_DESC:
            text  = "F";
            text += number;
            text += ' ';
            text += label;
            break;
         case TWO_LINES:
            text  = "F";
            text += number;
            text += '\n';
            text += label;
         break;
      }
      button_[ i ]->setFont( font );
      button_[ i ]->setText( text );
   }
}
// end of retranslate

//*******************************************************************
// clicked                                              PRIVATE slot
//*******************************************************************
void QBtButtonSpace::clicked( const int in_idx )
{
   if( ( in_idx >= F1 ) && ( in_idx <= F10 ) ) {
      QBtEventsController::instance()->send_event( QBtEvent::F1_KEY + in_idx );
   }
}
// end of clicked

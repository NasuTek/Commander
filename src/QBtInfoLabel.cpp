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

 /*------- include files:
 ------------------------------------------------------------------*/
 #include "QBtInfoLabel.h"
 #include "QBtShared.h"
 #include <QPaintEvent>
 #include <QPainter>
 #include <QFileInfo>

/*------- constants:
-------------------------------------------------------------------*/
const QString QBtInfoLabel::Spacer = "/.../";
const QString QBtInfoLabel::Slash  = "/";

//*******************************************************************
// QBtInfoLabel                                          CONSTRUCTOR
//*******************************************************************
QBtInfoLabel::QBtInfoLabel( QWidget* in_parent )
: QLabel( in_parent )
{
   //setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Preferred );
}
// end of QBtInfoLabel

//*******************************************************************
// setText                                                    PUBLIC
//*******************************************************************
void QBtInfoLabel::setText( const QString& in_text )
{
   const QFontMetrics fm( font() );
   QFileInfo fi( in_text );
   setMinimumWidth( fm.width( Spacer + fi.fileName() ) );
   QLabel::setText( in_text );
}
// end of setText

//*******************************************************************
// paintEvent                                      PRIVATE inherited
//*******************************************************************
void QBtInfoLabel::paintEvent( QPaintEvent* const in_event )
{
   Q_UNUSED( in_event )

   QPainter p( this );
   p.drawText( rect(), Qt::TextSingleLine, elide( contentsRect().width() ) );
   p.end();
}
// end of paintEvent

//*******************************************************************
// elide
//*******************************************************************
QString QBtInfoLabel::elide( const int in_width ) const
{
   const QFontMetrics fm( font() );
   
   QString buffer = text();
   if( fm.width( buffer ) <= in_width ) return buffer;

   const QStringList words    = buffer.split( Slash, QString::SkipEmptyParts );
         int         i        = 0;
         int         j        = words.count() - 1;
         QString     lft_part = QString();
         QString     rgt_part = words[j--];
         bool        lft_ok   = true;
         bool        rgt_ok   = true;

   while( lft_ok || rgt_ok ) {
      lft_ok = false;
      if( i < j ) {
         const QString tmp = lft_part + Slash + words[i];
         if( fm.width( tmp + Spacer + rgt_part ) < in_width ) {
            lft_part = tmp;
            lft_ok = true;
            ++i;
         }
      }
      //.............................................
      rgt_ok = false;
      if( i < j ) {
         const QString tmp = words[j] + Slash + rgt_part;
         if( fm.width( lft_part + Spacer + tmp ) < in_width ) {
            rgt_part = tmp;
            rgt_ok = true;
            --j;
         }
      }
      
   }
   return ( lft_part + Spacer + rgt_part );
}
// end of elide

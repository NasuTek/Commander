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

#ifndef INCLUDED_QBtConfigButtons_h
#define INCLUDED_QBtConfigButtons_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QWidget>
#include <QFont>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QRadioButton;
class QPushButton;
class QLabel;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtConfigButtons : public QWidget
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtConfigButtons( QWidget* = 0 );
private:
   QBtConfigButtons( const QBtConfigButtons& );
   QBtConfigButtons& operator=( const QBtConfigButtons& );

//******* CONSTANTS ********
private:
   static const char* const CAPTION_MODE;
   static const char* const CAPTION_FONT;
   static const char* const CAPTION_EXAMPLE;
   static const char* const CAPTION_FONTS;
   static const char* const ONLY_FN;
   static const char* const ONLY_TEXT;
   static const char* const FULL_DESC;
   static const char* const TWO_LINES;
   static const char* const DEFAULT_FONT;
   static const char* const CUSTOM_FONT;
   static const char* const EXAMPLE;
   static const char* const SELECT_FONT;
   static const char* const FONT_ICON;

//******* MEMBERS *******
private:
   QRadioButton* const only_fn_;
   QRadioButton* const only_text_;
   QRadioButton* const full_desc_;
   QRadioButton* const two_lines_;
   QRadioButton* const default_font_;
   QRadioButton* const custom_font_;
   QPushButton*  const select_font_;
   QPushButton*  const example_;
   QLabel*       const font_desc_;
   QFont               font_;
   qint32              mode_;
   

//******* METHODS *******
public:
   void save           () const;
private:
   void restore        ();
   void update_example ();
   void update_state   ();
private slots:
   void only_fn        ( bool );
   void only_text      ( bool );
   void full_desc      ( bool );
   void two_lines      ( bool );
   void default_font   ( bool );
   void custom_font    ( bool );
   void select_font    ();
};

#endif // INCLUDED_QBtConfigButtons_h

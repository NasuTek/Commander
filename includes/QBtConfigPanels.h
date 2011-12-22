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

#ifndef INCLUDED_QBtConfigPanels_h
#define INCLUDED_QBtConfigPanels_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QWidget>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QPushButton;
class QLabel;
class QBtColorDemo;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtConfigPanels : public QWidget
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtConfigPanels( QWidget* = 0 );
private:
   QBtConfigPanels( const QBtConfigPanels& );
   QBtConfigPanels& operator=( const QBtConfigPanels& );

//******* CONSTANTS ********
private:
   static const char* const EXAMPLE;
   static const char* const FONT;
   static const char* const BACKGROUND;
   static const char* const FOREGROUND;
   static const char* const DEFAULT;
   static const char* const WIDTH_FOCUS;
   static const char* const WIDTHOUT_FOCUS;
   static const char* const NC_NS;
   static const char* const NC_S;
   static const char* const C_NS;
   static const char* const C_S;
   static const char* const ICO_FONT;
   static const char* const ICO_COLOR;
      
//******* MEMBERS *******
private:
   QPushButton  * const font_;
   QLabel       * const font_example_;
   QBtColorDemo * const f_nc_ns_demo_;
   QPushButton  * const f_nc_ns_def_;
   QPushButton  * const f_nc_ns_bkg_;
   QPushButton  * const f_nc_ns_txt_;
   QBtColorDemo * const f_nc_s_demo_;
   QPushButton  * const f_nc_s_def_;
   QPushButton  * const f_nc_s_bkg_;
   QPushButton  * const f_nc_s_txt_;
   QBtColorDemo * const f_c_ns_demo_;
   QPushButton  * const f_c_ns_def_;
   QPushButton  * const f_c_ns_bkg_;
   QPushButton  * const f_c_ns_txt_;
   QBtColorDemo * const f_c_s_demo_;
   QPushButton  * const f_c_s_def_;
   QPushButton  * const f_c_s_bkg_;
   QPushButton  * const f_c_s_txt_;
   QBtColorDemo * const nf_nc_ns_demo_;
   QPushButton  * const nf_nc_ns_def_;
   QPushButton  * const nf_nc_ns_bkg_;
   QPushButton  * const nf_nc_ns_txt_;
   QBtColorDemo * const nf_nc_s_demo_;
   QPushButton  * const nf_nc_s_def_;
   QPushButton  * const nf_nc_s_bkg_;
   QPushButton  * const nf_nc_s_txt_;
   QBtColorDemo * const nf_c_ns_demo_;
   QPushButton  * const nf_c_ns_def_;
   QPushButton  * const nf_c_ns_bkg_;
   QPushButton  * const nf_c_ns_txt_;
   QBtColorDemo * const nf_c_s_demo_;
   QPushButton  * const nf_c_s_def_;
   QPushButton  * const nf_c_s_bkg_;
   QPushButton  * const nf_c_s_txt_;
   
//******* METHODS *******
private:
   void init() const;
public:
   void save() const;
private slots:
   void select_font ();
   //...................
   void f_nc_ns_def ();
   void f_nc_s_def  ();
   void f_c_ns_def  ();
   void f_c_s_def   ();
   //..................
   void nf_nc_ns_def();
   void nf_nc_s_def ();
   void nf_c_ns_def ();
   void nf_c_s_def  ();
};

#endif // INCLUDED_QBtConfigPanels_h

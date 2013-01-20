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

#ifndef INCLUDED_QBtConfig_h
#define INCLUDED_QBtConfig_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>
#include <QFont>
#include <QColor>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtConfig : public QObject
{
   Q_OBJECT
   
// ******* CONSTRUCTION / DESTRUCTION *******
private:
   QBtConfig();
   QBtConfig( const QBtConfig& );
   QBtConfig& operator=( const QBtConfig& );
public:
   ~QBtConfig();

// ******* CONSTANTS *******
public:
   static const QString MAIN_WINDOW_GROUP;
   static const QString POS_KEY;
   static const QString SIZE_KEY;
   static const QString STATE_KEY;
   static const QString BTN_MODE_KEY;
   static const QString BTN_FONT_KEY;
   static const QString WORKSPACE_GROUP;
   static const QString SPLITTER_KEY;
   static const QString LEFT_PANEL_GROUP;
   static const QString RIGHT_PANEL_GROUP;
   static const QString CURR_LEFT_DIR_KEY;
   static const QString CURR_RIGHT_DIR_KEY;
   static const QString SELECTED_LEFT_KEY;
   static const QString SELECTED_RIGHT_KEY;
   static const QString FOLDERS_LEFT_KEY;
   static const QString FOLDERS_RIGHT_KEY;
   static const QString TERMINAL_GROUP;
   static const QString DIFF_GROUP;
   static const QString USE_DEFAULT_KEY;
   static const QString COMMAND_KEY;
   static const QString EXT_GROUP;
   static const QString EXT_KEY;
   //----------------------------------
   static const QString VIEW_GROUP;
   static const QString FONT_KEY;
   static const QString BKG_F_NC_NS_COLOR_KEY;
   static const QString TXT_F_NC_NS_COLOR_KEY;
   static const QString BKG_NF_NC_NS_COLOR_KEY;
   static const QString TXT_NF_NC_NS_COLOR_KEY;
   static const QString BKG_F_NC_S_COLOR_KEY;
   static const QString TXT_F_NC_S_COLOR_KEY;
   static const QString BKG_NF_NC_S_COLOR_KEY;
   static const QString TXT_NF_NC_S_COLOR_KEY;
   static const QString BKG_F_C_S_COLOR_KEY;
   static const QString TXT_F_C_S_COLOR_KEY;
   static const QString BKG_NF_C_S_COLOR_KEY;
   static const QString TXT_NF_C_S_COLOR_KEY;
   static const QString BKG_F_C_NS_COLOR_KEY;
   static const QString TXT_F_C_NS_COLOR_KEY;
   static const QString BKG_NF_C_NS_COLOR_KEY;
   static const QString TXT_NF_C_NS_COLOR_KEY;
private:
   static const QString FILTER_KEY;

   static const bool    DEFAULT_FILTER_STATE;
   static const QColor  DEFAULT_BKG_F_NC_NS_COLOR;
   static const QColor  DEFAULT_TXT_F_NC_NS_COLOR;
   static const QColor  DEFAULT_BKG_NF_NC_NS_COLOR;
   static const QColor  DEFAULT_TXT_NF_NC_NS_COLOR;
   static const QColor  DEFAULT_BKG_F_NC_S_COLOR;
   static const QColor  DEFAULT_TXT_F_NC_S_COLOR;
   static const QColor  DEFAULT_BKG_NF_NC_S_COLOR;
   static const QColor  DEFAULT_TXT_NF_NC_S_COLOR;
   static const QColor  DEFAULT_BKG_F_C_S_COLOR;
   static const QColor  DEFAULT_TXT_F_C_S_COLOR;
   static const QColor  DEFAULT_BKG_NF_C_S_COLOR;
   static const QColor  DEFAULT_TXT_NF_C_S_COLOR;
   static const QColor  DEFAULT_BKG_F_C_NS_COLOR;
   static const QColor  DEFAULT_TXT_F_C_NS_COLOR;
   static const QColor  DEFAULT_BKG_NF_C_NS_COLOR;
   static const QColor  DEFAULT_TXT_NF_C_NS_COLOR;

   
// ******* MEMBERS *******
private:
   bool   filter_;
   int    btn_mode_;
   QFont  btn_font_;
      
   QFont  font_;
   QColor bkg_f_nc_ns_color_;
   QColor txt_f_nc_ns_color_;
   QColor bkg_nf_nc_ns_color_;
   QColor txt_nf_nc_ns_color_;
   QColor bkg_f_nc_s_color_;
   QColor txt_f_nc_s_color_;
   QColor bkg_nf_nc_s_color_;
   QColor txt_nf_nc_s_color_;
   QColor bkg_f_c_s_color_;
   QColor txt_f_c_s_color_;
   QColor bkg_nf_c_s_color_;
   QColor txt_nf_c_s_color_;
   QColor bkg_f_c_ns_color_;
   QColor txt_f_c_ns_color_;
   QColor bkg_nf_c_ns_color_;
   QColor txt_nf_c_ns_color_;
   

// ******* METHODS *******
public:
   static QBtConfig* const instance();
   void save_data() const;
   
   // filter state
   void filter( const bool in_state ) { filter_ = in_state; }
   bool filter() const { return filter_; }
   // btn mode
   void btn_mode( const int in_mode ) { btn_mode_ = in_mode; }
   int  btn_mode() const { return btn_mode_; }
   // btn font
   void btn_font( const QFont& in_font ) { btn_font_ = in_font; }
   const QFont& btn_font() const { return btn_font_; }

   // font
   void font( const QFont& in_font ) { font_ = in_font; }
   const QFont& font() const { return font_; }   
   // bkg f nc ns color
   void bkg_f_nc_ns_color( const QColor& in_color ) { bkg_f_nc_ns_color_ = in_color; }
   const QColor& bkg_f_nc_ns_color() const { return bkg_f_nc_ns_color_; }
   const QColor& bkg_f_nc_ns_def_color() const { return DEFAULT_BKG_F_NC_NS_COLOR; }
   // txt f nc ns color
   void txt_f_nc_ns_color( const QColor& in_color ) { txt_f_nc_ns_color_ = in_color; }
   const QColor& txt_f_nc_ns_color() const { return txt_f_nc_ns_color_; }
   const QColor& txt_f_nc_ns_def_color() const { return DEFAULT_TXT_F_NC_NS_COLOR; }
   // bkg nf nc ns color
   void bkg_nf_nc_ns_color( const QColor& in_color ) { bkg_nf_nc_ns_color_ = in_color; }
   const QColor& bkg_nf_nc_ns_color() const { return bkg_nf_nc_ns_color_; }
   const QColor& bkg_nf_nc_ns_def_color() const { return DEFAULT_BKG_NF_NC_NS_COLOR; }
   // txt f nc ns color
   void txt_nf_nc_ns_color( const QColor& in_color ) { txt_nf_nc_ns_color_ = in_color; }
   const QColor& txt_nf_nc_ns_color() const { return txt_nf_nc_ns_color_; }
   const QColor& txt_nf_nc_ns_def_color() const { return DEFAULT_TXT_NF_NC_NS_COLOR; }
   // bkg f nc s color
   void bkg_f_nc_s_color( const QColor& in_color ) { bkg_f_nc_s_color_ = in_color; }
   const QColor& bkg_f_nc_s_color() const { return bkg_f_nc_s_color_; }
   const QColor& bkg_f_nc_s_def_color() const { return DEFAULT_BKG_F_NC_S_COLOR; }
   // txt f nc s color
   void txt_f_nc_s_color( const QColor& in_color ) { txt_f_nc_s_color_ = in_color; }
   const QColor& txt_f_nc_s_color() const { return txt_f_nc_s_color_; }
   const QColor& txt_f_nc_s_def_color() const { return DEFAULT_TXT_F_NC_S_COLOR; }
   // bkg nf nc s color
   void bkg_nf_nc_s_color( const QColor& in_color ) { bkg_nf_nc_s_color_ = in_color; }
   const QColor& bkg_nf_nc_s_color() const { return bkg_nf_nc_s_color_; }
   const QColor& bkg_nf_nc_s_def_color() const { return DEFAULT_BKG_NF_NC_S_COLOR; }
   // txt nf nc s color
   void txt_nf_nc_s_color( const QColor& in_color ) { txt_nf_nc_s_color_ = in_color; }
   const QColor& txt_nf_nc_s_color() const { return txt_nf_nc_s_color_; }
   const QColor& txt_nf_nc_s_def_color() const { return DEFAULT_TXT_NF_NC_S_COLOR; }
   // bkg f c s color
   void bkg_f_c_s_color( const QColor& in_color ) { bkg_f_c_s_color_ = in_color; }
   const QColor& bkg_f_c_s_color() const { return bkg_f_c_s_color_; }
   const QColor& bkg_f_c_s_def_color() const { return DEFAULT_BKG_F_C_S_COLOR; }
   // txt f c s color
   void txt_f_c_s_color( const QColor& in_color ) { txt_f_c_s_color_ = in_color; }
   const QColor& txt_f_c_s_color() const { return txt_f_c_s_color_; }
   const QColor& txt_f_c_s_def_color() const { return DEFAULT_TXT_F_C_S_COLOR; }
   // bkg nf c s color
   void bkg_nf_c_s_color( const QColor& in_color ) { bkg_nf_c_s_color_ = in_color; }
   const QColor& bkg_nf_c_s_color() const { return bkg_nf_c_s_color_; }
   const QColor& bkg_nf_c_s_def_color() const { return DEFAULT_BKG_NF_C_S_COLOR; }
   // txt nf c s color
   void txt_nf_c_s_color( const QColor& in_color ) { txt_nf_c_s_color_ = in_color; }
   const QColor& txt_nf_c_s_color() const { return txt_nf_c_s_color_; }
   const QColor& txt_nf_c_s_def_color() const { return DEFAULT_TXT_NF_C_S_COLOR; }
   // bkg f c ns color
   void bkg_f_c_ns_color( const QColor& in_color ) { bkg_f_c_ns_color_ = in_color; }
   const QColor& bkg_f_c_ns_color() const { return bkg_f_c_ns_color_; }
   const QColor& bkg_f_c_ns_def_color() const { return DEFAULT_BKG_F_C_NS_COLOR; }
   // txt f c ns color
   void txt_f_c_ns_color( const QColor& in_color ) { txt_f_c_ns_color_ = in_color; }
   const QColor& txt_f_c_ns_color() const { return txt_f_c_ns_color_; }
   const QColor& txt_f_c_ns_def_color() const { return DEFAULT_TXT_F_C_NS_COLOR; }
   // bkg nf c ns color
   void bkg_nf_c_ns_color( const QColor& in_color ) { bkg_nf_c_ns_color_ = in_color; }
   const QColor& bkg_nf_c_ns_color() const { return bkg_nf_c_ns_color_; }
   const QColor& bkg_nf_c_ns_def_color() const { return DEFAULT_BKG_NF_C_NS_COLOR; }
   // txt nf c ns color
   void txt_nf_c_ns_color( const QColor& in_color ) { txt_nf_c_ns_color_ = in_color; }
   const QColor& txt_nf_c_ns_color() const { return txt_nf_c_ns_color_; }
   const QColor& txt_nf_c_ns_def_color() const { return DEFAULT_TXT_NF_C_NS_COLOR; }
      
private:
   void read_data();
};

#endif // INCLUDED_QBtConfig_h

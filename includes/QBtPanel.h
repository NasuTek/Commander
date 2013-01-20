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

#ifndef INCLUDED_QBtPanel_h
#define INCLUDED_QBtPanel_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QWidget>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QBtTabBar;
class QStackedWidget;
class QLabel;
class QComboBox;
class QBtView;
class QPushButton;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtPanel : public QWidget
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtPanel( qint32, QWidget* = 0 );
   ~QBtPanel();
private:
   QBtPanel( const QBtPanel& );
   QBtPanel& operator=( const QBtPanel& );

//******* CONSTANTS *******
private:
   static const char* const DIRS;
   static const char* const FILES;
   static const char* const SELECTED;

//******* MEMBERS *******
private:
   qint32                idx_;
   QComboBox*      const path_;
   QComboBox*      const fstab_;
   QBtTabBar*      const tbar_;
   QStackedWidget* const wstack_;
   QLabel*         const dirs_;
   QLabel*         const files_;
   QLabel*         const selected_;
   QLabel*         const infolabel_;
   QPushButton*    const dotdot_;
   QPushButton*    const rootbutton_;

//******* METHODS *******
public:
   void           show_fstab            ();
   void           set_tab_id            ( qint32 );
   QBtView* const current_view          () const;
private:
   void           keyPressEvent         ( QKeyEvent* );
   void           customEvent           ( QEvent* );
   void           new_tab_request       ();
   void           del_tab_request       ();
   qint32         new_tab               ( const QString& );
   void           update_fstab          ();
   void           save                  ();
   void           restore               ();
private slots:
   void           tab_mouse_event       ();
   void           tab_bar_changed       ( int );
   void           current_path          ( const QString& );
   void           update_dirs_count     ( qint32 );
   void           update_files_count    ( qint32 );
   void           update_selected_count ( qint32 );
   void           path_changed          ( const QString& );
   void           fstab_changed         ( const QString& );
   void           edit_finished         ();
};

#endif // INCLUDED_QBtPanel_h

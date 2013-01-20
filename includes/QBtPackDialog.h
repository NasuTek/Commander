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

#ifndef INCLUDED_QBtPackDialog_h
#define INCLUDED_QBtPackDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QDialog>
#include <QFontMetrics>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QLabel;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QPushButton;
class QRadioButton;
class QBtInfoField;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtPackDialog : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtPackDialog( QWidget* = 0 );
private:
   QBtPackDialog( const QBtPackDialog& );
   QBtPackDialog& operator=( const QBtPackDialog& );

//******* CONSTANTS ********
private:
   enum {
      USE_TAR = 0,
      USE_GZIP,
      USE_BZIP2,
      USE_ZIP
   };
   static const char* const CAPTION;
   static const char* const SRC_AND_DST;
   static const char* const SOURCE;
   static const char* const DESTINATION;
   static const char* const TOOL;
   static const char* const COMPRESSION;
   static const char* const REMOVE;
   static const char* const RUN;
   static const char* const CANCEL;
   static const char* const GZIP;
   static const char* const BZIP2;
   static const char* const ZIP;
   static const QString     TAR_EXT;
   static const QString     GZIP_EXT;
   static const QString     BZIP2_EXT;
   static const QString     ZIP_EXT;

//******* MEMBERS *******
private:
   QString             name_;
   QString             dst_dir_;
   QString             dst_path_;
   QBtInfoField* const source_;
   QBtInfoField* const destination_;
   QCheckBox*    const compression_;
   QCheckBox*    const remove_;
   QComboBox*    const ratio_;
   QPushButton*  const run_;
   QPushButton*  const cancel_;
   QGroupBox*    const tool_gbox_;
   QRadioButton* const gzip_;
   QRadioButton* const bzip2_;
   QRadioButton* const zip_;
   bool                started_;
   bool                break_;
   qint32              compress_type_;
   QFontMetrics        fm_;
   SelectionsSet       data_;

//******* METHODS *******
private:
   void showEvent      ( QShowEvent* );
public:
   void           set_source     ( const SelectionsSet& );
   void           set_destination( const QString&, const QString& );
   const QString& get_dst_path   () const;
   void           remove_ext     ();
   void           display_src    ( const QString& );
   void           display_dst    ();
   QString        path2display   ();
   void           run_tar        ();
   void           run_zip        ();
private slots:
   void reject            ();
   void compression       ( bool );
   void type_changed      ();
   void run               ();
};

#endif // INCLUDED_QBtPackDialog_h

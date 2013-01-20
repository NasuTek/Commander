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

#ifndef INCLUDED_QBtCopyDialog_h
#define INCLUDED_QBtCopyDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include "BtTypes.h"
#include <QDialog>
#include <QFontMetrics>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QProgressBar;
class QCheckBox;
class QPushButton;
class QBtInfoField;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtCopyDialog : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtCopyDialog( QWidget* = 0 );
private:
   QBtCopyDialog( const QBtCopyDialog& );
   QBtCopyDialog& operator=( const QBtCopyDialog& );

//******* CONSTANTS *******
private:
   static const char* const SRC_DST_CAPTION;
   static const char* const PROGRESS_CAPTION;
   static const char* const REMOVE;
   static const char* const OWNER;
   static const char* const PERMISSIONS;
   static const char* const DATIME;
   static const char* const START;
   static const char* const EXIT;
   static const char* const BREAK;
   static const char* const SRC_LABEL;
   static const char* const DST_LABEL;
   static const char* const RENAME;
   static const char* const NEW_FILE_NAME;
protected:
   static const char* const DIR_NOT_WRITABLE;
   static const char* const DIR_NOT_READABLE;
   static const char* const FILE_NOT_READABLE;
   static const char* const OPEN_READ_ERROR;
   static const char* const OPEN_WRITE_ERROR;
   static const char* const MKDIR_ERROR;
   static const char* const CANT_DEL_FILE;
   static const char* const CANT_DEL_DIR;
   

//******* MEMBERS *******
private:
   QFontMetrics  const font_metrics_;
   QBtInfoField* const src_path_;
   QBtInfoField* const dst_path_;
   QProgressBar* const progress_;
   QCheckBox*    const remove_;
   QCheckBox*    const owner_;
   QCheckBox*    const permissions_;
   QCheckBox*    const datime_;
   QPushButton*  const start_;
   QPushButton*  const exit_;
   bool                started_;
protected:
   bool                break_;
   bool                ask_again_;
   SelectionsSet       sources_;
   QString             destpath_;

//******* METHODS *******
public:
   void set_source     ( const SelectionsSet& );
   void set_destination( const QString& );
private:
   void showEvent      ( QShowEvent* );
protected:
   virtual void copy_file  ( const QString&, const QString& ) = 0;
   virtual void copy_dir   ( const QString&, const QString& ) = 0;
   virtual bool can_update ( const QString&, const QString& ) const = 0;

   void rename         ( QString& );   
   void started        ();
   void finished       ();
   void display_paths  ( const QString&, const QString& );
   bool do_remove      () const;
   bool do_owner       () const;
   bool do_permissions () const;
   bool do_datime      () const;
   bool can_copy       ( const QString&, QString& );
   void reset_progress ( qint32 = 0 );
   void set_progress   ( qint32 );

private slots:
   virtual void start  () = 0;
   void reject         ();
};

#endif // INCLUDED_QBtCopyDialog_h

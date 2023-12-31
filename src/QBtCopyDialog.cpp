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
-------------------------------------------------------------------*/
#include "QBtCopyDialog.h"
#include "QBtCanOverwrite.h"
#include "QBtInfoField.h"
#include "QBtShared.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QProgressBar>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QFileInfo>
#include <QProcess>
#include <QtDebug>

/*------- constants:
-------------------------------------------------------------------*/
const char* const QBtCopyDialog::SRC_DST_CAPTION  = QT_TR_NOOP( "Source and destination" );
const char* const QBtCopyDialog::PROGRESS_CAPTION = QT_TR_NOOP( "Progress" );
const char* const QBtCopyDialog::REMOVE           = QT_TR_NOOP( "&remove source file(s)" );
const char* const QBtCopyDialog::OWNER            = QT_TR_NOOP( "preserve &owner/group" );
const char* const QBtCopyDialog::PERMISSIONS      = QT_TR_NOOP( "preserve &permissions" );
const char* const QBtCopyDialog::DATIME           = QT_TR_NOOP( "preserve &date/time" );
const char* const QBtCopyDialog::START            = QT_TR_NOOP( "&Start" );
const char* const QBtCopyDialog::EXIT             = QT_TR_NOOP( "&Exit" );
const char* const QBtCopyDialog::BREAK            = QT_TR_NOOP( "&Break" );
const char* const QBtCopyDialog::SRC_LABEL        = QT_TR_NOOP( "Source:" );
const char* const QBtCopyDialog::DST_LABEL        = QT_TR_NOOP( "Destination:" );
const char* const QBtCopyDialog::DIR_NOT_WRITABLE = QT_TR_NOOP( "You can't wite to this directory (%1).\nCheck permission access." );
const char* const QBtCopyDialog::DIR_NOT_READABLE = QT_TR_NOOP( "You can't read from this directory: %1.\nCheck permission access." );
const char* const QBtCopyDialog::FILE_NOT_READABLE= QT_TR_NOOP( "You can't read from this file (%1).\nCheck permission access." );
const char* const QBtCopyDialog::OPEN_READ_ERROR  = QT_TR_NOOP( "Can't open the file for reading:\n%1" );
const char* const QBtCopyDialog::OPEN_WRITE_ERROR = QT_TR_NOOP( "Can't open the file for writing:\n%1" );
const char* const QBtCopyDialog::RENAME           = QT_TR_NOOP( "Rename" );
const char* const QBtCopyDialog::NEW_FILE_NAME    = QT_TR_NOOP( "New file name:" );
const char* const QBtCopyDialog::MKDIR_ERROR      = QT_TR_NOOP( "Can't create the directory: %1" );
const char* const QBtCopyDialog::CANT_DEL_FILE    = QT_TR_NOOP( "Can't remove a file:\n%1" );
const char* const QBtCopyDialog::CANT_DEL_DIR     = QT_TR_NOOP( "Can't remove a directory:\n%1" );


//*******************************************************************
// QBtCopyDialog                                         CONSTRUCTOR
//*******************************************************************
QBtCopyDialog::QBtCopyDialog( QWidget* const in_parent ) : QDialog( in_parent )
, font_metrics_ ( font() )
, src_path_     ( new QBtInfoField )
, dst_path_     ( new QBtInfoField )
, progress_     ( new QProgressBar )
, remove_       ( new QCheckBox( tr( REMOVE      ) ) )
, owner_        ( new QCheckBox( tr( OWNER       ) ) )
, permissions_  ( new QCheckBox( tr( PERMISSIONS ) ) )
, datime_       ( new QCheckBox( tr( DATIME      ) ) )
, start_        ( new QPushButton( tr( START     ) ) )
, exit_         ( new QPushButton( tr( EXIT      ) ) )
, started_      ( false )
, break_        ( false )
, ask_again_    ( true )
, sources_      ( SelectionsSet() )
, destpath_     ( QString() )
{
   reset_progress( 1000 );
   
   QGroupBox* const src_dst_gbox = new QGroupBox( tr( SRC_DST_CAPTION ) );
   QGridLayout* const grid = new QGridLayout( src_dst_gbox );
   QLabel* const src_label = new QLabel( tr( SRC_LABEL ) );
   QLabel* const dst_label = new QLabel( tr( DST_LABEL ) );
   src_label->setBuddy( src_path_ );
   dst_label->setBuddy( dst_path_ );
   grid->addWidget( src_label, 0, 0, 1, 1, Qt::AlignRight );
   grid->addWidget( src_path_, 0, 1 );
   grid->addWidget( dst_label, 1, 0, 1, 1, Qt::AlignRight );
   grid->addWidget( dst_path_, 1, 1 );

   // Progress
   QGroupBox* const progress_gbox = new QGroupBox( tr( PROGRESS_CAPTION ) );
   QHBoxLayout* const progress_layout = new QHBoxLayout( progress_gbox );
   progress_->setAlignment( Qt::AlignHCenter );
   progress_layout->addWidget( progress_ );
   
   // Przyciski
   QVBoxLayout* const chk_layout = new QVBoxLayout;
   chk_layout->addWidget( remove_ );
   chk_layout->addWidget( datime_ );
   chk_layout->addWidget( owner_ );
   chk_layout->addWidget( permissions_ );
   chk_layout->addStretch( 100 );
   QVBoxLayout* const btn_layout = new QVBoxLayout;
   btn_layout->addWidget( exit_ );
   btn_layout->addWidget( start_ );
   btn_layout->addStretch( 100 );
   QHBoxLayout* const in_layout = new QHBoxLayout;
   in_layout->addLayout( chk_layout );
   in_layout->addStretch( 100 );
   in_layout->addLayout( btn_layout );

   // Main layout
   QVBoxLayout* const main_layout = new QVBoxLayout;
   main_layout->addWidget( src_dst_gbox );
   main_layout->addWidget( progress_gbox );
   main_layout->addLayout( in_layout );
   setLayout( main_layout );

   connect( exit_ , SIGNAL( clicked() ), this, SLOT( reject() ) );
   connect( start_, SIGNAL( clicked() ), this, SLOT( start () ) );
}
// end of QBtCopyDialog

//*******************************************************************
// showEvent                                       PRIVATE inherited
//*******************************************************************
void QBtCopyDialog::showEvent( QShowEvent* const in_event )
{
   {
      QPalette p = QPalette();
      p.setColor( src_path_->backgroundRole(), palette().color( backgroundRole() ) );
      p.setColor( src_path_->foregroundRole(), palette().color( foregroundRole() ) );
      src_path_->setPalette( p );
   }
   {
      QPalette p = QPalette();
      p.setColor( dst_path_->backgroundRole(), palette().color( backgroundRole() ) );
      p.setColor( dst_path_->foregroundRole(), palette().color( foregroundRole() ) );
      dst_path_->setPalette( p );
   }
   
   QBtShared::resize_width( this, 40 );
   start_->setDefault( true );
   QDialog::showEvent( in_event );
}
// end of showEvent

//*******************************************************************
// started                                                 PROTECTED
//*******************************************************************
void QBtCopyDialog::started()
{
   remove_->setEnabled( false );
   owner_->setEnabled( false );
   permissions_->setEnabled( false );
   datime_->setEnabled( false );
   start_->setVisible( false );
   exit_->setText( tr( BREAK ) );
   started_ = true;
}
// end of started

//*******************************************************************
// finished                                                PROTECTED
//*******************************************************************
void QBtCopyDialog::finished()
{
   QDialog::accept();
}
// end of finished

//*******************************************************************
// reject                                          PRIVATE inherited
//*******************************************************************
void QBtCopyDialog::reject()
{
   if( !started_ ) QDialog::reject();
   break_ = true;
}
// end of reject

//*******************************************************************
// set_source                                                 PUBLIC
//*******************************************************************
void QBtCopyDialog::set_source( const SelectionsSet& in_data )
{
   sources_ = in_data;
}
// end of set_sources

//*******************************************************************
// set_destination                                            PUBLIC
//*******************************************************************
void QBtCopyDialog::set_destination( const QString& in_data )
{
   destpath_ = in_data;
}
// end of set_destination

//*******************************************************************
// display_info                                            PROTECTED
//*******************************************************************
void QBtCopyDialog::display_paths( const QString& in_src_path, const QString& in_dst_path )
{
   const qint32 MAXLEN = src_path_->width();

   QString src_path = in_src_path;
   if( font_metrics_.width( src_path ) > MAXLEN ) {
      QBtShared::elide( font_metrics_, MAXLEN, src_path );
   }
   src_path_->setText( src_path );
   
   QString dst_path = in_dst_path;
   if( font_metrics_.width( dst_path ) > MAXLEN ) {
      QBtShared::elide( font_metrics_, MAXLEN, dst_path );
   }
   dst_path_->setText( dst_path );

   QBtShared::idle();
}
// end of display_info

//*******************************************************************
// do_remove                                               PROTECTED
//*******************************************************************
bool QBtCopyDialog::do_remove() const
{
   return remove_->isChecked();
}
// end of do_remove

//*******************************************************************
// do_owner                                                PROTECTED
//*******************************************************************
bool QBtCopyDialog::do_owner() const
{
   return owner_->isChecked();
}
// end of do_owner

//*******************************************************************
// do_permissions                                          PROTECTED
//*******************************************************************
bool QBtCopyDialog::do_permissions() const
{
   return permissions_->isChecked();
}
// end of do_permissions

//*******************************************************************
// do_datime                                               PROTECTED
//*******************************************************************
bool QBtCopyDialog::do_datime() const
{
   return datime_->isChecked();
}
// end of do_datime

//*******************************************************************
// can_copy                                                PROTECTED
//*******************************************************************
bool QBtCopyDialog::can_copy( const QString& in_src_path, QString& in_dst_path )
{
   bool retval = true;
   static qint32 answer = QBtCanOverwrite::OVERWRITE_FILE;
   
    if( ask_again_ ) {
        if( QFile::exists( in_dst_path ) ) {
            QBtCanOverwrite dialog( this, in_dst_path );
            answer = dialog.exec();
            if( answer != QBtCanOverwrite::RENAME_FILE ) {
               ask_again_ = dialog.ask_again();
            }
        }
    }

    switch( answer ) {
        case QBtCanOverwrite::RENAME_FILE:
            rename( in_dst_path );
            break;
        case QBtCanOverwrite::OVERWRITE_FILE:
            break;
        case QBtCanOverwrite::CANCEL_FILE:
            retval = false;
            break_ = true;
      case QBtCanOverwrite::SKIP_FILE:
            retval = false;
            break;
        case QBtCanOverwrite::UPDATE_FILE:
            retval = can_update( in_src_path, in_dst_path );
            break;
    }
    return retval;
}
// end of can_copy

//*******************************************************************
// rename                                                    PRIVATE
//*******************************************************************
void QBtCopyDialog::rename( QString& inout_fpath )
{
    QString fpath = inout_fpath;
    QBtShared::auto_rename( fpath );
   
    const QFileInfo fi( fpath );
    const QString fname = fi.fileName();

    bool ok;
    const QString new_fname = QInputDialog::getText( this, tr( RENAME ), tr( NEW_FILE_NAME ), QLineEdit::Normal, fname, &ok );
    if( ok && !new_fname.isEmpty() ) {
        QString fpath = fi.path();
        if( !fpath.endsWith( '/' )) fpath += '/';
        inout_fpath = fpath + new_fname;
    }
}
// end of rename

//*******************************************************************
// reset_progress                                          PROTECTED
//*******************************************************************
void QBtCopyDialog:: reset_progress( const qint32 in_maximum )
{
   progress_->setRange( 0, in_maximum );
   progress_->setValue( 0 );
}
// end of reset_progress

//*******************************************************************
// set_progress                                            PROTECTED
//*******************************************************************
void QBtCopyDialog::set_progress( const qint32 in_value )
{
   progress_->setValue( in_value );
}
// end of set_progress

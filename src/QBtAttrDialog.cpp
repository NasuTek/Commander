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
#include "QBtAttrDialog.h"
#include "QBtSystemCall.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>
#include <QProcess>
#include <QtDebug>

#if _WIN32
#include <windows.h>
#endif

/*------- constants:
-------------------------------------------------------------------*/
#if !_WIN32
const char* const QBtAttrDialog::CAPTION   = QT_TR_NOOP( "Access permissions"  );
#else
const char* const QBtAttrDialog::CAPTION   = QT_TR_NOOP( "Attributes"  );
#endif
const char* const QBtAttrDialog::FILE_NAME = QT_TR_NOOP( "File name: "  );
const char* const QBtAttrDialog::RECURSIVE = QT_TR_NOOP( "&Recursive"  );
const char* const QBtAttrDialog::ACCEPT    = QT_TR_NOOP( "&Accept"  );
const char* const QBtAttrDialog::CLOSE     = QT_TR_NOOP( "&Close"  );
#if !_WIN32
const char* const QBtAttrDialog::USER      = QT_TR_NOOP( "User"  );
const char* const QBtAttrDialog::GROUP     = QT_TR_NOOP( "Group"  );
const char* const QBtAttrDialog::OTHER     = QT_TR_NOOP( "Other"  );
const char* const QBtAttrDialog::READ      = QT_TR_NOOP( "read"  );
const char* const QBtAttrDialog::WRITE     = QT_TR_NOOP( "write"  );
const char* const QBtAttrDialog::EXECUTE   = QT_TR_NOOP( "execute"  );
#else
const char* const QBtAttrDialog::READONLY     = QT_TR_NOOP( "read-only"  );
const char* const QBtAttrDialog::HIDDEN      = QT_TR_NOOP( "hidden"  );
const char* const QBtAttrDialog::ARCHIVE     = QT_TR_NOOP( "archive"  );
const char* const QBtAttrDialog::SYSTEM   = QT_TR_NOOP( "system"  );
#endif

//*******************************************************************
// QBtAttDialog                                          CONSTRUCTOR
//*******************************************************************
QBtAttrDialog::QBtAttrDialog( QWidget* in_parent, const SelectionsSet& in_data ) : QDialog( in_parent )
, data_       ( in_data                            )
, path_       ( new QLabel     ( *data_.begin()  ) )
, recursive_  ( new QCheckBox  ( tr( RECURSIVE ) ) )
  #if !_WIN32
, user_read_  ( new QCheckBox  ( tr( READ      ) ) )
, user_write_ ( new QCheckBox  ( tr( WRITE     ) ) )
, user_exec_  ( new QCheckBox  ( tr( EXECUTE   ) ) )
, group_read_ ( new QCheckBox  ( tr( READ      ) ) )
, group_write_( new QCheckBox  ( tr( WRITE     ) ) )
, group_exec_ ( new QCheckBox  ( tr( EXECUTE   ) ) )
, other_read_ ( new QCheckBox  ( tr( READ      ) ) )
, other_write_( new QCheckBox  ( tr( WRITE     ) ) )
, other_exec_ ( new QCheckBox  ( tr( EXECUTE   ) ) )
#else
  , readonly_   ( new QCheckBox  (tr(READONLY)))
  , hidden_ (new QCheckBox(tr(HIDDEN)))
  , archive_ (new QCheckBox(tr(ARCHIVE)))
  , system_ (new QCheckBox(tr(SYSTEM)))
#endif
, close_      ( new QPushButton( tr( CLOSE     ) ) )
, accept_     ( new QPushButton( tr( ACCEPT    ) ) )
{
   setWindowTitle( tr( CAPTION ) );

   QHBoxLayout* const info_layout = new QHBoxLayout;
   info_layout->addWidget( new QLabel( tr( FILE_NAME ) ) );
   info_layout->addWidget( path_ );
   info_layout->setStretchFactor( path_, 100 );
   
#if !_WIN32
   QGroupBox* const gbox_user = new QGroupBox( tr( USER ) );
   QVBoxLayout* const user_layout = new QVBoxLayout( gbox_user );
   user_layout->addWidget( user_read_ );
   user_layout->addWidget( user_write_ );
   user_layout->addWidget( user_exec_ );
   
   QGroupBox* const gbox_group = new QGroupBox( tr( GROUP ) );
   QVBoxLayout* const group_layout = new QVBoxLayout( gbox_group );
   group_layout->addWidget( group_read_ );
   group_layout->addWidget( group_write_ );
   group_layout->addWidget( group_exec_ );
   
   QGroupBox* const gbox_other = new QGroupBox( tr( OTHER ) );
   QVBoxLayout* const other_layout = new QVBoxLayout( gbox_other );
   other_layout->addWidget( other_read_ );
   other_layout->addWidget( other_write_ );
   other_layout->addWidget( other_exec_ );
#endif

#if !_WIN32
   QHBoxLayout* const gbox_layout = new QHBoxLayout;
   gbox_layout->addWidget( gbox_user );
   gbox_layout->addWidget( gbox_group );
   gbox_layout->addWidget( gbox_other );
#else
   QHBoxLayout* const gbox_layout = new QHBoxLayout;

   QVBoxLayout* const gbox_layout_a = new QVBoxLayout;
   gbox_layout_a->addWidget(readonly_);
   gbox_layout_a->addWidget(hidden_);
   QVBoxLayout* const gbox_layout_b = new QVBoxLayout;
   gbox_layout_b->addWidget(archive_);
   gbox_layout_b->addWidget(system_);

   gbox_layout->addLayout(gbox_layout_a);
   gbox_layout->addLayout(gbox_layout_b);
#endif

   QHBoxLayout* const btn_layout = new QHBoxLayout;
   btn_layout->addWidget( recursive_ );
   btn_layout->addStretch( 100 );
   btn_layout->addWidget( close_ );
   btn_layout->addWidget( accept_ );
   
   QVBoxLayout* const main_layout = new QVBoxLayout;
   main_layout->addLayout( info_layout );
   main_layout->addLayout( gbox_layout );
   main_layout->addLayout( btn_layout );
   setLayout( main_layout );

   set_info();
   
   connect( close_ , SIGNAL( clicked() ), this, SLOT( reject() ) );
   connect( accept_, SIGNAL( clicked() ), this, SLOT( accept() ) );
}
// end of QBtAttDialog

//*******************************************************************
// set_info                                                  PRIVATE
//*******************************************************************
void QBtAttrDialog::set_info()
{
   if( !are_dirs() ) recursive_->setEnabled( false );

#if !_WIN32
   const QFile::Permissions p = QFileInfo( *data_.begin() ).permissions();

   if( p & QFile::ReadUser   ) user_read_  ->setChecked( true );
   if( p & QFile::WriteUser  ) user_write_ ->setChecked( true );
   if( p & QFile::ExeUser    ) user_exec_  ->setChecked( true );
   if( p & QFile::ReadGroup  ) group_read_ ->setChecked( true );
   if( p & QFile::WriteGroup ) group_write_->setChecked( true );
   if( p & QFile::ExeGroup   ) group_exec_ ->setChecked( true );
   if( p & QFile::ReadOther  ) other_read_ ->setChecked( true );
   if( p & QFile::WriteOther ) other_write_->setChecked( true );
   if( p & QFile::ExeOther   ) other_exec_ ->setChecked( true );
#else
   const QFileInfo info = QFileInfo( *data_.begin() );

   DWORD attributes;
   attributes = GetFileAttributesA(info.filePath().toLocal8Bit());

   if (attributes == INVALID_FILE_ATTRIBUTES) return;

   if (attributes & FILE_ATTRIBUTE_READONLY) readonly_->setChecked(true);
   if (attributes & FILE_ATTRIBUTE_HIDDEN) hidden_->setChecked(true);
   if (attributes & FILE_ATTRIBUTE_ARCHIVE) archive_->setChecked(true);
   if (attributes & FILE_ATTRIBUTE_SYSTEM) system_->setChecked(true);
#endif
}
// end of set_info

//*******************************************************************
// get_info                                                  PRIVATE
//*******************************************************************
QString QBtAttrDialog::get_info() const
{
#if !_WIN32
   static const QString PREFIX = "0";
   
   qint32 user_attr = 0;
   if( user_read_ ->isChecked() ) user_attr += 4;
   if( user_write_->isChecked() ) user_attr += 2;
   if( user_exec_ ->isChecked() ) user_attr += 1;
   
   qint32 group_attr = 0;
   if( group_read_ ->isChecked() ) group_attr += 4;
   if( group_write_->isChecked() ) group_attr += 2;
   if( group_exec_ ->isChecked() ) group_attr += 1;
   
   qint32 other_attr = 0;
   if( other_read_ ->isChecked() ) other_attr += 4;
   if( other_write_->isChecked() ) other_attr += 2;
   if( other_exec_ ->isChecked() ) other_attr += 1;

   return ( PREFIX
            + QString::number( user_attr ) 
            + QString::number( group_attr )
            + QString::number( other_attr ));
#else
	return "";
#endif
}
// end of get_info

//*******************************************************************
// are_dirs                                                  PRIVATE
//*******************************************************************
bool QBtAttrDialog::are_dirs() const
{
   SelectionsSet::const_iterator it = data_.begin();
   const SelectionsSet::const_iterator end = data_.end();
   while( it != end ) {
      if( QFileInfo( *it ).isDir() ) {
         return true;
      }
      ++it;
   }
   return false;
}
// end of are_dirs

//*******************************************************************
// accept                                               PRIVATE slot
//*******************************************************************
void QBtAttrDialog::accept()
{
#if !_WIN32
   static const QString COMMAND   = "chmod";
   static const QString SILENT    = "-v";
   static const QString RECURSIVE = "-R";
   static const QString PATH      = "\"%1\"";
   static const QString SPACE     = " ";

   QString cmd = COMMAND;
   cmd += SPACE;
   cmd += SILENT;
   cmd += SPACE;
   if( recursive_->isChecked() ) cmd += RECURSIVE;
   cmd += SPACE;
   cmd += get_info();
   cmd += SPACE;

   QBtSystemCall syscall( this );
   
   SelectionsSet::const_iterator it = data_.begin();
   const SelectionsSet::const_iterator end = data_.end();
   while( it != end ) {
      path_->setText( *it );
      syscall.run( cmd + PATH.arg( *it ) );
      ++it;
   }
#else

#endif
   QDialog::accept();
}
// end of accept

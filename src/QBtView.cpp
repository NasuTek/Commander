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
#include "QBtView.h"
#include "QBtConfig.h"
#include "QBtSettings.h"
#include "QBtDirModel.h"
#include "QBtViewDelegate.h"
#include "QBtEventsController.h"
#include "QBtDeleteQuest.h"
#include "QBtDeleter.h"
#include "QBtShared.h"
#include "QBtFileViewer.h"
#include "QBtFileEditor.h"
#include "QBtAttrDialog.h"
#include "QBtFinder.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDir>
#include <QInputDialog>
#include <QProcess>
#include <QtDebug>
#include <QMessageBox>

#if _WIN32
#include <windows.h>
#endif

using namespace std;

/*------- constants:
-------------------------------------------------------------------*/
const char* const QBtView::MKDIR_CAPTION  = QT_TR_NOOP( "Create subdirectory"      );
const char* const QBtView::MKDIR_PROMPT   = QT_TR_NOOP( "Enter a name for new subdirectory:" );
const char* const QBtView::MKDIR_ERROR    = QT_TR_NOOP( "Can't create the subdirectory:\n %1" );
const char* const QBtView::RENAME_CAPTION = QT_TR_NOOP( "Rename a file/dir"  );
const char* const QBtView::RENAME_PROMPT  = QT_TR_NOOP( "Enter a new file name:" );
const char* const QBtView::RENAME_ERROR   = QT_TR_NOOP( "Can't rename the file\nfrom: %1\nto: %2" );


//*******************************************************************
// QBtView                                          CONSTRUCTOR
//*******************************************************************
QBtView::QBtView( const QString& in_path, QWidget* const in_parent )
: QTreeView ( in_parent )
, model_    ( new QBtDirModel )
{
   setAutoFillBackground( true );
   
   setItemDelegate( new QBtViewDelegate( this ) );
   setRootIsDecorated( false );
   setEditTriggers( NoEditTriggers );
   setAllColumnsShowFocus( true );
   
   header()->setStretchLastSection( true );
   header()->setSortIndicator( 0, Qt::AscendingOrder );
   header()->setSortIndicatorShown( true );
   header()->setSectionsClickable( true );

   settings();

   connect( model_, SIGNAL( update_finished() ), this, SLOT( request_finished() ) );
   setModel( model_ );
   
   requests_.push( RESIZE_COLUMNS );
   requests_.push( GOTO_TOP );
   model_->update( in_path );

   QBtEventsController* const ec = QBtEventsController::instance();
   ec->append( this, QBtEvent::F2_KEY );
   ec->append( this, QBtEvent::F3_KEY );
   ec->append( this, QBtEvent::F4_KEY );
   ec->append( this, QBtEvent::F6_KEY );
   ec->append( this, QBtEvent::F7_KEY );
   ec->append( this, QBtEvent::F8_KEY );
   ec->append( this, QBtEvent::SELECT_REQUEST );
   ec->append( this, QBtEvent::DESELECT_REQUEST );
   ec->append( this, QBtEvent::REVSEL_REQUEST );
   ec->append( this, QBtEvent::REFRESH_REQUEST );
   ec->append( this, QBtEvent::FILTER_CHANGED_REQUEST );
   ec->append( this, QBtEvent::FIND_REQUEST );
   ec->append( this, QBtEvent::CONFIG_CHANGED );
   
   connect( this, SIGNAL( doubleClicked ( const QModelIndex& ) ),
            this, SLOT  ( enter         ( const QModelIndex& ) ) );
}
// end of QBtView

//*******************************************************************
// ~QBtView                                               DESTRUCTOR
//*******************************************************************
QBtView::~QBtView()
{
   QBtEventsController::instance()->remove( this );
}
// end of ~QBtView

//*******************************************************************
// setting                                                   PRIVATE
//*******************************************************************
void QBtView::settings()
{
   QBtConfig* const cfg = QBtConfig::instance();
   setFont( cfg->font() );

   QPalette p = palette();
   p.setColor( backgroundRole(), cfg->bkg_f_nc_ns_color() );
   setPalette( p );
}
// end of settings

//*******************************************************************
// keyPressEvent                                   PRIVATE inherited
//*******************************************************************
void QBtView::keyPressEvent( QKeyEvent* in_event )
{
   if( model_->busy() ) {
      QTreeView::keyPressEvent( in_event );
      return;
   }

   if( in_event->modifiers() & Qt::AltModifier ) {
      switch( in_event->key() ) {
         case Qt::Key_Return:
         case Qt::Key_Enter:
            resize_columns();
            break;
         case Qt::Key_A:
            unselect_all();
            break;
      }
   }
   else if( in_event->modifiers() & Qt::ControlModifier ) {
      switch( in_event->key() ) {
         case Qt::Key_Return:
         case Qt::Key_Enter:
            in_event->accept();
            jump_to_home();
            break;
         case Qt::Key_A:
            select_all();
            break;
         case Qt::Key_R:
            refresh();
            break;
         case Qt::Key_K:
            console_start();
            break;
      }
   }
   else {
      switch( in_event->key() ) {
         case Qt::Key_Return:
         case Qt::Key_Enter:
            in_event->accept();
            enter_key();
            break;
         case Qt::Key_Backspace:
            in_event->accept();
            one_level_up();
            break;
         case Qt::Key_Insert:
            select();
            break;
         case Qt::Key_Plus:
            select_mask();
            break;
         case Qt::Key_Minus:
            deselect_mask();
            break;
         case Qt::Key_Asterisk:
            revert_selection();
            break;
         case Qt::Key_F2:
            access_permissions();
            break;
         case Qt::Key_F3:
            view();
            break;
         case Qt::Key_F4:
            edit();
            break;
         case Qt::Key_F6:
            rename();
            break;
         case Qt::Key_F7:
            mkdir();
            break;
         case Qt::Key_Delete:
         case Qt::Key_F8:
            remove_selected();
            break;
      }
   }
   QTreeView::keyPressEvent( in_event );
}
// end of keyPressEvent

//*******************************************************************
// customEvent                                     PRIVATE inherited
//*******************************************************************
void QBtView::customEvent( QEvent* const in_event )
{
   QBtEvent* const event = dynamic_cast< QBtEvent* >( in_event );
   const qint32 type = static_cast< qint32 >( event->type() );
   bool handled = false;

   if( hasFocus() ) {
      switch( type ) {
         case QBtEvent::F2_KEY:
            access_permissions();
            handled = true;
            break;
         case QBtEvent::F3_KEY:
            view();
            break;
         case QBtEvent::F4_KEY:
            edit();
            break;
         case QBtEvent::F6_KEY:
            rename();
            handled = true;
            break;
         case QBtEvent::F7_KEY:
            mkdir();
            handled = true;
            break;
         case QBtEvent::F8_KEY:
            remove_selected();
            handled = true;
            break;
         case QBtEvent::SELECT_REQUEST:
            select_mask();
            handled = true;
            break;
         case QBtEvent::DESELECT_REQUEST:
            deselect_mask();
            handled = true;
            break;
         case QBtEvent::REVSEL_REQUEST:
            revert_selection();
            handled = true;
            break;
         case QBtEvent::FIND_REQUEST:
            find();
            handled = true;
            break;
      }
   }

   if( !handled ) {
      switch( type ) {
         case QBtEvent::CONFIG_CHANGED:
            settings();
            repaint();
            break;
         case QBtEvent::FILTER_CHANGED_REQUEST:
         case QBtEvent::REFRESH_REQUEST:
            refresh();
            break;
      }
   }
   QTreeView::customEvent( in_event );
}
// end of customEvent

//*******************************************************************
// find                                                      PRIVATE
//*******************************************************************
void QBtView::find()
{
   QString file_path = QString();

   {
      QBtFinder dialog( this );
      if( QDialog::Accepted == dialog.exec() ) {
         dialog.selected_file( file_path );
      }
   }

   if( file_path.isEmpty() ) return;

   model_->clear();
   const QFileInfo fi( file_path );
   requests_.push( RESIZE_COLUMNS );
   requests_.push( INITIAL_FILE_SELECT );
   initial_file_stack_.push( fi.fileName() );
   model_->update( fi.absolutePath() );
}
// end of find

//*******************************************************************
// rename                                                    PRIVATE
//*******************************************************************
void QBtView::rename()
{
   if( QBtShared::is_regular_file( selected_file_full_name() ) ) {
      const QString current_name = selected_file_full_name();
      bool ok;
      const QString fname = QInputDialog::getText(  this,
                              tr( RENAME_CAPTION ),
                              tr( RENAME_PROMPT  ),
                              QLineEdit::Normal,
                              current_name,
                              &ok );
                              
      if( ok && !fname.isEmpty() ) {
         if( fname != current_name ) {
            QDir dir( current_path() );
            if( dir.rename( current_name, fname ) ) {
               refresh( fname );
            }
            else {
               QMessageBox::critical(  this,
                  tr( RENAME_CAPTION ),
                  tr( RENAME_ERROR ).arg( current_name ).arg( fname ) );
            }
         }
      }
   }
}
// end of rename

//*******************************************************************
// mkdir                                                     PRIVATE
//*******************************************************************
void QBtView::mkdir()
{
   bool ok;
   const QString fname = QInputDialog::getText(  this,
                                                tr( MKDIR_CAPTION ),
                                                tr( MKDIR_PROMPT  ),
                                                QLineEdit::Normal,
                                                QString(),
                                                &ok );
   if( ok && !fname.isEmpty() ) {
      QDir dir( current_path() );
      if( dir.mkdir( fname ) ) {
         refresh( fname );
      }
      else {
         QMessageBox::critical(  this,
            tr( MKDIR_CAPTION ),
            tr( MKDIR_ERROR   ).arg( fname ) );
      }
   }
}
// end of mkdir

//*******************************************************************
// access_permissions                                        PRIVATE
//*******************************************************************
void QBtView::access_permissions()
{
   SelectionsSet data = get_selected_items();
   if( data.empty() ) {
      if( QBtShared::is_regular_file( selected_file_full_name() ) ) {
         const QFileInfo fi( selected_file_path() );
         data.insert( fi.absoluteFilePath() );
      }
   }
   if( data.empty() ) return;

   QBtAttrDialog dialog( this, data );
   if( QDialog::Accepted ==  dialog.exec() ) refresh();
}
// end of access_permissions

//*******************************************************************
// view                                                      PRIVATE
//*******************************************************************
void QBtView::view()
{
   QBtFileViewer dialog( this, selected_file_path() );
   dialog.exec();
}
// end of view

//*******************************************************************
// edit                                                      PRIVATE
//*******************************************************************
void QBtView::edit()
{
   QBtFileEditor dialog( this, selected_file_path() );
   dialog.exec();
}
// end of edit

//*******************************************************************
// remove_selected                                           PRIVATE
//-------------------------------------------------------------------
// Funkcja wywolywana po nacisnieciu klawiszy Delete lub F8.
// Usuwa z dysku zaznaczone /lub aktualny plik.
//*******************************************************************
void QBtView::remove_selected()
{
   SelectionsSet data = get_selected_items();
   if( data.empty() ) {
      if( QBtShared::is_regular_file( selected_file_full_name() ) ) {
         const QFileInfo fi( selected_file_path() );
         data.insert( fi.absoluteFilePath() );
      }
   }
   if( data.empty() ) return;
   
   QBtDeleteQuest quest( this );
   quest.set_files( data );
   if( quest.exec() != QDialog::Accepted ) return;
   const bool wipe = quest.to_wipe();
   
   QBtDeleter deleter( this );
   deleter.set_data( data, wipe );
   if( QDialog::Accepted == deleter.exec() ) refresh();
}
// end of remove_selected

//*******************************************************************
// current_file                                               PUBLIC
//*******************************************************************
QString QBtView::selected_file_full_name() const
{
   return model_->file_full_name( currentIndex() );
}
// end of selected_file_full_name

//*******************************************************************
// selected_file_path                                         PUBLIC
//*******************************************************************
QString QBtView::selected_file_path() const
{
   return model_->file_path( currentIndex() );
}
// end of selected_file_path

//*******************************************************************
// set_initial_file_request                                   PUBLIC
//*******************************************************************
void QBtView::set_initial_file_request( const QString& in_file )
{
   initial_file_stack_.push( in_file );
   requests_.push( INITIAL_FILE_SELECT );
}

//*******************************************************************
// enter_key                                                 PRIVATE
//*******************************************************************
void QBtView::enter_key()
{
   enter( currentIndex() );
}
// end of enter_key

//*******************************************************************
// update                                                     PUBLIC
//*******************************************************************
void QBtView::update( const QString& in_path )
{
   requests_.push( RESIZE_COLUMNS );
   requests_.push( GOTO_TOP );
   model_->update( in_path );
}
// end of update

//*******************************************************************
// path                                                       PUBLIC
//*******************************************************************
const QString& QBtView::current_path() const
{
   return model_->current_path();
}
// end of current_path

//*******************************************************************
// get_selected_items                                         PUBLIC
//*******************************************************************
const SelectionsSet&  QBtView::get_selected_items() const
{
   return model_->get_selected_items();
}
// end of get_selected_items

//*******************************************************************
// select                                                    PRIVATE
//-------------------------------------------------------------------
// Nacisnieto klawisz Insert - reczne zaznaczenie pliku.
//*******************************************************************
void QBtView::select()
{
   const QModelIndex index = currentIndex();
   if( model_->select( index ) ) {
      emit select_count( model_->select_count() );
      const QModelIndex next_index = model_->head_item_index( index.row() + 1 );
      if( next_index.isValid() ) {
         setCurrentIndex( next_index );
         scrollTo( next_index );
      }
      else {
         // Co prawda na tej pozycji juz jestesmy,
         // ale wywoluje te funkcje po to aby zostala
         // ona ponownie odmalowana na ekranie.
         // [Ostatni i zaznaczony jednoczesnie.]
         scrollTo( index );
      }
   }
}
// end of select

//*******************************************************************
// console_start                                             PRIVATE
//*******************************************************************
void QBtView::console_start() const
{
   const QString path = model_->current_path();
   
   if( !path.isEmpty() ) {
      QBtSettings stt;
      QVariant data;
      bool use_default = true;

      if( stt.read( QBtConfig::TERMINAL_GROUP + QBtConfig::USE_DEFAULT_KEY, data ) ) {
         use_default = data.toBool();
      }
      if( use_default ) {
         static const QString GNOME = "gnome-terminal --working-directory=%1 &";
         static const QString KDE   = "konsole --workdir %1 &";
         const QString cmd = QBtShared::is_gnome() ? GNOME : KDE;
         system( cmd.arg( path ).toLatin1() );
      }
      else {
         QString command = QString();
         if( stt.read( QBtConfig::TERMINAL_GROUP + QBtConfig::COMMAND_KEY, data ) ) {
            command = data.toString().trimmed();
         }
         if( !command.isEmpty() ) {
            if( command.contains( "$dir" ) ) {
               command.replace( "$dir", path );
            }
            command += " &";
            system( command.toLatin1() );
         }
      }
   }
}
// end of console_start

//*******************************************************************
// enter                                                PRIVATE slot
//*******************************************************************
void QBtView::enter( const QModelIndex& in_index )
{
   const QString fname = model_->file_full_name( in_index ); // tak ma byc ze wzgledu na ..
   const QFileInfo fi( model_->file_path( in_index ) );
   const QString fpath = fi.absoluteFilePath();
   const QString dir = fi.absolutePath();
   
   if( fi.isDir() ) {                                 // KATALOG
      if( fi.isExecutable() && fi.isReadable() ) {
         if( ".." == fname ) {
            one_level_up();
         }
         else {
            initial_file_stack_.push( fi.fileName() );
            requests_.push( GOTO_TOP );
            model_->update( fpath );
         }
      }
      return;
   }
   else {                                             // PLIK (NIE KATALOG)
      if( fi.isExecutable() ) {                       // wykonywalne
#if !_WIN32
         if( QBtShared::is_binary_file( fpath ) ) {   // program
            static const QString PRG = "%1 &";
            system( PRG.arg( fpath ).toLocal8Bit() );
         }
         else {                                       // skrypt
            static const QString GNOME = "gnome-terminal --working-directory=%1 --command=%2";
            static const QString KDE = "konsole --workdir %1 -e %2";
            const QString cmd = QBtShared::is_gnome() ? GNOME : KDE;
            system( cmd.arg( dir ).arg( fpath ).toLocal8Bit() );
         }
#else
          ShellExecuteA(NULL, "open", fpath.toLocal8Bit(), NULL, dir.toLocal8Bit(), SW_SHOWNORMAL);
#endif
      }
      else {                                          // ZWYKLY PLIK
         const QString ext = fi.suffix().toLower();
         QString prg = QString();
         QString par = QString();
         if( is_ext_declared( ext, prg, par  ) ) {
            par.replace( "$dir", fi.absolutePath() );
            par.replace( "$name", fi.fileName() );
            par.replace( "$path", fi.absoluteFilePath() );
            const QString cmd = "\"%1\" \"%2\" &";
            system( cmd.arg( prg ).arg( par ).toLocal8Bit() );
         }
         else {
#if !_WIN32
            static const QString GNOME = "gnome-open %1";
            static const QString KDE   = "kfmclient exec %1";
            const QString cmd = QBtShared::is_gnome() ? GNOME : KDE;
            system( cmd.arg( fpath ).toLocal8Bit() );
#else
             ShellExecuteA(NULL, "open", fpath.toLocal8Bit(), NULL, dir.toLocal8Bit(), SW_SHOWNORMAL);
#endif
         }
      }
   }
}
// end of enter

//*******************************************************************
// is_ext_declared                                           PRIVATE
//*******************************************************************
bool QBtView::is_ext_declared( const QString& in_ext, QString& out_prg, QString& out_par ) const
{
   QStringList data = QStringList();

   QBtSettings stt;
   QVariant value;
   if( stt.read( QBtConfig::EXT_GROUP + QBtConfig::EXT_KEY, value ) ) {
      data = value.toStringList();
   }

   const qint32 n = data.size();
   for( qint32 i = 0; i < n; ++i ) {
      const QStringList record = data.at( i ).split( ',' );
      if( in_ext == record.at( 0 ).toLower() ) {
         out_prg = record.at( 1 );
         out_par = record.at( 2 );
         return true;
      }
   }
   return false;
}
// end of is_ext_declared

//*******************************************************************
// refresh                                                    PUBLIC
//*******************************************************************
void QBtView::refresh( const QString& in_path )
{
   requests_.push( RESIZE_COLUMNS );
   requests_.push( INITIAL_FILE_SELECT );
   initial_file_stack_.push( in_path.isEmpty() ? selected_file_full_name() : in_path );
   model_->refresh();
}
// end of refresh

//*******************************************************************
// one_level_up                                              PRIVATE
//*******************************************************************
void QBtView::one_level_up()
{
   requests_.push( INITIAL_FILE_SELECT );
   model_->cdup();
}
// end_level_up

//*******************************************************************
// jump_to_home                                              PRIVATE
//*******************************************************************
void QBtView::jump_to_home()
{
   const QString home_path = QDir::homePath();
   if( model_->current_path() != home_path ) {
      requests_.push( GOTO_TOP );
      model_->update( home_path );
   }
}
// end of jump_to_home

//*******************************************************************
// select_mask                                               PRIVATE
//*******************************************************************
void QBtView::select_mask()
{
   model_->select_mask( true, this );
   emit select_count( model_->select_count() );
}
// end of select_mask

//*******************************************************************
// deselect_mask                                             PRIVATE
//*******************************************************************
void QBtView::deselect_mask()
{
   model_->select_mask( false, this );
   emit select_count( model_->select_count() );
}
// end of deselect_mask

//*******************************************************************
// revert_selection                                          PRIVATE
//*******************************************************************
void QBtView::revert_selection()
{
   model_->revert_selections();
   emit select_count( model_->select_count() );
}
// end of revert_selection

//*******************************************************************
// select_all                                                PRIVATE
//*******************************************************************
void QBtView::select_all()
{
   model_->select_all();
   emit select_count( model_->select_count() );
}
// end of select_all

//*******************************************************************
// unselect_all
//*******************************************************************
void QBtView::unselect_all()
{
   model_->clear_selections();
   emit select_count( model_->select_count() );
}
// end of unselect_all

//*******************************************************************
// request_finished                                     PRIVATE slot
//*******************************************************************
void QBtView::request_finished()
{
   while( !requests_.empty() ) {
      const qint32 cmd = requests_.front();
      requests_.pop();
      
      switch( cmd ) {
         case INITIAL_FILE_SELECT:
            set_initial_file();
            break;
         case RESIZE_COLUMNS:
            resize_columns();
            break;
         case GOTO_TOP:
            goto_top();
            break;
      }
   }
   emit dir_count   ( model_->dir_count ()   );
   emit file_count  ( model_->file_count()   );
   emit select_count( model_->select_count() );
   emit path_changed( model_->current_path() );
}
// end of request_finished

//*******************************************************************
// resize_columns                                            PRIVATE
//*******************************************************************
void QBtView::resize_columns()
{
   for( qint32 i = 0; i < model_->columnCount(); ++i ) {
      resizeColumnToContents( i );
   }
}
// end of resize_columns

//*******************************************************************
// goto_top                                                   PUBLIC
//*******************************************************************
void QBtView::goto_top()
{
   const QModelIndex index = model_->head_item_index( 0 );
   if( index.isValid() ) {
      setCurrentIndex( index );
      scrollTo( index, PositionAtTop );
   }
}
// end of goto_top

//*******************************************************************
// set_current_file                                           PUBLIC
//*******************************************************************
void QBtView::set_initial_file()
{
   if( initial_file_stack_.empty() ) {
      goto_top();
      return;
   }

   const QString full_name = initial_file_stack_.top();
   initial_file_stack_.pop();
   
   const QModelIndex index = model_->search_file( full_name );
   if( index.isValid() ) {
      setCurrentIndex( index );
      scrollTo( index, PositionAtCenter );
   }
   else {
      goto_top();
   }
}
// end of set_current_file

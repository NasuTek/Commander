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

#ifndef INCLUDED_QBtShared_h
#define INCLUDED_QBtShared_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>
#include <QString>
#include <QFile>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QWidget;
class QSize;
class QBtFileInfo;
class QFontMetrics;
class QCursor;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtShared : public QObject
{
   Q_OBJECT

// ******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtShared() : QObject() {}
private:
   QBtShared( const QBtShared& );
   QBtShared& operator=( const QBtShared& );

// ******* MEMBERS *******
private:
   static QString buffer_;

// ******* CONSTANTS *******
public:
   static const QChar   DIGIT_SEPARATOR;
   static const QString THIS_DIR;
   static const QString PARENT_DIR;
   static const QString ORGANISATION;
   static const QString VERSION;
   static const QString PROGRAM_NAME;

// ******* METHODS *******
public:
   static const QString& program_name();
   static void           resize         ( QWidget*, qint32, qint32 );
   static void           resize         ( QWidget*, const QSize& );
   static void           resize_width   ( QWidget*, qint32 );
   static QString&       reverse        ( QString& );
   static QString        num2str        ( qint64, const QChar& = DIGIT_SEPARATOR );
   static QString        access         ( const QBtFileInfo& );
   static void           idle           ();
   static void           elide          ( const QFontMetrics&, qint32, QString& );
   static void           auto_rename    ( QString& );
   static bool           is_regular_file( const QString& );
   static bool           is_binary_file ( const QString& );
   static bool           is_gnome       ();
   static void           set_cursor     ( const QCursor& );
   static void           restore_cursor ();
   static QString        slashed_dir    ( const QString& );
   static QString        quoted_fpath   ( const QString& );
   static void           touch          ( const QString&, const QString& );
};

#endif // INCLUDED_QBtShared_h

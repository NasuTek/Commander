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

#ifndef INCLUDED_QBtWiper_h
#define INCLUDED_QBtWiper_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>
#include <QString>
#include <QDialog>
#include <unistd.h>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtWiper : public QObject
{
    Q_OBJECT

// ******* CONSTRUCTION / DESTRUCTION *******
public:
    QBtWiper( QWidget* );
private:
    QBtWiper( const QBtWiper& );
    QBtWiper& operator=( const QBtWiper& );

// ******* TYPES *******
private:
    enum {
        WIPE_BUFSIZE     = 4096,
        SINGLE_PATS_SIZE = 16,
        TRIPLE_PATS_ROWS = 6,
        TRIPLE_PATS_COLS = 3,
    };

// ******* CONSTANTS *******
private:
    static const unsigned char SINGLE_PATS [ SINGLE_PATS_SIZE ];
    static const unsigned char TRIPLE_PATS [ TRIPLE_PATS_ROWS][TRIPLE_PATS_COLS ];
    static const char* const   WIPE_MESSAGE;

// ******* MEMBERS *******
private:
    QString        file_path_;
    qint32         devrand_fd_;
    qint32         devrand_fd_noblock_;
    qint32         devurand_fd_;
    bool           break_;
    unsigned char  buffer_[ WIPE_BUFSIZE ];

// ******* METHODS *******
public:
   qint32 wipe               ( const QString& );
private:
   qint32  fd_wipe           ( qint32 );
   qint32  pattern_pass      ( qint32, unsigned char*, size_t, size_t );
   qint32  random_pass       ( qint32, size_t );
   qint32  write_data        ( qint32, const void*, size_t );
   qint32  make_fd_noblocking( qint32 );
   qint32  rand_init         ();
   qint32  rand              ( unsigned char*, size_t );
   void    progress          ( qint32 );
   bool    can_do            ();
signals:
   void    wipe_progress     ( const QString& );
};

#endif // INCLUDED_QBtWiper_h

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

#ifndef INCLUDED_QBtFileInfo_h
#define INCLUDED_QBtFileInfo_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QFileInfo>
#include <QString>
#include <QDateTime>
#include <QMetaType>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtFileInfo
{
//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtFileInfo()
   : is_dir_        ( false                )
   , is_executable_ ( false                )
   , is_file_       ( false                )
   , is_symlink_    ( false                )
   , is_readable_   ( false                )
   , is_writable_   ( false                )
   , size_          ( qint64()             )
   , permission_    ( QFile::Permissions() )
   , lastmod_       ( QDateTime()          )
   , owner_         ( QString()            )
   , group_         ( QString()            )
   , full_name_     ( QString()            )
   , path_          ( QString()            )
   , name_          ( QString()            )
   , ext_           ( QString()            )
   {}
   QBtFileInfo( const QBtFileInfo& rhs )
   : is_dir_        ( rhs.is_dir_        )
   , is_executable_ ( rhs.is_executable_ )
   , is_file_       ( rhs.is_file_       )
   , is_symlink_    ( rhs.is_symlink_    )
   , is_readable_   ( rhs.is_readable_   )
   , is_writable_   ( rhs.is_writable_   )
   , size_          ( rhs.size_          )
   , permission_    ( rhs.permission_    )
   , lastmod_       ( rhs.lastmod_       )
   , owner_         ( rhs.owner_         )
   , group_         ( rhs.group_         )
   , full_name_     ( rhs.full_name_     )
   , path_          ( rhs.path_          )
   , name_          ( rhs.name_          )
   , ext_           ( rhs.ext_           )
   {}
   QBtFileInfo( const QFileInfo& fi )
   : is_dir_        ( fi.isDir()            )
   , is_executable_ ( fi.isExecutable()     )
   , is_file_       ( fi.isFile()           )
   , is_symlink_    ( fi.isSymLink()        )
   , is_readable_   ( fi.isReadable()       )
   , is_writable_   ( fi.isWritable()       )
   , size_          ( fi.size()             )
   , permission_    ( fi.permissions()      )
   , lastmod_       ( fi.lastModified()     )
   , owner_         ( fi.owner()            )
   , group_         ( fi.group()            )
   , full_name_     ( fi.fileName()         )
   , path_          ( fi.absoluteFilePath() )
   , name_          ( fi.completeBaseName() )
   , ext_           ( fi.suffix()           )
   {}
   QBtFileInfo& operator=( const QBtFileInfo& rhs )
   {
      if( this != &rhs ) {
         is_dir_        = rhs.is_dir_        ;
         is_executable_ = rhs.is_executable_ ;
         is_file_       = rhs.is_file_       ;
         is_symlink_    = rhs.is_symlink_    ;
         is_readable_   = rhs.is_readable_   ;
         is_writable_   = rhs.is_writable_   ;
         size_          = rhs.size_          ;
         permission_    = rhs.permission_    ;
         lastmod_       = rhs.lastmod_       ;
         owner_         = rhs.owner_         ;
         group_         = rhs.group_         ;
         full_name_     = rhs.full_name_     ;
         path_          = rhs.path_          ;
         name_          = rhs.name_          ;
         ext_           = rhs.ext_           ;
      }
      return *this;
   }
   
   ~QBtFileInfo()
   {}

   bool               is_dir       () const { return is_dir_;        }
   bool               is_executable() const { return is_executable_; }
   bool               is_file      () const { return is_file_;       }
   bool               is_symlink   () const { return is_symlink_;    }
   bool               is_readable  () const { return is_readable_;   }
   bool               is_writable  () const { return is_writable_;   }
   qint64             size         () const { return size_;          }
   QFile::Permissions permission   () const { return permission_;    }
   const QDateTime&   lastmod      () const { return lastmod_;       }
   const QString&     owner        () const { return owner_;         }
   const QString&     group        () const { return group_;         }
   const QString&     path         () const { return path_;          }
   const QString&     full_name    () const { return full_name_;     }
   const QString&     name         () const { return name_;          }
   const QString&     ext          () const { return ext_;           }

   
//******* MEMBERS *******
private:
   bool      is_dir_;
   bool      is_executable_;
   bool      is_file_;
   bool      is_symlink_;
   bool      is_readable_;
   bool      is_writable_;
   qint64    size_;
   QFile::Permissions permission_;
   QDateTime lastmod_;
   QString   owner_;
   QString   group_;
   QString   full_name_;   // nazwa ze wszystkimi rozszerzeniami
   QString   path_;
   QString   name_;        // nazwa bez ostatniego rozszerzenia
   QString   ext_;         // ostatnie rozszerzenie
};
Q_DECLARE_METATYPE( QBtFileInfo )

#endif // INCLUDED_QBtFileInfo_h

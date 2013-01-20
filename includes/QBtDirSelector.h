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

#ifndef INCLUDED_QBtDirSelector_h
#define INCLUDED_QBtDirSelector_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QTreeView;
class QPushButton;
class QDirModel;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtDirSelector : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtDirSelector( QWidget*, const QString& );
private:
   QBtDirSelector( const QBtDirSelector& );
   QBtDirSelector& operator=( const QBtDirSelector& );

//******* CONSTANTS *******
private:
   static const char* const Caption;
   static const char* const Select;
   static const char* const Close;

//******* MEMBERS *******
private:
   QTreeView*   const view_;
   QPushButton* const select_btn_;
   QPushButton* const cancel_btn_;
   QDirModel*   const model_;
   QString            path_;

//******* METHODS *******
public:
   QString path();
private:
   void showEvent( QShowEvent* );
};

#endif // INCLUDED_QBtDirSelector_h

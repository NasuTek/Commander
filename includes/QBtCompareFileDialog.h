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

#ifndef INCLUDED_QBtCompareFileDialog_h
#define INCLUDED_QBtCompareFileDialog_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>

/*------- forward declarations:
-------------------------------------------------------------------*/
class QProgressBar;
class QPushButton;
class QBtInfoField;
class QBtFileComparator;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtCompareFileDialog : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtCompareFileDialog( QWidget*, const QString&, const QString& );
private:
   QBtCompareFileDialog( const QBtCompareFileDialog& );
   QBtCompareFileDialog& operator=( const QBtCompareFileDialog& );

//******* CONSTANTS *******
private:
   static const char* const CAPTION;
   static const char* const FILES;
   static const char* const PROGRESS;
   static const char* const FILE_NR1;
   static const char* const FILE_NR2;
   static const char* const CANCEL;
   static const char* const START;
   static const char* const BREAK;
   static const char* const EQUAL;
   static const char* const NOT_EQUAL;
   static const char* const IO_ERROR;

//******* MEMBERS *******
private:
   const QString            fpath1_;
   const QString            fpath2_;
   QBtInfoField*      const ifield1_;
   QBtInfoField*      const ifield2_;
   QProgressBar*      const progress_bar_;
   QPushButton*       const cancel_;
   QPushButton*       const start_;
   QBtFileComparator* const comparator_;
   bool                     is_started_;
   bool                     is_canceled_;

//******* METHODS *******
private:
   void showEvent    ( QShowEvent* );
   bool check_files  ();
private slots:
   void init_progress( qint64 );
   void progress     ( qint64 );
   void cancel       ();
   void start        ();
};

#endif // INCLUDED_QBtCompareFileDialog_h

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

#ifndef INCLUDED_QBtTimeStamp_h
#define INCLUDED_QBtTimeStamp_h

/*------- include files:
-------------------------------------------------------------------*/
#include <QDialog>
#include <QDate>
#include <QTime>
#include <QFileInfo>
#include "BtTypes.h"

/*------- forward declaration:
-------------------------------------------------------------------*/
class QPushButton;
class QLabel;
class QCheckBox;
class QDateEdit;
class QTimeEdit;

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtTimeStamp : public QDialog
{
   Q_OBJECT

//******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtTimeStamp( QWidget*, const SelectionsSet&, const QString& );
private:
   QBtTimeStamp( const QBtTimeStamp& );
   QBtTimeStamp& operator=( const QBtTimeStamp& );

//******* CONSTANTS *******
private:
   static const char* const Caption;
   static const char* const DataCaption;
   static const char* const MusterCaption;
   static const char* const Now;
   static const char* const Accept;
   static const char* const Cancel;
   static const char* const UseMuster;
   static const QString     Date;
   static const QString     Time;
   static const QString     DateTime;

//******* MEMBERS *******
private:
   const SelectionsSet data_;
   const QFileInfo     muster_fi_;
   QPushButton*  const now_btn_;
   QPushButton*  const accept_btn_;
   QPushButton*  const cancel_btn_;
   QLabel*       const muster_;
   QCheckBox*    const use_muster_;
   QDateEdit*    const date_edit_;
   QTimeEdit*    const time_edit_;
   QDate               date_bak_;
   QTime               time_bak_;

//******* METHODS *******
private slots:
   void now   ();
   void touch ();
   void muster( bool );
};

#endif // INCLUDED_QBtTimeStamp_h

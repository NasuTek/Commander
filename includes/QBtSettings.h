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

#ifndef INCLUDED_QBtSettings_H
#define INCLUDED_QBtSettings_H

/*------- include files:
-------------------------------------------------------------------*/
#include <QObject>
#include <QSettings>
#include <QVariant>

/*------- class declaration:
-------------------------------------------------------------------*/
class QBtSettings : protected QSettings
{
   Q_OBJECT

// ******* CONSTRUCTION / DESTRUCTION *******
public:
   QBtSettings() : QSettings() {}
private:
   QBtSettings( const QBtSettings& );
   QBtSettings& operator=( const QBtSettings& );

// ******* METHODS *******
public:   
   bool save( const QString&, const QVariant& );
   bool read( const QString&, QVariant& );
};

#endif // INCLUDED_QBtSettings_H

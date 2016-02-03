/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHDBUS_H
#define QCHDBUS_H

#include <QObject>
#include <QDBusConnection>
#include <qdeclarative.h>

class QchDBus : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(BusType)
    
public:
    enum BusType {
        SessionBus = 0,
        SystemBus
    };
    
    inline static QDBusConnection connection(BusType bus) {
        return bus == SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus();
    }

private:
    QchDBus() : QObject() {}
    
    Q_DISABLE_COPY(QchDBus)
};

QML_DECLARE_TYPE(QchDBus)
    
#endif // QCHDBUS_H

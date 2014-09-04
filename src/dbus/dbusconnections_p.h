/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef DBUSCONNECTIONS_P_H
#define DBUSCONNECTIONS_P_H
 
#include "qdeclarativeconnections_p.h"

class DBusConnectionsPrivate;

class DBusConnections : public QDeclarativeConnections
{
    Q_OBJECT
    
    Q_PROPERTY(QObject *target READ target SCRIPTABLE false) // Make target read-only to QML
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString interfaceName READ interfaceName WRITE setInterfaceName NOTIFY interfaceNameChanged)
    Q_PROPERTY(BusType bus READ bus WRITE setBus NOTIFY busChanged)
    
    Q_ENUMS(BusType)
    
public:
    enum BusType {
        SessionBus = 0,
        SystemBus
    };
    
    explicit DBusConnections(QObject *parent = 0);
    ~DBusConnections();
    
    QString serviceName() const;
    void setServiceName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    QString interfaceName() const;
    void setInterfaceName(const QString &name);
    
    BusType bus() const;
    void setBus(BusType bus);
    
signals:
    void serviceNameChanged();
    void pathChanged();
    void interfaceNameChanged();
    void busChanged();

private:
    DBusConnections(DBusConnectionsPrivate &dd, QObject *parent = 0);
    
    QScopedPointer<DBusConnectionsPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(DBusConnections)
    Q_DISABLE_COPY(DBusConnections)
};

QML_DECLARE_TYPE(DBusConnections)

#endif // DBUSCONNECTIONS_P_H

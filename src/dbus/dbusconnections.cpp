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

#include "dbusconnections_p.h"
#include <QDBusConnection>
#include <QDBusInterface>

class DBusConnectionsPrivate
{

public:
    DBusConnectionsPrivate(DBusConnections *parent) :
        q_ptr(parent),
        iface(0),
        bus(DBusConnections::SessionBus)
    {
    }
    
    virtual ~DBusConnectionsPrivate() {}
    
    void setTarget() {
        Q_Q(DBusConnections);
        
        if (iface) {
            delete iface;
            iface = 0;
        }
        
        if (interface.isEmpty()) {
            q->setTarget(0);
            return;
        }
        
        QDBusConnection connection = (bus == DBusConnections::SystemBus) ? QDBusConnection::systemBus() 
                                                                         : QDBusConnection::sessionBus();
                                                                         
        iface = new QDBusInterface(service, path, interface, connection, q);
        q->setTarget(iface);
    }
    
    DBusConnections *q_ptr;
    
    QDBusInterface *iface;
    
    QString service;
    QString path;
    QString interface;
   
    DBusConnections::BusType bus;
    
    Q_DECLARE_PUBLIC(DBusConnections)
};

DBusConnections::DBusConnections(QObject *parent) :
    QDeclarativeConnections(parent),
    d_ptr(new DBusConnectionsPrivate(this))
{
}

DBusConnections::DBusConnections(DBusConnectionsPrivate &dd, QObject *parent) :
    QDeclarativeConnections(parent),
    d_ptr(&dd)
{
}

DBusConnections::~DBusConnections() {}

QString DBusConnections::serviceName() const {
    Q_D(const DBusConnections);

    return d->service;
}

void DBusConnections::setServiceName(const QString &name) {
    if (name != this->serviceName()) {
        Q_D(DBusConnections);
        d->service = name;
        d->setTarget();
        emit serviceNameChanged();
    }
}

QString DBusConnections::path() const {
    Q_D(const DBusConnections);

    return d->path;
}

void DBusConnections::setPath(const QString &path) {
    if (path != this->path()) {
        Q_D(DBusConnections);
        d->path = path;
        d->setTarget();
        emit pathChanged();
    }
}

QString DBusConnections::interfaceName() const {
    Q_D(const DBusConnections);

    return d->interface;
}

void DBusConnections::setInterfaceName(const QString &name) {
    if (name != this->interfaceName()) {
        Q_D(DBusConnections);
        d->interface = name;
        d->setTarget();
        emit interfaceNameChanged();
    }
}


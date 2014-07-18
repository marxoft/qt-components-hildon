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

#include "dbusadaptor_p.h"
#include <QDeclarativeInfo>
#include <QDBusConnection>

class DBusAdaptorPrivate
{

public:
    DBusAdaptorPrivate(DBusAdaptor *parent) :
        q_ptr(parent),
        path("/"),
        target(0),
        complete(false)
    {
    }

    virtual ~DBusAdaptorPrivate() {}

    bool serviceRegistered() {
        return services.contains(service);
    }

    void registerService() {
        if (service.isEmpty()) {
            return;
        }

        if (!serviceRegistered()) {
            if (QDBusConnection::sessionBus().registerService(service)) {
                services[service] = 1;
            }
            else {
                Q_Q(DBusAdaptor);
                qmlInfo(q) << DBusAdaptor::tr("Cannot register service") << service;
            }
        }
        else {
            services[service]++;
        }
    }

    void unregisterService() {
        if (services[service] == 1) {
            if (QDBusConnection::sessionBus().unregisterService(service)) {
                services.remove(service);
            }
            else {
                Q_Q(DBusAdaptor);
                qmlInfo(q) << DBusAdaptor::tr("Cannot unregister service") << service;
            }
        }
        else {
            services[service]--;
        }
    }

    void registerTarget() {
        if (target) {
            if (!QDBusConnection::sessionBus().registerObject(path.isEmpty() ? "/" : path,
                                                              target,
                                                              QDBusConnection::ExportAllContents)) {

                Q_Q(DBusAdaptor);
                qmlInfo(q) << DBusAdaptor::tr("Cannot register target object");

            }
        }
    }

    void unregisterTarget() {
        if (target) {
            QDBusConnection::sessionBus().unregisterObject(path.isEmpty() ? "/" : path);
        }
    }

    static QHash<QString, int> services;

    DBusAdaptor *q_ptr;

    QString service;
    QString path;

    QObject *target;

    bool complete;

    Q_DECLARE_PUBLIC(DBusAdaptor)
};

QHash<QString, int> DBusAdaptorPrivate::services;

DBusAdaptor::DBusAdaptor(QObject *parent) :
    QObject(parent),
    d_ptr(new DBusAdaptorPrivate(this))
{
}

DBusAdaptor::DBusAdaptor(DBusAdaptorPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

DBusAdaptor::~DBusAdaptor() {
    Q_D(DBusAdaptor);

    d->unregisterTarget();
    d->unregisterService();
}

QString DBusAdaptor::serviceName() const {
    Q_D(const DBusAdaptor);

    return d->service;
}

void DBusAdaptor::setServiceName(const QString &name) {
    Q_D(DBusAdaptor);

    if (!d->complete) {
        d->service = name;
    }
    else {
        qmlInfo(this) << tr("Service name can only be set during initialisation");
    }
}

QString DBusAdaptor::path() const {
    Q_D(const DBusAdaptor);

    return d->path;
}

void DBusAdaptor::setPath(const QString &path) {
    Q_D(DBusAdaptor);

    if (!d->complete) {
        d->path = path;
    }
    else {
        qmlInfo(this) << tr("Path can only be set during initialisation");
    }
}

QObject* DBusAdaptor::target() const {
    Q_D(const DBusAdaptor);

    return d->target;
}

void DBusAdaptor::setTarget(QObject *obj) {
    if (obj != this->target()) {
        Q_D(DBusAdaptor);

        if (d->complete) {
            d->unregisterTarget();
            d->target = obj;
            d->registerTarget();

            emit targetChanged();
        }
    }
}

void DBusAdaptor::classBegin() {}

void DBusAdaptor::componentComplete() {
    Q_D(DBusAdaptor);

    d->complete = true;

    d->registerService();
    d->registerTarget();
}

#include "moc_dbusadaptor_p.cpp"

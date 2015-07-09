/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchdbusadaptor.h"
#include <QDeclarativeInfo>
#include <QDBusConnection>

class QchDBusAdaptorPrivate
{

public:
    QchDBusAdaptorPrivate(QchDBusAdaptor *parent) :
        q_ptr(parent),
        bus(QchDBusAdaptor::SessionBus),
        path("/"),
        target(0),
        complete(false)
    {
    }

    virtual ~QchDBusAdaptorPrivate() {}

    bool serviceRegistered() {
        return services.contains(service);
    }

    void registerService() {
        if (service.isEmpty()) {
            return;
        }

        if (!serviceRegistered()) {
            QDBusConnection connection = (bus == QchDBusAdaptor::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (connection.registerService(service)) {
                services[service] = 1;
            }
            else {
                Q_Q(QchDBusAdaptor);
                qmlInfo(q) << QchDBusAdaptor::tr("Cannot register service %1").arg(service);
            }
        }
        else {
            services[service]++;
        }
    }

    void unregisterService() {
        if (services[service] == 1) {
            QDBusConnection connection = (bus == QchDBusAdaptor::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (connection.unregisterService(service)) {
                services.remove(service);
            }
            else {
                Q_Q(QchDBusAdaptor);
                qmlInfo(q) << QchDBusAdaptor::tr("Cannot unregister service %1").arg(service);
            }
        }
        else {
            services[service]--;
        }
    }

    void registerTarget() {
        if (target) {
            QDBusConnection connection = (bus == QchDBusAdaptor::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (!connection.registerObject(path.isEmpty() ? "/" : path,
                                                              target,
                                                              QDBusConnection::ExportAllContents)) {

                Q_Q(QchDBusAdaptor);
                qmlInfo(q) << QchDBusAdaptor::tr("Cannot register target object");

            }
        }
    }

    void unregisterTarget() {
        if (target) {
            QDBusConnection connection = (bus == QchDBusAdaptor::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());
            connection.unregisterObject(path.isEmpty() ? "/" : path);
        }
    }

    static QHash<QString, int> services;

    QchDBusAdaptor *q_ptr;

    QchDBusAdaptor::BusType bus;

    QString service;
    QString path;

    QObject *target;

    bool complete;

    Q_DECLARE_PUBLIC(QchDBusAdaptor)
};

QHash<QString, int> QchDBusAdaptorPrivate::services;

QchDBusAdaptor::QchDBusAdaptor(QObject *parent) :
    QObject(parent),
    d_ptr(new QchDBusAdaptorPrivate(this))
{
}

QchDBusAdaptor::QchDBusAdaptor(QchDBusAdaptorPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

QchDBusAdaptor::~QchDBusAdaptor() {
    Q_D(QchDBusAdaptor);

    d->unregisterTarget();
    d->unregisterService();
}

QchDBusAdaptor::BusType QchDBusAdaptor::bus() const {
    Q_D(const QchDBusAdaptor);

    return d->bus;
}

void QchDBusAdaptor::setBus(BusType bus) {
    Q_D(QchDBusAdaptor);

    if (!d->complete) {
        d->bus = bus;
        emit busChanged();
    }
    else {
        qmlInfo(this) << tr("Bus can only be set during initialisation");
    }
}

QString QchDBusAdaptor::serviceName() const {
    Q_D(const QchDBusAdaptor);

    return d->service;
}

void QchDBusAdaptor::setServiceName(const QString &name) {
    Q_D(QchDBusAdaptor);

    if (!d->complete) {
        d->service = name;
        emit serviceNameChanged();
    }
    else {
        qmlInfo(this) << tr("Service name can only be set during initialisation");
    }
}

QString QchDBusAdaptor::path() const {
    Q_D(const QchDBusAdaptor);

    return d->path;
}

void QchDBusAdaptor::setPath(const QString &path) {
    Q_D(QchDBusAdaptor);

    if (!d->complete) {
        d->path = path;
        emit pathChanged();
    }
    else {
        qmlInfo(this) << tr("Path can only be set during initialisation");
    }
}

QObject* QchDBusAdaptor::target() const {
    Q_D(const QchDBusAdaptor);

    return d->target;
}

void QchDBusAdaptor::setTarget(QObject *obj) {
    if (obj != target()) {
        Q_D(QchDBusAdaptor);
        d->unregisterTarget();
        d->target = obj;
        emit targetChanged();

        if (d->complete) {
            d->registerTarget();
        }
    }
}

void QchDBusAdaptor::classBegin() {}

void QchDBusAdaptor::componentComplete() {
    Q_D(QchDBusAdaptor);

    d->complete = true;

    d->registerService();
    d->registerTarget();
}

#include "moc_qchdbusadaptor.cpp"

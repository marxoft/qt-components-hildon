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

#include "qchdbusconnections.h"
#include "qchdbusutils.h"
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDeclarativeInfo>
#include <QMetaMethod>
#include <QMetaObject>

class QchDBusConnectionsPrivate
{

public:
    QchDBusConnectionsPrivate(QchDBusConnections *parent) :
        q_ptr(parent),
        bus(QchDBus::SessionBus),
        complete(false),
        enabled(true)
    {
    }
    
    ~QchDBusConnectionsPrivate() {
        clearSignals();
    }
        
    void getSignals() {
        if ((!complete) || (service.isEmpty()) || (interface.isEmpty())) {
            return;
        }
                
        Q_Q(QchDBusConnections);
        QDBusConnection connection = QchDBus::connection(bus);
        QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
        QList<QByteArray> signalNames = QchDBusUtils::getSignalNames(iface);
        
        if (signalNames.isEmpty()) {
            qmlInfo(q) << QchDBusConnections::tr("No signals found");
            return;
        }
        
        const QMetaObject *mo = q->metaObject();
        
        for (int i = QchDBusConnections::staticMetaObject.methodCount(); i < mo->methodCount(); i++) {
            const QMetaMethod method = mo->method(i);
            const QByteArray signature = method.signature();
            QByteArray name = signature.left(signature.indexOf('('));
            
            if (!signalNames.contains(name)) {
                name = name.left(1).toUpper() + name.mid(1);
                
                if (!signalNames.contains(name)) {
                    continue;
                }
            }
            
            dynamicSignals[QString::fromUtf8(name)] = method.methodIndex();
        }
    }
    
    void connectSignals() {
        if (dynamicSignals.isEmpty()) {
            return;
        }
                
        Q_Q(QchDBusConnections);
        QDBusConnection connection = QchDBus::connection(bus);
        
        foreach (const QString &dynamicSignal, dynamicSignals.keys()) {
            if (!connection.connect(service, path.isEmpty() ? "/" : path, interface, dynamicSignal, q,
                                    SLOT(_q_handleSignal(QDBusMessage)))) {
                qmlInfo(q) << QchDBusConnections::tr("Cannot connect to signal %1").arg(dynamicSignal);
            }
        }
    }
    
    void disconnectSignals() {
        if (dynamicSignals.isEmpty()) {
            return;
        }
                        
        Q_Q(QchDBusConnections);
        QDBusConnection connection = QchDBus::connection(bus);
        
        foreach (const QString &dynamicSignal, dynamicSignals.keys()) {
            connection.disconnect(service, path.isEmpty() ? "/" : path, interface, dynamicSignal, q,
                                  SLOT(_q_handleSignal(QDBusMessage)));
        }
    }
    
    void clearSignals() {
        disconnectSignals();
        dynamicSignals.clear();
    }
        
    void _q_handleSignal(const QDBusMessage &message) {        
        if (!dynamicSignals.contains(message.member())) {
            return;
        }
        
        Q_Q(QchDBusConnections);
        QVariantList arguments;
        
        foreach (const QVariant &argument, message.arguments()) {
            if (argument.canConvert<QDBusArgument>()) {
                arguments << QchDBusUtils::dbusArgumentToVariant(argument.value<QDBusArgument>());
            }
            else {
                arguments << argument;
            }
        }
        
        QGenericArgument args[10];
        
        for (int i = 0; i < qMin(arguments.size(), 10); i++) {
            const QVariant &arg = arguments.at(i);
            args[i] = Q_ARG(QVariant, arg);
        }
        
        const QMetaMethod &method = q->metaObject()->method(dynamicSignals.value(message.member()));
        method.invoke(q, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);      
    }
    
    QchDBusConnections *q_ptr;
    
    QchDBus::BusType bus;
    
    QString interface;
    QString path;
    QString service;
    
    QHash<QString, int> dynamicSignals;
        
    bool complete;
    bool enabled;
        
    Q_DECLARE_PUBLIC(QchDBusConnections);
};

/*!
    \class DBusConnections
    \brief Establishes connections to signals via DBus.
    
    \ingroup dbus
    
    \snippet dbus.qml DBusConnection
    
    \sa DBusMessage
*/
QchDBusConnections::QchDBusConnections(QObject *parent) :
    QObject(parent),
    d_ptr(new QchDBusConnectionsPrivate(this))
{
}

QchDBusConnections::QchDBusConnections(QchDBusConnectionsPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

QchDBusConnections::~QchDBusConnections() {}

/*!
    \brief The bus on which the signal connections should be established.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>DBus.SessionBus</td>
            <td>Send the message on the session bus (default).</td>
        </tr>
        <tr>
            <td>DBus.SystemBus</td>
            <td>Send the message on the system bus.</td>
        </tr>
    </table>
*/
QchDBus::BusType QchDBusConnections::bus() const {
    Q_D(const QchDBusConnections);
    return d->bus;
}

void QchDBusConnections::setBus(QchDBus::BusType b) {
    if (b != bus()) {
        Q_D(QchDBusConnections);
        d->bus = b;
        emit busChanged();
        
        if (d->complete) {
            d->clearSignals();
            d->getSignals();
            
            if (d->enabled) {
                d->connectSignals();
            }
        }
    }
}

/*!
    \brief Whether signal connections are enabled.
    
    The default value is \c true.
*/
bool QchDBusConnections::isEnabled() const {
    Q_D(const QchDBusConnections);
    return d->enabled;
}

void QchDBusConnections::setEnabled(bool enabled) {
    if (enabled != isEnabled()) {
        Q_D(QchDBusConnections);
        d->enabled = enabled;
        emit enabledChanged();
        
        if (d->complete) {
            if (enabled) {
                d->connectSignals();
            }
            else {
                d->disconnectSignals();
            }
        }
    }
}

/*!
    \brief The interface on which the signal connections should be established.
*/
QString QchDBusConnections::interfaceName() const {
    Q_D(const QchDBusConnections);
    return d->interface;
}

void QchDBusConnections::setInterfaceName(const QString &name) {
    if (name != interfaceName()) {
        Q_D(QchDBusConnections);
        d->interface = name;
        emit interfaceNameChanged();
        
        if (d->complete) {
            d->clearSignals();
            d->getSignals();
            
            if (d->enabled) {
                d->connectSignals();
            }
        }
    }
}

/*!
    \brief The path on which the signal connections should be established.
*/
QString QchDBusConnections::path() const {
    Q_D(const QchDBusConnections);
    return d->path;
}

void QchDBusConnections::setPath(const QString &p) {
    if (p != path()) {
        Q_D(QchDBusConnections);
        d->path = p;
        emit pathChanged();
        
        if (d->complete) {
            d->clearSignals();
            d->getSignals();
            
            if (d->enabled) {
                d->connectSignals();
            }
        }
    }
}

/*!
    \brief The service on which the signal connections should be established.
*/
QString QchDBusConnections::serviceName() const {
    Q_D(const QchDBusConnections);
    return d->service;
}

void QchDBusConnections::setServiceName(const QString &name) {
    if (name != serviceName()) {
        Q_D(QchDBusConnections);
        d->service = name;
        emit serviceNameChanged();
        
        if (d->complete) {
            d->clearSignals();
            d->getSignals();
            
            if (d->enabled) {
                d->connectSignals();
            }
        }
    }
}

void QchDBusConnections::classBegin() {}

void QchDBusConnections::componentComplete() {
    Q_D(QchDBusConnections);
    d->complete = true;
    d->getSignals();
    
    if (d->enabled) {
        d->connectSignals();
    }
}

#include "moc_qchdbusconnections.cpp"

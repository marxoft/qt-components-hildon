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

#include "dbusmessage_p.h"
#include "dbusutils_p.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDeclarativeInfo>

class DBusMessagePrivate
{

public:
    DBusMessagePrivate(DBusMessage *parent) :
        q_ptr(parent),
        path("/"),
        bus(DBusMessage::SessionBus),
        type(DBusMessage::MethodCallMessage),
        status(DBusMessage::Null)
    {
    }

    virtual ~DBusMessagePrivate() {}

    void callMethod() {
        Q_Q(DBusMessage);

        if ((service.isEmpty()) || (method.isEmpty())) {
            status = DBusMessage::Error;
            qmlInfo(q) << DBusMessage::tr("Cannot send message. Missing parameters.");
        }
        else {
            status = DBusMessage::Loading;
            QDBusMessage message = QDBusMessage::createMethodCall(service, path.isEmpty() ? "/" : path, interface, method);
            QDBusConnection connection = (bus == DBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (!arguments.isEmpty()) {
                if (convertedArguments.isEmpty()) {
                    QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                    convertedArguments = DBusUtils::convertMethodCallArguments(iface, arguments);
                }

                message.setArguments(convertedArguments);
            }

            if (!connection.callWithCallback(message, q, SLOT(_q_onReplyFinished(QDBusMessage)), SLOT(_q_onReplyError(QDBusError)))) {
                status = DBusMessage::Error;
                qmlInfo(q) << DBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void emitSignal() {
        Q_Q(DBusMessage);

        if ((path.isEmpty()) || (method.isEmpty())) {
            status = DBusMessage::Error;
            qmlInfo(q) << DBusMessage::tr("Cannot send message. Missing parameters.");
        }
        else {
            QDBusMessage message = QDBusMessage::createSignal(path, interface, method);
            QDBusConnection connection = (bus == DBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (!arguments.isEmpty()) {
                if (convertedArguments.isEmpty()) {
                    QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                    convertedArguments = DBusUtils::convertMethodCallArguments(iface, arguments);
                }

                message.setArguments(convertedArguments);
            }

            if (connection.send(message)) {
                status = DBusMessage::Ready;
            }
            else {
                status = DBusMessage::Error;
                qmlInfo(q) << DBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void sendReply() {
        Q_Q(DBusMessage);

        QDBusMessage message;
        QDBusConnection connection = (bus == DBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

        if (!arguments.isEmpty()) {
            if (convertedArguments.isEmpty()) {
                QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                convertedArguments = DBusUtils::convertMethodCallArguments(iface, arguments);
            }

            message.setArguments(convertedArguments);
        }

        if (connection.send(message)) {
            status = DBusMessage::Ready;
        }
        else {
            status = DBusMessage::Error;
            qmlInfo(q) << DBusMessage::tr("Cannot send message.");
        }

        emit q->statusChanged();
    }

    void sendError() {
        Q_Q(DBusMessage);

        if (arguments.count() < 2) {
            status = DBusMessage::Error;
            qmlInfo(q) << DBusMessage::tr("Cannot send message. Insufficient parameters.");
        }
        else {
            QDBusMessage message = QDBusMessage::createError(arguments.first().toString(), arguments.at(1).toString());
            QDBusConnection connection = (bus == DBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (connection.send(message)) {
                status = DBusMessage::Ready;
            }
            else {
                status = DBusMessage::Error;
                qmlInfo(q) << DBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void _q_onReplyFinished(const QDBusMessage &replyMessage) {
        QVariantList list;

        foreach (QVariant arg, replyMessage.arguments()) {
            if (arg.canConvert<QDBusArgument>()) {
                list.append(DBusUtils::dbusArgumentToVariant(arg.value<QDBusArgument>()));
            }
            else {
                list.append(arg);
            }
        }

        if (list.size() == 1) {
            reply = list.first();
        }
        else {
            reply = list;
        }

        Q_Q(DBusMessage);
        status = DBusMessage::Ready;
        emit q->statusChanged();
    }

    void _q_onReplyError(const QDBusError &error) {
        Q_Q(DBusMessage);
        status = DBusMessage::Error;
        qmlInfo(q) << DBusMessage::tr("Error received: ") << error.message();
        emit q->statusChanged();
    }

    DBusMessage *q_ptr;

    QString service;
    QString path;
    QString interface;
    QString method;

    QVariantList arguments;
    QVariantList convertedArguments;

    DBusMessage::BusType bus;

    DBusMessage::MessageType type;

    DBusMessage::Status status;

    QVariant reply;

    Q_DECLARE_PUBLIC(DBusMessage)
};

DBusMessage::DBusMessage(QObject *parent) :
    QObject(parent),
    d_ptr(new DBusMessagePrivate(this))
{
}

DBusMessage::DBusMessage(DBusMessagePrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

DBusMessage::~DBusMessage() {}

QString DBusMessage::serviceName() const {
    Q_D(const DBusMessage);

    return d->service;
}

void DBusMessage::setServiceName(const QString &name) {
    if (name != this->serviceName()) {
        Q_D(DBusMessage);
        d->service = name;
        d->convertedArguments.clear();
        emit serviceNameChanged();
    }
}

QString DBusMessage::path() const {
    Q_D(const DBusMessage);

    return d->path;
}

void DBusMessage::setPath(const QString &path) {
    if (path != this->path()) {
        Q_D(DBusMessage);
        d->path = path;
        d->convertedArguments.clear();
        emit pathChanged();
    }
}

QString DBusMessage::interfaceName() const {
    Q_D(const DBusMessage);

    return d->interface;
}

void DBusMessage::setInterfaceName(const QString &name) {
    if (name != this->interfaceName()) {
        Q_D(DBusMessage);
        d->interface = name;
        d->convertedArguments.clear();
        emit interfaceNameChanged();
    }
}

QString DBusMessage::methodName() const {
    Q_D(const DBusMessage);

    return d->method;
}

void DBusMessage::setMethodName(const QString &name) {
    if (name != this->methodName()) {
        Q_D(DBusMessage);
        d->method = name;
        d->convertedArguments.clear();
        emit methodNameChanged();
    }
}

QVariantList DBusMessage::arguments() const {
    Q_D(const DBusMessage);

    return d->arguments;
}

void DBusMessage::setArguments(const QVariantList &args) {
    Q_D(DBusMessage);
    d->arguments = args;
    d->convertedArguments.clear();
    emit argumentsChanged();
}

DBusMessage::BusType DBusMessage::bus() const {
    Q_D(const DBusMessage);

    return d->bus;
}

void DBusMessage::setBus(DBusMessage::BusType bus) {
    if (bus != this->bus()) {
        Q_D(DBusMessage);
        d->bus = bus;
        d->convertedArguments.clear();
        emit busChanged();
    }
}

DBusMessage::MessageType DBusMessage::type() const {
    Q_D(const DBusMessage);

    return d->type;
}

void DBusMessage::setType(MessageType type) {
    if (type != this->type()) {
        Q_D(DBusMessage);
        d->type = type;
        d->convertedArguments.clear();
        emit typeChanged();
    }
}

DBusMessage::Status DBusMessage::status() const {
    Q_D(const DBusMessage);

    return d->status;
}

QVariant DBusMessage::reply() const {
    Q_D(const DBusMessage);

    return d->reply;
}

void DBusMessage::send() {
    Q_D(DBusMessage);

    switch (this->status()) {
    case DBusMessage::Loading:
        return;
    default:
        d->reply = QVariant();
        break;
    }

    switch (this->type()) {
    case MethodCallMessage:
        d->callMethod();
        return;
    case SignalMessage:
        d->emitSignal();
        return;
    case ReplyMessage:
        d->sendReply();
        return;
    case ErrorMessage:
        d->sendError();
        return;
    default:
        return;
    }
}

#include "moc_dbusmessage_p.cpp"

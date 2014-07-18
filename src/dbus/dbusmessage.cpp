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
#include <QDBusInterface>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDeclarativeInfo>

class DBusMessagePrivate
{

public:
    DBusMessagePrivate(DBusMessage *parent) :
        q_ptr(parent),
        path("/"),
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
            QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface);
            QDBusPendingCall call = iface.asyncCallWithArgumentList(method, arguments);
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, q);
            q->connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)), q, SLOT(_q_onReplyFinished(QDBusPendingCallWatcher*)));
        }

        emit q->statusChanged();
    }

    void emitSignal() {
        Q_Q(DBusMessage);

        if ((path.isEmpty()) || (interface.isEmpty()) || (method.isEmpty())) {
            status = DBusMessage::Error;
            qmlInfo(q) << DBusMessage::tr("Cannot send message. Missing parameters.");
        }
        else {
            QDBusMessage message = QDBusMessage::createSignal(path, interface, method);

            if (QDBusConnection::sessionBus().send(message)) {
                status = DBusMessage::Ready;
            }
            else {
                status = DBusMessage::Error;
            }
        }

        emit q->statusChanged();
    }

    void sendReply() {
        Q_Q(DBusMessage);

        QDBusMessage message;
        message.setArguments(arguments);

        if (QDBusConnection::sessionBus().send(message)) {
            status = DBusMessage::Ready;
        }
        else {
            status = DBusMessage::Error;
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

            if (QDBusConnection::sessionBus().send(message)) {
                status = DBusMessage::Ready;
            }
            else {
                status = DBusMessage::Error;
            }
        }

        emit q->statusChanged();
    }

    void _q_onReplyFinished(QDBusPendingCallWatcher *watcher) {
        Q_Q(DBusMessage);

        QDBusPendingReply<QVariant> reply = *watcher;

        if (reply.isError()) {
            status = DBusMessage::Error;
        }
        else {
            status = DBusMessage::Ready;
        }

        if (reply.count()) {
            response = reply.argumentAt(0);
        }

        emit q->statusChanged();

        watcher->deleteLater();
    }

    DBusMessage *q_ptr;

    QString service;
    QString path;
    QString interface;
    QString method;

    QVariantList arguments;

    DBusMessage::MessageType type;

    DBusMessage::Status status;

    QVariant response;

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
    emit argumentsChanged();
}

DBusMessage::MessageType DBusMessage::type() const {
    Q_D(const DBusMessage);

    return d->type;
}

void DBusMessage::setType(MessageType type) {
    if (type != this->type()) {
        Q_D(DBusMessage);
        d->type = type;
        emit typeChanged();
    }
}

DBusMessage::Status DBusMessage::status() const {
    Q_D(const DBusMessage);

    return d->status;
}

QVariant DBusMessage::response() const {
    Q_D(const DBusMessage);

    return d->response;
}

void DBusMessage::send() {
    Q_D(DBusMessage);

    switch (this->status()) {
    case DBusMessage::Loading:
        return;
    default:
        d->response = QVariant();
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

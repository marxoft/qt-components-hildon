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

#include "qchdbusmessage.h"
#include "qchdbusutils.h"
#include "qdbusutil_p.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDeclarativeInfo>

class QchDBusMessagePrivate
{

public:
    QchDBusMessagePrivate(QchDBusMessage *parent) :
        q_ptr(parent),
        path("/"),
        bus(QchDBusMessage::SessionBus),
        type(QchDBusMessage::MethodCallMessage),
        status(QchDBusMessage::Null)
    {
    }

    virtual ~QchDBusMessagePrivate() {}

    void callMethod() {
        Q_Q(QchDBusMessage);

        if ((service.isEmpty()) || (method.isEmpty())) {
            status = QchDBusMessage::Error;
            qmlInfo(q) << QchDBusMessage::tr("Cannot send message. Missing parameters.");
        }
        else {
            status = QchDBusMessage::Loading;
            QDBusMessage message = QDBusMessage::createMethodCall(service, path.isEmpty() ? "/" : path, interface, method);
            QDBusConnection connection = (bus == QchDBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (!arguments.isEmpty()) {
                if (convertedArguments.isEmpty()) {
                    QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                    convertedArguments = QchDBusUtils::convertMethodCallArguments(iface, arguments);
                }

                message.setArguments(convertedArguments);
            }

            if (!connection.callWithCallback(message, q, SLOT(_q_onReplyFinished(QDBusMessage)), SLOT(_q_onReplyError(QDBusError)))) {
                status = QchDBusMessage::Error;
                qmlInfo(q) << QchDBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void emitSignal() {
        Q_Q(QchDBusMessage);

        if ((path.isEmpty()) || (method.isEmpty())) {
            status = QchDBusMessage::Error;
            qmlInfo(q) << QchDBusMessage::tr("Cannot send message. Missing parameters.");
        }
        else {
            QDBusMessage message = QDBusMessage::createSignal(path, interface, method);
            QDBusConnection connection = (bus == QchDBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (!arguments.isEmpty()) {
                if (convertedArguments.isEmpty()) {
                    QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                    convertedArguments = QchDBusUtils::convertMethodCallArguments(iface, arguments);
                }

                message.setArguments(convertedArguments);
            }

            if (connection.send(message)) {
                status = QchDBusMessage::Ready;
            }
            else {
                status = QchDBusMessage::Error;
                qmlInfo(q) << QchDBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void sendReply() {
        Q_Q(QchDBusMessage);

        QDBusMessage message;
        QDBusConnection connection = (bus == QchDBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

        if (!arguments.isEmpty()) {
            if (convertedArguments.isEmpty()) {
                QDBusInterface iface(service, path.isEmpty() ? "/" : path, interface, connection);
                convertedArguments = QchDBusUtils::convertMethodCallArguments(iface, arguments);
            }

            message.setArguments(convertedArguments);
        }

        if (connection.send(message)) {
            status = QchDBusMessage::Ready;
        }
        else {
            status = QchDBusMessage::Error;
            qmlInfo(q) << QchDBusMessage::tr("Cannot send message.");
        }

        emit q->statusChanged();
    }

    void sendError() {
        Q_Q(QchDBusMessage);

        if (arguments.count() < 2) {
            status = QchDBusMessage::Error;
            qmlInfo(q) << QchDBusMessage::tr("Cannot send message. Insufficient parameters.");
        }
        else {
            QDBusMessage message = QDBusMessage::createError(arguments.first().toString(), arguments.at(1).toString());
            QDBusConnection connection = (bus == QchDBusMessage::SystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());

            if (connection.send(message)) {
                status = QchDBusMessage::Ready;
            }
            else {
                status = QchDBusMessage::Error;
                qmlInfo(q) << QchDBusMessage::tr("Cannot send message.");
            }
        }

        emit q->statusChanged();
    }

    void _q_onReplyFinished(const QDBusMessage &replyMessage) {
        QVariantList list;

        foreach (QVariant arg, replyMessage.arguments()) {
            if (arg.canConvert<QDBusArgument>()) {
                list.append(QchDBusUtils::dbusArgumentToVariant(arg.value<QDBusArgument>()));
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

        Q_Q(QchDBusMessage);
        status = QchDBusMessage::Ready;
        emit q->statusChanged();
    }

    void _q_onReplyError(const QDBusError &error) {
        Q_Q(QchDBusMessage);
        status = QchDBusMessage::Error;
        qmlInfo(q) << QchDBusMessage::tr("Error received: ") << error.message();
        emit q->statusChanged();
    }

    QchDBusMessage *q_ptr;

    QString service;
    QString path;
    QString interface;
    QString method;

    QVariantList arguments;
    QVariantList convertedArguments;

    QchDBusMessage::BusType bus;

    QchDBusMessage::MessageType type;

    QchDBusMessage::Status status;

    QVariant reply;

    Q_DECLARE_PUBLIC(QchDBusMessage)
};

QchDBusMessage::QchDBusMessage(QObject *parent) :
    QObject(parent),
    d_ptr(new QchDBusMessagePrivate(this))
{
}

QchDBusMessage::QchDBusMessage(QchDBusMessagePrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

QchDBusMessage::~QchDBusMessage() {}

QString QchDBusMessage::serviceName() const {
    Q_D(const QchDBusMessage);

    return d->service;
}

void QchDBusMessage::setServiceName(const QString &name) {
    if (name != serviceName()) {
        Q_D(QchDBusMessage);
        d->service = name;
        d->convertedArguments.clear();
        emit serviceNameChanged();
    }
}

QString QchDBusMessage::path() const {
    Q_D(const QchDBusMessage);

    return d->path;
}

void QchDBusMessage::setPath(const QString &path) {
    if (path != this->path()) {
        Q_D(QchDBusMessage);
        d->path = path;
        d->convertedArguments.clear();
        emit pathChanged();
    }
}

QString QchDBusMessage::interfaceName() const {
    Q_D(const QchDBusMessage);

    return d->interface;
}

void QchDBusMessage::setInterfaceName(const QString &name) {
    if (name != interfaceName()) {
        Q_D(QchDBusMessage);
        d->interface = name;
        d->convertedArguments.clear();
        emit interfaceNameChanged();
    }
}

QString QchDBusMessage::methodName() const {
    Q_D(const QchDBusMessage);

    return d->method;
}

void QchDBusMessage::setMethodName(const QString &name) {
    if (name != methodName()) {
        Q_D(QchDBusMessage);
        d->method = name;
        d->convertedArguments.clear();
        emit methodNameChanged();
    }
}

QVariantList QchDBusMessage::arguments() const {
    Q_D(const QchDBusMessage);

    return d->arguments;
}

void QchDBusMessage::setArguments(const QVariantList &args) {
    Q_D(QchDBusMessage);
    d->arguments = args;
    d->convertedArguments.clear();
    emit argumentsChanged();
}

QchDBusMessage::BusType QchDBusMessage::bus() const {
    Q_D(const QchDBusMessage);

    return d->bus;
}

void QchDBusMessage::setBus(QchDBusMessage::BusType bus) {
    if (bus != this->bus()) {
        Q_D(QchDBusMessage);
        d->bus = bus;
        d->convertedArguments.clear();
        emit busChanged();
    }
}

QchDBusMessage::MessageType QchDBusMessage::type() const {
    Q_D(const QchDBusMessage);

    return d->type;
}

void QchDBusMessage::setType(MessageType type) {
    if (type != this->type()) {
        Q_D(QchDBusMessage);
        d->type = type;
        d->convertedArguments.clear();
        emit typeChanged();
    }
}

QchDBusMessage::Status QchDBusMessage::status() const {
    Q_D(const QchDBusMessage);

    return d->status;
}

QVariant QchDBusMessage::reply() const {
    Q_D(const QchDBusMessage);

    return d->reply;
}

QString QchDBusMessage::replyString() const {
    return QDBusUtil::argumentToString(reply());
}

void QchDBusMessage::send() {
    Q_D(QchDBusMessage);

    switch (status()) {
    case QchDBusMessage::Loading:
        return;
    default:
        d->reply = QVariant();
        break;
    }

    switch (type()) {
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

#include "moc_qchdbusmessage.cpp"

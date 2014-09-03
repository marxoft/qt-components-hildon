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

#ifndef DBUSMESSAGE_P_H
#define DBUSMESSAGE_P_H

#include <QObject>
#include <qdeclarative.h>

class QDBusMessage;
class QDBusError;
class DBusMessagePrivate;

class DBusMessage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString interfaceName READ interfaceName WRITE setInterfaceName NOTIFY interfaceNameChanged)
    Q_PROPERTY(QString methodName READ methodName WRITE setMethodName NOTIFY methodNameChanged)
    Q_PROPERTY(QVariantList arguments READ arguments WRITE setArguments NOTIFY argumentsChanged)
    Q_PROPERTY(BusType bus READ bus WRITE setBus NOTIFY busChanged)
    Q_PROPERTY(MessageType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QVariant reply READ reply NOTIFY statusChanged)
    Q_PROPERTY(QString replyString READ replyString NOTIFY statusChanged)

    Q_ENUMS(BusType MessageType Status)

public:
    enum BusType {
        SessionBus = 0,
        SystemBus
    };

    enum MessageType {
        MethodCallMessage = 0,
        SignalMessage,
        ReplyMessage,
        ErrorMessage
    };

    enum Status {
        Null = 0,
        Loading,
        Ready,
        Error
    };

    explicit DBusMessage(QObject *parent = 0);
    ~DBusMessage();

    QString serviceName() const;
    void setServiceName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    QString interfaceName() const;
    void setInterfaceName(const QString &name);

    QString methodName() const;
    void setMethodName(const QString &name);

    QVariantList arguments() const;
    void setArguments(const QVariantList &args);

    BusType bus() const;
    void setBus(BusType bus);

    MessageType type() const;
    void setType(MessageType type);

    Status status() const;

    QVariant reply() const;
    QString replyString() const;

public slots:
    void send();

signals:
    void serviceNameChanged();
    void pathChanged();
    void interfaceNameChanged();
    void methodNameChanged();
    void argumentsChanged();
    void busChanged();
    void typeChanged();
    void statusChanged();

protected:
    DBusMessage(DBusMessagePrivate &dd, QObject *parent = 0);

    QScopedPointer<DBusMessagePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DBusMessage)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished(QDBusMessage))
    Q_PRIVATE_SLOT(d_func(), void _q_onReplyError(QDBusError))

private:
    Q_DISABLE_COPY(DBusMessage)
};

QML_DECLARE_TYPE(DBusMessage)

#endif // DBUSMESSAGE_P_H

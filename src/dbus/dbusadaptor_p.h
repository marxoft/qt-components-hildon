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

#ifndef DBUSADAPTOR_P_H
#define DBUSADAPTOR_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class DBusAdaptorPrivate;

class DBusAdaptor : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(BusType bus READ bus WRITE setBus NOTIFY busChanged)
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged)

    Q_ENUMS(BusType)

    Q_INTERFACES(QDeclarativeParserStatus)

public:
    enum BusType {
        SessionBus = 0,
        SystemBus
    };

    explicit DBusAdaptor(QObject *parent = 0);
    ~DBusAdaptor();

    BusType bus() const;
    void setBus(BusType bus);

    QString serviceName() const;
    void setServiceName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    QObject* target() const;
    void setTarget(QObject *obj);
    void resetTarget();

signals:
    void busChanged();
    void serviceNameChanged();
    void pathChanged();
    void targetChanged();

protected:
    DBusAdaptor(DBusAdaptorPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<DBusAdaptorPrivate> d_ptr;

    Q_DECLARE_PRIVATE(DBusAdaptor)

private:
    Q_DISABLE_COPY(DBusAdaptor)
};

QML_DECLARE_TYPE(DBusAdaptor)

#endif // DBUSADAPTOR_P_H

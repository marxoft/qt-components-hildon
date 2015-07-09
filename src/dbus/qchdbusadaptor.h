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

#ifndef QCHDBUSADAPTOR_H
#define QCHDBUSADAPTOR_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchDBusAdaptorPrivate;

class QchDBusAdaptor : public QObject, public QDeclarativeParserStatus
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

    explicit QchDBusAdaptor(QObject *parent = 0);
    ~QchDBusAdaptor();

    BusType bus() const;
    void setBus(BusType bus);

    QString serviceName() const;
    void setServiceName(const QString &name);

    QString path() const;
    void setPath(const QString &path);

    QObject* target() const;
    void setTarget(QObject *obj);
    void resetTarget();

Q_SIGNALS:
    void busChanged();
    void serviceNameChanged();
    void pathChanged();
    void targetChanged();

protected:
    QchDBusAdaptor(QchDBusAdaptorPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<QchDBusAdaptorPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchDBusAdaptor)

private:
    Q_DISABLE_COPY(QchDBusAdaptor)
};

QML_DECLARE_TYPE(QchDBusAdaptor)

#endif // QCHDBUSADAPTOR_H

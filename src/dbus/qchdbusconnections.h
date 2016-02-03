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

#ifndef QCHDBUSCONNECTIONS_H
#define QCHDBUSCONNECTIONS_H

#include "qchdbus.h"
#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDBusMessage;
class QchDBusConnectionsPrivate;
    
class QchDBusConnections : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QchDBus::BusType bus READ bus WRITE setBus NOTIFY busChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString interfaceName READ interfaceName WRITE setInterfaceName NOTIFY interfaceNameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit QchDBusConnections(QObject *parent = 0);
    ~QchDBusConnections();
    
    QchDBus::BusType bus() const;
    void setBus(QchDBus::BusType b);
    
    bool isEnabled() const;
    void setEnabled(bool enabled);
    
    QString interfaceName() const;
    void setInterfaceName(const QString &name);
    
    QString path() const;
    void setPath(const QString &path);
    
    QString serviceName() const;
    void setServiceName(const QString &name);
        
Q_SIGNALS:
    void busChanged();
    void enabledChanged();
    void interfaceNameChanged();
    void pathChanged();
    void serviceNameChanged();

protected:
    QchDBusConnections(QchDBusConnectionsPrivate &dd, QObject *parent = 0);
    
    virtual void classBegin();
    virtual void componentComplete();
        
    QScopedPointer<QchDBusConnectionsPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchDBusConnections)
    
    Q_PRIVATE_SLOT(d_func(), void _q_handleSignal(QDBusMessage))
    
private:
    Q_DISABLE_COPY(QchDBusConnections)
};

QML_DECLARE_TYPE(QchDBusConnections)

#endif // QCHDBUSCONNECTIONS_H

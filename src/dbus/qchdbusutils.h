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

#ifndef QCHDBUSUTILS_H
#define QCHDBUSUTILS_H

#include <QVariantList>
#include <QMetaType>

class QDBusInterface;
class QDBusArgument;

struct QchDBusMethod {
    QByteArray methodName;
    QList<QByteArray> parameterNames;
    
    QchDBusMethod(const QByteArray &name, const QList<QByteArray> &params) :
        methodName(name),
        parameterNames(params)
    {
    }
};

class QchDBusUtils
{

public:
    static QVariantList convertMethodCallArguments(const QDBusInterface &iface, const QString &methodName,
                                                   const QVariantList &arguments);
    
    static QList<QchDBusMethod> getSignals(const QDBusInterface &iface);
    static QList<QByteArray> getSignalNames(const QDBusInterface &iface);
            
    static QVariant dbusArgumentToVariant(const QDBusArgument &argument);

private:    
    static QVariant basicTypeToVariant(const QDBusArgument &arg);
    static QVariant arrayTypeToVariant(const QDBusArgument &arg);
    static QVariant mapTypeToVariant(const QDBusArgument &arg);
    static QVariant structureTypeToVariant(const QDBusArgument &arg);
};

Q_DECLARE_METATYPE(QList<bool>)
Q_DECLARE_METATYPE(QList<double>)
Q_DECLARE_METATYPE(QList<int>)

#endif // QCHDBUSUTILS_H

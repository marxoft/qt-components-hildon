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

#ifndef QCHDBUSUTILS_H
#define QCHDBUSUTILS_H

#include <QVariantList>

class QDBusInterface;
class QDBusArgument;

class QchDBusUtils
{

public:
    static QVariantList convertMethodCallArguments(const QDBusInterface &iface, const QVariantList &arguments);
    static QVariant dbusArgumentToVariant(const QDBusArgument &arg);

private:
    static QVariant basicTypeToVariant(const QDBusArgument &arg);
    static QVariant arrayTypeToVariant(const QDBusArgument &arg);
    static QVariant mapTypeToVariant(const QDBusArgument &arg);
};

#endif // QCHDBUSUTILS_H

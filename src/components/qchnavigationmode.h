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

#ifndef QCHNAVIGATIONMODE_H
#define QCHNAVIGATIONMODE_H

#include <QObject>
#include <qdeclarative.h>

class QchNavigationMode : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(NavigationMode)

public:
    enum NavigationMode {
        TouchNavigation = 0,
        KeyNavigation
    };

private:
    QchNavigationMode() : QObject() {}
};

QML_DECLARE_TYPE(QchNavigationMode)

#endif // QCHNAVIGATIONMODE_H

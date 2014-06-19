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

#ifndef ACTIONGROUP_P_H
#define ACTIONGROUP_P_H

#include <QActionGroup>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class ActionGroupPrivate;

class ActionGroup : public QActionGroup, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PRIVATE_PROPERTY(ActionGroup::d_func(), QDeclarativeListProperty<QObject> data READ data)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ActionGroup(QObject *parent = 0);
    ~ActionGroup();

private:
    ActionGroup(ActionGroupPrivate &dd, QObject *parent = 0);

    void classBegin();
    void componentComplete();

    QScopedPointer<ActionGroupPrivate> d_ptr;

    Q_DISABLE_COPY(ActionGroup)
    Q_DECLARE_PRIVATE(ActionGroup)
};

QML_DECLARE_TYPE(ActionGroup)

#endif // ACTIONGROUP_P_H

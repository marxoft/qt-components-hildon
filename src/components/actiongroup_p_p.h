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

#ifndef ACTIONGROUP_P_P_H
#define ACTIONGROUP_P_P_H

#include "actiongroup_p.h"

class ActionGroupPrivate
{

public:
    ActionGroupPrivate(ActionGroup *parent) :
        q_ptr(parent),
        complete(false)
    {
    }

    virtual ~ActionGroupPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    void componentComplete();

    ActionGroup *q_ptr;

    bool complete;

    QList<QObject*> dataList;

    Q_DECLARE_PUBLIC(ActionGroup)
};

#endif // ACTIONGROUP_P_P_H

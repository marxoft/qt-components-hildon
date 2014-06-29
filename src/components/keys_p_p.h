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

#ifndef KEYS_P_P_H
#define KEYS_P_P_H

#include "keys_p.h"

class KeysPrivate
{

public:
    KeysPrivate(Keys *parent) :
        q_ptr(parent),
        enabled(true),
        priority(Keys::BeforeItem)
    {
    }

    virtual ~KeysPrivate() {}

    static void forwardto_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> forwardTo();

    Keys *q_ptr;

    bool enabled;

    Keys::Priority priority;

    QList<QObject*> forwardtoList;

    Q_DECLARE_PUBLIC(Keys)
};

#endif // KEYS_P_P_H

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

#ifndef VALUESELECTOR_P_P_H
#define VALUESELECTOR_P_P_H

#include "valueselector_p.h"
#include <QMaemo5AbstractPickSelector>

class ValueSelectorPrivate
{

public:
    ValueSelectorPrivate(ValueSelector *parent) :
        q_ptr(parent),
        selector(0)
    {
    }

    virtual ~ValueSelectorPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    ValueSelector *q_ptr;

    QMaemo5AbstractPickSelector *selector;

    QList<QObject*> dataList;

    Q_DECLARE_PUBLIC(ValueSelector)
};

#endif // VALUESELECTOR_P_P_H

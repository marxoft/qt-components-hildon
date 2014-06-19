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

#include "valueselector_p.h"
#include "valueselector_p_p.h"

ValueSelector::ValueSelector(QObject *parent) :
    QObject(parent),
    d_ptr(new ValueSelectorPrivate(this))
{
}

ValueSelector::ValueSelector(ValueSelectorPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

ValueSelector::~ValueSelector() {}

void ValueSelector::classBegin() {}

void ValueSelector::componentComplete() {}

void ValueSelectorPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ValueSelector *selector = qobject_cast<ValueSelector*>(obj)) {
        selector->d_func()->dataList.append(obj);
    }
}

QDeclarativeListProperty<QObject> ValueSelectorPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ValueSelectorPrivate::data_append);
}

#include "moc_valueselector_p.cpp"

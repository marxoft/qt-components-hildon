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

#ifndef TEXTFIELD_P_P_H
#define TEXTFIELD_P_P_H

#include "item_p_p.h"
#include "textfield_p.h"

class TextFieldPrivate : public ItemPrivate
{

public:
    TextFieldPrivate(TextField *parent) :
        ItemPrivate(parent),
        val(0)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QObject> actions();

    QValidator* validator() const;
    void setValidator(QValidator *v);

    QValidator *val;

    Q_DECLARE_PUBLIC(TextField)
};

#endif // TEXTFIELD_P_P_H

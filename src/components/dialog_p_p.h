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

#ifndef DIALOG_P_P_H
#define DIALOG_P_P_H

#include "item_p_p.h"
#include "dialog_p.h"
#include <QGridLayout>
#include <QDialogButtonBox>

class DialogPrivate : public ItemPrivate
{

public:
    DialogPrivate(Dialog *parent) :
        ItemPrivate(parent),
        contentItem(0),
        grid(0),
        buttonBox(0)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void content_append(QDeclarativeListProperty<QWidget> *list, QWidget *obj);

    static void buttons_append(QDeclarativeListProperty<QAbstractButton> *list, QAbstractButton *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    QDeclarativeListProperty<QObject> actions();

    QDeclarativeListProperty<QWidget> content();

    QDeclarativeListProperty<QAbstractButton> buttons();

    void _q_onOrientationChanged(Screen::Orientation orientation);

    Item *contentItem;

    QGridLayout *grid;

    QDialogButtonBox *buttonBox;

    QList<QWidget*> contentList;

    QList<QAbstractButton*> buttonList;

    Q_DECLARE_PUBLIC(Dialog)
};

#endif // DIALOG_P_P_H

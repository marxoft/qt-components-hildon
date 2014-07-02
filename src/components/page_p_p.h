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

#ifndef PAGE_P_P_H
#define PAGE_P_P_H

#include "item_p_p.h"
#include "page_p.h"

class PagePrivate : ItemPrivate
{

public:
    PagePrivate(Page *parent) :
        ItemPrivate(parent),
        orientation(Screen::LandscapeOrientation)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void tools_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    QDeclarativeListProperty<QObject> actions();

    QDeclarativeListProperty<QObject> tools();

    void componentComplete();

    Screen::Orientation orientation;

    QList<QObject*> toolList;

    Q_DECLARE_PUBLIC(Page)
};

#endif // PAGE_P_P_H

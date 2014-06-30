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

#ifndef GRID_P_P_H
#define GRID_P_P_H

#include "item_p_p.h"
#include "grid_p.h"

class QGridLayout;

class GridPrivate : public ItemPrivate
{

public:
    GridPrivate(Grid *parent) : ItemPrivate(parent) {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    void clearGrid();
    void loadGrid();
    void addWidgetToGrid(QWidget *widget);

    QGridLayout *grid;

    int columns;

    QHash<int, int> gridMap;

    Q_DECLARE_PUBLIC(Grid)
};

#endif // GRID_P_P_H

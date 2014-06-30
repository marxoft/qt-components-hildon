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

#include "grid_p.h"
#include "grid_p_p.h"
#include <QGridLayout>

Grid::Grid(QWidget *parent) :
    Item(*new GridPrivate(this), parent)
{
    Q_D(Grid);

    d->grid = new QGridLayout(this);
    d->grid->setContentsMargins(0, 0, 0, 0);
    d->grid->setAlignment(Qt::AlignTop);
    d->columns = 0;
}

Grid::Grid(GridPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(Grid);

    if (!d->grid) {
        d->grid = new QGridLayout(this);
        d->grid->setContentsMargins(0, 0, 0, 0);
        d->grid->setAlignment(Qt::AlignTop);
        d->columns = 0;
    }
    else {
        this->setLayout(d->grid);
    }
}

Grid::~Grid() {}

int Grid::columns() const {
    Q_D(const Grid);

    return d->columns;
}

void Grid::setColumns(int columns) {
    if (columns != this->columns()) {
        Q_D(Grid);
        d->columns = columns;

        if (d->complete) {
            d->clearGrid();
            d->loadGrid();
        }

        emit columnsChanged();
    }
}

int Grid::spacing() const {
    Q_D(const Grid);

    return d->grid->spacing();
}

void Grid::setSpacing(int spacing) {
    if (spacing != this->spacing()) {
        Q_D(Grid);
        d->grid->setSpacing(spacing);
        emit spacingChanged();
    }
}

int Grid::horizontalSpacing() const {
    Q_D(const Grid);

    return d->grid->horizontalSpacing();
}

void Grid::setHorizontalSpacing(int spacing) {
    if (spacing != this->horizontalSpacing()) {
        Q_D(Grid);
        d->grid->setHorizontalSpacing(spacing);
        emit horizontalSpacingChanged();
    }
}

int Grid::verticalSpacing() const {
    Q_D(const Grid);

    return d->grid->verticalSpacing();
}

void Grid::setVerticalSpacing(int spacing) {
    if (spacing != this->verticalSpacing()) {
        Q_D(Grid);
        d->grid->setVerticalSpacing(spacing);
        emit verticalSpacingChanged();
    }
}

void Grid::componentComplete() {
    Q_D(Grid);

    d->loadGrid();
    Item::componentComplete();
}

void GridPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Grid *grid = qobject_cast<Grid*>(list->object)) {
        grid->d_func()->dataList.append(obj);

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            grid->d_func()->childrenList.append(widget);

            if (grid->d_func()->complete) {
                grid->d_func()->addWidgetToGrid(widget);
            }
        }
    }
}

void GridPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Grid *grid = qobject_cast<Grid*>(list->object)) {
        grid->d_func()->childrenList.append(widget);
        grid->d_func()->dataList.append(widget);

        if (grid->d_func()->complete) {
            grid->d_func()->addWidgetToGrid(widget);
        }
    }
}

QDeclarativeListProperty<QObject> GridPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, GridPrivate::data_append);
}

QDeclarativeListProperty<QWidget> GridPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, GridPrivate::children_append);
}

void GridPrivate::clearGrid() {
    foreach (QWidget *widget, childrenList) {
        grid->removeWidget(widget);
    }

    gridMap.clear();
}

void GridPrivate::loadGrid() {
    int row = grid->rowCount() - 1;
    int col = gridMap.value(row, 0);
    int maxCols = columns;

    if (maxCols > 1) {
        foreach (QWidget *widget, childrenList) {
            if (col < maxCols) {
                grid->addWidget(widget, row, col);
                gridMap[row] = col;
                col++;
            }
            else {
                grid->addWidget(widget);
                row++;
                col = 1;
                gridMap[row] = 1;
            }
        }
    }
    else {
        foreach (QWidget *widget, childrenList) {
            grid->addWidget(widget, row, 0);
            gridMap[row] = 1;
            row++;
        }
    }
}

void GridPrivate::addWidgetToGrid(QWidget *widget) {
    int row = grid->rowCount() - 1;
    int col = gridMap.value(row, 0);
    int maxCols = columns;

    if (maxCols > 1) {
        if (col < maxCols) {
            grid->addWidget(widget, row, col);
            gridMap[row] = col;
        }
        else {
            grid->addWidget(widget);
            gridMap[row] = 1;
        }
    }
    else {
        grid->addWidget(widget, row, 0);
        gridMap[row] = 1;
    }
}

#include "moc_grid_p.cpp"

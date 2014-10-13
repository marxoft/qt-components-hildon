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

#include "column_p.h"
#include "column_p_p.h"
#include <QVBoxLayout>

Column::Column(QWidget *parent) :
    Item(*new ColumnPrivate(this), parent)
{
    Q_D(Column);

    d->vbox = new QVBoxLayout(this);
    d->vbox->setContentsMargins(0, 0, 0, 0);
    d->vbox->setAlignment(Qt::AlignTop);
}

Column::Column(ColumnPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(Column);

    if (!d->vbox) {
        d->vbox = new QVBoxLayout(this);
        d->vbox->setContentsMargins(0, 0, 0, 0);
        d->vbox->setAlignment(Qt::AlignTop);
    }
    else {
        this->setLayout(d->vbox);
    }
}

Column::~Column() {}

int Column::spacing() const {
    Q_D(const Column);

    return d->vbox->spacing();
}

void Column::setSpacing(int spacing) {
    if (spacing != this->spacing()) {
        Q_D(Column);
        d->vbox->setSpacing(spacing);
        emit spacingChanged();
    }
}

void Column::componentComplete() {
    Q_D(Column);

    foreach(QWidget *widget, d->childrenList) {
        d->vbox->addWidget(widget);
    }

    Item::componentComplete();
}

void ColumnPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    obj->setParent(list->object);

    if (Column *column = qobject_cast<Column*>(list->object)) {
        column->d_func()->dataList.append(obj);

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            column->d_func()->childrenList.append(widget);

            if (column->d_func()->complete) {
                column->d_func()->vbox->addWidget(widget);
            }
        }
    }
}

void ColumnPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Column *column = qobject_cast<Column*>(list->object)) {
        column->d_func()->childrenList.append(widget);
        column->d_func()->dataList.append(widget);

        if (column->d_func()->complete) {
            column->d_func()->vbox->addWidget(widget);
        }
    }
}

QDeclarativeListProperty<QObject> ColumnPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ColumnPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ColumnPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ColumnPrivate::children_append);
}

#include "moc_column_p.cpp"


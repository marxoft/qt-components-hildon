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

#include "row_p.h"
#include "row_p_p.h"
#include <QHBoxLayout>

Row::Row(QWidget *parent) :
    Item(*new RowPrivate(this), parent)
{
    Q_D(Row);

    d->hbox = new QHBoxLayout(this);
    d->hbox->setContentsMargins(0, 0, 0, 0);
    d->hbox->setAlignment(Qt::AlignLeft);
}

Row::Row(RowPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(Row);

    if (!d->hbox) {
        d->hbox = new QHBoxLayout(this);
        d->hbox->setContentsMargins(0, 0, 0, 0);
        d->hbox->setAlignment(Qt::AlignLeft);
    }
    else {
        this->setLayout(d->hbox);
    }
}

Row::~Row() {}

int Row::spacing() const {
    Q_D(const Row);

    return d->hbox->spacing();
}

void Row::setSpacing(int spacing) {
    if (spacing != this->spacing()) {
        Q_D(Row);
        d->hbox->setSpacing(spacing);
        emit spacingChanged();
    }
}

void Row::componentComplete() {
    Q_D(Row);

    foreach(QWidget *widget, d->childrenList) {
        d->hbox->addWidget(widget, 0);
    }

    Item::componentComplete();
}

void RowPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Row *row = qobject_cast<Row*>(list->object)) {
        row->d_func()->dataList.append(obj);

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            row->d_func()->childrenList.append(widget);

            if (row->d_func()->complete) {
                row->d_func()->hbox->addWidget(widget);
            }
        }
    }
}

void RowPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Row *row = qobject_cast<Row*>(list->object)) {
        row->d_func()->childrenList.append(widget);
        row->d_func()->dataList.append(widget);

        if (row->d_func()->complete) {
            row->d_func()->hbox->addWidget(widget);
        }
    }
}

QDeclarativeListProperty<QObject> RowPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, RowPrivate::data_append);
}

QDeclarativeListProperty<QWidget> RowPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, RowPrivate::children_append);
}

#include "moc_row_p.cpp"

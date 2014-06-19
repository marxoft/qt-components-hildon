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

#include "flow_p.h"
#include "flow_p_p.h"
#include <QGridLayout>

Flow::Flow(QWidget *parent) :
    Item(*new FlowPrivate(this), parent)
{
    Q_D(Flow);

    d->grid = new QGridLayout(this);
    d->grid->setContentsMargins(0, 0, 0, 0);
    d->grid->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

Flow::Flow(FlowPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(Flow);

    if (!d->grid) {
        d->grid = new QGridLayout(this);
        d->grid->setContentsMargins(0, 0, 0, 0);
        d->grid->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    }
    else {
        this->setLayout(d->grid);
    }
}

Flow::~Flow() {}

int Flow::spacing() const {
    Q_D(const Flow);

    return d->grid->spacing();
}

void Flow::setSpacing(int spacing) {
    if (spacing != this->spacing()) {
        Q_D(Flow);
        d->grid->setSpacing(spacing);
        emit spacingChanged();
    }
}

void Flow::componentComplete() {
    Q_D(Flow);

    foreach(QObject *obj, d->dataList) {
        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            if (widget->width() + d->grid->contentsRect().width() <= this->width()) {
                d->grid->addWidget(widget, d->grid->rowCount() - 1, d->grid->columnCount() - 1);
            }
            else {
                d->grid->addWidget(widget, d->grid->rowCount(), 0);
            }
        }
    }

    Item::componentComplete();
}

void FlowPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flow *flow = qobject_cast<Flow*>(list->object)) {
        flow->d_func()->dataList.append(obj);

        if (!flow->d_func()->complete) {
            return;
        }

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            if (widget->width() + flow->d_func()->grid->contentsRect().width() <= flow->width()) {
                flow->d_func()->grid->addWidget(widget);
            }
            else {
                flow->d_func()->grid->addWidget(widget, flow->d_func()->grid->rowCount(), 0);
            }
        }
    }
}

QDeclarativeListProperty<QObject> FlowPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlowPrivate::data_append);
}

#include "moc_flow_p.cpp"

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

#include "flickable_p.h"
#include "flickable_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>

Flickable::Flickable(QWidget *parent) :
    QScrollArea(parent),
    d_ptr(new FlickablePrivate(this))
{
    this->setWidgetResizable(true);
    this->setWidget(new Item(this));
}

Flickable::Flickable(FlickablePrivate &dd, QWidget *parent) :
    QScrollArea(parent),
    d_ptr(&dd)
{
    this->setWidgetResizable(true);
    this->setWidget(new Item(this));
}

Flickable::~Flickable() {}

void Flickable::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Flickable::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine Flickable::left() const {
    Q_D(const Flickable);

    return d->left;
}

AnchorLine Flickable::right() const {
    Q_D(const Flickable);

    return d->right;
}

AnchorLine Flickable::top() const {
    Q_D(const Flickable);

    return d->top;
}

AnchorLine Flickable::bottom() const {
    Q_D(const Flickable);

    return d->bottom;
}

AnchorLine Flickable::horizontalCenter() const {
    Q_D(const Flickable);

    return d->horizontalCenter;
}

AnchorLine Flickable::verticalCenter() const {
    Q_D(const Flickable);

    return d->verticalCenter;
}

void Flickable::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QWidget::changeEvent(event);
}

void Flickable::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QWidget::moveEvent(event);
}

void Flickable::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QWidget::resizeEvent(event);
}

void Flickable::classBegin() {}

void Flickable::componentComplete() {
    Q_D(Flickable);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void FlickablePrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->dataList.append(obj);
        obj->setParent(flickable->widget());
    }
}

void FlickablePrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->actionList.append(obj);

        if (!flickable->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            flickable->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            flickable->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> FlickablePrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlickablePrivate::data_append);
}

QDeclarativeListProperty<QObject> FlickablePrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlickablePrivate::actions_append);
}

#include "moc_flickable_p.cpp"

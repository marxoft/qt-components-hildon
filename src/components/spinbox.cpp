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

#include "spinbox_p.h"
#include "spinbox_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>

SpinBox::SpinBox(QWidget *parent) :
    QSpinBox(parent),
    d_ptr(new SpinBoxPrivate(this))
{
}

SpinBox::SpinBox(SpinBoxPrivate &dd, QWidget *parent) :
    QSpinBox(parent),
    d_ptr(&dd)
{
}

SpinBox::~SpinBox() {}

void SpinBox::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void SpinBox::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine SpinBox::left() const {
    Q_D(const SpinBox);

    return d->left;
}

AnchorLine SpinBox::right() const {
    Q_D(const SpinBox);

    return d->right;
}

AnchorLine SpinBox::top() const {
    Q_D(const SpinBox);

    return d->top;
}

AnchorLine SpinBox::bottom() const {
    Q_D(const SpinBox);

    return d->bottom;
}

AnchorLine SpinBox::horizontalCenter() const {
    Q_D(const SpinBox);

    return d->horizontalCenter;
}

AnchorLine SpinBox::verticalCenter() const {
    Q_D(const SpinBox);

    return d->verticalCenter;
}

void SpinBox::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QSpinBox::changeEvent(event);
}

void SpinBox::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QSpinBox::moveEvent(event);
}

void SpinBox::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QSpinBox::resizeEvent(event);
}

void SpinBox::classBegin() {}

void SpinBox::componentComplete() {
    Q_D(SpinBox);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void SpinBoxPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (SpinBox *spinbox = qobject_cast<SpinBox*>(list->object)) {
        spinbox->d_func()->dataList.append(obj);
    }
}

void SpinBoxPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (SpinBox *spinbox = qobject_cast<SpinBox*>(list->object)) {
        spinbox->d_func()->actionList.append(obj);

        if (!spinbox->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            spinbox->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            spinbox->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> SpinBoxPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, SpinBoxPrivate::data_append);
}

QDeclarativeListProperty<QObject> SpinBoxPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, SpinBoxPrivate::actions_append);
}

#include "moc_spinbox_p.cpp"

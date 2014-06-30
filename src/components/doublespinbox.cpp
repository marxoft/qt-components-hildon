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

#include "doublespinbox_p.h"
#include "doublespinbox_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

DoubleSpinBox::DoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent),
    d_ptr(new DoubleSpinBoxPrivate(this))
{
}

DoubleSpinBox::DoubleSpinBox(DoubleSpinBoxPrivate &dd, QWidget *parent) :
    QDoubleSpinBox(parent),
    d_ptr(&dd)
{
}

DoubleSpinBox::~DoubleSpinBox() {}

void DoubleSpinBox::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void DoubleSpinBox::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal DoubleSpinBox::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void DoubleSpinBox::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine DoubleSpinBox::left() const {
    Q_D(const DoubleSpinBox);

    return d->left;
}

AnchorLine DoubleSpinBox::right() const {
    Q_D(const DoubleSpinBox);

    return d->right;
}

AnchorLine DoubleSpinBox::top() const {
    Q_D(const DoubleSpinBox);

    return d->top;
}

AnchorLine DoubleSpinBox::bottom() const {
    Q_D(const DoubleSpinBox);

    return d->bottom;
}

AnchorLine DoubleSpinBox::horizontalCenter() const {
    Q_D(const DoubleSpinBox);

    return d->horizontalCenter;
}

AnchorLine DoubleSpinBox::verticalCenter() const {
    Q_D(const DoubleSpinBox);

    return d->verticalCenter;
}

void DoubleSpinBox::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QDoubleSpinBox::changeEvent(event);
}

void DoubleSpinBox::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QDoubleSpinBox::moveEvent(event);
}

void DoubleSpinBox::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QDoubleSpinBox::resizeEvent(event);
}

void DoubleSpinBox::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QDoubleSpinBox::showEvent(event);
}

void DoubleSpinBox::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QDoubleSpinBox::hideEvent(event);
}

void DoubleSpinBox::classBegin() {}

void DoubleSpinBox::componentComplete() {
    Q_D(DoubleSpinBox);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void DoubleSpinBoxPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (DoubleSpinBox *spinbox = qobject_cast<DoubleSpinBox*>(list->object)) {
        spinbox->d_func()->dataList.append(obj);
    }
}

void DoubleSpinBoxPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (DoubleSpinBox *spinbox = qobject_cast<DoubleSpinBox*>(list->object)) {
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

QDeclarativeListProperty<QObject> DoubleSpinBoxPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, DoubleSpinBoxPrivate::data_append);
}

QDeclarativeListProperty<QObject> DoubleSpinBoxPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, DoubleSpinBoxPrivate::actions_append);
}

#include "moc_doublespinbox_p.cpp"

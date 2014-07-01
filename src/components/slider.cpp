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

#include "slider_p.h"
#include "slider_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

Slider::Slider(QWidget *parent) :
    QSlider(Qt::Horizontal, parent),
    d_ptr(new SliderPrivate(this))
{
}

Slider::Slider(SliderPrivate &dd, QWidget *parent) :
    QSlider(Qt::Horizontal, parent),
    d_ptr(&dd)
{
}

Slider::~Slider() {}

void Slider::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Slider::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Slider::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Slider::setOpacity(qreal opacity) {
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

void Slider::setFocus(bool focus) {
    if (focus != this->hasFocus()) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

AnchorLine Slider::left() const {
    Q_D(const Slider);

    return d->left;
}

AnchorLine Slider::right() const {
    Q_D(const Slider);

    return d->right;
}

AnchorLine Slider::top() const {
    Q_D(const Slider);

    return d->top;
}

AnchorLine Slider::bottom() const {
    Q_D(const Slider);

    return d->bottom;
}

AnchorLine Slider::horizontalCenter() const {
    Q_D(const Slider);

    return d->horizontalCenter;
}

AnchorLine Slider::verticalCenter() const {
    Q_D(const Slider);

    return d->verticalCenter;
}

void Slider::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QSlider::changeEvent(event);
}

void Slider::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QSlider::moveEvent(event);
}

void Slider::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QSlider::resizeEvent(event);
}

void Slider::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QSlider::showEvent(event);
}

void Slider::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QSlider::hideEvent(event);
}

void Slider::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QSlider::focusInEvent(event);
}

void Slider::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QSlider::focusOutEvent(event);
}

void Slider::classBegin() {}

void Slider::componentComplete() {
    Q_D(Slider);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void SliderPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Slider *slider = qobject_cast<Slider*>(list->object)) {
        slider->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            slider->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void SliderPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Slider *slider = qobject_cast<Slider*>(list->object)) {
        slider->d_func()->childrenList.append(widget);
        slider->d_func()->dataList.append(widget);
    }
}

void SliderPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Slider *slider = qobject_cast<Slider*>(list->object)) {
        slider->d_func()->actionList.append(obj);
        slider->d_func()->dataList.append(obj);

        if (!slider->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            slider->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            slider->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> SliderPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, SliderPrivate::data_append);
}

QDeclarativeListProperty<QWidget> SliderPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, SliderPrivate::children_append);
}

QDeclarativeListProperty<QObject> SliderPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, SliderPrivate::actions_append);
}

#include "moc_slider_p.cpp"

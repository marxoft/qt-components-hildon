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

#include "informationbox_p.h"
#include "informationbox_p_p.h"
#include <QActionGroup>
#include <QEvent>
#include <QGraphicsOpacityEffect>

InformationBox::InformationBox(QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(new InformationBoxPrivate(this))
{
    Item *item = new Item(this);
    item->setMinimumHeight(30);
    this->setWidget(item);
}

InformationBox::InformationBox(InformationBoxPrivate &dd, QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(&dd)
{
    Item *item = new Item(this);
    item->setMinimumHeight(30);
    this->setWidget(item);
}

InformationBox::~InformationBox() {}

qreal InformationBox::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void InformationBox::setOpacity(qreal opacity) {
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

void InformationBox::setFocus(bool focus) {
    if (focus != this->hasFocus()) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

void InformationBox::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMaemo5InformationBox::changeEvent(event);
}

void InformationBox::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QMaemo5InformationBox::showEvent(event);
}

void InformationBox::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QMaemo5InformationBox::hideEvent(event);
}

void InformationBox::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QMaemo5InformationBox::focusInEvent(event);
}

void InformationBox::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QMaemo5InformationBox::focusOutEvent(event);
}

void InformationBox::classBegin() {}

void InformationBox::componentComplete() {
    Q_D(InformationBox);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Dialog);
    }
}

void InformationBoxPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            box->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void InformationBoxPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->childrenList.append(widget);
        box->d_func()->dataList.append(widget);
    }
}

void InformationBoxPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->actionList.append(obj);

        if (!box->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            box->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            box->addActions(group->actions());
        }
    }
}

void InformationBoxPrivate::content_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->contentList.append(widget);
        box->d_func()->childrenList.append(widget);
        widget->setParent(box->widget());
    }
}

QDeclarativeListProperty<QObject> InformationBoxPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, InformationBoxPrivate::data_append);
}

QDeclarativeListProperty<QWidget> InformationBoxPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, InformationBoxPrivate::children_append);
}

QDeclarativeListProperty<QObject> InformationBoxPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, InformationBoxPrivate::actions_append);
}

QDeclarativeListProperty<QWidget> InformationBoxPrivate::content() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, InformationBoxPrivate::content_append);
}

#include "moc_informationbox_p.cpp"

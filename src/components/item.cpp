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

#include "item_p.h"
#include "item_p_p.h"
#include "anchors_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

Item::Item(QWidget *parent) :
    QWidget(parent),
    d_ptr(new ItemPrivate(this))
{
}

Item::Item(ItemPrivate &dd, QWidget *parent) :
    QWidget(parent),
    d_ptr(&dd)
{
}

Item::~Item() {}

void Item::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Item::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Item::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Item::setOpacity(qreal opacity) {
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

void Item::setFocus(bool focus) {
    Q_D(const Item);

    if ((d->complete) && (focus != this->hasFocus())) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

AnchorLine Item::left() const {
    Q_D(const Item);

    return d->left;
}

AnchorLine Item::right() const {
    Q_D(const Item);

    return d->right;
}

AnchorLine Item::top() const {
    Q_D(const Item);

    return d->top;
}

AnchorLine Item::bottom() const {
    Q_D(const Item);

    return d->bottom;
}

AnchorLine Item::horizontalCenter() const {
    Q_D(const Item);

    return d->horizontalCenter;
}

AnchorLine Item::verticalCenter() const {
    Q_D(const Item);

    return d->verticalCenter;
}

void Item::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QWidget::changeEvent(event);
}

void Item::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QWidget::moveEvent(event);
}

void Item::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QWidget::resizeEvent(event);
}

void Item::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QWidget::showEvent(event);
}

void Item::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QWidget::hideEvent(event);
}

void Item::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QWidget::focusInEvent(event);
}

void Item::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QWidget::focusOutEvent(event);
}

void Item::keyPressEvent(QKeyEvent *event) {
    Q_D(Item);

    if (d->keys) {
        switch (d->keys->priority()) {
        case Keys::BeforeItem:
            d->keys->event(event);
            QWidget::keyPressEvent(event);
            return;
        default:
            QWidget::keyPressEvent(event);
            d->keys->event(event);
            return;
        }
    }
}

void Item::keyReleaseEvent(QKeyEvent *event) {
    Q_D(Item);

    if (d->keys) {
        switch (d->keys->priority()) {
        case Keys::BeforeItem:
            d->keys->event(event);
            QWidget::keyReleaseEvent(event);
            return;
        default:
            QWidget::keyReleaseEvent(event);
            d->keys->event(event);
            return;
        }
    }
}

void Item::classBegin() {}

void Item::componentComplete() {
    Q_D(Item);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ItemPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Item *item = qobject_cast<Item*>(list->object)) {
        item->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            item->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void ItemPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Item *item = qobject_cast<Item*>(list->object)) {
        item->d_func()->childrenList.append(widget);
        item->d_func()->dataList.append(widget);
    }
}

void ItemPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Item *item = qobject_cast<Item*>(list->object)) {
        item->d_func()->actionList.append(obj);
        item->d_func()->dataList.append(obj);

        if (!item->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            item->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            item->addActions(group->actions());
        }
    }
}

Keys* ItemPrivate::attachedKeys() {
    Q_Q(Item);

    if (!keys) {
        keys = new Keys(q);
    }

    return keys;
}

Anchors* ItemPrivate::anchors() {
    Q_Q(Item);

    if (!anc) {
        anc = new Anchors(q, q);
    }

    return anc;
}

QDeclarativeListProperty<QObject> ItemPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ItemPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ItemPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ItemPrivate::children_append);
}

QDeclarativeListProperty<QObject> ItemPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ItemPrivate::actions_append);
}

bool ItemPrivate::qmlVisible() const {
    return qmlVis;
}

void ItemPrivate::setQmlVisible(bool visible) {
    if (visible != this->qmlVisible()) {
        Q_Q(Item);
        qmlVis = visible;
        q->setVisible(visible);
    }
}

void ItemPrivate::componentComplete() {
    Q_Q(Item);

    complete = true;

    foreach (QObject *obj, actionList) {
        if (QAction *action = qobject_cast<QAction*>(obj)) {
            q->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            q->addActions(group->actions());
        }
    }

    if (anc) {
        anc->d_func()->onWidgetCompleted();
    }
}

#include "moc_item_p.cpp"

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

#include "valuebutton_p.h"
#include "valuebutton_p_p.h"
#include "valueselector_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

ValueButton::ValueButton(QWidget *parent) :
    QMaemo5ValueButton(parent),
    d_ptr(new ValueButtonPrivate(this))
{
}

ValueButton::ValueButton(ValueButtonPrivate &dd, QWidget *parent) :
    QMaemo5ValueButton(parent),
    d_ptr(&dd)
{
}

ValueButton::~ValueButton() {}

void ValueButton::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ValueButton::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal ValueButton::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void ValueButton::setOpacity(qreal opacity) {
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

void ValueButton::setFocus(bool focus) {
    if (focus != this->hasFocus()) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

QString ValueButton::iconSource() const {
    return this->icon().name();
}

void ValueButton::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
        emit iconChanged();
    }
}

QString ValueButton::shortcutString() const {
    return this->shortcut().toString();
}

void ValueButton::setShortcutString(const QString &shortcut) {
    if (shortcut != this->shortcutString()) {
        this->setShortcut(QKeySequence(shortcut));
        emit shortcutChanged();
    }
}

ValueSelector* ValueButton::selector() const {
    Q_D(const ValueButton);

    return d->selector;
}

void ValueButton::setSelector(ValueSelector *selector) {
    Q_D(ValueButton);

    this->setPickSelector(selector->d_func()->selector);
    d->selector = selector;
}

AnchorLine ValueButton::left() const {
    Q_D(const ValueButton);

    return d->left;
}

AnchorLine ValueButton::right() const {
    Q_D(const ValueButton);

    return d->right;
}

AnchorLine ValueButton::top() const {
    Q_D(const ValueButton);

    return d->top;
}

AnchorLine ValueButton::bottom() const {
    Q_D(const ValueButton);

    return d->bottom;
}

AnchorLine ValueButton::horizontalCenter() const {
    Q_D(const ValueButton);

    return d->horizontalCenter;
}

AnchorLine ValueButton::verticalCenter() const {
    Q_D(const ValueButton);

    return d->verticalCenter;
}

void ValueButton::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMaemo5ValueButton::changeEvent(event);
}

void ValueButton::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QMaemo5ValueButton::moveEvent(event);
}

void ValueButton::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QMaemo5ValueButton::resizeEvent(event);
}

void ValueButton::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QMaemo5ValueButton::showEvent(event);
}

void ValueButton::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QMaemo5ValueButton::hideEvent(event);
}

void ValueButton::focusInEvent(QFocusEvent *event) {
    emit visibleChanged();
    QMaemo5ValueButton::focusInEvent(event);
}

void ValueButton::focusOutEvent(QFocusEvent *event) {
    emit visibleChanged();
    QMaemo5ValueButton::focusOutEvent(event);
}

void ValueButton::classBegin() {}

void ValueButton::componentComplete() {
    Q_D(ValueButton);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ValueButtonPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ValueButton *button = qobject_cast<ValueButton*>(list->object)) {
        button->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            button->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void ValueButtonPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (ValueButton *button = qobject_cast<ValueButton*>(list->object)) {
        button->d_func()->childrenList.append(widget);
        button->d_func()->dataList.append(widget);
    }
}

void ValueButtonPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ValueButton *button = qobject_cast<ValueButton*>(list->object)) {
        button->d_func()->actionList.append(obj);

        if (!button->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            button->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            button->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> ValueButtonPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ValueButtonPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ValueButtonPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ValueButtonPrivate::children_append);
}

QDeclarativeListProperty<QObject> ValueButtonPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ValueButtonPrivate::actions_append);
}

#include "moc_valuebutton_p.cpp"

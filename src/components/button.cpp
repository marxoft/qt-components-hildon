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

#include "button_p.h"
#include "button_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

Button::Button(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new ButtonPrivate(this))
{
}

Button::Button(ButtonPrivate &dd, QWidget *parent) :
    QPushButton(parent),
    d_ptr(&dd)
{
}

Button::~Button() {}

void Button::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Button::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Button::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Button::setOpacity(qreal opacity) {
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

void Button::setFocus(bool focus) {
    Q_D(const Button);

    if ((d->complete) && (focus != this->hasFocus())) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

QString Button::iconSource() const {
    return this->icon().name();
}

void Button::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
        emit iconChanged();
    }
}

QString Button::shortcutString() const {
    return this->shortcut().toString();
}

void Button::setShortcutString(const QString &shortcut) {
    if (shortcut != this->shortcutString()) {
        this->setShortcut(QKeySequence(shortcut));
        emit shortcutChanged();
    }
}

AnchorLine Button::left() const {
    Q_D(const Button);

    return d->left;
}

AnchorLine Button::right() const {
    Q_D(const Button);

    return d->right;
}

AnchorLine Button::top() const {
    Q_D(const Button);

    return d->top;
}

AnchorLine Button::bottom() const {
    Q_D(const Button);

    return d->bottom;
}

AnchorLine Button::horizontalCenter() const {
    Q_D(const Button);

    return d->horizontalCenter;
}

AnchorLine Button::verticalCenter() const {
    Q_D(const Button);

    return d->verticalCenter;
}

void Button::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QPushButton::changeEvent(event);
}

void Button::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QPushButton::moveEvent(event);
}

void Button::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QPushButton::resizeEvent(event);
}

void Button::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QPushButton::showEvent(event);
}

void Button::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QPushButton::hideEvent(event);
}

void Button::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QPushButton::focusInEvent(event);
}

void Button::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QPushButton::focusOutEvent(event);
}

void Button::classBegin() {}

void Button::componentComplete() {
    Q_D(Button);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ButtonPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Button *button = qobject_cast<Button*>(list->object)) {
        button->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            button->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void ButtonPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Button *button = qobject_cast<Button*>(list->object)) {
        button->d_func()->childrenList.append(widget);
        button->d_func()->dataList.append(widget);
    }
}

void ButtonPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Button *button = qobject_cast<Button*>(list->object)) {
        button->d_func()->actionList.append(obj);
        button->d_func()->dataList.append(obj);

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

QDeclarativeListProperty<QObject> ButtonPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ButtonPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ButtonPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ButtonPrivate::children_append);
}

QDeclarativeListProperty<QObject> ButtonPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ButtonPrivate::actions_append);
}

#include "moc_button_p.cpp"

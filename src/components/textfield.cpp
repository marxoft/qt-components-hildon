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

#include "textfield_p.h"
#include "textfield_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

TextField::TextField(QWidget *parent) :
    QLineEdit(parent),
    d_ptr(new TextFieldPrivate(this))
{
}

TextField::TextField(TextFieldPrivate &dd, QWidget *parent) :
    QLineEdit(parent),
    d_ptr(&dd)
{
}

TextField::~TextField() {}

void TextField::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void TextField::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal TextField::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void TextField::setOpacity(qreal opacity) {
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

void TextField::setFocus(bool focus) {
    Q_D(const TextField);

    if ((d->complete) && (focus != this->hasFocus())) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

AnchorLine TextField::left() const {
    Q_D(const TextField);

    return d->left;
}

AnchorLine TextField::right() const {
    Q_D(const TextField);

    return d->right;
}

AnchorLine TextField::top() const {
    Q_D(const TextField);

    return d->top;
}

AnchorLine TextField::bottom() const {
    Q_D(const TextField);

    return d->bottom;
}

AnchorLine TextField::horizontalCenter() const {
    Q_D(const TextField);

    return d->horizontalCenter;
}

AnchorLine TextField::verticalCenter() const {
    Q_D(const TextField);

    return d->verticalCenter;
}

void TextField::changeEvent(QEvent *event) {
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

    QLineEdit::changeEvent(event);
}

void TextField::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QLineEdit::moveEvent(event);
}

void TextField::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QLineEdit::resizeEvent(event);
}

void TextField::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QLineEdit::showEvent(event);
}

void TextField::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QLineEdit::hideEvent(event);
}

void TextField::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QLineEdit::focusInEvent(event);
}

void TextField::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QLineEdit::focusOutEvent(event);
}

void TextField::classBegin() {}

void TextField::componentComplete() {
    Q_D(TextField);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void TextFieldPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TextField *field = qobject_cast<TextField*>(list->object)) {
        field->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            field->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void TextFieldPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (TextField *field = qobject_cast<TextField*>(list->object)) {
        field->d_func()->childrenList.append(widget);
        field->d_func()->dataList.append(widget);
    }
}

void TextFieldPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TextField *field = qobject_cast<TextField*>(list->object)) {
        field->d_func()->actionList.append(obj);
        field->d_func()->dataList.append(obj);

        if (!field->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            field->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            field->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> TextFieldPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TextFieldPrivate::data_append);
}

QDeclarativeListProperty<QWidget> TextFieldPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, TextFieldPrivate::children_append);
}

QDeclarativeListProperty<QObject> TextFieldPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TextFieldPrivate::actions_append);
}

QValidator* TextFieldPrivate::validator() const {
    return val;
}

void TextFieldPrivate::setValidator(QValidator *v) {
    Q_Q(TextField);

    val = v;
    q->setValidator(v);
}

#include "moc_textfield_p.cpp"

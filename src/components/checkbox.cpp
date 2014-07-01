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

#include "checkbox_p.h"
#include "checkbox_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

CheckBox::CheckBox(QWidget *parent) :
    QCheckBox(parent),
    d_ptr(new CheckBoxPrivate(this))
{
}

CheckBox::CheckBox(CheckBoxPrivate &dd, QWidget *parent) :
    QCheckBox(parent),
    d_ptr(&dd)
{
}

CheckBox::~CheckBox() {}

void CheckBox::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void CheckBox::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal CheckBox::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void CheckBox::setOpacity(qreal opacity) {
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

void CheckBox::setFocus(bool focus) {
    if (focus != this->hasFocus()) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

QString CheckBox::iconSource() const {
    return this->icon().name();
}

void CheckBox::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
    }
}

AnchorLine CheckBox::left() const {
    Q_D(const CheckBox);

    return d->left;
}

AnchorLine CheckBox::right() const {
    Q_D(const CheckBox);

    return d->right;
}

AnchorLine CheckBox::top() const {
    Q_D(const CheckBox);

    return d->top;
}

AnchorLine CheckBox::bottom() const {
    Q_D(const CheckBox);

    return d->bottom;
}

AnchorLine CheckBox::horizontalCenter() const {
    Q_D(const CheckBox);

    return d->horizontalCenter;
}

AnchorLine CheckBox::verticalCenter() const {
    Q_D(const CheckBox);

    return d->verticalCenter;
}

void CheckBox::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QCheckBox::changeEvent(event);
}

void CheckBox::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QCheckBox::moveEvent(event);
}

void CheckBox::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QCheckBox::resizeEvent(event);
}

void CheckBox::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QCheckBox::showEvent(event);
}

void CheckBox::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QCheckBox::hideEvent(event);
}

void CheckBox::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QCheckBox::focusInEvent(event);
}

void CheckBox::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QCheckBox::focusOutEvent(event);
}

void CheckBox::classBegin() {}

void CheckBox::componentComplete() {
    Q_D(CheckBox);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void CheckBoxPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (CheckBox *checkbox = qobject_cast<CheckBox*>(list->object)) {
        checkbox->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            checkbox->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void CheckBoxPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (CheckBox *checkbox = qobject_cast<CheckBox*>(list->object)) {
        checkbox->d_func()->childrenList.append(widget);
        checkbox->d_func()->dataList.append(widget);
    }
}

void CheckBoxPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (CheckBox *checkbox = qobject_cast<CheckBox*>(list->object)) {
        checkbox->d_func()->actionList.append(obj);
        checkbox->d_func()->dataList.append(obj);

        if (!checkbox->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            checkbox->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            checkbox->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> CheckBoxPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, CheckBoxPrivate::data_append);
}

QDeclarativeListProperty<QWidget> CheckBoxPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, CheckBoxPrivate::children_append);
}

QDeclarativeListProperty<QObject> CheckBoxPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, CheckBoxPrivate::actions_append);
}

#include "moc_checkbox_p.cpp"

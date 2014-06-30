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

#include "toolbutton_p.h"
#include "toolbutton_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>

ToolButton::ToolButton(QWidget *parent) :
    QToolButton(parent),
    d_ptr(new ToolButtonPrivate(this))
{
}

ToolButton::ToolButton(ToolButtonPrivate &dd, QWidget *parent) :
    QToolButton(parent),
    d_ptr(&dd)
{
}

ToolButton::~ToolButton() {}

void ToolButton::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ToolButton::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

QString ToolButton::iconSource() const {
    return this->icon().name();
}

void ToolButton::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
    }
}

AnchorLine ToolButton::left() const {
    Q_D(const ToolButton);

    return d->left;
}

AnchorLine ToolButton::right() const {
    Q_D(const ToolButton);

    return d->right;
}

AnchorLine ToolButton::top() const {
    Q_D(const ToolButton);

    return d->top;
}

AnchorLine ToolButton::bottom() const {
    Q_D(const ToolButton);

    return d->bottom;
}

AnchorLine ToolButton::horizontalCenter() const {
    Q_D(const ToolButton);

    return d->horizontalCenter;
}

AnchorLine ToolButton::verticalCenter() const {
    Q_D(const ToolButton);

    return d->verticalCenter;
}

void ToolButton::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QToolButton::changeEvent(event);
}

void ToolButton::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QToolButton::moveEvent(event);
}

void ToolButton::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QToolButton::resizeEvent(event);
}

void ToolButton::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QToolButton::showEvent(event);
}

void ToolButton::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QToolButton::hideEvent(event);
}

void ToolButton::classBegin() {}

void ToolButton::componentComplete() {
    Q_D(ToolButton);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ToolButtonPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ToolButton *button = qobject_cast<ToolButton*>(list->object)) {
        button->d_func()->dataList.append(obj);
    }
}

void ToolButtonPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ToolButton *button = qobject_cast<ToolButton*>(list->object)) {
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

QDeclarativeListProperty<QObject> ToolButtonPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ToolButtonPrivate::data_append);
}

QDeclarativeListProperty<QObject> ToolButtonPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ToolButtonPrivate::actions_append);
}

#include "moc_toolbutton_p.cpp"

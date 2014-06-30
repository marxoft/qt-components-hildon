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

#include "tabgroup_p.h"
#include "tabgroup_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>

TabGroup::TabGroup(QWidget *parent) :
    QStackedWidget(parent),
    d_ptr(new TabGroupPrivate(this))
{
    this->connect(this, SIGNAL(currentChanged(int)), this, SIGNAL(currentTabChanged()));
}

TabGroup::TabGroup(TabGroupPrivate &dd, QWidget *parent) :
    QStackedWidget(parent),
    d_ptr(&dd)
{
    this->connect(this, SIGNAL(currentChanged(int)), this, SIGNAL(currentTabChanged()));
}

TabGroup::~TabGroup() {}

void TabGroup::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void TabGroup::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine TabGroup::left() const {
    Q_D(const TabGroup);

    return d->left;
}

AnchorLine TabGroup::right() const {
    Q_D(const TabGroup);

    return d->right;
}

AnchorLine TabGroup::top() const {
    Q_D(const TabGroup);

    return d->top;
}

AnchorLine TabGroup::bottom() const {
    Q_D(const TabGroup);

    return d->bottom;
}

AnchorLine TabGroup::horizontalCenter() const {
    Q_D(const TabGroup);

    return d->horizontalCenter;
}

AnchorLine TabGroup::verticalCenter() const {
    Q_D(const TabGroup);

    return d->verticalCenter;
}

void TabGroup::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QStackedWidget::changeEvent(event);
}

void TabGroup::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QStackedWidget::moveEvent(event);
}

void TabGroup::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QStackedWidget::resizeEvent(event);
}

void TabGroup::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QStackedWidget::showEvent(event);
}

void TabGroup::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QStackedWidget::hideEvent(event);
}

void TabGroup::classBegin() {}

void TabGroup::componentComplete() {
    Q_D(TabGroup);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    foreach (QObject *obj, d->dataList) {
        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            this->addWidget(widget);
        }
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void TabGroupPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TabGroup *stack = qobject_cast<TabGroup*>(list->object)) {
        stack->d_func()->dataList.append(obj);

        if (!stack->d_func()->complete) {
            return;
        }

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            stack->addWidget(widget);
        }
    }
}

void TabGroupPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TabGroup *stack = qobject_cast<TabGroup*>(list->object)) {
        stack->d_func()->actionList.append(obj);

        if (!stack->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            stack->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            stack->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> TabGroupPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TabGroupPrivate::data_append);
}

QDeclarativeListProperty<QObject> TabGroupPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TabGroupPrivate::actions_append);
}

#include "moc_tabgroup_p.cpp"

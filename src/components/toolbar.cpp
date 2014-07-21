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

#include "toolbar_p.h"
#include "toolbar_p_p.h"
#include "separator_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

ToolBar::ToolBar(QWidget *parent) :
    QToolBar(parent),
    d_ptr(new ToolBarPrivate(this))
{
    this->setFixedHeight(70);
}

ToolBar::ToolBar(ToolBarPrivate &dd, QWidget *parent) :
    QToolBar(parent),
    d_ptr(&dd)
{
    this->setFixedHeight(70);
}

ToolBar::~ToolBar() {}

void ToolBar::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ToolBar::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal ToolBar::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void ToolBar::setOpacity(qreal opacity) {
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

void ToolBar::setFocus(bool focus) {
    Q_D(const ToolBar);

    if ((d->complete) && (focus != this->hasFocus())) {
        if (focus) {
            this->setFocus(Qt::OtherFocusReason);
        }
        else {
            this->clearFocus();
        }
    }
}

AnchorLine ToolBar::left() const {
    Q_D(const ToolBar);

    return d->left;
}

AnchorLine ToolBar::right() const {
    Q_D(const ToolBar);

    return d->right;
}

AnchorLine ToolBar::top() const {
    Q_D(const ToolBar);

    return d->top;
}

AnchorLine ToolBar::bottom() const {
    Q_D(const ToolBar);

    return d->bottom;
}

AnchorLine ToolBar::horizontalCenter() const {
    Q_D(const ToolBar);

    return d->horizontalCenter;
}

AnchorLine ToolBar::verticalCenter() const {
    Q_D(const ToolBar);

    return d->verticalCenter;
}

void ToolBar::changeEvent(QEvent *event) {
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

    QToolBar::changeEvent(event);
}

void ToolBar::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QToolBar::moveEvent(event);
}

void ToolBar::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QToolBar::resizeEvent(event);
}

void ToolBar::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QToolBar::showEvent(event);
}

void ToolBar::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QToolBar::hideEvent(event);
}

void ToolBar::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QToolBar::focusInEvent(event);
}

void ToolBar::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QToolBar::focusOutEvent(event);
}

void ToolBar::classBegin() {}

void ToolBar::componentComplete() {
    Q_D(ToolBar);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ToolBarPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ToolBar *bar = qobject_cast<ToolBar*>(list->object)) {
        bar->d_func()->dataList.append(obj);

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            bar->d_func()->childrenList.append(widget);
        }

        if (!bar->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            bar->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            bar->addActions(group->actions());
        }
        else if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            bar->addWidget(widget);
        }
        else if (qobject_cast<Separator*>(obj)) {
            bar->addSeparator();
        }
    }
}

void ToolBarPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (ToolBar *bar = qobject_cast<ToolBar*>(list->object)) {
        bar->d_func()->childrenList.append(widget);
        bar->d_func()->dataList.append(widget);

        if (bar->d_func()->complete) {
            bar->addWidget(widget);
        }
    }
}

QDeclarativeListProperty<QObject> ToolBarPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ToolBarPrivate::data_append);
}

QDeclarativeListProperty<QWidget> ToolBarPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, ToolBarPrivate::children_append);
}

void ToolBarPrivate::componentComplete() {
    Q_Q(ToolBar);

    foreach (QObject *obj, dataList) {
        if (QAction *action = qobject_cast<QAction*>(obj)) {
            q->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            q->addActions(group->actions());
        }
        else if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            q->addWidget(widget);
        }
        else if (qobject_cast<Separator*>(obj)) {
            q->addSeparator();
        }
    }

    ItemPrivate::componentComplete();
}

#include "moc_toolbar_p.cpp"

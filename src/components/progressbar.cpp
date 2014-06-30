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

#include "progressbar_p.h"
#include "progressbar_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

ProgressBar::ProgressBar(QWidget *parent) :
    QProgressBar(parent),
    d_ptr(new ProgressBarPrivate(this))
{
}

ProgressBar::ProgressBar(ProgressBarPrivate &dd, QWidget *parent) :
    QProgressBar(parent),
    d_ptr(&dd)
{
}

ProgressBar::~ProgressBar() {}

void ProgressBar::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ProgressBar::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal ProgressBar::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void ProgressBar::setOpacity(qreal opacity) {
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

AnchorLine ProgressBar::left() const {
    Q_D(const ProgressBar);

    return d->left;
}

AnchorLine ProgressBar::right() const {
    Q_D(const ProgressBar);

    return d->right;
}

AnchorLine ProgressBar::top() const {
    Q_D(const ProgressBar);

    return d->top;
}

AnchorLine ProgressBar::bottom() const {
    Q_D(const ProgressBar);

    return d->bottom;
}

AnchorLine ProgressBar::horizontalCenter() const {
    Q_D(const ProgressBar);

    return d->horizontalCenter;
}

AnchorLine ProgressBar::verticalCenter() const {
    Q_D(const ProgressBar);

    return d->verticalCenter;
}

void ProgressBar::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QProgressBar::changeEvent(event);
}

void ProgressBar::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QProgressBar::moveEvent(event);
}

void ProgressBar::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QProgressBar::resizeEvent(event);
}

void ProgressBar::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QProgressBar::showEvent(event);
}

void ProgressBar::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QProgressBar::hideEvent(event);
}

void ProgressBar::classBegin() {}

void ProgressBar::componentComplete() {
    Q_D(ProgressBar);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ProgressBarPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ProgressBar *bar = qobject_cast<ProgressBar*>(list->object)) {
        bar->d_func()->dataList.append(obj);
    }
}

void ProgressBarPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ProgressBar *bar = qobject_cast<ProgressBar*>(list->object)) {
        bar->d_func()->actionList.append(obj);

        if (!bar->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            bar->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            bar->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> ProgressBarPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ProgressBarPrivate::data_append);
}

QDeclarativeListProperty<QObject> ProgressBarPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ProgressBarPrivate::actions_append);
}

#include "moc_progressbar_p.cpp"

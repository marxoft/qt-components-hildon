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

#include "flickable_p.h"
#include "flickable_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QScrollBar>

Flickable::Flickable(QWidget *parent) :
    QScrollArea(parent),
    d_ptr(new FlickablePrivate(this))
{
    this->setWidgetResizable(true);
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(contentXChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(contentYChanged()));
}

Flickable::Flickable(FlickablePrivate &dd, QWidget *parent) :
    QScrollArea(parent),
    d_ptr(&dd)
{
    this->setWidgetResizable(true);
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(contentXChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(contentYChanged()));
}

Flickable::~Flickable() {}

void Flickable::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Flickable::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine Flickable::left() const {
    Q_D(const Flickable);

    return d->left;
}

AnchorLine Flickable::right() const {
    Q_D(const Flickable);

    return d->right;
}

AnchorLine Flickable::top() const {
    Q_D(const Flickable);

    return d->top;
}

AnchorLine Flickable::bottom() const {
    Q_D(const Flickable);

    return d->bottom;
}

AnchorLine Flickable::horizontalCenter() const {
    Q_D(const Flickable);

    return d->horizontalCenter;
}

AnchorLine Flickable::verticalCenter() const {
    Q_D(const Flickable);

    return d->verticalCenter;
}

bool Flickable::interactive() const {
    Q_D(const Flickable);

    return d->kineticScroller->isEnabled();
}

void Flickable::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(Flickable);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool Flickable::moving() const {
    Q_D(const Flickable);

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool Flickable::atXBeginning() const {
    return this->horizontalScrollBar()->value();
}

bool Flickable::atXEnd() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum();
}

bool Flickable::atYBeginning() const {
    return this->verticalScrollBar()->value() == 0;
}

bool Flickable::atYEnd() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->maximum();
}

int Flickable::contentX() const {
    return this->horizontalScrollBar()->value();
}

void Flickable::setContentX(int x) {
    this->horizontalScrollBar()->setValue(x);
}

int Flickable::contentY() const {
    return this->horizontalScrollBar()->value();
}

void Flickable::setContentY(int y) {
    this->verticalScrollBar()->setValue(y);
}

qreal Flickable::flickDeceleration() const {
    Q_D(const Flickable);

    return d->kineticScroller->decelerationFactor();
}

void Flickable::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(Flickable);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal Flickable::maximumFlickVelocity() const {
    Q_D(const Flickable);

    return d->kineticScroller->maximumVelocity();
}

void Flickable::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(Flickable);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

void Flickable::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QScrollArea::changeEvent(event);
}

void Flickable::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QScrollArea::moveEvent(event);
}

void Flickable::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QScrollArea::resizeEvent(event);
}

void Flickable::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QScrollArea::showEvent(event);
}

void Flickable::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QScrollArea::hideEvent(event);
}

void Flickable::classBegin() {}

void Flickable::componentComplete() {
    Q_D(Flickable);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void FlickablePrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->dataList.append(obj);
        obj->setParent(flickable);

        if ((!flickable->widget()) && (obj->isWidgetType())) {
            flickable->setWidget(qobject_cast<QWidget*>(obj));
        }
    }
}

void FlickablePrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->actionList.append(obj);

        if (!flickable->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            flickable->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            flickable->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> FlickablePrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlickablePrivate::data_append);
}

QDeclarativeListProperty<QObject> FlickablePrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlickablePrivate::actions_append);
}

#include "moc_flickable_p.cpp"

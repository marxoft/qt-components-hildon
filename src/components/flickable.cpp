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
#include <QGraphicsOpacityEffect>
#include <QTimer>

Flickable::Flickable(QWidget *parent) :
    QScrollArea(parent),
    d_ptr(new FlickablePrivate(this))
{
    Q_D(Flickable);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->setWidgetResizable(true);
    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
}

Flickable::Flickable(FlickablePrivate &dd, QWidget *parent) :
    QScrollArea(parent),
    d_ptr(&dd)
{
    Q_D(Flickable);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    this->setWidgetResizable(true);
    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged(int)));
    this->connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged(int)));
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

qreal Flickable::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Flickable::setOpacity(qreal opacity) {
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

    if (d->scrollTimer->isActive()) {
        return true;
    }

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool Flickable::atXBeginning() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->minimum();
}

bool Flickable::atXEnd() const {
    return this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum();
}

bool Flickable::atYBeginning() const {
    return this->verticalScrollBar()->value() == this->verticalScrollBar()->minimum();
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
    case QEvent::EnabledChange:
        emit enabledChanged();
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

void Flickable::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QScrollArea::focusInEvent(event);
}

void Flickable::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QScrollArea::focusOutEvent(event);
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

        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            flickable->d_func()->childrenList.append(widget);

            if (!flickable->widget()) {
                flickable->setWidget(widget);
            }
        }
    }
}

void FlickablePrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->childrenList.append(widget);
        flickable->d_func()->dataList.append(widget);

        if (!flickable->widget()) {
            flickable->setWidget(widget);
        }
    }
}

void FlickablePrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Flickable *flickable = qobject_cast<Flickable*>(list->object)) {
        flickable->d_func()->actionList.append(obj);
        flickable->d_func()->dataList.append(obj);

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

QDeclarativeListProperty<QWidget> FlickablePrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, FlickablePrivate::children_append);
}

QDeclarativeListProperty<QObject> FlickablePrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, FlickablePrivate::actions_append);
}

void FlickablePrivate::_q_onHorizontalScrollPositionChanged() {
    Q_Q(Flickable);

    if (!scrollTimer->isActive()) {
        emit q->movingChanged();

        if (atXBeginning) {
            atXBeginning = false;
            emit q->atXBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atXEndChanged();
        }
    }

    emit q->contentXChanged();

    scrollTimer->start();
}

void FlickablePrivate::_q_onVerticalScrollPositionChanged() {
    Q_Q(Flickable);

    if (!scrollTimer->isActive()) {
        emit q->movingChanged();

        if (atYBeginning) {
            atYBeginning = false;
            emit q->atYBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atYEndChanged();
        }
    }

    emit q->contentYChanged();

    scrollTimer->start();
}

void FlickablePrivate::_q_onScrollingStopped() {
    Q_Q(Flickable);

    bool xb = q->atXBeginning();
    bool xe = q->atYEnd();
    bool yb = q->atYBeginning();
    bool ye = q->atYEnd();

    if (xb != atXBeginning) {
        atXBeginning = xb;
        emit q->atXBeginningChanged();
    }

    if (xe != atXEnd) {
        atXEnd = xe;
        emit q->atXEndChanged();
    }

    if (yb != atYBeginning) {
        atYBeginning = yb;
        emit q->atYBeginningChanged();
    }

    if (ye != atYEnd) {
        atYEnd = ye;
        emit q->atYEndChanged();
    }

    emit q->movingChanged();
}

#include "moc_flickable_p.cpp"

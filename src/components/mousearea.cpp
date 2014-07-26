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

#include "mousearea_p.h"
#include "mousearea_p_p.h"
#include <QMouseEvent>

static const int PRESS_AND_HOLD_DURATION = 800;

MouseDrag::MouseDrag(QObject *parent) :
    QObject(parent),
    m_target(0),
    m_active(false),
    m_axis(XandYAxis),
    m_minX(0),
    m_maxX(10000),
    m_minY(0),
    m_maxY(10000),
    m_filter(false)
{
}

MouseDrag::~MouseDrag() {}

QWidget* MouseDrag::target() const {
    return m_target;
}

void MouseDrag::setTarget(QWidget *target) {
    if (target != this->target()) {
        m_target = target;
        emit targetChanged();
    }
}

void MouseDrag::resetTarget() {
    this->setTarget(0);
}

bool MouseDrag::active() const {
    return m_active;
}

void MouseDrag::setActive(bool active) {
    if (active != this->active()) {
        m_active = active;
        emit activeChanged();
    }
}

MouseDrag::DragAxis MouseDrag::axis() const {
    return m_axis;
}

void MouseDrag::setAxis(DragAxis axis) {
    if (axis != this->axis()) {
        m_axis = axis;
        emit axisChanged();
    }
}

int MouseDrag::minimumX() const {
    return m_minX;
}

void MouseDrag::setMinimumX(int x) {
    if (x != this->minimumX()) {
        m_minX = x;
        emit minimumXChanged();
    }
}

int MouseDrag::maximumX() const {
    return m_maxX;
}

void MouseDrag::setMaximumX(int x) {
    if (x != this->maximumX()) {
        m_maxX = x;
        emit maximumXChanged();
    }
}

int MouseDrag::minimumY() const {
    return m_minY;
}

void MouseDrag::setMinimumY(int y) {
    if (y != this->minimumY()) {
        m_minY = y;
        emit minimumYChanged();
    }
}

int MouseDrag::maximumY() const {
    return m_maxY;
}

void MouseDrag::setMaximumY(int y) {
    if (y != this->maximumY()) {
        m_maxY = y;
        emit maximumYChanged();
    }
}

bool MouseDrag::filterChildren() const {
    return m_filter;
}

void MouseDrag::setFilterChildren(bool filter) {
    if (filter != this->filterChildren()) {
        m_filter = filter;
        emit filterChildrenChanged();
    }
}

MouseArea::MouseArea(QWidget *parent) :
    Item(*new MouseAreaPrivate(this), parent)
{
}

MouseArea::MouseArea(MouseAreaPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
}

MouseArea::~MouseArea() {}

bool MouseArea::containsMouse() const {
    Q_D(const MouseArea);

    return d->containsMouse;
}

int MouseArea::mouseX() const {
    Q_D(const MouseArea);

    return d->mouseX;
}

int MouseArea::mouseY() const {
    Q_D(const MouseArea);

    return d->mouseY;
}

bool MouseArea::isPressed() const {
    Q_D(const MouseArea);

    return d->pressed;
}

bool MouseArea::preventStealing() const {
    Q_D(const MouseArea);

    return d->preventStealing;
}

void MouseArea::setPreventStealing(bool prevent) {
    if (prevent != this->preventStealing()) {
        Q_D(MouseArea);
        d->preventStealing = prevent;
        emit preventStealingChanged();
    }
}

void MouseArea::mousePressEvent(QMouseEvent *event) {
    if ((!this->isPressed()) && (this->rect().contains(event->pos()))) {
        Q_D(MouseArea);
        d->pressed = true;
        emit pressed();
        emit pressedChanged();

        if (!d->timerId) {
            d->timerId = this->startTimer(PRESS_AND_HOLD_DURATION);
        }
    }

    if (this->preventStealing()) {
        event->accept();
    }

    Item::mousePressEvent(event);
}

void MouseArea::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(MouseArea);

    if (this->isPressed()) {
        d->pressed = false;
        emit pressedChanged();
        emit released();

        if (this->rect().contains(event->pos())) {
            if (d->timerId) {
                emit clicked();
            }
        }
    }

    if (d->timerId) {
        this->killTimer(d->timerId);
        d->timerId = 0;
    }

    if (d->_drag) {
        d->_drag->setActive(false);
    }

    if (this->preventStealing()) {
        event->accept();
    }

    Item::mouseReleaseEvent(event);
}

void MouseArea::mouseMoveEvent(QMouseEvent *event) {
    if (!this->isPressed()) {
        return;
    }

    Q_D(MouseArea);

    if (event->x() != this->mouseX()) {
        if ((d->_drag) && (d->_drag->target())) {
            switch (d->_drag->axis()) {
            case MouseDrag::XAxis:
            case MouseDrag::XandYAxis:
            {
                int x = d->_drag->target()->x() + (event->x() - this->mouseX());

                if ((x >= d->_drag->minimumX()) && (x <= d->_drag->maximumX())) {
                    d->_drag->target()->move(x, d->_drag->target()->y());
                }

                break;
            }
            default:
                break;
            }
        }

        d->mouseX = event->x();
    }

    if (event->y() != this->mouseY()) {
        if ((d->_drag) && (d->_drag->target())) {
            switch (d->_drag->axis()) {
            case MouseDrag::YAxis:
            case MouseDrag::XandYAxis:
            {
                int y = d->_drag->target()->y() + (event->y() - this->mouseY());

                if ((y >= d->_drag->minimumY()) && (y <= d->_drag->maximumY())) {
                    d->_drag->target()->move(d->_drag->target()->x(), y);
                }

                break;
            }
            default:
                break;
            }
        }

        d->mouseY = event->y();
    }

    emit positionChanged();

    if (this->rect().contains(event->pos())) {
        if (!this->containsMouse()) {
            d->containsMouse = true;
            emit containsMouseChanged();
            emit entered();
        }
    }
    else if (this->containsMouse()) {
        d->containsMouse = false;
        emit containsMouseChanged();
        emit exited();

        if (d->timerId) {
            this->killTimer(d->timerId);
            d->timerId = 0;
        }
    }

    if (this->preventStealing()) {
        event->accept();
    }

    Item::mouseMoveEvent(event);
}

void MouseArea::mouseDoubleClickEvent(QMouseEvent *event) {
    if (this->rect().contains(event->pos())) {
        emit doubleClicked();
    }

    if (this->preventStealing()) {
        event->accept();
    }

    Item::mouseDoubleClickEvent(event);
}

void MouseArea::timerEvent(QTimerEvent *event) {
    if (this->isPressed()) {
        Q_D(MouseArea);
        emit pressAndHold();

        if (d->timerId) {
            this->killTimer(d->timerId);
            d->timerId = 0;
        }
    }

    Item::timerEvent(event);
}

MouseAreaPrivate::MouseAreaPrivate(MouseArea *parent) :
    ItemPrivate(parent),
    _drag(0),
    containsMouse(false),
    mouseX(0),
    mouseY(0),
    pressed(false),
    preventStealing(false),
    timerId(0)
{
}

MouseDrag* MouseAreaPrivate::drag() {
    if (!_drag) {
        _drag = new MouseDrag(q_func());
    }

    return _drag;
}

#include "moc_mousearea_p.cpp"

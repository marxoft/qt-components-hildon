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


#include "listitemmousearea_p.h"
#include "listitemcontent_p_p.h"
#include "mouseevent_p.h"
#include <QMouseEvent>

static const int PRESS_AND_HOLD_DURATION = 800;

class ListItemMouseAreaPrivate : public ListItemContentPrivate
{

public:
    ListItemMouseAreaPrivate(ListItemMouseArea *parent) :
        ListItemContentPrivate(parent),
        containsMouse(false),
        mouseX(0),
        mouseY(0),
        pressed(false),
        preventStealing(false),
        timerId(0)
    {
    }

    bool containsMouse;

    int mouseX;
    int mouseY;

    bool pressed;

    bool preventStealing;

    int timerId;

    QRect rect;

    Q_DECLARE_PUBLIC(ListItemMouseArea)
};

ListItemMouseArea::ListItemMouseArea(QObject *parent) :
    ListItemContent(*new ListItemMouseAreaPrivate(this), parent)
{
}

ListItemMouseArea::ListItemMouseArea(ListItemMouseAreaPrivate &dd, QObject *parent) :
    ListItemContent(dd, parent)
{
}

bool ListItemMouseArea::containsMouse() const {
    Q_D(const ListItemMouseArea);

    return d->containsMouse;
}

int ListItemMouseArea::mouseX() const {
    Q_D(const ListItemMouseArea);

    return d->mouseX;
}

int ListItemMouseArea::mouseY() const {
    Q_D(const ListItemMouseArea);

    return d->mouseY;
}

bool ListItemMouseArea::isPressed() const {
    Q_D(const ListItemMouseArea);

    return d->pressed;
}

bool ListItemMouseArea::preventStealing() const {
    Q_D(const ListItemMouseArea);

    return d->preventStealing;
}

void ListItemMouseArea::setPreventStealing(bool prevent) {
    if (prevent != this->preventStealing()) {
        Q_D(ListItemMouseArea);
        d->preventStealing = prevent;
        emit preventStealingChanged();
    }
}

bool ListItemMouseArea::editorEvent(QEvent *event, const QRect &rect) {
    Q_D(ListItemMouseArea);
    d->rect = QRect(rect.left(), rect.top(), this->width(), this->height());

    switch (event->type()) {
    case QEvent::MouseButtonPress:
        if (QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event)) {
            return this->mousePressEvent(mouseEvent);
        }

        break;
    case QEvent::MouseButtonRelease:
        if (QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event)) {
            return this->mouseReleaseEvent(mouseEvent);
        }

        break;
    case QEvent::MouseMove:
        if (QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event)) {
            return this->mouseMoveEvent(mouseEvent);
        }

        break;
    case QEvent::MouseButtonDblClick:
        if (QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event)) {
            return this->mouseDoubleClickEvent(mouseEvent);
        }

        break;
    default:
        break;
    }

    return ListItemContent::event(event);
}

bool ListItemMouseArea::mousePressEvent(QMouseEvent *event) {
    Q_D(ListItemMouseArea);

    if ((!this->isPressed()) && (d->rect.contains(event->pos()))) {
        d->pressed = true;
        MouseEvent me(event->x(), event->y(), event->button(), event->buttons(), event->modifiers());
        emit pressed(&me);
        emit pressedChanged();

        if (!d->timerId) {
            d->timerId = this->startTimer(PRESS_AND_HOLD_DURATION);
        }

        return true;
    }

    return false;
}

bool ListItemMouseArea::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(ListItemMouseArea);

    bool accept = false;

    if (this->isPressed()) {
        accept = true;
        d->pressed = false;
        MouseEvent me(event->x(), event->y(), event->button(), event->buttons(), event->modifiers(),
                      ((d->rect.contains(event->pos())) && (d->timerId)));
        emit pressedChanged();
        emit released(&me);

        if (me.isClick()) {
            emit clicked(&me);
        }
    }

    if (d->timerId) {
        this->killTimer(d->timerId);
        d->timerId = 0;
    }

    return accept;
}

bool ListItemMouseArea::mouseMoveEvent(QMouseEvent *event) {
    if (!this->isPressed()) {
        return false;
    }

    Q_D(ListItemMouseArea);
    
    d->mouseX = event->x();
    d->mouseY = event->y();
    MouseEvent me(event->x(), event->y(), event->button(), event->buttons(), event->modifiers());
    emit positionChanged(&me);

    if (d->rect.contains(event->pos())) {
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

    return true;
}

bool ListItemMouseArea::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_D(const ListItemMouseArea);

    if (d->rect.contains(event->pos())) {
        MouseEvent me(event->x(), event->y(), event->button(), event->buttons(), event->modifiers(), true);
        emit doubleClicked(&me);
        return true;
    }

    return false;
}

void ListItemMouseArea::timerEvent(QTimerEvent *event) {
    if (this->isPressed()) {
        Q_D(ListItemMouseArea);
        MouseEvent me(this->mouseX(), this->mouseY(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, false, true);
        emit pressAndHold(&me);

        if (d->timerId) {
            this->killTimer(d->timerId);
            d->timerId = 0;
        }
    }

    ListItemContent::timerEvent(event);
}

#include "moc_listitemmousearea_p.cpp"

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
 
#include "mouseevent_p.h"

MouseEvent::MouseEvent(int x, int y, Qt::MouseButton button, Qt::MouseButtons buttons,
                       Qt::KeyboardModifiers modifiers, bool isClick, bool wasHeld, QObject *parent) :
    QObject(parent),
    m_x(x),
    m_y(y),
    m_button(button),
    m_buttons(buttons),
    m_modifiers(modifiers),
    m_isClick(isClick),
    m_wasHeld(wasHeld),
    m_accepted(true)
{
}

MouseEvent::~MouseEvent() {}

int MouseEvent::x() const {
    return m_x;
}

void MouseEvent::setX(int x) {
    m_x = x;
}

int MouseEvent::y() const {
    return m_y;
}

void MouseEvent::setY(int y) {
    m_y = y;
}

int MouseEvent::button() const {
    return m_button;
}

int MouseEvent::buttons() const {
    return m_buttons;
}

int MouseEvent::modifiers() const {
    return m_modifiers;
}

bool MouseEvent::isClick() const {
    return m_isClick;
}

bool MouseEvent::wasHeld() const {
    return m_wasHeld;
}

bool MouseEvent::isAccepted() const {
    return m_accepted;
}

void MouseEvent::setAccepted(bool accepted) {
    m_accepted = accepted;
}


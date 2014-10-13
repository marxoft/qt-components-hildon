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
 
#include "keyevent_p.h"

KeyEvent::KeyEvent(const QKeyEvent &event, QObject *parent) :
    QObject(parent),
    m_event(event)
{
}

KeyEvent::~KeyEvent() {}

bool KeyEvent::isAccepted() const {
    return m_event.isAccepted();
}

void KeyEvent::setAccepted(bool accepted) {
    m_event.setAccepted(accepted);
}

bool KeyEvent::isAutoRepeat() const {
    return m_event.isAutoRepeat();
}

int KeyEvent::count() const {
    return m_event.count();
}

int KeyEvent::key() const {
    return m_event.key();
}

int KeyEvent::modifiers() const {
    return m_event.modifiers();
}

QString KeyEvent::text() const {
    return m_event.text();
}


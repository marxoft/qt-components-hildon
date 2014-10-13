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

#ifndef MOUSEEVENT_P_H
#define MOUSEEVENT_P_H

#include <QObject>
#include <qdeclarative.h>

class MouseEvent : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(int x READ x)
    Q_PROPERTY(int y READ y)
    Q_PROPERTY(int button READ button)
    Q_PROPERTY(int buttons READ buttons)
    Q_PROPERTY(int modifiers READ modifiers)
    Q_PROPERTY(bool wasHeld READ wasHeld)
    Q_PROPERTY(bool isClick READ isClick)
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)

public:
    MouseEvent(int x, int y, Qt::MouseButton button, Qt::MouseButtons buttons, 
               Qt::KeyboardModifiers modifiers, bool isClick = false, bool wasHeld = false, QObject *parent = 0);
               
    ~MouseEvent();

    int x() const;
    int y() const;
    int button() const;
    int buttons() const;
    int modifiers() const;
    bool wasHeld() const;
    bool isClick() const;

    void setX(int x);
    void setY(int y);

    bool isAccepted() const;
    void setAccepted(bool accepted);

private:
    int m_x;
    int m_y;
    Qt::MouseButton m_button;
    Qt::MouseButtons m_buttons;
    Qt::KeyboardModifiers m_modifiers;
    bool m_wasHeld;
    bool m_isClick;
    bool m_accepted;
};

QML_DECLARE_TYPE(MouseEvent)

#endif // MOUSEEVENT_P_H

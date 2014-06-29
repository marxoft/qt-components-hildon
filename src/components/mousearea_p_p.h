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

#ifndef MOUSEAREA_P_P_H
#define MOUSEAREA_P_P_H

#include "item_p_p.h"
#include "mousearea_p.h"

class MouseAreaPrivate : public ItemPrivate
{

public:
    MouseAreaPrivate(MouseArea *parent);

    MouseDrag* drag();

    MouseDrag *_drag;

    bool containsMouse;

    int mouseX;
    int mouseY;

    bool pressed;

    bool preventStealing;

    int timerId;
};

#endif // MOUSEAREA_P_P_H

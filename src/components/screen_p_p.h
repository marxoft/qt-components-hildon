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

#ifndef SCREEN_P_P_H
#define SCREEN_P_P_H

#include "screen_p.h"

class ScreenPrivate
{

public:
    ScreenPrivate(Screen *parent) :
        q_ptr(parent),
        orientationLock(Screen::LandscapeOrientation),
        currentOrientation(Screen::LandscapeOrientation),
        covered(false)
    {
    }

    virtual ~ScreenPrivate() {}

    void _q_onResized();

    void _q_onLockStateChanged(const QString &state);

    Screen *q_ptr;

    Screen::Orientation orientationLock;

    Screen::Orientation currentOrientation;

    bool covered;

    Q_DECLARE_PUBLIC(Screen)
};

#endif // SCREEN_P_P_H

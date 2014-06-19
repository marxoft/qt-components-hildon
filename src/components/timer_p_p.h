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

#ifndef TIMER_P_P_H
#define TIMER_P_P_H

#include "timer_p.h"

class TimerPrivate
{

public:
    TimerPrivate(Timer *parent) :
        q_ptr(parent),
        complete(false),
        timerId(0),
        interval(1000),
        repeat(false),
        running(false),
        triggeredOnStart(false)
    {
    }

    Timer *q_ptr;

    bool complete;

    int timerId;

    int interval;

    bool repeat;

    bool running;

    bool triggeredOnStart;

    Q_DECLARE_PUBLIC(Timer)
};

#endif // TIMER_P_P_H

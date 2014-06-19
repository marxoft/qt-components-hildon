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

#include "timer_p.h"
#include "timer_p_p.h"
#include <QTimerEvent>

Timer::Timer(QObject *parent) :
    QObject(parent),
    d_ptr(new TimerPrivate(this))
{
}

Timer::Timer(TimerPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Timer::~Timer() {
    this->stop();
}

int Timer::interval() const {
    Q_D(const Timer);

    return d->interval;
}

void Timer::setInterval(int interval) {
    Q_D(Timer);

    if (interval != this->interval()) {
        d->interval = interval;
        emit intervalChanged();
    }
}

bool Timer::repeat() const {
    Q_D(const Timer);

    return d->repeat;
}

void Timer::setRepeat(bool repeat) {
    Q_D(Timer);

    if (repeat != this->repeat()) {
        d->repeat = repeat;
        emit repeatChanged();
    }
}

bool Timer::running() const {
    Q_D(const Timer);

    return d->running;
}

void Timer::setRunning(bool running) {
    Q_D(Timer);

    if (!d->complete) {
        d->running = true;
        return;
    }

    if (running) {
        if (!this->running()) {
            this->start();
        }
    }
    else if (this->running()) {
        this->stop();
    }
}

bool Timer::triggeredOnStart() const {
    Q_D(const Timer);

    return d->triggeredOnStart;
}

void Timer::setTriggeredOnStart(bool triggered) {
    Q_D(Timer);

    if (triggered != this->triggeredOnStart()) {
        d->triggeredOnStart = triggered;
        emit triggeredOnStartChanged();
    }
}

void Timer::restart() {
    if (this->running()) {
        this->stop();
    }

    this->start();
}

void Timer::start() {
    Q_D(Timer);

    if (this->running()) {
        return;
    }

    d->timerId = this->startTimer(this->interval());

    if (d->timerId > 0) {
        d->running = true;
        emit runningChanged();

        if (this->triggeredOnStart()) {
            emit triggered();
        }
    }
}

void Timer::stop() {
    Q_D(Timer);

    if (this->running()) {
        this->killTimer(d->timerId);
        d->running = false;
        emit runningChanged();
    }
}

void Timer::classBegin() {}

void Timer::componentComplete() {
    Q_D(Timer);

    d->complete = true;

    if (this->running()) {
        this->start();
    }
}

void Timer::timerEvent(QTimerEvent *event) {
    event->accept();

    if (!this->repeat()) {
        this->stop();
    }

    emit triggered();
}

#include "moc_timer_p.cpp"

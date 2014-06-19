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

#include "timeselector_p.h"
#include "valueselector_p_p.h"
#include <QMaemo5TimePickSelector>

TimeSelector::TimeSelector(QObject *parent) :
    ValueSelector(parent)
{
    Q_D(ValueSelector);

    d->selector = new QMaemo5TimePickSelector(this);
    this->connect(d->selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

TimeSelector::~TimeSelector() {}

QTime TimeSelector::currentTime() const {
    Q_D(const ValueSelector);

    if (QMaemo5TimePickSelector *timeSelector = qobject_cast<QMaemo5TimePickSelector*>(d->selector)) {
        return timeSelector->currentTime();
    }

    return QTime();
}

void TimeSelector::setCurrentTime(const QTime &Time) {
    Q_D(ValueSelector);

    if (QMaemo5TimePickSelector *timeSelector = qobject_cast<QMaemo5TimePickSelector*>(d->selector)) {
        timeSelector->setCurrentTime(Time);
    }
}

int TimeSelector::minuteStep() const {
    Q_D(const ValueSelector);

    if (QMaemo5TimePickSelector *timeSelector = qobject_cast<QMaemo5TimePickSelector*>(d->selector)) {
        return timeSelector->minuteStep();
    }

    return 5;
}

void TimeSelector::setMinuteStep(int step) {
    Q_D(ValueSelector);

    if (QMaemo5TimePickSelector *timeSelector = qobject_cast<QMaemo5TimePickSelector*>(d->selector)) {
        timeSelector->setMinuteStep(step);
    }
}

QString TimeSelector::currentValueText() const {
    Q_D(const ValueSelector);

    return d->selector->currentValueText();
}

#include "moc_timeselector_p.cpp"

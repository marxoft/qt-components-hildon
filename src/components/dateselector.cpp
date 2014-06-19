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

#include "dateselector_p.h"
#include "valueselector_p_p.h"
#include <QMaemo5DatePickSelector>

DateSelector::DateSelector(QObject *parent) :
    ValueSelector(parent)
{
    Q_D(ValueSelector);

    d->selector = new QMaemo5DatePickSelector(this);
    this->connect(d->selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

DateSelector::~DateSelector() {}

QDate DateSelector::currentDate() const {
    Q_D(const ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        return dateSelector->currentDate();
    }

    return QDate();
}

void DateSelector::setCurrentDate(const QDate &date) {
    Q_D(ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        dateSelector->setCurrentDate(date);
    }
}

int DateSelector::minimumYear() const {
    Q_D(const ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        return dateSelector->minimumYear();
    }

    return 1900;
}

void DateSelector::setMinimumYear(int minYear) {
    Q_D(ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        dateSelector->setMinimumYear(minYear);
    }
}

int DateSelector::maximumYear() const {
    Q_D(const ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        return dateSelector->maximumYear();
    }

    return 2084;
}

void DateSelector::setMaximumYear(int maxYear) {
    Q_D(ValueSelector);

    if (QMaemo5DatePickSelector *dateSelector = qobject_cast<QMaemo5DatePickSelector*>(d->selector)) {
        dateSelector->setMaximumYear(maxYear);
    }
}

QString DateSelector::currentValueText() const {
    Q_D(const ValueSelector);

    return d->selector->currentValueText();
}

#include "moc_dateselector_p.cpp"

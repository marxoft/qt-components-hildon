/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHDATETIME_H
#define QCHDATETIME_H

#include <QObject>
#include <QDateTime>

class QchDateTime : public QObject
{
    Q_OBJECT

public:
    explicit QchDateTime(QObject *parent = 0);
    
public Q_SLOTS:
    static QDateTime currentDateTime();
    static QDate currentDate();
    static QTime currentTime();
    
    static int currentYear();
    static int currentMonth();
    static int currentDay();
    static int currentHour();
    static int currentMinute();
    static int currentSecond();
    
    static QDateTime dateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
    static QDate date(int year, int month, int day);
    static QTime time(int hour, int minute, int second = 0);
    
    static int day(const QDateTime &dt);
    static int month(const QDateTime &dt);
    static int year(const QDateTime &dt);
    static int hour(const QDateTime &dt);
    static int minute(const QDateTime &dt);
    static int second(const QDateTime &dt);

    static int daysInMonth(int year, int month);
    
    static QString shortDayName(int day);
    static QString longDayName(int day);
    static QString shortMonthName(int month);
    static QString longMonthName(int month);
    
    static QString amText();
    static QString pmText();
};

#endif // QCHDATETIME_H

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

#include "qchdatetime.h"
#include <QLocale>

/*!
    \class DateTime
    \brief Provides datetime functions.
    
    \ingroup components
    
    \note DateTime is a context property and cannot be created in QML.
*/
QchDateTime::QchDateTime(QObject *parent) :
    QObject(parent)
{
}

/*!
    \brief Returns the current datetime.
*/
QDateTime QchDateTime::currentDateTime() {
    return QDateTime::currentDateTime();
}

/*!
    \brief Returns the current date.
*/
QDate QchDateTime::currentDate() {
    return QDate::currentDate();
}

/*!
    \brief Returns the current time.
*/
QTime QchDateTime::currentTime() {
    return QTime::currentTime();
}

/*!
    \brief Returns the current year.
*/
int QchDateTime::currentYear() {
    return QDate::currentDate().year();
}

/*!
    \brief Returns the current month (1-12).
*/
int QchDateTime::currentMonth() {
    return QDate::currentDate().month();
}

/*!
    \brief Returns the current day (1-31).
*/
int QchDateTime::currentDay() {
    return QDate::currentDate().day();
}

/*!
    \brief Returns the current hour (0-23).
*/
int QchDateTime::currentHour() {
    return QTime::currentTime().hour();
}

/*!
    \brief Returns the current minute (0-59).
*/
int QchDateTime::currentMinute() {
    return QTime::currentTime().minute();
}

/*!
    \brief Returns the current second (0-59).
*/
int QchDateTime::currentSecond() {
    return QTime::currentTime().second();
}

/*!
    \brief Returns a datetime object created from \a year, \a month, \a day, \a hour, \a minute and \a second.
*/
QDateTime QchDateTime::dateTime(int year, int month, int day, int hour, int minute, int second) {
    return QDateTime(QDate(year, month, day), QTime(hour, minute, second));
}

/*!
    \brief Returns a date object created from \a year, \a month and \a day.
*/
QDate QchDateTime::date(int year, int month, int day) {
    return QDate(year, month, day);
}

/*!
    \brief Returns a time object created from \a hour, \a minute and \a second.
*/
QTime QchDateTime::time(int hour, int minute, int second) {
    return QTime(hour, minute, second);
}

/*!
    \brief Returns the day of the specified datetime object.
*/
int QchDateTime::day(const QDateTime &dt) {
    return dt.date().day();
}

/*!
    \brief Returns the month of the specified datetime object.
*/
int QchDateTime::month(const QDateTime &dt) {
    return dt.date().month();
}

/*!
    \brief Returns the year of the specified datetime object.
*/
int QchDateTime::year(const QDateTime &dt) {
    return dt.date().year();
}

/*!
    \brief Returns the hour of the specified datetime object.
*/
int QchDateTime::hour(const QDateTime &dt) {
    return dt.time().hour();
}

/*!
    \brief Returns the minute of the specified datetime object.
*/
int QchDateTime::minute(const QDateTime &dt) {
    return dt.time().minute();
}

/*!
    \brief Returns the second of the specified datetime object.
*/
int QchDateTime::second(const QDateTime &dt) {
    return dt.time().second();
}

/*!
    \brief Returns the number of days in the specified \a month of \a year.
*/
int QchDateTime::daysInMonth(int year, int month) {
    return QDate(year, month, 1).daysInMonth();
}

/*!
    \brief Returns the localized short name of \a day.
*/
QString QchDateTime::shortDayName(int day) {
    return QDate::shortDayName(day);
}

/*!
    \brief Returns the localized long name of \a day.
*/
QString QchDateTime::longDayName(int day) {
    return QDate::longDayName(day);
}

/*!
    \brief Returns the localized short name of \a month.
*/
QString QchDateTime::shortMonthName(int month) {
    return QDate::shortMonthName(month);
}

/*!
    \brief Returns the localized short name of \a month.
*/
QString QchDateTime::longMonthName(int month) {
    return QDate::longMonthName(month);
}

/*!
    \brief Returns the localized am text.
*/
QString QchDateTime::amText() {
    return QLocale().amText();
}

/*!
    \brief Returns the localized pm text.
*/
QString QchDateTime::pmText() {
    return QLocale().pmText();
}

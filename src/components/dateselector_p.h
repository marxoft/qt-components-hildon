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

#ifndef DATESELECTOR_P_H
#define DATESELECTOR_P_H

#include "valueselector_p.h"
#include <QDate>

class DateSelector : public ValueSelector
{
    Q_OBJECT

    Q_PROPERTY(int minimumYear READ minimumYear WRITE setMinimumYear)
    Q_PROPERTY(int maximumYear READ maximumYear WRITE setMaximumYear)
    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)

public:
    explicit DateSelector(QObject *parent = 0);
    ~DateSelector();

    QDate currentDate() const;
    void setCurrentDate(const QDate &date);

    int minimumYear() const;
    void setMinimumYear(int minYear);

    int maximumYear() const;
    void setMaximumYear(int maxYear);

    QString currentValueText() const;

signals:
    void selected(const QString &text);

private:
    Q_DISABLE_COPY(DateSelector)
};

QML_DECLARE_TYPE(DateSelector)

#endif // DATESELECTOR_P_H

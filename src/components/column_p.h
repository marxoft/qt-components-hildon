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

#ifndef COLUMN_P_H
#define COLUMN_P_H

#include "item_p.h"

class ColumnPrivate;

class Column : public Item
{
    Q_OBJECT

    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

public:
    explicit Column(QWidget *parent = 0);
    ~Column();

    int spacing() const;
    void setSpacing(int spacing);

signals:
    void spacingChanged();

protected:
    Column(ColumnPrivate &dd, QWidget *parent = 0);

    virtual void componentComplete();

    Q_DECLARE_PRIVATE(Column)

private:
    Q_DISABLE_COPY(Column)
};

QML_DECLARE_TYPE(Column)

#endif // COLUMN_P_H

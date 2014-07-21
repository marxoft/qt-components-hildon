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

#ifndef BUTTONROW_P_H
#define BUTTONROW_P_H

#include "item_p.h"

class ButtonRowPrivate;

class ButtonRow : public Item
{
    Q_OBJECT

    Q_PROPERTY(bool exclusive READ exclusive WRITE setExclusive NOTIFY exclusiveChanged)

public:
    explicit ButtonRow(QWidget *parent = 0);
    ~ButtonRow();

    bool exclusive() const;
    void setExclusive(bool exclusive);

signals:
    void exclusiveChanged();

protected:
    ButtonRow(ButtonRowPrivate &dd, QWidget *parent = 0);

    Q_DECLARE_PRIVATE(ButtonRow)

private:
    Q_DISABLE_COPY(ButtonRow)
};

QML_DECLARE_TYPE(ButtonRow)

#endif // BUTTONROW_P_H

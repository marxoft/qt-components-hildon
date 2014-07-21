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

#ifndef FLOW_P_H
#define FLOW_P_H

#include "item_p.h"

class FlowPrivate;

class Flow : public Item
{
    Q_OBJECT

    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

public:
    explicit Flow(QWidget *parent = 0);
    ~Flow();

    int spacing() const;
    void setSpacing(int spacing);

signals:
    void spacingChanged();

protected:
    Flow(FlowPrivate &dd, QWidget *parent = 0);

    virtual void componentComplete();

    Q_DECLARE_PRIVATE(Flow)

private:
    Q_DISABLE_COPY(Flow)
};

QML_DECLARE_TYPE(Flow)

#endif // FLOW_P_H

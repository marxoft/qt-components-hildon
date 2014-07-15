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

#ifndef LISTITEMRECTANGLE_P_H
#define LISTITEMRECTANGLE_P_H

#include "listitemcontent_p.h"
#include "rectangleproperties_p.h"

class ListItemRectanglePrivate;

class ListItemRectangle : public ListItemContent
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PRIVATE_PROPERTY(ListItemRectangle::d_func(), Border* border READ border CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(ListItemRectangle::d_func(), Gradient* gradient READ gradient WRITE setGradient RESET resetGradient)

public:
    explicit ListItemRectangle(QObject *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    qreal radius() const;
    void setRadius(qreal radius);

    void paint(QPainter *painter, const QRect &rect);

signals:
    void colorChanged();
    void radiusChanged();

protected:
    ListItemRectangle(ListItemRectanglePrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(ListItemRectangle)

private:
    Q_DISABLE_COPY(ListItemRectangle)
};

QML_DECLARE_TYPE(ListItemRectangle)

#endif // LISTITEMRECTANGLE_P_H

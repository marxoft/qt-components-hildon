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

#ifndef ZOOMAREA_P_H
#define ZOOMAREA_P_H

#include "item_p.h"

class ZoomAreaPrivate;

class ZoomArea : public Item
{
    Q_OBJECT

public:
    explicit ZoomArea(QWidget *parent = 0);
    ~ZoomArea();

signals:
    void zoomIn();
    void zoomOut();
    void zoomAt(int xPos, int yPos);

protected:
    ZoomArea(ZoomAreaPrivate &dd, QWidget *parent = 0);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    Q_DECLARE_PRIVATE(ZoomArea)

private:
    Q_DISABLE_COPY(ZoomArea)
};

QML_DECLARE_TYPE(ZoomArea)

#endif // ZOOMAREA_P_H

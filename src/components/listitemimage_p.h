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

#ifndef LISTITEMIMAGE_P_H
#define LISTITEMIMAGE_P_H

#include "listitemimagebase_p.h"

class ListItemImagePrivate;

class ListItemImage : public ListItemImageBase
{
    Q_OBJECT

    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(int paintedWidth READ paintedWidth NOTIFY paintedGeometryChanged)
    Q_PROPERTY(int paintedHeight READ paintedHeight NOTIFY paintedGeometryChanged)

    Q_ENUMS(FillMode)

public:
    enum FillMode {
        Stretch = 0,
        PreserveAspectFit,
        PreserveAspectCrop,
        Tile,
        TileVertically,
        TileHorizontally
    };

    explicit ListItemImage(QObject *parent = 0);

    FillMode fillMode() const;
    void setFillMode(FillMode mode);
    
    QPixmap pixmap() const;
    void setPixmap(const QPixmap &p);
    
    int paintedWidth() const;
    int paintedHeight() const;

    virtual void paint(QPainter *painter, const QRect &rect);

signals:
    void fillModeChanged();
    void paintedGeometryChanged();

protected:
    ListItemImage(ListItemImagePrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(ListItemImage)

private:
    Q_DISABLE_COPY(ListItemImage)
};

QML_DECLARE_TYPE(ListItemImage)

#endif // LISTITEMIMAGE_P_H

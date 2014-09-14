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

#ifndef LISTITEMBORDERIMAGE_P_H
#define LISTITEMBORDERIMAGE_P_H

#include "listitemimagebase_p.h"
#include <qdeclarative.h>

class ImageBorder;
class ListItemBorderImagePrivate;

class ListItemBorderImage : public ListItemImageBase
{
    Q_OBJECT

    Q_PRIVATE_PROPERTY(ListItemBorderImage::d_func(), ImageBorder* border READ border CONSTANT FINAL)
    Q_PROPERTY(TileMode horizontalTileMode READ horizontalTileMode WRITE setHorizontalTileMode NOTIFY horizontalTileModeChanged)
    Q_PROPERTY(TileMode verticalTileMode READ verticalTileMode WRITE setVerticalTileMode NOTIFY verticalTileModeChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize NOTIFY sourceSizeChanged) // read-only

    Q_ENUMS(TileMode)

public:
    enum TileMode {
        Stretch = 0,
        Repeat,
        Round
    };

    explicit ListItemBorderImage(QObject *parent = 0);
    ~ListItemBorderImage();

    TileMode horizontalTileMode() const;
    void setHorizontalTileMode(TileMode mode);

    TileMode verticalTileMode() const;
    void setVerticalTileMode(TileMode mode);
    
    virtual void paint(QPainter *painter, const QRect &rect);

signals:
    void horizontalTileModeChanged();
    void verticalTileModeChanged();
    void sourceSizeChanged();

protected:
    ListItemBorderImage(ListItemBorderImagePrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(ListItemBorderImage)

private:
    Q_DISABLE_COPY(ListItemBorderImage)
};

QML_DECLARE_TYPE(ListItemBorderImage)

#endif // LISTITEMBORDERIMAGE_P_H

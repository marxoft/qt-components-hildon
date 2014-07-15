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

class ImageLoader;
class ListItemImagePrivate;

class ListItemImage : public ListItemImageBase
{
    Q_OBJECT

    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize WRITE setSourceSize RESET resetSourceSize NOTIFY sourceSizeChanged)

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

    void setSourceSize(const QSize &size);
    void resetSourceSize();

    void paint(QPainter *painter, const QRect &rect);

signals:
    void fillModeChanged();

protected:
    ListItemImage(ListItemImagePrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(ListItemImage)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderFinished(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderCanceled(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderProgressChanged(qreal))

private:
    Q_DISABLE_COPY(ListItemImage)
};

QML_DECLARE_TYPE(ListItemImage)

#endif // LISTITEMIMAGE_P_H

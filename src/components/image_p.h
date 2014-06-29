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

#ifndef IMAGE_P_H
#define IMAGE_P_H

#include "imagebase_p.h"
#include <qdeclarative.h>

class ImageLoader;
class ImagePrivate;

class Image : public ImageBase
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

    explicit Image(QWidget *parent = 0);
    ~Image();

    FillMode fillMode() const;
    void setFillMode(FillMode mode);

    void setSourceSize(const QSize &size);
    void resetSourceSize();

signals:
    void fillModeChanged();

private:
    Image(ImagePrivate &dd, QWidget *parent = 0);

    Q_DISABLE_COPY(Image)
    Q_DECLARE_PRIVATE(Image)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderFinished(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderCanceled(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderProgressChanged(qreal))
};

QML_DECLARE_TYPE(Image)

#endif // IMAGE_P_H

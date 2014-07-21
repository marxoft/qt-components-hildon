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

#ifndef BORDERIMAGE_P_H
#define BORDERIMAGE_P_H

#include "imagebase_p.h"
#include <qdeclarative.h>

class ImageBorder : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int left READ left WRITE setLeft RESET resetLeft NOTIFY leftChanged)
    Q_PROPERTY(int right READ right WRITE setRight RESET resetRight NOTIFY rightChanged)
    Q_PROPERTY(int top READ top WRITE setTop RESET resetTop NOTIFY topChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY resetBottom NOTIFY bottomChanged)

public:
    explicit ImageBorder(ImageBase *parent = 0);
    ~ImageBorder();

    int left() const;
    void setLeft(int left);
    void resetLeft();

    int right() const;
    void setRight(int right);
    void resetRight();

    int top() const;
    void setTop(int top);
    void resetTop();

    int bottom() const;
    void setBottom(int bottom);
    void resetBottom();

signals:
    void leftChanged();
    void rightChanged();
    void topChanged();
    void bottomChanged();

private:
    int m_left;
    int m_right;
    int m_top;
    int m_bottom;

    Q_DISABLE_COPY(ImageBorder)
};

class ImageLoader;
class BorderImagePrivate;

class BorderImage : public ImageBase
{
    Q_OBJECT

    Q_PRIVATE_PROPERTY(BorderImage::d_func(), ImageBorder* border READ border CONSTANT FINAL)
    Q_PROPERTY(TileMode horizontalTileMode READ horizontalTileMode WRITE setHorizontalTileMode NOTIFY horizontalTileModeChanged)
    Q_PROPERTY(TileMode verticalTileMode READ verticalTileMode WRITE setVerticalTileMode NOTIFY verticalTileModeChanged)

    Q_ENUMS(TileMode)

public:
    enum TileMode {
        Stretch = 0,
        Repeat,
        Round
    };

    explicit BorderImage(QWidget *parent = 0);
    ~BorderImage();

    TileMode horizontalTileMode() const;
    void setHorizontalTileMode(TileMode mode);

    TileMode verticalTileMode() const;
    void setVerticalTileMode(TileMode mode);

signals:
    void horizontalTileModeChanged();
    void verticalTileModeChanged();

protected:
    BorderImage(BorderImagePrivate &dd, QWidget *parent = 0);

    Q_DECLARE_PRIVATE(BorderImage)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderFinished(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderCanceled(ImageLoader*))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoaderProgressChanged(qreal))

private:
    Q_DISABLE_COPY(BorderImage)
};

QML_DECLARE_TYPE(BorderImage)
QML_DECLARE_TYPE(ImageBorder)

#endif // BORDERIMAGE_P_H

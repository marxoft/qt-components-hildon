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

#ifndef IMAGELOADER_P_H
#define IMAGELOADER_P_H

#include <QObject>
#include <QUrl>
#include <QSize>
#include <QImage>
#include <QCache>

class CachedImage;
class ImageLoaderPrivate;

class ImageLoader : public QObject
{
    Q_OBJECT

public:
    explicit ImageLoader();
    ~ImageLoader();

    QImage image() const;

public slots:
    void loadImage(const QUrl &url,
              const QSize &size,
              const QSize &sourceSize,
              int fillMode,
              Qt::TransformationMode transformMode,
              bool mirror,
              bool cache);

    void loadBorderImage(const QUrl &url,
                         const QSize &size,
                         int topBorder,
                         int rightBorder,
                         int leftBorder,
                         int bottomBorder,
                         int horizontalTileMode,
                         int verticalTileMode,
                         Qt::TransformationMode transformMode,
                         bool mirror,
                         bool cache);

    void cancel();

signals:
    void finished(ImageLoader *loader);
    void canceled(ImageLoader *loader);
    void progressChanged(qreal progress);

protected:
    ImageLoader(ImageLoaderPrivate &dd);

    static QThread *loadingThread;

    static QCache<QUrl, CachedImage> imageCache;

    QScopedPointer<ImageLoaderPrivate> d_ptr;

    Q_DECLARE_PRIVATE(ImageLoader)

    Q_PRIVATE_SLOT(d_func(), void _q_onProgressChanged(qint64,qint64))
    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
    Q_PRIVATE_SLOT(d_func(), void _q_loadImageFromProvider(QString,QString))
    Q_PRIVATE_SLOT(d_func(), void _q_loadImageFromCache(QUrl))
    Q_PRIVATE_SLOT(d_func(), void _q_loadImageFromLocalFile(QString))
    Q_PRIVATE_SLOT(d_func(), void _q_loadImageFromData(QByteArray))

private:
    Q_DISABLE_COPY(ImageLoader)
};

#endif // IMAGELOADER_P_H

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

#include "imageloader_p.h"
#include "imageloader_p_p.h"
#include "screen_p.h"
#include <qdeclarative.h>
#include <QDeclarativeEngine>
#include <QDeclarativeImageProvider>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QPainter>

QThread* ImageLoader::loadingThread = 0;

QCache<QUrl, CachedImage> ImageLoader::imageCache;

static const int MAX_REDIRECTS = 8;

class CachedImage
{

public:
    CachedImage(const QUrl &u) :
        url(u)
    {
    }

    const QUrl url;
    QImage image;
};

ImageLoader::ImageLoader() :
    QObject(),
    d_ptr(new ImageLoaderPrivate(this))
{
}

ImageLoader::ImageLoader(ImageLoaderPrivate &dd) :
    QObject(),
    d_ptr(&dd)
{
}

ImageLoader::~ImageLoader() {}

QImage ImageLoader::image() const {
    Q_D(const ImageLoader);

    return d->image;
}

void ImageLoader::loadImage(const QUrl &url,
                            const QSize &size,
                            const QSize &sourceSize,
                            Image::FillMode fillMode,
                            Qt::TransformationMode transformMode,
                            bool mirror,
                            bool cache) {

    Q_D(ImageLoader);

    d->url = url;
    d->size = size;
    d->sourceSize = sourceSize;
    d->fillMode = fillMode;
    d->transformMode = transformMode;
    d->mirror = mirror;
    d->cache = cache;
    d->isBorderImage = false;

    d->load();
}

void ImageLoader::loadBorderImage(const QUrl &url,
                                  const QSize &size,
                                  int topBorder,
                                  int rightBorder,
                                  int leftBorder,
                                  int bottomBorder,
                                  BorderImage::TileMode horizontalTileMode,
                                  BorderImage::TileMode verticalTileMode,
                                  Qt::TransformationMode transformMode,
                                  bool mirror,
                                  bool cache) {

    Q_D(ImageLoader);

    d->url = url;
    d->size = size;
    d->topBorder = topBorder;
    d->rightBorder = rightBorder;
    d->leftBorder = leftBorder;
    d->bottomBorder = bottomBorder;
    d->horizontalTileMode = horizontalTileMode;
    d->verticalTileMode = verticalTileMode;
    d->transformMode = transformMode;
    d->mirror = mirror;
    d->cache = cache;
    d->isBorderImage = true;

    d->load();
}

void ImageLoader::cancel() {
    Q_D(ImageLoader);

    if (d->reply) {
        d->reply->abort();
    }
    else {
        emit canceled(this);
    }
}

ImageLoaderPrivate::ImageLoaderPrivate(ImageLoader *parent) :
    q_ptr(parent),
    reply(0),
    initialThread(parent->thread()),
    fillMode(Image::Stretch),
    horizontalTileMode(BorderImage::Stretch),
    verticalTileMode(BorderImage::Stretch),
    transformMode(Qt::FastTransformation),
    topBorder(0),
    rightBorder(0),
    leftBorder(0),
    bottomBorder(0),
    mirror(false),
    cache(true)
{
}

ImageLoaderPrivate::~ImageLoaderPrivate() {
    if (reply) {
        delete reply;
        reply = 0;
    }
}

void ImageLoaderPrivate::load() {
    Q_Q(ImageLoader);

    if (url.isEmpty()) {
        emit q->finished(q);
        return;
    }

    if (url.scheme().isEmpty()) {
        url.setScheme("file");
    }

    if (CachedImage *ci = ImageLoader::imageCache.object(url)) {
        if (ci->image.size() == sourceSize) {
            if (!ImageLoader::loadingThread) {
                ImageLoader::loadingThread = new QThread;
                ImageLoader::loadingThread->start(QThread::LowPriority);
            }

            q->moveToThread(ImageLoader::loadingThread);
            QMetaObject::invokeMethod(q, "_q_loadImageFromCache", Qt::QueuedConnection, Q_ARG(QUrl, url));
            return;
        }
    }

    if (url.scheme() == "image") {
        if (!ImageLoader::loadingThread) {
            ImageLoader::loadingThread = new QThread;
            ImageLoader::loadingThread->start(QThread::LowPriority);
        }

        q->moveToThread(ImageLoader::loadingThread);
        QMetaObject::invokeMethod(q, "_q_loadImageFromProvider", Qt::QueuedConnection, Q_ARG(QString, url.host()), Q_ARG(QString, url.path().mid(1)));
    }
    else if (url.scheme() == "file") {
        if (!ImageLoader::loadingThread) {
            ImageLoader::loadingThread = new QThread;
            ImageLoader::loadingThread->start(QThread::LowPriority);
        }

        q->moveToThread(ImageLoader::loadingThread);
        QMetaObject::invokeMethod(q, "_q_loadImageFromLocalFile", Qt::QueuedConnection, Q_ARG(QString, url.toLocalFile()));
    }
    else {
        if (reply) {
            delete reply;
            reply = 0;
        }

        // TODO: Find a better way to aquire the QDeclarativeEngine instance
        reply = qmlEngine(Screen::instance())->networkAccessManager()->get(QNetworkRequest(url));
        q->connect(reply, SIGNAL(downloadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
        q->connect(reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

void ImageLoaderPrivate::followRedirect(const QUrl &u) {
    Q_Q(const ImageLoader);

    if (reply) {
        delete reply;
        reply = 0;
    }

    // TODO: Find a better way to aquire the QDeclarativeEngine instance
    reply = qmlEngine(Screen::instance())->networkAccessManager()->get(QNetworkRequest(u));
    q->connect(reply, SIGNAL(downloadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
    q->connect(reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
}

void ImageLoaderPrivate::_q_onProgressChanged(qint64 downloaded, qint64 total) {
    Q_Q(ImageLoader);

    emit q->progressChanged((downloaded > 0) && (total > 0) ? float (downloaded / total) : 0);
}

void ImageLoaderPrivate::_q_onReplyFinished() {
    if (!reply) {
        return;
    }

    if (redirects < MAX_REDIRECTS) {
        QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

        if (!redirect.isEmpty()) {
            reply->deleteLater();
            reply = 0;
            redirects++;
            this->followRedirect(redirect);
            return;
        }
    }

    Q_Q(ImageLoader);

    switch (reply->error()) {
    case QNetworkReply::NoError:
        break;
    case QNetworkReply::OperationCanceledError:
        reply->deleteLater();
        reply = 0;
        emit q->canceled(q);
        return;
    default:
        reply->deleteLater();
        reply = 0;
        emit q->finished(q);
        return;
    }

    if (!ImageLoader::loadingThread) {
        ImageLoader::loadingThread = new QThread;
        ImageLoader::loadingThread->start(QThread::LowPriority);
    }

    q->moveToThread(ImageLoader::loadingThread);
    QMetaObject::invokeMethod(q, "_q_loadImageFromData", Qt::QueuedConnection, Q_ARG(QByteArray, reply->readAll()));
}

void ImageLoaderPrivate::_q_loadImageFromProvider(const QString &provider, const QString &id) {
    Q_Q(ImageLoader);

    QImage i;

    // TODO: Find a better way to aquire the QDeclarativeEngine instance
    if (QDeclarativeImageProvider *p = qmlEngine(Screen::instance())->imageProvider(provider)) {
        switch (p->imageType()) {
        case QDeclarativeImageProvider::Pixmap:
            i = p->requestPixmap(id, &size, sourceSize).toImage();
            break;
        default:
            i = p->requestImage(id, &size, sourceSize);
            break;
        }
    }

    if (!i.isNull()) {
        if (cache) {
            CachedImage *ci = new CachedImage(url);

            if ((!sourceSize.isEmpty()) && ((sourceSize.width() < i.width()) || (sourceSize.height() < i.height()))) {
                ci->image = i.scaled(sourceSize, (sourceSize.width() == 0) || (sourceSize.height() == 0) ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio, transformMode);
            }
            else {
                ci->image = i;
            }

            ImageLoader::imageCache.insert(url, ci);
        }

        if (isBorderImage) {
            this->drawBorderImage(i);
        }
        else {
            this->drawImage(i);
        }
    }

    if (initialThread) {
        q->moveToThread(initialThread);
    }

    emit q->finished(q);
}

void ImageLoaderPrivate::_q_loadImageFromCache(const QUrl &key) {
    Q_Q(ImageLoader);

    if (CachedImage *ci = ImageLoader::imageCache.object(key)) {
        if (isBorderImage) {
            this->drawBorderImage(ci->image);
        }
        else {
            this->drawImage(ci->image);
        }
    }

    if (initialThread) {
        q->moveToThread(initialThread);
    }

    emit q->finished(q);
}

void ImageLoaderPrivate::_q_loadImageFromLocalFile(const QString &fileName) {
    Q_Q(ImageLoader);

    if (image.load(fileName)) {
        if (cache) {
            CachedImage *ci = new CachedImage(url);

            if ((!sourceSize.isEmpty()) && ((sourceSize.width() < image.width()) || (sourceSize.height() < image.height()))) {
                ci->image = image.scaled(sourceSize, (sourceSize.width() == 0) || (sourceSize.height() == 0) ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio, transformMode);
            }
            else {
                ci->image = image;
            }

            ImageLoader::imageCache.insert(url, ci);
        }

        if (isBorderImage) {
            this->drawBorderImage(image);
        }
        else {
            this->drawImage(image);
        }
    }

    if (initialThread) {
        q->moveToThread(initialThread);
    }

    emit q->finished(q);
}

void ImageLoaderPrivate::_q_loadImageFromData(const QByteArray &data) {
    Q_Q(ImageLoader);

    if (image.loadFromData(data)) {
        if (cache) {
            CachedImage *ci = new CachedImage(url);

            if ((!sourceSize.isEmpty()) && ((sourceSize.width() < image.width()) || (sourceSize.height() < image.height()))) {
                ci->image = image.scaled(sourceSize, (sourceSize.width() == 0) || (sourceSize.height() == 0) ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio, transformMode);
            }
            else {
                ci->image = image;
            }

            ImageLoader::imageCache.insert(url, ci);
        }

        if (isBorderImage) {
            this->drawBorderImage(image);
        }
        else {
            this->drawImage(image);
        }
    }

    if (initialThread) {
        q->moveToThread(initialThread);
    }

    emit q->finished(q);
}

void ImageLoaderPrivate::drawImage(QImage &i) {
    switch (fillMode) {
    case Image::Stretch:
        image = i.scaled(size, Qt::IgnoreAspectRatio, transformMode);
        break;
    case Image::PreserveAspectFit:
    {
        image = QImage(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);

        i = i.scaled(size, Qt::KeepAspectRatio, transformMode);

        QPainter painter;
        painter.begin(&image);
        painter.drawImage((image.width() - i.width()) / 2, (image.height() - i.height()) / 2, i);
        painter.end();
        break;
    }
    case Image::PreserveAspectCrop:
    {
        image = QImage(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);

        i = i.scaled(size, Qt::KeepAspectRatioByExpanding, transformMode);

        QPainter painter;
        painter.begin(&image);
        painter.drawImage((image.width() - i.width()) / 2, (image.height() - i.height()) / 2, i);
        painter.end();
        break;
    }
    case Image::Tile:
    {
        image = QImage(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::red);

        QPainter painter;
        painter.begin(&image);
        painter.drawTiledPixmap(image.rect(), QPixmap::fromImage(i));
        painter.end();
        break;
    }
    case Image::TileHorizontally:
    {
        image = QImage(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);

        i = i.scaled(i.width(), image.height(), Qt::IgnoreAspectRatio, transformMode);

        QPainter painter;
        painter.begin(&image);
        painter.drawTiledPixmap(image.rect(), QPixmap::fromImage(i));
        painter.end();
        break;
    }
    case Image::TileVertically:
    {
        image = QImage(size, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::transparent);

        i = i.scaled(image.width(), i.height(), Qt::IgnoreAspectRatio, transformMode);

        QPainter painter;
        painter.begin(&image);
        painter.drawTiledPixmap(image.rect(), QPixmap::fromImage(i));
        painter.end();
        break;
    }
    default:
        image = i.scaled(size, Qt::IgnoreAspectRatio, transformMode);
        break;
    }

    if (mirror) {
        image = image.mirrored(true, false);
    }
}

void ImageLoaderPrivate::drawBorderImage(QImage &i) {
    image = QImage(size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&image);

    QRect rect = image.rect();
    QRect sourceRect = i.rect();

    // Top-left
    painter.drawImage(QRect(rect.left(), rect.top(), leftBorder, topBorder),
                       i,
                       QRect(sourceRect.left(), sourceRect.top(), leftBorder, topBorder));

    // Top-right
    painter.drawImage(QRect(rect.right() - rightBorder, rect.top(), rightBorder, topBorder),
                       i,
                       QRect(sourceRect.right() - rightBorder, sourceRect.top(), rightBorder, topBorder));

    // Bottom-left
    painter.drawImage(QRect(rect.left(), rect.bottom() - bottomBorder, leftBorder, bottomBorder),
                       i,
                       QRect(sourceRect.left(), sourceRect.bottom() - bottomBorder, leftBorder, bottomBorder));

    // Bottom-right
    painter.drawImage(QRect(rect.right() - rightBorder, rect.bottom() - bottomBorder, bottomBorder, rightBorder),
                       i,
                       QRect(sourceRect.right() - rightBorder, sourceRect.bottom() - bottomBorder, rightBorder, bottomBorder));

    QRect topMiddleRect(rect.left() + leftBorder, rect.top(), rect.width() - (leftBorder + rightBorder), topBorder);
    QRect bottomMiddleRect(rect.left() + leftBorder, rect.bottom() - bottomBorder, rect.width() - (leftBorder + rightBorder), bottomBorder);
    QRect leftMiddleRect(rect.left(), rect.top() + topBorder, leftBorder, rect.height() - (topBorder + bottomBorder));
    QRect rightMiddleRect(rect.right() - rightBorder, rect.top() + topBorder, rightBorder, rect.height() - (topBorder + bottomBorder));
    QRect centerRect(rect.left() + leftBorder, rect.top() + topBorder, rect.width() - (leftBorder + rightBorder), rect.height() - (topBorder + bottomBorder));

    QRect topMiddleSourceRect(sourceRect.left() + leftBorder, sourceRect.top(), sourceRect.width() - (leftBorder + rightBorder), topBorder);
    QRect bottomMiddleSourceRect(sourceRect.left() + leftBorder, sourceRect.bottom() - bottomBorder, sourceRect.width() - (leftBorder + rightBorder), bottomBorder);
    QRect leftMiddleSourceRect(sourceRect.left(), sourceRect.top() + topBorder, leftBorder, sourceRect.height() - (topBorder + bottomBorder));
    QRect rightMiddleSourceRect(sourceRect.right() - rightBorder, sourceRect.top() + topBorder, rightBorder, sourceRect.height() - (topBorder + bottomBorder));
    QRect centerSourceRect(sourceRect.left() + leftBorder, sourceRect.top() + topBorder, sourceRect.width() - (leftBorder + rightBorder), sourceRect.height() - (topBorder + bottomBorder));


    switch (horizontalTileMode) {
    case BorderImage::Repeat:
        switch (verticalTileMode) {
        case BorderImage::Repeat:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect)));

            break;
        case BorderImage::Round:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect).scaled(leftMiddleSourceRect.width(), leftMiddleRect.height() / leftMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect).scaled(rightMiddleSourceRect.width(), rightMiddleRect.height() / rightMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerSourceRect.width(), centerRect.height() / centerSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        default:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect).scaled(leftMiddleSourceRect.width(), leftMiddleRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect).scaled(rightMiddleSourceRect.width(), rightMiddleRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerSourceRect.width(), centerRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        }

        break;
    case BorderImage::Round:
        switch (verticalTileMode) {
        case BorderImage::Repeat:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect).scaled(topMiddleRect.width() / topMiddleSourceRect.width(), topMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect).scaled(bottomMiddleRect.width() / bottomMiddleSourceRect.width(), bottomMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerRect.width() / centerSourceRect.width(), centerRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        case BorderImage::Round:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect).scaled(topMiddleRect.width() / topMiddleSourceRect.width(), topMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect).scaled(bottomMiddleRect.width() / bottomMiddleSourceRect.width(), bottomMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect).scaled(leftMiddleSourceRect.width(), leftMiddleRect.height() / leftMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect).scaled(rightMiddleSourceRect.width(), rightMiddleRect.height() / rightMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerRect.width() / centerSourceRect.width(), centerRect.height() / centerSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        default:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect).scaled(topMiddleRect.width() / topMiddleSourceRect.width(), topMiddleRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect).scaled(bottomMiddleRect.width() / bottomMiddleSourceRect.width(), bottomMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect).scaled(leftMiddleSourceRect.width(), leftMiddleRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect).scaled(rightMiddleSourceRect.width(), rightMiddleRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerRect.width() / centerSourceRect.width(), centerRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        }

        break;
    default:
        switch (verticalTileMode) {
        case BorderImage::Repeat:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect).scaled(topMiddleRect.width(), topMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect).scaled(bottomMiddleRect.width(), bottomMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerRect.width(), centerSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        case BorderImage::Round:
            // Top-middle
            painter.drawTiledPixmap(topMiddleRect, QPixmap::fromImage(i.copy(topMiddleSourceRect).scaled(topMiddleRect.width(), topMiddleRect.height() / topMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Bottom-middle
            painter.drawTiledPixmap(bottomMiddleRect, QPixmap::fromImage(i.copy(bottomMiddleSourceRect).scaled(bottomMiddleRect.width(), bottomMiddleRect.height() / bottomMiddleSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            // Left-middle
            painter.drawTiledPixmap(leftMiddleRect, QPixmap::fromImage(i.copy(leftMiddleSourceRect)));

            // Right-middle
            painter.drawTiledPixmap(rightMiddleRect, QPixmap::fromImage(i.copy(rightMiddleSourceRect)));

            // Center
            painter.drawTiledPixmap(centerRect, QPixmap::fromImage(i.copy(centerSourceRect).scaled(centerRect.width(), centerSourceRect.height() / centerSourceRect.height(), Qt::IgnoreAspectRatio, transformMode)));

            break;
        default:
            // Top-middle
            painter.drawImage(topMiddleRect, i, topMiddleSourceRect);

            // Bottom-middle
            painter.drawImage(bottomMiddleRect, i, bottomMiddleSourceRect);

            // Left-middle
            painter.drawImage(leftMiddleRect, i, leftMiddleSourceRect);

            // Right-middle
            painter.drawImage(rightMiddleRect, i, rightMiddleSourceRect);

            // Center
            painter.drawImage(centerRect, i, centerSourceRect);

            break;
        }

        break;
    }

    painter.end();

    if (mirror) {
        image = image.mirrored(true, false);
    }
}

#include "moc_imageloader_p.cpp"

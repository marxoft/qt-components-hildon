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

#include "imagebase_p.h"
#include "imagebase_p_p.h"
#include <QDeclarativeInfo>

ImageBase::ImageBase(QWidget *parent) :
    Item(*new ImageBasePrivate(this), parent)
{
}

ImageBase::ImageBase(ImageBasePrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
}

ImageBase::~ImageBase() {}

QUrl ImageBase::source() const {
    Q_D(const ImageBase);

    return d->source;
}

void ImageBase::setSource(const QUrl &url) {
    if (url != this->source()) {
        Q_D(ImageBase);
        d->source = url;
        emit sourceChanged();

        if (d->complete) {
            d->load();
        }
    }
}

QSize ImageBase::sourceSize() const {
    Q_D(const ImageBase);

    return d->sourceSize;
}

void ImageBase::setSourceSize(const QSize &size) {
    if (size != this->sourceSize()) {
        Q_D(ImageBase);
        d->sourceSize = size;
        emit sourceSizeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

void ImageBase::resetSourceSize() {
    this->setSourceSize(QSize());
}

bool ImageBase::asynchronous() const {
    Q_D(const ImageBase);
    
    return d->asynchronous;
}

void ImageBase::setAsynchronous(bool async) {
    if (async != this->asynchronous()) {
        Q_D(ImageBase);
        d->asynchronous = async;
        emit asynchronousChanged();
    }
}

bool ImageBase::cache() const {
    Q_D(const ImageBase);

    return d->cache;
}

void ImageBase::setCache(bool cache) {
    if (cache != this->cache()) {
        Q_D(ImageBase);
        d->cache = cache;
        emit cacheChanged();
    }
}

bool ImageBase::mirror() const {
    Q_D(const ImageBase);

    return d->mirror;
}

void ImageBase::setMirror(bool mirror) {
    if (mirror != this->mirror()) {
        Q_D(ImageBase);
        d->mirror = mirror;
        emit mirrorChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

bool ImageBase::smooth() const {
    Q_D(const ImageBase);

    return d->smooth;
}

void ImageBase::setSmooth(bool smooth) {
    if (smooth != this->smooth()) {
        Q_D(ImageBase);
        d->smooth = smooth;
        emit smoothChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

qreal ImageBase::progress() const {
    Q_D(const ImageBase);

    return d->progress;
}

ImageBase::Status ImageBase::status() const {
    Q_D(const ImageBase);

    return d->status;
}

void ImageBase::componentComplete() {
    Item::componentComplete();

    Q_D(ImageBase);

    if (!this->source().isEmpty()) {
        d->load();
    }
}

QSize ImageBase::sizeHint() const {
    Q_D(const ImageBase);
    return QSize(d->pix.width(), d->pix.height());
}

ImageBasePrivate::ImageBasePrivate(ImageBase *parent) :
    ItemPrivate(parent),
    explicitSourceSize(false),
    asynchronous(false),
    cache(true),
    mirror(false),
    smooth(false),
    progress(0.0),
    status(ImageBase::Null)
{
}

void ImageBasePrivate::load() {
    Q_Q(ImageBase);
    
    if (source.isEmpty()) {
        pix.clear(q);
        status = ImageBase::Null;
        progress = 0.0;
        this->pixmapChange();
        emit q->progressChanged();
        emit q->statusChanged();
        q->update();
    }
    else {
        QDeclarativePixmap::Options options;
        
        if (asynchronous) {
            options |= QDeclarativePixmap::Asynchronous;
        }
        
        if (cache) {
            options |= QDeclarativePixmap::Cache;
        }
        
        pix.clear(q);
        pix.load(qmlEngine(q), source, explicitSourceSize ? sourceSize : QSize(), options);
        
        if (pix.isLoading()) {
            progress = 0.0;
            status = ImageBase::Loading;
            emit q->progressChanged();
            emit q->statusChanged();
            
            static int thisRequestProgress = -1;
            static int thisRequestFinished = -1;
            
            if (thisRequestProgress == -1) {
                thisRequestProgress =
                ImageBase::staticMetaObject.indexOfSlot("_q_requestProgress(qint64,qint64)");
                thisRequestFinished =
                ImageBase::staticMetaObject.indexOfSlot("_q_requestFinished()");
            }
            
            pix.connectFinished(q, thisRequestFinished);
            pix.connectDownloadProgress(q, thisRequestProgress);
        }
        else {
            this->_q_requestFinished();
        }
    }
}

void ImageBasePrivate::_q_requestProgress(qint64 received, qint64 total) {
    switch (status) {
    case ImageBase::Loading:
        if (total > 0) {
            Q_Q(ImageBase);
            progress = qreal (received) / total;
            emit q->progressChanged();
        }
        
        break;
    default:
        break;
    }
}

void ImageBasePrivate::_q_requestFinished() {
    Q_Q(ImageBase);
    ImageBase::Status oldStatus = status;
    qreal oldProgress = progress;
    
    if (pix.isError()) {
        status = ImageBase::Error;
        qmlInfo(q) << pix.error();
    }
    else {
        status = ImageBase::Ready;
    }
    
    progress = 1.0;
    this->pixmapChange();
    
    if ((sourceSize.width() != pix.width()) || (sourceSize.height() != pix.height())) {
        emit q->sourceSizeChanged();
    }
    
    if (status != oldStatus) {
        emit q->statusChanged();
    }
    
    if (progress != oldProgress) {
        emit q->progressChanged();
    }
    
    q->update();
}

void ImageBasePrivate::pixmapChange() {}

#include "moc_imagebase_p.cpp"

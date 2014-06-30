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
#include <QPainter>
#include <QPaintEvent>

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

void ImageBase::paintEvent(QPaintEvent *event) {
    Q_D(ImageBase);

    QPainter painter(this);
    painter.drawImage(this->rect(), d->image);

    event->accept();
}

ImageBasePrivate::ImageBasePrivate(ImageBase *parent) :
    ItemPrivate(parent),
    cache(true),
    mirror(false),
    smooth(false),
    progress(0.0),
    status(ImageBase::Null)
{
}

void ImageBasePrivate::load() {}

#include "moc_imagebase_p.cpp"

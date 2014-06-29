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

#include "image_p.h"
#include "image_p_p.h"
#include "imageloader_p.h"

Image::Image(QWidget *parent) :
    ImageBase(*new ImagePrivate(this), parent)
{
}

Image::Image(ImagePrivate &dd, QWidget *parent) :
    ImageBase(dd, parent)
{
}

Image::~Image() {}

Image::FillMode Image::fillMode() const {
    Q_D(const Image);

    return d->fillMode;
}

void Image::setFillMode(FillMode mode) {
    if (mode != this->fillMode()) {
        Q_D(Image);
        d->fillMode = mode;
        emit fillModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

void Image::setSourceSize(const QSize &size) {
    if (size != this->sourceSize()) {
        Q_D(Image);
        d->sourceSize = size;

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

void Image::resetSourceSize() {
    this->setSourceSize(QSize());
}

ImagePrivate::ImagePrivate(Image *parent) :
    ImageBasePrivate(parent),
    fillMode(Image::Stretch)
{
}

void ImagePrivate::load() {
    Q_Q(Image);

    if (source.isEmpty()) {
        image = QImage();
        progress = 1.0;
        status = Image::Null;
        q->update();
        emit q->progressChanged();
        emit q->statusChanged();
        return;
    }

    progress = 0.0;
    status = Image::Loading;
    emit q->progressChanged();
    emit q->statusChanged();

    ImageLoader *loader = new ImageLoader;
    q->connect(loader, SIGNAL(finished(ImageLoader*)), q, SLOT(_q_onLoaderFinished(ImageLoader*)));
    q->connect(loader, SIGNAL(canceled(ImageLoader*)), q, SLOT(_q_onLoaderCanceled(ImageLoader*)));
    q->connect(loader, SIGNAL(progressChanged(qreal)), q, SLOT(_q_onLoaderProgressChanged(qreal)));
    q->connect(q, SIGNAL(destroyed()), loader, SLOT(deleteLater()));
    loader->loadImage(source, q->size(), sourceSize, fillMode, smooth ? Qt::SmoothTransformation : Qt::FastTransformation, mirror, cache);
}

void ImagePrivate::_q_onLoaderFinished(ImageLoader *loader) {
    Q_Q(Image);

    image = loader->image();
    loader->deleteLater();
    q->update();

    progress = 1.0;
    status = image.isNull() ? Image::Error : Image::Ready;
    emit q->progressChanged();
    emit q->statusChanged();    
}

void ImagePrivate::_q_onLoaderCanceled(ImageLoader *loader) {
    Q_Q(Image);

    loader->deleteLater();
    progress = 0.0;
    status = Image::Null;
    emit q->progressChanged();
    emit q->statusChanged();
}

void ImagePrivate::_q_onLoaderProgressChanged(qreal p) {
    Q_Q(Image);

    progress = p;
    emit q->progressChanged();
}

#include "moc_image_p.cpp"

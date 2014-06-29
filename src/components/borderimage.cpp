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

#include "borderimage_p.h"
#include "borderimage_p_p.h"
#include "imageloader_p.h"

ImageBorder::ImageBorder(ImageBase *parent) :
    QObject(parent),
    m_left(0),
    m_right(0),
    m_top(0),
    m_bottom(0)
{
}

ImageBorder::~ImageBorder() {}

int ImageBorder::left() const {
    return m_left;
}

void ImageBorder::setLeft(int left) {
    if (left != this->left()) {
        m_left = left;
        emit leftChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetLeft() {
    this->setLeft(0);
}

int ImageBorder::right() const {
    return m_right;
}

void ImageBorder::setRight(int right) {
    if (right != this->right()) {
        m_right = right;
        emit rightChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetRight() {
    this->setRight(0);
}

int ImageBorder::top() const {
    return m_top;
}

void ImageBorder::setTop(int top) {
    if (top != this->top()) {
        m_top = top;
        emit topChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetTop() {
    this->setTop(0);
}

int ImageBorder::bottom() const {
    return m_bottom;
}

void ImageBorder::setBottom(int bottom) {
    if (bottom != this->bottom()) {
        m_bottom = bottom;
        emit bottomChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetBottom() {
    this->setBottom(0);
}

BorderImage::BorderImage(QWidget *parent) :
    ImageBase(*new BorderImagePrivate(this), parent)
{
}

BorderImage::BorderImage(BorderImagePrivate &dd, QWidget *parent) :
    ImageBase(dd, parent)
{
}

BorderImage::~BorderImage() {}

BorderImage::TileMode BorderImage::horizontalTileMode() const {
    Q_D(const BorderImage);

    return d->horizontalTileMode;
}

void BorderImage::setHorizontalTileMode(TileMode mode) {
    if (mode != this->horizontalTileMode()) {
        Q_D(BorderImage);
        d->horizontalTileMode = mode;
        emit horizontalTileModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

BorderImage::TileMode BorderImage::verticalTileMode() const {
    Q_D(const BorderImage);

    return d->verticalTileMode;
}

void BorderImage::setVerticalTileMode(TileMode mode) {
    if (mode != this->verticalTileMode()) {
        Q_D(BorderImage);
        d->verticalTileMode = mode;
        emit verticalTileModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

BorderImagePrivate::BorderImagePrivate(BorderImage *parent) :
    ImageBasePrivate(parent),
    imageBorder(0)
{
}

ImageBorder* BorderImagePrivate::border() {
    Q_Q(BorderImage);

    if (!imageBorder) {
        imageBorder = new ImageBorder(q);
    }

    return imageBorder;
}

void BorderImagePrivate::load() {
    Q_Q(BorderImage);

    if (source.isEmpty()) {
        image = QImage();
        progress = 1.0;
        status = ImageBase::Null;
        q->update();
        emit q->progressChanged();
        emit q->statusChanged();
        return;
    }

    progress = 0.0;
    status = BorderImage::Loading;
    emit q->progressChanged();
    emit q->statusChanged();

    ImageLoader *loader = new ImageLoader;
    q->connect(loader, SIGNAL(finished(ImageLoader*)), q, SLOT(_q_onLoaderFinished(ImageLoader*)));
    q->connect(loader, SIGNAL(canceled(ImageLoader*)), q, SLOT(_q_onLoaderCanceled(ImageLoader*)));
    q->connect(loader, SIGNAL(progressChanged(qreal)), q, SLOT(_q_onLoaderProgressChanged(qreal)));
    q->connect(q, SIGNAL(destroyed()), loader, SLOT(deleteLater()));

    if (imageBorder) {
        loader->loadBorderImage(source, q->size(), imageBorder->top(), imageBorder->right(), imageBorder->left(), imageBorder->bottom(),
                                horizontalTileMode, verticalTileMode, smooth ? Qt::SmoothTransformation : Qt::FastTransformation, mirror, cache);
    }
    else {
        loader->loadBorderImage(source, q->size(), 0, 0, 0, 0,
                                horizontalTileMode, verticalTileMode, smooth ? Qt::SmoothTransformation : Qt::FastTransformation, mirror, cache);
    }
}

void BorderImagePrivate::_q_onLoaderFinished(ImageLoader *loader) {
    Q_Q(BorderImage);

    image = loader->image();
    loader->deleteLater();
    q->update();

    progress = 1.0;
    status = image.isNull() ? ImageBase::Error : ImageBase::Ready;
    emit q->progressChanged();
    emit q->statusChanged();
}

void BorderImagePrivate::_q_onLoaderCanceled(ImageLoader *loader) {
    Q_Q(BorderImage);

    loader->deleteLater();
    progress = 0.0;
    status = ImageBase::Null;
    emit q->progressChanged();
    emit q->statusChanged();
}

void BorderImagePrivate::_q_onLoaderProgressChanged(qreal p) {
    Q_Q(BorderImage);

    progress = p;
    emit q->progressChanged();
}

#include "moc_borderimage_p.cpp"

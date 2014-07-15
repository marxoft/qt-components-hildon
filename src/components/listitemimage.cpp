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

#include "listitemimage_p.h"
#include "listitemimagebase_p_p.h"
#include "imageloader_p.h"
#include <QPainter>

class ListItemImagePrivate : public ListItemImageBasePrivate
{

public:
    ListItemImagePrivate(ListItemImage *parent) :
        ListItemImageBasePrivate(parent),
        fillMode(ListItemImage::Stretch)
    {
    }

    ListItemImage::FillMode fillMode;

    void load() {
        Q_Q(ListItemImage);

        if (source.isEmpty()) {
            image = QImage();
            progress = 1.0;
            status = ListItemImage::Null;
            emit q->progressChanged();
            emit q->statusChanged();
            return;
        }

        progress = 0.0;
        status = ListItemImage::Loading;
        emit q->progressChanged();
        emit q->statusChanged();

        ImageLoader *loader = new ImageLoader;
        q->connect(loader, SIGNAL(finished(ImageLoader*)), q, SLOT(_q_onLoaderFinished(ImageLoader*)));
        q->connect(loader, SIGNAL(canceled(ImageLoader*)), q, SLOT(_q_onLoaderCanceled(ImageLoader*)));
        q->connect(loader, SIGNAL(progressChanged(qreal)), q, SLOT(_q_onLoaderProgressChanged(qreal)));
        q->connect(q, SIGNAL(destroyed()), loader, SLOT(deleteLater()));
        loader->loadImage(source, QSize(q->width(), q->height()), sourceSize, fillMode, smooth ? Qt::SmoothTransformation : Qt::FastTransformation, mirror, cache);
    }

    void _q_onLoaderFinished(ImageLoader *loader) {
        Q_Q(ListItemImage);

        image = loader->image();
        loader->deleteLater();

        progress = 1.0;
        status = image.isNull() ? ListItemImage::Error : ListItemImage::Ready;
        emit q->progressChanged();
        emit q->statusChanged();
    }

    void _q_onLoaderCanceled(ImageLoader *loader) {
        Q_Q(ListItemImage);

        loader->deleteLater();
        progress = 0.0;
        status = ListItemImage::Null;
        emit q->progressChanged();
        emit q->statusChanged();
    }

    void _q_onLoaderProgressChanged(qreal p) {
        Q_Q(ListItemImage);

        progress = p;
        emit q->progressChanged();
    }

    Q_DECLARE_PUBLIC(ListItemImage)
};

ListItemImage::ListItemImage(QObject *parent) :
    ListItemImageBase(*new ListItemImagePrivate(this), parent)
{
}

ListItemImage::ListItemImage(ListItemImagePrivate &dd, QObject *parent) :
    ListItemImageBase(dd, parent)
{
}

ListItemImage::FillMode ListItemImage::fillMode() const {
    Q_D(const ListItemImage);

    return d->fillMode;
}

void ListItemImage::setFillMode(FillMode mode) {
    if (mode != this->fillMode()) {
        Q_D(ListItemImage);
        d->fillMode = mode;
        emit fillModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
//            d->load();
        }
    }
}

void ListItemImage::setSourceSize(const QSize &size) {
    if (size != this->sourceSize()) {
        Q_D(ListItemImage);
        d->sourceSize = size;

        if ((d->complete) && (!this->source().isEmpty())) {
//            d->load();
        }
    }
}

void ListItemImage::resetSourceSize() {
    this->setSourceSize(QSize());
}

void ListItemImage::paint(QPainter *painter, const QRect &rect) {
    Q_D(const ListItemImage);

    painter->save();
    painter->setOpacity(this->opacity());
    painter->setRenderHint(QPainter::Antialiasing, this->smooth());
    painter->drawImage(QRect(rect.left() + this->x(),
                             rect.top() + this->y(),
                             this->width(),
                             this->height()),
                       QImage(this->source().toLocalFile()));
    painter->restore();

    foreach (ListItemContent *content, d->contentList) {
        if (content->isVisible()) {
            content->paint(painter,
                           QRect(rect.left() + this->x(),
                                 rect.top() + this->y(),
                                 this->width(),
                                 this->height()));
        }
    }
}

#include "moc_listitemimage_p.cpp"

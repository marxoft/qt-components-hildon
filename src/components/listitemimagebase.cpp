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

#include "listitemimagebase_p.h"
#include "listitemimagebase_p_p.h"

ListItemImageBase::ListItemImageBase(QObject *parent) :
    ListItemContent(*new ListItemImageBasePrivate(this), parent)
{
}

ListItemImageBase::ListItemImageBase(ListItemImageBasePrivate &dd, QObject *parent) :
    ListItemContent(dd, parent)
{
}

QUrl ListItemImageBase::source() const {
    Q_D(const ListItemImageBase);

    return d->source;
}

void ListItemImageBase::setSource(const QUrl &url) {
    if (url != this->source()) {
        Q_D(ListItemImageBase);
        d->source = url;
        emit sourceChanged();

        if (d->complete) {
//            d->load();
        }
    }
}

QSize ListItemImageBase::sourceSize() const {
    Q_D(const ListItemImageBase);

    return d->sourceSize;
}

bool ListItemImageBase::cache() const {
    Q_D(const ListItemImageBase);

    return d->cache;
}

void ListItemImageBase::setCache(bool cache) {
    if (cache != this->cache()) {
        Q_D(ListItemImageBase);
        d->cache = cache;
        emit cacheChanged();
    }
}

bool ListItemImageBase::mirror() const {
    Q_D(const ListItemImageBase);

    return d->mirror;
}

void ListItemImageBase::setMirror(bool mirror) {
    if (mirror != this->mirror()) {
        Q_D(ListItemImageBase);
        d->mirror = mirror;
        emit mirrorChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
//            d->load();
        }
    }
}

bool ListItemImageBase::smooth() const {
    Q_D(const ListItemImageBase);

    return d->smooth;
}

void ListItemImageBase::setSmooth(bool smooth) {
    if (smooth != this->smooth()) {
        Q_D(ListItemImageBase);
        d->smooth = smooth;
        emit smoothChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
//            d->load();
        }
    }
}

qreal ListItemImageBase::progress() const {
    Q_D(const ListItemImageBase);

    return d->progress;
}

ListItemImageBase::Status ListItemImageBase::status() const {
    Q_D(const ListItemImageBase);

    return d->status;
}

void ListItemImageBase::componentComplete() {
    ListItemContent::componentComplete();

    Q_D(ListItemImageBase);

    if (!this->source().isEmpty()) {
//        d->load();
    }
}

void ListItemImageBase::paint(QPainter *painter, const QRect &rect) {
    Q_UNUSED(painter);
    Q_UNUSED(rect);
}

#include "moc_listitemimagebase_p.cpp"

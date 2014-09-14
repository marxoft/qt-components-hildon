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
#include "modelindex_p.h"
#include <QDeclarativeInfo>
#include <QDeclarativeContext>
#include <QAbstractItemView>

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
    }
}

QSize ListItemImageBase::sourceSize() const {
    Q_D(const ListItemImageBase);

    return d->sourceSize;
}

void ListItemImageBase::setSourceSize(const QSize &size) {
    if (size != this->sourceSize()) {
        Q_D(ListItemImageBase);
        d->sourceSize = size;
        d->explicitSourceSize = size.isValid();
        emit sourceSizeChanged();
    }
}

void ListItemImageBase::resetSourceSize() {
    this->setSourceSize(QSize());
}

bool ListItemImageBase::asynchronous() const {
    Q_D(const ListItemImageBase);
    
    return d->asynchronous;
}

void ListItemImageBase::setAsynchronous(bool async) {
    if (async != this->asynchronous()) {
        Q_D(ListItemImageBase);
        d->asynchronous = async;
        emit asynchronousChanged();
    }
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

void ListItemImageBase::update() {
    if (QDeclarativeContext *context = qmlContext(this)) {
        if (QObject *obj = context->contextProperty("view").value<QObject*>()) {
            if (QAbstractItemView *view = qobject_cast<QAbstractItemView*>(obj)) {
                view->viewport()->update(view->viewport()->rect());
            }
        }
    }
}

bool ListItemImageBasePrivate::load() {
    Q_Q(ListItemImageBase);
    
    if (pix.isLoading()) {
        return false;
    }
    
    if (source.isEmpty()) {
        pix.clear(q);
        status = ListItemImageBase::Null;
        progress = 0.0;
        this->pixmapChange();
        emit q->progressChanged();
        emit q->statusChanged();
        return true;
    }
    
    pix.clear(q);
    pix.load(qmlEngine(q), source, explicitSourceSize ? sourceSize : QSize());
    
    if (pix.isLoading()) {
        progress = 0.0;
        status = ListItemImageBase::Loading;
        emit q->progressChanged();
        emit q->statusChanged();
            
        static int thisRequestProgress = -1;
        static int thisRequestFinished = -1;
            
        if (thisRequestProgress == -1) {
            thisRequestProgress =
            ListItemImageBase::staticMetaObject.indexOfSlot("_q_requestProgress(qint64,qint64)");
            thisRequestFinished =
            ListItemImageBase::staticMetaObject.indexOfSlot("_q_requestFinished()");
        }
        
        pix.connectFinished(q, thisRequestFinished);
        pix.connectDownloadProgress(q, thisRequestProgress);
        return false;
    }
    
    ListItemImageBase::Status oldStatus = status;
    qreal oldProgress = progress;
    
    if (pix.isError()) {
        status = ListItemImageBase::Error;
        qmlInfo(q) << pix.error();
    }
    else {
        status = ListItemImageBase::Ready;
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
    
    return true;
}

void ListItemImageBasePrivate::_q_requestProgress(qint64 received, qint64 total) {
    switch (status) {
    case ListItemImageBase::Loading:
        if (total > 0) {
            Q_Q(ListItemImageBase);
            progress = qreal (received) / total;
            emit q->progressChanged();
        }
        
        break;
    default:
        break;
    }
}

void ListItemImageBasePrivate::_q_requestFinished() {
    Q_Q(ListItemImageBase);
    q->update();
}

void ListItemImageBasePrivate::pixmapChange() {}

#include "moc_listitemimagebase_p.cpp"

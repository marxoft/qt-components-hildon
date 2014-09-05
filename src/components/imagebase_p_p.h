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

#ifndef IMAGEBASE_P_P_H
#define IMAGEBASE_P_P_H

#include "imagebase_p.h"
#include "item_p_p.h"
#include "private/qdeclarativepixmapcache_p.h"

class ImageBasePrivate : public ItemPrivate
{

public:
    ImageBasePrivate(ImageBase *parent);

    virtual void load();
    
    virtual void pixmapChange();
    
    void _q_requestProgress(qint64 received, qint64 total);
    
    virtual void _q_requestFinished();
    
    QDeclarativePixmap pix;

    QUrl source;

    QSize sourceSize;
    
    bool explicitSourceSize;
    
    bool asynchronous;

    bool cache;

    bool mirror;

    bool smooth;

    qreal progress;

    ImageBase::Status status;

    Q_DECLARE_PUBLIC(ImageBase)
};

#endif // IMAGEBASE_P_P_H

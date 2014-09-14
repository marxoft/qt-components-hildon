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

#ifndef LISTITEMIMAGEBASE_P_P_H
#define LISTITEMIMAGEBASE_P_P_H

#include "listitemimagebase_p.h"
#include "listitemcontent_p_p.h"
#include "private/qdeclarativepixmapcache_p.h"

class ListItemImageBasePrivate : public ListItemContentPrivate
{

public:
    ListItemImageBasePrivate(ListItemImageBase *parent) :
        ListItemContentPrivate(parent),
        explicitSourceSize(false),
        asynchronous(false),
        cache(true),
        mirror(false),
        smooth(false),
        progress(0.0),
        status(ListItemImageBase::Null)
    {
    }

    virtual bool load();
    
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

    ListItemImageBase::Status status;
    
    mutable QHash<QUrl, QDeclarativePixmap> pixmaps;

    Q_DECLARE_PUBLIC(ListItemImageBase)
};

#endif // LISTITEMIMAGEBASE_P_P_H

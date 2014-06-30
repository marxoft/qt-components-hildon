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
#include <QUrl>

class ImageBasePrivate : public ItemPrivate
{

public:
    ImageBasePrivate(ImageBase *parent);

    virtual void load();

    QUrl source;

    QSize sourceSize;

    bool cache;

    bool mirror;

    bool smooth;

    qreal progress;

    ImageBase::Status status;

    QImage image;

    Q_DECLARE_PUBLIC(ImageBase)
};

#endif // IMAGEBASE_P_P_H

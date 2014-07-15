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

#ifndef LISTITEMIMAGEBASE_P_H
#define LISTITEMIMAGEBASE_P_H

#include "listitemcontent_p.h"

class ListItemImageBasePrivate;

class ListItemImageBase : public ListItemContent
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSize sourceSize READ sourceSize NOTIFY sourceSizeChanged)
    Q_PROPERTY(bool cache READ cache WRITE setCache NOTIFY cacheChanged)
    Q_PROPERTY(bool mirror READ mirror WRITE setMirror NOTIFY mirrorChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    Q_ENUMS(Status)

public:
    enum Status {
        Null = 0,
        Ready,
        Loading,
        Error
    };

    explicit ListItemImageBase(QObject *parent = 0);

    QUrl source() const;
    void setSource(const QUrl &url);

    QSize sourceSize() const;

    bool cache() const;
    void setCache(bool cache);

    bool mirror() const;
    void setMirror(bool mirror);

    bool smooth() const;
    void setSmooth(bool smooth);

    qreal progress() const;

    Status status() const;

    void paint(QPainter *painter, const QRect &rect);

signals:
    void sourceChanged();
    void sourceSizeChanged();
    void cacheChanged();
    void mirrorChanged();
    void smoothChanged();
    void progressChanged();
    void statusChanged();

protected:
    ListItemImageBase(ListItemImageBasePrivate &dd, QObject *parent = 0);

    void componentComplete();

    Q_DECLARE_PRIVATE(ListItemImageBase)

private:
    Q_DISABLE_COPY(ListItemImageBase)
};

#endif // LISTITEMIMAGEBASE_P_H

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

#ifndef IMAGELOADER_P_P_H
#define IMAGELOADER_P_P_H

#include "imageloader_p.h"

class QNetworkReply;

class ImageLoaderPrivate
{

public:
    ImageLoaderPrivate(ImageLoader *parent);
    virtual ~ImageLoaderPrivate();

    void load();

    void followRedirect(const QUrl &u);

    void _q_onProgressChanged(qint64 downloaded, qint64 total);

    void _q_onReplyFinished();

    void _q_loadImageFromProvider(const QString &provider, const QString &id);

    void _q_loadImageFromCache(const QUrl &key);

    void _q_loadImageFromLocalFile(const QString &fileName);

    void _q_loadImageFromData(const QByteArray &data);

    void drawImage(QImage &i);
    void drawBorderImage(QImage &i);

    ImageLoader *q_ptr;

    QThread *initialThread;

    QNetworkReply *reply;

    QUrl url;

    QSize size;

    QSize sourceSize;

    int fillMode;

    int horizontalTileMode;
    int verticalTileMode;

    Qt::TransformationMode transformMode;

    int topBorder;
    int rightBorder;
    int leftBorder;
    int bottomBorder;

    bool mirror;

    bool cache;

    bool isBorderImage;

    int redirects;

    QImage image;

    Q_DECLARE_PUBLIC(ImageLoader)
};

#endif // IMAGELOADER_P_P_H

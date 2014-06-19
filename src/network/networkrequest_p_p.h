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

#ifndef NETWORKREQUEST_P_P_H
#define NETWORKREQUEST_P_P_H

#include "networkrequest_p.h"
#include <QFile>

class QNetworkReply;

class NetworkRequestPrivate
{

public:
    NetworkRequestPrivate(NetworkRequest *parent);
    virtual ~NetworkRequestPrivate();

    QNetworkRequest initRequest();

    void followRedirect(const QUrl &url);

    void _q_onMetaDataChanged();

    void _q_onProgressChanged(qint64 transferred, qint64 total);

    void _q_onReadyRead();

    void _q_onFinished();

    NetworkRequest *q_ptr;

    QNetworkReply *reply;

    QFile file;

    QUrl url;

    QVariantMap requestHeaders;

    QVariantMap responseHeaders;

    QByteArray response;

    QString errorString;

    int progress;

    NetworkRequest::Status status;

    int redirects;

    bool followRedirects;

    bool writeToFile;

    Q_DECLARE_PUBLIC(NetworkRequest)
};

#endif // NETWORKREQUEST_P_P_H

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

#ifndef NETWORKREQUEST_P_H
#define NETWORKREQUEST_P_H

#include <QObject>
#include <QNetworkRequest>
#include <qdeclarative.h>

class NetworkRequestPrivate;

class NetworkRequest : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QVariantMap requestHeaders READ requestHeaders WRITE setRequestHeaders NOTIFY requestHeadersChanged)
    Q_PROPERTY(QVariantMap responseHeaders READ responseHeaders NOTIFY responseHeadersChanged)
    Q_PROPERTY(QByteArray responseData READ responseData NOTIFY statusChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY statusChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(bool followRedirects READ followRedirects WRITE setFollowRedirects NOTIFY followRedirectsChanged)

    Q_ENUMS(Status QNetworkRequest::KnownHeaders)

public:
    enum Status {
        Null = 0,
        Loading,
        Ready,
        Aborted,
        Error
    };

    explicit NetworkRequest(QObject *parent = 0);
    ~NetworkRequest();

    QUrl url() const;
    void setUrl(const QUrl &url);

    QVariantMap requestHeaders() const;
    void setRequestHeaders(const QVariantMap &headers);

    QVariantMap responseHeaders() const;

    QByteArray responseData() const;

    QString errorString() const;

    Status status() const;

    int progress() const;

    bool followRedirects() const;
    void setFollowRedirects(bool follow);

public slots:
    void get();
    void getFile(const QString &localPath);

    void put(const QByteArray &data);
    void putFile(const QString &localPath);

    void post(const QByteArray &data);
    void postFile(const QString &localPath);

    void deleteResource();

    void abort();

signals:
    void urlChanged();
    void requestHeadersChanged();
    void responseHeadersChanged();
    void progressChanged();
    void statusChanged();
    void followRedirectsChanged();

private:
    NetworkRequest(NetworkRequestPrivate &dd, QObject *parent = 0);

    QScopedPointer<NetworkRequestPrivate> d_ptr;

    Q_DISABLE_COPY(NetworkRequest)
    Q_DECLARE_PRIVATE(NetworkRequest)

    Q_PRIVATE_SLOT(d_func(), void _q_onMetaDataChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onProgressChanged(qint64, qint64))
    Q_PRIVATE_SLOT(d_func(), void _q_onReadyRead())
    Q_PRIVATE_SLOT(d_func(), void _q_onFinished())
};

QML_DECLARE_TYPE(NetworkRequest)

#endif // NETWORKREQUEST_P_H

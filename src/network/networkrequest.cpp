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

#include "networkrequest_p.h"
#include "networkrequest_p_p.h"
#include <QNetworkReply>
#include <QDeclarativeEngine>

const int MAX_REDIRECTS = 16;

NetworkRequest::NetworkRequest(QObject *parent) :
    QObject(parent),
    d_ptr(new NetworkRequestPrivate(this))
{
}

NetworkRequest::NetworkRequest(NetworkRequestPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

NetworkRequest::~NetworkRequest() {}

QUrl NetworkRequest::url() const {
    Q_D(const NetworkRequest);

    return d->url;
}

void NetworkRequest::setUrl(const QUrl &url) {
    if ((url != this->url()) && (this->status() != Loading)) {
        Q_D(NetworkRequest);
        d->url = url;
        emit urlChanged();
    }
}

QVariantMap NetworkRequest::requestHeaders() const {
    Q_D(const NetworkRequest);

    return d->requestHeaders;
}

void NetworkRequest::setRequestHeaders(const QVariantMap &headers) {
    if ((headers != this->requestHeaders()) && (this->status() != Loading)) {
        Q_D(NetworkRequest);
        d->requestHeaders = headers;
        emit requestHeadersChanged();
    }
}

QVariantMap NetworkRequest::responseHeaders() const {
    Q_D(const NetworkRequest);

    return d->responseHeaders;
}

QByteArray NetworkRequest::responseData() const {
    Q_D(const NetworkRequest);

    return d->response;
}

QString NetworkRequest::errorString() const {
    Q_D(const NetworkRequest);

    return d->errorString;
}

NetworkRequest::Status NetworkRequest::status() const {
    Q_D(const NetworkRequest);

    return d->status;
}

int NetworkRequest::progress() const {
    Q_D(const NetworkRequest);

    return d->progress;
}

bool NetworkRequest::followRedirects() const {
    Q_D(const NetworkRequest);

    return d->followRedirects;
}

void NetworkRequest::setFollowRedirects(bool follow) {
    if (follow != this->followRedirects()) {
        Q_D(NetworkRequest);
        d->followRedirects = follow;
        emit followRedirectsChanged();
    }
}

void NetworkRequest::get() {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->get(request);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::getFile(const QString &localPath) {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    d->file.setFileName(localPath);

    if (!d->file.open(d->file.exists() ? QIODevice::Append : QIODevice::WriteOnly)) {
        d->status = Error;
        d->errorString = tr("Cannot open file %1: %2").arg(localPath).arg(d->file.errorString());
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = true;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->get(request);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(readyRead()), this, SLOT(_q_onReadyRead()));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::put(const QByteArray &data) {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->put(request, data);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::putFile(const QString &localPath) {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    d->file.setFileName(localPath);

    if (!d->file.open(QIODevice::ReadOnly)) {
        d->status = Error;
        d->errorString = tr("Cannot open file %1: %2").arg(localPath).arg(d->file.errorString());
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->put(request, &d->file);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::post(const QByteArray &data) {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->post(request, data);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::postFile(const QString &localPath) {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    d->file.setFileName(localPath);

    if (!d->file.open(QIODevice::ReadOnly)) {
        d->status = Error;
        d->errorString = tr("Cannot open file %1: %2").arg(localPath).arg(d->file.errorString());
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->post(request, &d->file);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::deleteResource() {
    if (this->status() == Loading) {
        return;
    }

    Q_D(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(this)->networkAccessManager();

    if (!manager) {
        d->status = Error;
        d->errorString = tr("No QNetworkAccessManager instance");
        emit statusChanged();
        return;
    }

    QNetworkRequest request = d->initRequest();

    d->writeToFile = false;
    d->status = Loading;
    emit statusChanged();

    d->reply = manager->deleteResource(request);
    this->connect(d->reply, SIGNAL(metaDataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(_q_onProgressChanged(qint64,qint64)));
    this->connect(d->reply, SIGNAL(finished()), this, SLOT(_q_onFinished()));
}

void NetworkRequest::abort() {
    Q_D(NetworkRequest);

    if (d->reply) {
        d->reply->abort();
    }
}

NetworkRequestPrivate::NetworkRequestPrivate(NetworkRequest *parent) :
    q_ptr(parent),
    reply(0),
    status(NetworkRequest::Null),
    progress(0),
    redirects(0),
    followRedirects(true),
    writeToFile(false)
{
}

NetworkRequestPrivate::~NetworkRequestPrivate() {
    if (reply) {
        delete reply;
    }
}

QNetworkRequest NetworkRequestPrivate::initRequest() {
    if (reply) {
        delete reply;
        reply = 0;
    }

    Q_Q(NetworkRequest);

    response.clear();
    responseHeaders.clear();
    errorString.clear();
    redirects = 0;

    emit q->responseHeadersChanged();

    QNetworkRequest request(url);

    QMapIterator<QString, QVariant> iterator(requestHeaders);

    while (iterator.hasNext()) {
        iterator.next();
        bool ok;
        int knownHeader = iterator.key().toInt(&ok);

        if (ok) {
            request.setHeader(static_cast<QNetworkRequest::KnownHeaders>(knownHeader), iterator.value());
        }
        else {
            request.setRawHeader(iterator.key().toUtf8(), iterator.value().toByteArray());
        }
    }

    return request;
}

void NetworkRequestPrivate::followRedirect(const QUrl &url) {
    Q_Q(NetworkRequest);

    QNetworkAccessManager *manager = qmlEngine(q)->networkAccessManager();

    if (!manager) {
        status = NetworkRequest::Error;
        errorString = NetworkRequest::tr("No QNetworkAccessManager instance");
        emit q->statusChanged();
        return;
    }

    responseHeaders.clear();
    redirects++;

    emit q->responseHeadersChanged();

    QNetworkRequest request(url);
    reply = manager->get(request);
    q->connect(reply, SIGNAL(metaDataChanged()), q, SLOT(_q_onMetaDataChanged()));
    q->connect(reply, SIGNAL(downloadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
    q->connect(reply, SIGNAL(finished()), q, SLOT(_q_onFinished()));

    if (writeToFile) {
        q->connect(reply, SIGNAL(readyRead()), q, SLOT(_q_onReadyRead()));
    }
}

void NetworkRequestPrivate::_q_onMetaDataChanged() {
    if (!reply) {
        return;
    }

    Q_Q(NetworkRequest);

    foreach (QNetworkReply::RawHeaderPair pair, reply->rawHeaderPairs()) {
        responseHeaders.insert(pair.first, pair.second);
    }

    emit q->responseHeadersChanged();
}

void NetworkRequestPrivate::_q_onProgressChanged(qint64 transferred, qint64 total) {
    int p = transferred * 100 / total;

    if (p != progress) {
        Q_Q(NetworkRequest);
        progress = p;
        emit q->progressChanged();
    }
}

void NetworkRequestPrivate::_q_onReadyRead() {
    if ((reply) && (writeToFile)) {
        file.write(reply->readAll());
    }
}

void NetworkRequestPrivate::_q_onFinished() {
    if (!reply) {
        return;
    }

    Q_Q(NetworkRequest);

    if ((followRedirects) && (redirects < MAX_REDIRECTS)) {
        QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

        if (redirect.isEmpty()) {
            redirect = reply->header(QNetworkRequest::LocationHeader).toUrl();
        }

        if (!redirect.isEmpty()) {
            reply->deleteLater();
            reply = 0;
            this->followRedirect(redirect);
            return;
        }
    }

    errorString = reply->errorString();

    switch (reply->error()) {
    case QNetworkReply::OperationCanceledError:
        status = NetworkRequest::Aborted;
        break;
    case QNetworkReply::NoError:
        status = NetworkRequest::Ready;
        break;
    default:
        status = NetworkRequest::Error;
        break;
    }

    if (writeToFile) {
        file.close();
    }
    else {
        response = reply->readAll();
    }

    emit q->statusChanged();
}

#include "moc_networkrequest_p.cpp"

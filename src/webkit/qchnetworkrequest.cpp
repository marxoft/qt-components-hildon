/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchnetworkrequest.h"
#include <QScriptEngine>
#include <QScriptValue>

QchNetworkRequest::QchNetworkRequest(QObject *parent) :
    QObject(parent)
{
}

QVariant QchNetworkRequest::attribute(int code, const QVariant &defaultValue) const {
    if (const QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        return request->attribute(QNetworkRequest::Attribute(code), defaultValue);
    }
    
    return QVariant();
}

QVariant QchNetworkRequest::header(int knownHeader) const {
    if (const QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        return request->header(QNetworkRequest::KnownHeaders(knownHeader));
    }
    
    return QVariant();
}

void QchNetworkRequest::setHeader(int knownHeader, const QVariant &value) {
    if (QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        request->setHeader(QNetworkRequest::KnownHeaders(knownHeader), value);
    }
}

bool QchNetworkRequest::hasRawHeader(const QString &name) const {
    if (const QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        return request->hasRawHeader(name.toUtf8());
    }
    
    return false;
}

QString QchNetworkRequest::rawHeader(const QString &name) const {
    if (const QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        return request->rawHeader(name.toUtf8());
    }
    
    return QString();
}

void QchNetworkRequest::setRawHeader(const QString &name, const QVariant &value) {
    if (QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        request->setRawHeader(name.toUtf8(), value.toByteArray());
    }
}

QUrl QchNetworkRequest::url() const {
    if (const QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        return request->url();
    }
    
    return QUrl();
}

void QchNetworkRequest::setUrl(const QUrl &u) {
    if (QNetworkRequest *request = qscriptvalue_cast<QNetworkRequest*>(thisObject())) {
        request->setUrl(u);
    }
}

QScriptValue QchNetworkRequest::newInstance(QScriptContext *context, QScriptEngine *engine) {
    switch (context->argumentCount()) {
    case 0:
        return engine->toScriptValue(QNetworkRequest());
    case 1:
        return engine->toScriptValue(QNetworkRequest(context->argument(0).toString()));
    default:
        return context->throwError(QScriptContext::SyntaxError,
                                   QObject::tr("NetworkRequest constructor requires either 0 or 1 arguments."));
    }
}

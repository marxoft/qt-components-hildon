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

#ifndef QCHNETWORKREQUEST_H
#define QCHNETWORKREQUEST_H

#include <QObject>
#include <QScriptable>
#include <QNetworkRequest>

class QchNetworkRequest : public QObject, public QScriptable
{
    Q_OBJECT
    
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    
    Q_ENUMS(QNetworkRequest::Attribute QNetworkRequest::CacheLoadControl QNetworkRequest::KnownHeaders
            QNetworkRequest::LoadControl QNetworkRequest::Priority)
    
public:
    explicit QchNetworkRequest(QObject *parent = 0);
    
    Q_INVOKABLE QVariant attribute(int code, const QVariant &defaultValue = QVariant()) const;
    
    Q_INVOKABLE QVariant header(int knownHeader) const;
    Q_INVOKABLE void setHeader(int knownHeader, const QVariant &value);
    
    Q_INVOKABLE bool hasRawHeader(const QString &name) const;
    Q_INVOKABLE QString rawHeader(const QString &name) const;
    Q_INVOKABLE void setRawHeader(const QString &name, const QVariant &value);    
        
    QUrl url() const;
    void setUrl(const QUrl &u);
    
    static QScriptValue newInstance(QScriptContext *context, QScriptEngine *engine);
    
private:
    Q_DISABLE_COPY(QchNetworkRequest)
};

Q_DECLARE_METATYPE(QchNetworkRequest*)
Q_DECLARE_METATYPE(QNetworkRequest*)

#endif // QCHNETWORKREQUEST_H

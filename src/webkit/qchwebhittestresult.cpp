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

#include "qchwebhittestresult.h"
#include <QScriptEngine>
#include <QScriptValue>

QchWebHitTestResult::QchWebHitTestResult(QObject *parent) :
    QObject(parent)
{
}

QString QchWebHitTestResult::alternateText() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->alternateText();
    }
    
    return QString();
}

QRect QchWebHitTestResult::boundingRect() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->boundingRect();
    }
}

QWebElement QchWebHitTestResult::element() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->element();
    }
    
    return QWebElement();
}

QWebElement QchWebHitTestResult::enclosingBlockElement() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->enclosingBlockElement();
    }
    
    return QWebElement();
}

QWebElement QchWebHitTestResult::linkElement() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->linkElement();
    }
    
    return QWebElement();
}

QUrl QchWebHitTestResult::imageUrl() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->imageUrl();
    }
    
    return QUrl();
}

bool QchWebHitTestResult::isContentEditable() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->isContentEditable();
    }
    
    return false;
}

bool QchWebHitTestResult::isContentSelected() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->isContentSelected();
    }
    
    return false;
}

bool QchWebHitTestResult::isNull() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->isNull();
    }
    
    return true;
}

QString QchWebHitTestResult::linkText() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->linkText();
    }
    
    return QString();
}

QUrl QchWebHitTestResult::linkTitle() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->linkTitle();
    }
    
    return QUrl();
}

QUrl QchWebHitTestResult::linkUrl() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->linkUrl();
    }
    
    return QUrl();
}

QPixmap QchWebHitTestResult::pixmap() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->pixmap();
    }
    
    return QPixmap();
}

QPoint QchWebHitTestResult::pos() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->pos();
    }
    
    return QPoint();
}

QString QchWebHitTestResult::title() const {
    if (const QWebHitTestResult *result = qscriptvalue_cast<QWebHitTestResult*>(thisObject())) {
        return result->title();
    }
    
    QString();
}

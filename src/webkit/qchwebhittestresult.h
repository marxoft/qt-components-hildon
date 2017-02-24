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

#ifndef QCHWEBHITTESTRESULT_H
#define QCHWEBHITTESTRESULT_H

#include <QObject>
#include <QScriptable>
#include <QWebElement>
#include <QWebHitTestResult>

class QchWebHitTestResult : public QObject, public QScriptable
{
    Q_OBJECT
    
    Q_PROPERTY(QString alternateText READ alternateText)
    Q_PROPERTY(QRect boundingRect READ boundingRect)
    Q_PROPERTY(QWebElement element READ element)
    Q_PROPERTY(QWebElement enclosingBlockElement READ enclosingBlockElement)
    Q_PROPERTY(QWebElement linkElement READ linkElement)
    Q_PROPERTY(QUrl imageUrl READ imageUrl)
    Q_PROPERTY(bool contentEditable READ isContentEditable)
    Q_PROPERTY(bool contentSelected READ isContentSelected)
    Q_PROPERTY(bool isNull READ isNull)
    Q_PROPERTY(QString linkText READ linkText)
    Q_PROPERTY(QUrl linkTitle READ linkTitle)
    Q_PROPERTY(QUrl linkUrl READ linkUrl)
    Q_PROPERTY(QPixmap pixmap READ pixmap)
    Q_PROPERTY(QPoint pos READ pos)
    Q_PROPERTY(QString title READ title)

public:
    explicit QchWebHitTestResult(QObject *parent = 0);
    
    QString alternateText() const;
    
    QRect boundingRect() const;
    
    QWebElement element() const;
    QWebElement enclosingBlockElement() const;
    QWebElement linkElement() const;
    
    QUrl imageUrl() const;
    
    bool isContentEditable() const;
    bool isContentSelected() const;
    
    bool isNull() const;
    
    QString linkText() const;
    QUrl linkTitle() const;
    QUrl linkUrl() const;
    
    QPixmap pixmap() const;
    
    QPoint pos() const;
    
    QString title() const;
        
private:
    Q_DISABLE_COPY(QchWebHitTestResult)
};

Q_DECLARE_METATYPE(QWebHitTestResult)
Q_DECLARE_METATYPE(QWebHitTestResult*)

#endif // QCHWEBHITTESTRESULT_H

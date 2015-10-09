/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHTEXTMETRICS_H
#define QCHTEXTMETRICS_H

#include <QObject>
#include <QFontMetrics>
#include <qdeclarative.h>

class QchTextMetrics : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(int advanceWidth READ advanceWidth NOTIFY changed)
    Q_PROPERTY(QRect boundingRect READ boundingRect NOTIFY changed)
    Q_PROPERTY(Qt::TextElideMode elide READ elide WRITE setElide NOTIFY changed)
    Q_PROPERTY(QString elidedText READ elidedText NOTIFY changed)
    Q_PROPERTY(int elideWidth READ elideWidth WRITE setElideWidth NOTIFY changed)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY changed)
    Q_PROPERTY(int height READ height NOTIFY changed)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY changed)
    Q_PROPERTY(QRect tightBoundingRect READ tightBoundingRect NOTIFY changed)
    Q_PROPERTY(int width READ width NOTIFY changed)
    
public:
    explicit QchTextMetrics(QObject *parent = 0);
    
    int advanceWidth() const;
    
    QRect boundingRect() const;
    
    Qt::TextElideMode elide() const;
    void setElide(Qt::TextElideMode m);
    
    QString elidedText() const;
    
    int elideWidth() const;
    void setElideWidth(int w);
    
    QFont font() const;
    void setFont(const QFont &f);
    
    int height() const;
    void setHeight(int h);
    
    QString text() const;
    void setText(const QString &t);
    
    QRect tightBoundingRect() const;
    
    int width() const;
    
Q_SIGNALS:
    void changed();
    
private:
    QFont m_font;
    QFontMetrics m_fontMetrics;
    
    Qt::TextElideMode m_elide;
    int m_elideWidth;
    
    QString m_text;
    
    Q_DISABLE_COPY(QchTextMetrics)
};

QML_DECLARE_TYPE(QchTextMetrics)

#endif // QCHTEXTMETRICS_H

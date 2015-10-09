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

#ifndef QCHFONTMETRICS_H
#define QCHFONTMETRICS_H

#include <QObject>
#include <QFontMetrics>
#include <qdeclarative.h>

class QchFontMetrics : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(int ascent READ ascent NOTIFY changed)
    Q_PROPERTY(int averageCharacterWidth READ averageCharacterWidth NOTIFY changed)
    Q_PROPERTY(int descent READ descent NOTIFY changed)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY changed)
    Q_PROPERTY(int height READ height NOTIFY changed)
    Q_PROPERTY(int leading READ leading NOTIFY changed)
    Q_PROPERTY(int lineSpacing READ lineSpacing NOTIFY changed)
    Q_PROPERTY(int lineWidth READ lineWidth NOTIFY changed)
    Q_PROPERTY(int maximumCharacterWidth READ maximumCharacterWidth NOTIFY changed)
    Q_PROPERTY(int minimumLeftBearing READ minimumLeftBearing NOTIFY changed)
    Q_PROPERTY(int minimumRightBearing READ minimumRightBearing NOTIFY changed)
    Q_PROPERTY(int overlinePosition READ overlinePosition NOTIFY changed)
    Q_PROPERTY(int strikeOutPosition READ strikeOutPosition NOTIFY changed)
    Q_PROPERTY(int underlinePosition READ underlinePosition NOTIFY changed)
    Q_PROPERTY(int xHeight READ xHeight NOTIFY changed)
    
public:
    explicit QchFontMetrics(QObject *parent = 0);
    
    int ascent() const;
    
    int averageCharacterWidth() const;
    
    int descent() const;
    
    QFont font() const;
    void setFont(const QFont &f);
    
    int height() const;
    
    int leading() const;
    
    int lineSpacing() const;
    
    int lineWidth() const;
    
    int maximumCharacterWidth() const;
    
    int minimumLeftBearing() const;
    
    int minimumRightBearing() const;
    
    int overlinePosition() const;
    
    int strikeOutPosition() const;
    
    int underlinePosition() const;
    
    int xHeight() const;

public Q_SLOTS:
    int advanceWidth(const QString &text);
    
    QRect boundingRect(const QString &text);
        
    QRect tightBoundingRect(const QString &text);
    
Q_SIGNALS:
    void changed();
    
private:
    QFont m_font;
    QFontMetrics m_fontMetrics;
    
    Q_DISABLE_COPY(QchFontMetrics)
};

QML_DECLARE_TYPE(QchFontMetrics)

#endif // QCHFONTMETRICS_H

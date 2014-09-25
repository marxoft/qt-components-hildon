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
 
#ifndef STYLE_P_H
#define STYLE_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class StylePrivate;

class Style : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(Origin backgroundClip READ backgroundClip WRITE setBackgroundClip NOTIFY changed)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY changed)
    Q_PROPERTY(QString backgroundImage READ backgroundImage WRITE setBackgroundImage NOTIFY changed)
    Q_PROPERTY(Origin backgroundOrigin READ backgroundOrigin WRITE setBackgroundOrigin NOTIFY changed)
    Q_PROPERTY(Qt::Alignment backgroundPosition READ backgroundPosition WRITE setBackgroundPosition NOTIFY changed)
    Q_PROPERTY(Repeat backgroundRepeat READ backgroundRepeat WRITE setBackgroundRepeat NOTIFY changed)
    
    Q_ENUMS(Repeat)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    enum Origin {
        Margin = 0,
        Border,
        Padding,
        Content
    };
        
    enum Repeat {
        RepeatX = 0,
        RepeatY,
        RepeatXandY,
        NoRepeat
    };
    
    explicit Style(QObject *parent = 0);
    ~Style();
    
    Origin backgroundClip() const;
    void setBackgroundClip(Origin clip);
    
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    
    QString backgroundImage() const;
    void setBackgroundImage(const QString &source);
    
    Origin backgroundOrigin() const;
    void setBackgroundOrigin(Origin origin);
    
    Qt::Alignment backgroundPosition() const;
    void setBackgroundPosition(Qt::Alignment align);
    
    Repeat backgroundRepeat() const;
    void setBackgroundRepeat(Repeat r);
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    Style(StylePrivate &dd, QObject *parent = 0);
    
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<StylePrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(Style)

private:
    Q_DISABLE_COPY(Style)
};

QML_DECLARE_TYPE(Style)

#endif // STYLE_P_H


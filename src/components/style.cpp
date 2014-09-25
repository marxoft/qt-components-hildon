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

#include "style_p.h"
#include "style_p_p.h"

Style::Style(QObject *parent) :
    QObject(parent),
    d_ptr(new StylePrivate(this))
{
}

Style::Style(StylePrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Style::~Style() {}

Style::Origin Style::backgroundClip() const {
    Q_D(const Style);
    
    return d->backgroundClip;
}

void Style::setBackgroundClip(Origin clip) {
    if (clip != this->backgroundClip()) {
        Q_D(Style);
        d->backgroundClip = clip;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor Style::backgroundColor() const {
    Q_D(const Style);
    
    return d->backgroundColor;
}

void Style::setBackgroundColor(const QColor &color) {
    if (color != this->backgroundColor()) {
        Q_D(Style);
        d->backgroundColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString Style::backgroundImage() const {
    Q_D(const Style);
    
    return d->backgroundImage;
}

void Style::setBackgroundImage(const QString &source) {
    if (source != this->backgroundImage()) {
        Q_D(Style);
        d->backgroundImage = source;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

Style::Origin Style::backgroundOrigin() const {
    Q_D(const Style);
    
    return d->backgroundOrigin;
}

void Style::setBackgroundOrigin(Origin origin) {
    if (origin != this->backgroundOrigin()) {
        Q_D(Style);
        d->backgroundOrigin;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

Qt::Alignment Style::backgroundPosition() const {
    Q_D(const Style);
    
    return d->backgroundPosition;
}

void Style::setBackgroundPosition(Qt::Alignment align) {
    if (align != this->backgroundPosition()) {
        Q_D(Style);
        d->backgroundPosition = align;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

Style::Repeat Style::backgroundRepeat() const {
    Q_D(const Style);
    
    return d->backgroundRepeat;
}

void Style::setBackgroundRepeat(Repeat r) {
    if (r != this->backgroundRepeat()) {
        Q_D(Style);
        d->backgroundRepeat = r;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString Style::toStyleSheet() const {
    Q_D(const Style);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s;
    
    switch (d->backgroundClip) {
    case Margin:
        s += "background-clip: margin;";
        break;
    case Border:
        s += "background-clip: border;";
        break;
    case Padding:
        s += "background-clip: padding;";
        break;
    case Content:
        s += "background-clip: content;";
        break;
    default:
        s += "background-clip: border;";
        break;
    }
        
    switch (d->backgroundOrigin) {
    case Margin:
        s += "background-origin: margin;";
        break;
    case Border:
        s += "background-origin: border;";
        break;
    case Padding:
        s += "background-origin: padding;";
        break;
    case Content:
        s += "background-origin: content;";
        break;
    default:
        s += "background-origin: padding;";
        break;
    }
    
    if (d->backgroundColor.isValid()) {
        s += "background-color: " + d->backgroundColor.name() + ";";
    }
    
    if (!d->backgroundImage.isEmpty()) {
        s += "background-image: url(" + d->backgroundImage + ");";
        
        if (d->backgroundPosition & Qt::AlignCenter) {
            s += " center;";
        }
        else {
            if (d->backgroundPosition & Qt::AlignTop) {
                s += " top";
            }
            else if (d->backgroundPosition & Qt::AlignBottom) {
                s += " bottom";
            }
            else if (d->backgroundPosition & Qt::AlignVCenter) {
                s += " center";
            }
            
            if (d->backgroundPosition & Qt::AlignLeft) {
                s += " left";
            }
            else if (d->backgroundPosition & Qt::AlignRight) {
                s += " right";
            }
            else if (d->backgroundPosition & Qt::AlignHCenter) {
                s += " center";
            }
            
            s += ";";
        }
        
        switch(d->backgroundRepeat) {
        case RepeatX:
            s += "background-repeat: repeat-x;";
            break;
        case RepeatY:
            s += "background-repeat: repeat-y;";
            break;
        case RepeatXandY:
            s += "background-repeat: repeat;";
            break;
        case NoRepeat:
            s += "background-repeat: no-repeat;";
            break;
        default:
            s += "background-repeat: repeat;";
            break;
        }
    }
    
    return s;
}

void Style::classBegin() {}

void Style::componentComplete() {
    Q_D(Style);
    
    d->complete = true;
    
    if (d->dirty) {
        emit changed();
    }
}

#include "moc_style_p.cpp"


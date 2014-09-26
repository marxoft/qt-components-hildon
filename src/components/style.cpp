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

StylePrivate::StylePrivate(Style *parent) :
    q_ptr(parent),
    complete(false),
    dirty(false),
    backgroundClip(Style::Border),
    backgroundOrigin(Style::Padding),
    backgroundPosition(Qt::AlignTop | Qt::AlignLeft),
    backgroundRepeat(Style::RepeatXandY)
{
}

QString StylePrivate::mainBody() const {
    QString body;
    
    switch (backgroundClip) {
    case Style::Margin:
        body += "background-clip: margin;";
        break;
    case Style::Border:
        body += "background-clip: border;";
        break;
    case Style::Padding:
        body += "background-clip: padding;";
        break;
    case Style::Content:
        body += "background-clip: content;";
        break;
    default:
        body += "background-clip: border;";
        break;
    }
        
    switch (backgroundOrigin) {
    case Style::Margin:
        body += "background-origin: margin;";
        break;
    case Style::Border:
        body += "background-origin: border;";
        break;
    case Style::Padding:
        body += "background-origin: padding;";
        break;
    case Style::Content:
        body += "background-origin: content;";
        break;
    default:
        body += "background-origin: padding;";
        break;
    }
    
    if (backgroundColor.isValid()) {
        body += "background-color: " + backgroundColor.name() + ";";
    }
    
    if (!backgroundImage.isEmpty()) {
        body += "background-image: url(" + backgroundImage + ");";
        
        if (backgroundPosition & Qt::AlignCenter) {
            body += " center;";
        }
        else {
            if (backgroundPosition & Qt::AlignTop) {
                body += " top";
            }
            else if (backgroundPosition & Qt::AlignBottom) {
                body += " bottom";
            }
            else if (backgroundPosition & Qt::AlignVCenter) {
                body += " center";
            }
            
            if (backgroundPosition & Qt::AlignLeft) {
                body += " left";
            }
            else if (backgroundPosition & Qt::AlignRight) {
                body += " right";
            }
            else if (backgroundPosition & Qt::AlignHCenter) {
                body += " center";
            }
            
            body += ";";
        }
        
        switch(backgroundRepeat) {
        case Style::RepeatX:
            body += "background-repeat: repeat-x;";
            break;
        case Style::RepeatY:
            body += "background-repeat: repeat-y;";
            break;
        case Style::RepeatXandY:
            body += "background-repeat: repeat;";
            break;
        case Style::NoRepeat:
            body += "background-repeat: no-repeat;";
            break;
        default:
            body += "background-repeat: repeat;";
            break;
        }
    }
    
    return body;
}

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
    
    return d->complete ? d->mainBody() : QString();
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


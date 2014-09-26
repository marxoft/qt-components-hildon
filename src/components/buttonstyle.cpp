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

#include "buttonstyle_p.h"
#include "buttonstyle_p_p.h"

ButtonStylePrivate::ButtonStylePrivate(ButtonStyle *parent) :
    BoxStylePrivate(parent),
    indicator(0),
    textAlignment(0)
{
}

QString ButtonStylePrivate::indicatorBody() const {
    return indicator ? indicator->toStyleSheet()
                     : QString();
}

QString ButtonStylePrivate::mainBody() const {
    QString body = BoxStylePrivate::mainBody();
    
    if (textAlignment) {
        body += "text-align:";
        
        if (textAlignment & Qt::AlignCenter) {
            body += " center;";
        }
        else {
            if (textAlignment & Qt::AlignTop) {
                body += " top";
            }
            else if (textAlignment & Qt::AlignBottom) {
                body += " bottom";
            }
            else if (textAlignment & Qt::AlignVCenter) {
                body += " center";
            }
            
            if (textAlignment & Qt::AlignLeft) {
                body += " left";
            }
            else if (textAlignment & Qt::AlignRight) {
                body += " right";
            }
            else if (textAlignment & Qt::AlignHCenter) {
                body += " center";
            }
            
            body += ";";
        }
    }
    
    return body;
}

ButtonStyle::ButtonStyle(QObject *parent) :
    BoxStyle(*new ButtonStylePrivate(this), parent)
{
}

ButtonStyle::ButtonStyle(ButtonStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

ButtonStyle::~ButtonStyle() {}

Style* ButtonStyle::indicator() const {
    Q_D(const ButtonStyle);
    
    return d->indicator;
}

void ButtonStyle::setIndicator(Style *style) {
    if (style != this->indicator()) {
        Q_D(ButtonStyle);
        
        if (d->indicator) {
            this->disconnect(d->indicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->indicator = style;
        
        if (d->indicator) {
            this->connect(d->indicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ButtonStyle::resetIndicator() {
    this->setIndicator(0);
}

Qt::Alignment ButtonStyle::textAlignment() const {
    Q_D(const ButtonStyle);
    
    return d->textAlignment;
}

void ButtonStyle::setTextAlignment(Qt::Alignment align) {
    if (align != this->textAlignment()) {
        Q_D(ButtonStyle);
        d->textAlignment = align;
        d->dirty = true;
        
        if (!d->complete) {
            emit changed();
        }
    }
}

QString ButtonStyle::toStyleSheet() const {
    Q_D(const ButtonStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    return d->indicator ? "QPushButton { " + d->mainBody() + " } QPushButton::menu-indicator { " + d->indicatorBody() + " }" 
                        : d->mainBody();
}

#include "moc_buttonstyle_p.cpp"


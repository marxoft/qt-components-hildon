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
    textAlignment(0)
{
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
    
    return d->complete ? d->mainBody() : QString();
}

#include "moc_buttonstyle_p.cpp"


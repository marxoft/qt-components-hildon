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

#include "flickablestyle_p.h"
#include "flickablestyle_p_p.h"

FlickableStylePrivate::FlickableStylePrivate(FlickableStyle *parent) :
    BoxStylePrivate(parent),
    backgroundAttachment(FlickableStyle::Scroll)
{
}

QString FlickableStylePrivate::mainBody() const {
    QString body = BoxStylePrivate::mainBody();
    
    switch (backgroundAttachment) {
    case FlickableStyle::Fixed:
        body += "background-attachment: fixed;";
        break;
    default:
        body += "background-attachment: scroll;";
        break;
    }
    
    return body;
}

FlickableStyle::FlickableStyle(QObject *parent) :
    BoxStyle(*new FlickableStylePrivate(this), parent)
{
}

FlickableStyle::FlickableStyle(FlickableStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

FlickableStyle::~FlickableStyle() {}

FlickableStyle::Attachment FlickableStyle::backgroundAttachment() const {
    Q_D(const FlickableStyle);
    
    return d->backgroundAttachment;
}

void FlickableStyle::setBackgroundAttachment(Attachment a) {
    if (a != this->backgroundAttachment()) {
        Q_D(FlickableStyle);
        d->backgroundAttachment = a;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

#include "moc_flickablestyle_p.cpp"


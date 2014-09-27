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

#include "sliderstyle_p.h"
#include "sliderstyle_p_p.h"

SliderStylePrivate::SliderStylePrivate(SliderStyle *parent) :
    BoxStylePrivate(parent),
    groove(0),
    handle(0)
{
}

QString SliderStylePrivate::grooveBody() const {
    return groove ? groove->toStyleSheet()
                     : QString();
}

QString SliderStylePrivate::handleBody() const {
    return handle ? handle->toStyleSheet()
                     : QString();
}

SliderStyle::SliderStyle(QObject *parent) :
    BoxStyle(*new SliderStylePrivate(this), parent)
{
}

SliderStyle::SliderStyle(SliderStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

SliderStyle::~SliderStyle() {}

Style* SliderStyle::groove() const {
    Q_D(const SliderStyle);
    
    return d->groove;
}

void SliderStyle::setGroove(Style *style) {
    if (style != this->groove()) {
        Q_D(SliderStyle);
        
        if (d->groove) {
            this->disconnect(d->groove, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->groove = style;
        d->dirty = true;
        
        if (d->groove) {
            this->connect(d->groove, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SliderStyle::resetGroove() {
    this->setGroove(0);
}

Style* SliderStyle::handle() const {
    Q_D(const SliderStyle);
    
    return d->handle;
}

void SliderStyle::setHandle(Style *style) {
    if (style != this->handle()) {
        Q_D(SliderStyle);
        
        if (d->handle) {
            this->disconnect(d->handle, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->handle = style;
        d->dirty = true;
        
        if (d->handle) {
            this->connect(d->handle, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SliderStyle::resetHandle() {
    this->setHandle(0);
}

QString SliderStyle::toStyleSheet() const {
    Q_D(const SliderStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QSlider { " + d->mainBody() + " }");
    
    if (d->groove) {
        s += " QSlider::groove { " + d->grooveBody() + " }";
    }
    
    if (d->handle) {
        s += " QSlider::handle { " + d->handleBody() + " }";
    }
    
    return s;
}

#include "moc_sliderstyle_p.cpp"


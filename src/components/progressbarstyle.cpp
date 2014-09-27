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

#include "progressbarstyle_p.h"
#include "progressbarstyle_p_p.h"

ProgressBarStylePrivate::ProgressBarStylePrivate(ProgressBarStyle *parent) :
    BoxStylePrivate(parent),
    chunk(0),
    textAlignment(0)
{
}

QString ProgressBarStylePrivate::chunkBody() const {
    return chunk ? chunk->toStyleSheet()
                     : QString();
}

QString ProgressBarStylePrivate::mainBody() const {
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

ProgressBarStyle::ProgressBarStyle(QObject *parent) :
    BoxStyle(*new ProgressBarStylePrivate(this), parent)
{
}

ProgressBarStyle::ProgressBarStyle(ProgressBarStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

ProgressBarStyle::~ProgressBarStyle() {}

Style* ProgressBarStyle::chunk() const {
    Q_D(const ProgressBarStyle);
    
    return d->chunk;
}

void ProgressBarStyle::setChunk(Style *style) {
    if (style != this->chunk()) {
        Q_D(ProgressBarStyle);
        
        if (d->chunk) {
            this->disconnect(d->chunk, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->chunk = style;
        d->dirty = true;
        
        if (d->chunk) {
            this->connect(d->chunk, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ProgressBarStyle::resetChunk() {
    this->setChunk(0);
}

Qt::Alignment ProgressBarStyle::textAlignment() const {
    Q_D(const ProgressBarStyle);
    
    return d->textAlignment;
}

void ProgressBarStyle::setTextAlignment(Qt::Alignment align) {
    if (align != this->textAlignment()) {
        Q_D(ProgressBarStyle);
        d->textAlignment = align;
        d->dirty = true;
        
        if (!d->complete) {
            emit changed();
        }
    }
}

QString ProgressBarStyle::toStyleSheet() const {
    Q_D(const ProgressBarStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    return d->chunk ? "QProgressBar { " + d->mainBody() + " } QProgressBar::chunk { " + d->chunkBody() + " }" 
                        : d->mainBody();
}

#include "moc_progressbarstyle_p.cpp"


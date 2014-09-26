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

#include "checkboxstyle_p.h"
#include "checkboxstyle_p_p.h"

CheckBoxStylePrivate::CheckBoxStylePrivate(CheckBoxStyle *parent) :
    ButtonStylePrivate(parent),
    indicatorWidth(-1),
    indicatorHeight(-1),
    spacing(-1)
{
}

QString CheckBoxStylePrivate::mainBody() const {
    QString body = ButtonStylePrivate::mainBody();
    
    if (spacing != -1) {
        body += "spacing: " + QString::number(spacing) + "px;";
    }
    
    return body;
}

QString CheckBoxStylePrivate::indicatorBody() const {
    QString body;
    
    if (indicatorWidth != -1) {
        body += "width: " + QString::number(indicatorWidth) + "px;";
    }
    
    if (indicatorHeight != -1) {
        body += "height: " + QString::number(indicatorHeight) + "px;";
    }
    
    if (!indicatorImage.isEmpty()) {
        body += "image: url(" + indicatorImage + ");";
    }
    
    return body;
}

CheckBoxStyle::CheckBoxStyle(QObject *parent) :
    ButtonStyle(*new CheckBoxStylePrivate(this), parent)
{
}

CheckBoxStyle::CheckBoxStyle(CheckBoxStylePrivate &dd, QObject *parent) :
    ButtonStyle(dd, parent)
{
}

CheckBoxStyle::~CheckBoxStyle() {}

QString CheckBoxStyle::indicatorImage() const {
    Q_D(const CheckBoxStyle);
    
    return d->indicatorImage;
}

void CheckBoxStyle::setIndicatorImage(const QString &source) {
    if (source != this->indicatorImage()) {
        Q_D(CheckBoxStyle);
        d->indicatorImage = source;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int CheckBoxStyle::indicatorWidth() const {
    Q_D(const CheckBoxStyle);
    
    return d->indicatorWidth;
}

void CheckBoxStyle::setIndicatorWidth(int width) {
    if (width != this->indicatorWidth()) {
        Q_D(CheckBoxStyle);
        d->indicatorWidth = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int CheckBoxStyle::indicatorHeight() const {
    Q_D(const CheckBoxStyle);
    
    return d->indicatorHeight;
}

void CheckBoxStyle::setIndicatorHeight(int height) {
    if (height != this->indicatorHeight()) {
        Q_D(CheckBoxStyle);
        d->indicatorHeight = height;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int CheckBoxStyle::spacing() const {
    Q_D(const CheckBoxStyle);
    
    return d->spacing;
}

void CheckBoxStyle::setSpacing(int s) {
    if (s != this->spacing()) {
        Q_D(CheckBoxStyle);
        d->spacing = s;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString CheckBoxStyle::toStyleSheet() const {
    Q_D(const CheckBoxStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString main = d->mainBody();
    QString indicator = d->indicatorBody();
    
    return indicator.isEmpty() ? main : "QCheckBox { " 
                                        + main 
                                        + " } QCheckBox::indicator { " 
                                        + indicator 
                                        + " }";
}

#include "moc_checkboxstyle_p.cpp"


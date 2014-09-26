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

CheckBoxStyle::CheckBoxStyle(QObject *parent) :
    ButtonStyle(*new CheckBoxStylePrivate(this), parent)
{
}

CheckBoxStyle::CheckBoxStyle(CheckBoxStylePrivate &dd, QObject *parent) :
    ButtonStyle(dd, parent)
{
}

CheckBoxStyle::~CheckBoxStyle() {}

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
    
    return d->indicator ? "QCheckBox { " + d->mainBody() + " } QCheckBox::indicator { " + d->indicatorBody() + " }" 
                        : d->mainBody();
}

#include "moc_checkboxstyle_p.cpp"


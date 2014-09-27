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

#include "texteditstyle_p.h"
#include "texteditstyle_p_p.h"

TextEditStylePrivate::TextEditStylePrivate(TextEditStyle *parent) :
    FlickableStylePrivate(parent)
{
}

QString TextEditStylePrivate::mainBody() const {
    QString body = "QScrollArea { " + FlickableStylePrivate::mainBody() + " } QTextEdit { ";
    
    if (selectionBackgroundColor.isValid()) {
        body += "selection-background-color: " + selectionBackgroundColor.name() + ";";
    }
    
    if (selectionColor.isValid()) {
        body += "selection-color: " + selectionColor.name() + ";";
    }
    
    body += " }";
    
    return body;
}

TextEditStyle::TextEditStyle(QObject *parent) :
    FlickableStyle(*new TextEditStylePrivate(this), parent)
{
}

TextEditStyle::TextEditStyle(TextEditStylePrivate &dd, QObject *parent) :
    FlickableStyle(dd, parent)
{
}

TextEditStyle::~TextEditStyle() {}

QColor TextEditStyle::selectionBackgroundColor() const {
    Q_D(const TextEditStyle);
    
    return d->selectionBackgroundColor;
}

void TextEditStyle::setSelectionBackgroundColor(const QColor &color) {
    if (color != this->selectionBackgroundColor()) {
        Q_D(TextEditStyle);
        d->selectionBackgroundColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor TextEditStyle::selectionColor() const {
    Q_D(const TextEditStyle);
    
    return d->selectionColor;
}

void TextEditStyle::setSelectionColor(const QColor &color) {
    if (color != this->selectionColor()) {
        Q_D(TextEditStyle);
        d->selectionColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

#include "moc_texteditstyle_p.cpp"


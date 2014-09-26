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

#include "textfieldstyle_p.h"
#include "textfieldstyle_p_p.h"

TextFieldStylePrivate::TextFieldStylePrivate(TextFieldStyle *parent) :
    BoxStylePrivate(parent)
{
}

QString TextFieldStylePrivate::mainBody() const {
    QString body = BoxStylePrivate::mainBody();
    
    if (!passwordCharacter.isEmpty()) {
        body += "lineedit-password-character: " + QString::number(passwordCharacter.at(0).unicode()) + ";";
    }
    
    if (selectionBackgroundColor.isValid()) {
        body += "selection-background-color: " + selectionBackgroundColor.name() + ";";
    }
    
    if (selectionColor.isValid()) {
        body += "selection-color: " + selectionColor.name() + ";";
    }
    
    return body;
}

TextFieldStyle::TextFieldStyle(QObject *parent) :
    BoxStyle(*new TextFieldStylePrivate(this), parent)
{
}

TextFieldStyle::TextFieldStyle(TextFieldStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

TextFieldStyle::~TextFieldStyle() {}

QString TextFieldStyle::passwordCharacter() const {
    Q_D(const TextFieldStyle);
    
    return d->passwordCharacter;
}

void TextFieldStyle::setPasswordCharacter(const QString &c) {
    if (c != this->passwordCharacter()) {
        Q_D(TextFieldStyle);
        d->passwordCharacter = c;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor TextFieldStyle::selectionBackgroundColor() const {
    Q_D(const TextFieldStyle);
    
    return d->selectionBackgroundColor;
}

void TextFieldStyle::setSelectionBackgroundColor(const QColor &color) {
    if (color != this->selectionBackgroundColor()) {
        Q_D(TextFieldStyle);
        d->selectionBackgroundColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor TextFieldStyle::selectionColor() const {
    Q_D(const TextFieldStyle);
    
    return d->selectionColor;
}

void TextFieldStyle::setSelectionColor(const QColor &color) {
    if (color != this->selectionColor()) {
        Q_D(TextFieldStyle);
        d->selectionColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString TextFieldStyle::toStyleSheet() const {
    Q_D(const TextFieldStyle);
    
    return d->complete ? d->mainBody() : QString();
}

#include "moc_textfieldstyle_p.cpp"


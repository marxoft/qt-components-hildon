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

#include "spinboxstyle_p.h"
#include "spinboxstyle_p_p.h"

SpinBoxStylePrivate::SpinBoxStylePrivate(SpinBoxStyle *parent) :
    BoxStylePrivate(parent),
    downArrow(0),
    downButton(0),
    upArrow(0),
    upButton(0)
{
}

QString SpinBoxStylePrivate::downArrowBody() const {
    return downArrow ? downArrow->toStyleSheet()
                     : QString();
}

QString SpinBoxStylePrivate::downButtonBody() const {
    return downArrow ? downButton->toStyleSheet()
                     : QString();
}

QString SpinBoxStylePrivate::upArrowBody() const {
    return upArrow ? upArrow->toStyleSheet()
                     : QString();
}

QString SpinBoxStylePrivate::upButtonBody() const {
    return upArrow ? upButton->toStyleSheet()
                     : QString();
}

SpinBoxStyle::SpinBoxStyle(QObject *parent) :
    BoxStyle(*new SpinBoxStylePrivate(this), parent)
{
}

SpinBoxStyle::SpinBoxStyle(SpinBoxStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

SpinBoxStyle::~SpinBoxStyle() {}

Style* SpinBoxStyle::downArrow() const {
    Q_D(const SpinBoxStyle);
    
    return d->downArrow;
}

void SpinBoxStyle::setDownArrow(Style *style) {
    if (style != this->downArrow()) {
        Q_D(SpinBoxStyle);
        
        if (d->downArrow) {
            this->disconnect(d->downArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->downArrow = style;
        d->dirty = true;
        
        if (d->downArrow) {
            this->connect(d->downArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SpinBoxStyle::resetDownArrow() {
    this->setDownArrow(0);
}

Style* SpinBoxStyle::downButton() const {
    Q_D(const SpinBoxStyle);
    
    return d->downButton;
}

void SpinBoxStyle::setDownButton(Style *style) {
    if (style != this->downButton()) {
        Q_D(SpinBoxStyle);
        
        if (d->downButton) {
            this->disconnect(d->downButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->downButton = style;
        d->dirty = true;
        
        if (d->downButton) {
            this->connect(d->downButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SpinBoxStyle::resetDownButton() {
    this->setDownButton(0);
}

Style* SpinBoxStyle::upArrow() const {
    Q_D(const SpinBoxStyle);
    
    return d->upArrow;
}

void SpinBoxStyle::setUpArrow(Style *style) {
    if (style != this->upArrow()) {
        Q_D(SpinBoxStyle);
        
        if (d->upArrow) {
            this->disconnect(d->upArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->upArrow = style;
        d->dirty = true;
        
        if (d->upArrow) {
            this->connect(d->upArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SpinBoxStyle::resetUpArrow() {
    this->setUpArrow(0);
}

Style* SpinBoxStyle::upButton() const {
    Q_D(const SpinBoxStyle);
    
    return d->upButton;
}

void SpinBoxStyle::setUpButton(Style *style) {
    if (style != this->upButton()) {
        Q_D(SpinBoxStyle);
        
        if (d->upButton) {
            this->disconnect(d->upButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->upButton = style;
        d->dirty = true;
        
        if (d->upButton) {
            this->connect(d->upButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void SpinBoxStyle::resetUpButton() {
    this->setUpButton(0);
}

QString SpinBoxStyle::toStyleSheet() const {
    Q_D(const SpinBoxStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QSpinBox { " + d->mainBody() + " }");
    
    if (d->downArrow) {
        s += " QSpinBox::down-arrow { " + d->downArrowBody() + " }";
    }
    
    if (d->downButton) {
        s += " QSpinBox::down-button { " + d->downButtonBody() + " }";
    }
    
    if (d->upArrow) {
        s += " QSpinBox::up-arrow { " + d->upArrowBody() + " }";
    }
    
    if (d->upButton) {
        s += " QSpinBox::up-button { " + d->upButtonBody() + " }";
    }
    
    return s;
}

#include "moc_spinboxstyle_p.cpp"


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

#include "toolbuttonstyle_p.h"
#include "toolbuttonstyle_p_p.h"

ToolButtonStylePrivate::ToolButtonStylePrivate(ToolButtonStyle *parent) :
    BoxStylePrivate(parent),
    menuButton(0),
    menuIndicator(0),
    downArrow(0),
    leftArrow(0),
    rightArrow(0),
    upArrow(0)
{
}

QString ToolButtonStylePrivate::menuButtonBody() const {
    return menuButton ? menuButton->toStyleSheet()
                     : QString();
}

QString ToolButtonStylePrivate::menuIndicatorBody() const {
    return menuIndicator ? menuIndicator->toStyleSheet()
                     : QString();
}

QString ToolButtonStylePrivate::downArrowBody() const {
    return downArrow ? downArrow->toStyleSheet()
                     : QString();
}

QString ToolButtonStylePrivate::leftArrowBody() const {
    return leftArrow ? leftArrow->toStyleSheet()
                     : QString();
}

QString ToolButtonStylePrivate::rightArrowBody() const {
    return rightArrow ? rightArrow->toStyleSheet()
                     : QString();
}

QString ToolButtonStylePrivate::upArrowBody() const {
    return upArrow ? upArrow->toStyleSheet()
                     : QString();
}

ToolButtonStyle::ToolButtonStyle(QObject *parent) :
    BoxStyle(*new ToolButtonStylePrivate(this), parent)
{
}

ToolButtonStyle::ToolButtonStyle(ToolButtonStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

ToolButtonStyle::~ToolButtonStyle() {}

Style* ToolButtonStyle::menuButton() const {
    Q_D(const ToolButtonStyle);
    
    return d->menuButton;
}

void ToolButtonStyle::setMenuButton(Style *style) {
    if (style != this->menuButton()) {
        Q_D(ToolButtonStyle);
        
        if (d->menuButton) {
            this->disconnect(d->menuButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->menuButton = style;
        d->dirty = true;
        
        if (d->menuButton) {
            this->connect(d->menuButton, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ToolButtonStyle::resetMenuButton() {
    this->setMenuButton(0);
}

Style* ToolButtonStyle::menuIndicator() const {
    Q_D(const ToolButtonStyle);
    
    return d->menuIndicator;
}

void ToolButtonStyle::setMenuIndicator(Style *style) {
    if (style != this->menuIndicator()) {
        Q_D(ToolButtonStyle);
        
        if (d->menuIndicator) {
            this->disconnect(d->menuIndicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->menuIndicator = style;
        d->dirty = true;
        
        if (d->menuIndicator) {
            this->connect(d->menuIndicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ToolButtonStyle::resetMenuIndicator() {
    this->setMenuIndicator(0);
}

Style* ToolButtonStyle::downArrow() const {
    Q_D(const ToolButtonStyle);
    
    return d->downArrow;
}

void ToolButtonStyle::setDownArrow(Style *style) {
    if (style != this->downArrow()) {
        Q_D(ToolButtonStyle);
        
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

void ToolButtonStyle::resetDownArrow() {
    this->setDownArrow(0);
}

Style* ToolButtonStyle::leftArrow() const {
    Q_D(const ToolButtonStyle);
    
    return d->leftArrow;
}

void ToolButtonStyle::setLeftArrow(Style *style) {
    if (style != this->leftArrow()) {
        Q_D(ToolButtonStyle);
        
        if (d->leftArrow) {
            this->disconnect(d->leftArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->leftArrow = style;
        d->dirty = true;
        
        if (d->leftArrow) {
            this->connect(d->leftArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ToolButtonStyle::resetLeftArrow() {
    this->setLeftArrow(0);
}

Style* ToolButtonStyle::rightArrow() const {
    Q_D(const ToolButtonStyle);
    
    return d->rightArrow;
}

void ToolButtonStyle::setRightArrow(Style *style) {
    if (style != this->rightArrow()) {
        Q_D(ToolButtonStyle);
        
        if (d->rightArrow) {
            this->disconnect(d->rightArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->rightArrow = style;
        d->dirty = true;
        
        if (d->rightArrow) {
            this->connect(d->rightArrow, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ToolButtonStyle::resetRightArrow() {
    this->setRightArrow(0);
}

Style* ToolButtonStyle::upArrow() const {
    Q_D(const ToolButtonStyle);
    
    return d->upArrow;
}

void ToolButtonStyle::setUpArrow(Style *style) {
    if (style != this->upArrow()) {
        Q_D(ToolButtonStyle);
        
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

void ToolButtonStyle::resetUpArrow() {
    this->setUpArrow(0);
}

QString ToolButtonStyle::toStyleSheet() const {
    Q_D(const ToolButtonStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QToolButton { " + d->mainBody() + " }");
    
    if (d->menuButton) {
        s += " QToolButton::menu-button { " + d->menuButtonBody() + " }";
    }
    
    if (d->menuIndicator) {
        s += " QToolButton::menu-indicator { " + d->menuIndicatorBody() + " }";
    }
    
    if (d->downArrow) {
        s += " QToolButton::down-arrow { " + d->downArrowBody() + " }";
    }
    
    if (d->leftArrow) {
        s += " QToolButton::left-arrow { " + d->leftArrowBody() + " }";
    }
    
    if (d->rightArrow) {
        s += " QToolButton::right-arrow { " + d->rightArrowBody() + " }";
    }
    
    if (d->upArrow) {
        s += " QToolButton::up-arrow { " + d->upArrowBody() + " }";
    }
    
    return s;
}

#include "moc_toolbuttonstyle_p.cpp"

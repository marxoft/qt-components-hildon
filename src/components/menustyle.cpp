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

#include "menustyle_p.h"
#include "menustyle_p_p.h"

MenuStylePrivate::MenuStylePrivate(MenuStyle *parent) :
    BoxStylePrivate(parent),
    indicator(0),
    item(0),
    leftArrow(0),
    rightArrow(0),
    scroller(0),
    separator(0),
    tearoff(0)
{
}

QString MenuStylePrivate::indicatorBody() const {
    return indicator ? indicator->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::itemBody() const {
    return item ? item->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::leftArrowBody() const {
    return leftArrow ? leftArrow->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::rightArrowBody() const {
    return rightArrow ? rightArrow->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::scrollerBody() const {
    return scroller ? scroller->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::separatorBody() const {
    return separator ? separator->toStyleSheet()
                     : QString();
}

QString MenuStylePrivate::tearoffBody() const {
    return tearoff ? tearoff->toStyleSheet()
                     : QString();
}

MenuStyle::MenuStyle(QObject *parent) :
    BoxStyle(*new MenuStylePrivate(this), parent)
{
}

MenuStyle::MenuStyle(MenuStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

MenuStyle::~MenuStyle() {}

Style* MenuStyle::indicator() const {
    Q_D(const MenuStyle);
    
    return d->indicator;
}

void MenuStyle::setIndicator(Style *style) {
    if (style != this->indicator()) {
        Q_D(MenuStyle);
        
        if (d->indicator) {
            this->disconnect(d->indicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->indicator = style;
        d->dirty = true;
        
        if (d->indicator) {
            this->connect(d->indicator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void MenuStyle::resetIndicator() {
    this->setIndicator(0);
}

Style* MenuStyle::item() const {
    Q_D(const MenuStyle);
    
    return d->item;
}

void MenuStyle::setItem(Style *style) {
    if (style != this->item()) {
        Q_D(MenuStyle);
        
        if (d->item) {
            this->disconnect(d->item, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->item = style;
        d->dirty = true;
        
        if (d->item) {
            this->connect(d->item, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void MenuStyle::resetItem() {
    this->setItem(0);
}

Style* MenuStyle::leftArrow() const {
    Q_D(const MenuStyle);
    
    return d->leftArrow;
}

void MenuStyle::setLeftArrow(Style *style) {
    if (style != this->leftArrow()) {
        Q_D(MenuStyle);
        
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

void MenuStyle::resetLeftArrow() {
    this->setLeftArrow(0);
}

Style* MenuStyle::rightArrow() const {
    Q_D(const MenuStyle);
    
    return d->rightArrow;
}

void MenuStyle::setRightArrow(Style *style) {
    if (style != this->rightArrow()) {
        Q_D(MenuStyle);
        
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

void MenuStyle::resetRightArrow() {
    this->setRightArrow(0);
}

Style* MenuStyle::scroller() const {
    Q_D(const MenuStyle);
    
    return d->scroller;
}

void MenuStyle::setScroller(Style *style) {
    if (style != this->scroller()) {
        Q_D(MenuStyle);
        
        if (d->scroller) {
            this->disconnect(d->scroller, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->scroller = style;
        d->dirty = true;
        
        if (d->scroller) {
            this->connect(d->scroller, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void MenuStyle::resetScroller() {
    this->setScroller(0);
}

Style* MenuStyle::separator() const {
    Q_D(const MenuStyle);
    
    return d->separator;
}

void MenuStyle::setSeparator(Style *style) {
    if (style != this->separator()) {
        Q_D(MenuStyle);
        
        if (d->separator) {
            this->disconnect(d->separator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->separator = style;
        d->dirty = true;
        
        if (d->separator) {
            this->connect(d->separator, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void MenuStyle::resetSeparator() {
    this->setSeparator(0);
}

Style* MenuStyle::tearoff() const {
    Q_D(const MenuStyle);
    
    return d->tearoff;
}

void MenuStyle::setTearoff(Style *style) {
    if (style != this->tearoff()) {
        Q_D(MenuStyle);
        
        if (d->tearoff) {
            this->disconnect(d->tearoff, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->tearoff = style;
        d->dirty = true;
        
        if (d->tearoff) {
            this->connect(d->tearoff, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void MenuStyle::resetTearoff() {
    this->setTearoff(0);
}

QString MenuStyle::toStyleSheet() const {
    Q_D(const MenuStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QMenu { " + d->mainBody() + " }");
    
    if (d->indicator) {
        s += " QMenu::indicator { " + d->indicatorBody() + " }";
    }
    
    if (d->item) {
        s += " QMenu::item { " + d->itemBody() + " }";
    }
    
    if (d->leftArrow) {
        s += " QMenu::left-arrow { " + d->leftArrowBody() + " }";
    }
    
    if (d->rightArrow) {
        s += " QMenu::right-arrow { " + d->rightArrowBody() + " }";
    }
    
    if (d->scroller) {
        s += " QMenu::scroller { " + d->scrollerBody() + " }";
    }
    
    if (d->separator) {
        s += " QMenu::separator { " + d->separatorBody() + " }";
    }
    
    if (d->tearoff) {
        s += " QMenu::tearoff { " + d->tearoffBody() + " }";
    }
    
    return s;
}

#include "moc_menustyle_p.cpp"


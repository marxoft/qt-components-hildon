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

#include "toolbarstyle_p.h"
#include "toolbarstyle_p_p.h"

ToolBarStylePrivate::ToolBarStylePrivate(ToolBarStyle *parent) :
    BoxStylePrivate(parent),
    handle(0),
    separator(0)
{
}

QString ToolBarStylePrivate::handleBody() const {
    return handle ? handle->toStyleSheet()
                     : QString();
}

QString ToolBarStylePrivate::separatorBody() const {
    return separator ? separator->toStyleSheet()
                     : QString();
}

ToolBarStyle::ToolBarStyle(QObject *parent) :
    BoxStyle(*new ToolBarStylePrivate(this), parent)
{
}

ToolBarStyle::ToolBarStyle(ToolBarStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

ToolBarStyle::~ToolBarStyle() {}

Style* ToolBarStyle::handle() const {
    Q_D(const ToolBarStyle);
    
    return d->handle;
}

void ToolBarStyle::setHandle(Style *style) {
    if (style != this->handle()) {
        Q_D(ToolBarStyle);
        
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

void ToolBarStyle::resetHandle() {
    this->setHandle(0);
}

Style* ToolBarStyle::separator() const {
    Q_D(const ToolBarStyle);
    
    return d->separator;
}

void ToolBarStyle::setSeparator(Style *style) {
    if (style != this->separator()) {
        Q_D(ToolBarStyle);
        
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

void ToolBarStyle::resetSeparator() {
    this->setSeparator(0);
}

QString ToolBarStyle::toStyleSheet() const {
    Q_D(const ToolBarStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QToolBar { " + d->mainBody() + " }");
    
    if (d->handle) {
        s += " QToolBar::handle { " + d->handleBody() + " }";
    }
    
    if (d->separator) {
        s += " QToolBar::separator { " + d->separatorBody() + " }";
    }
    
    return s;
}

#include "moc_toolbarstyle_p.cpp"


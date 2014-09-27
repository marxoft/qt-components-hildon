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

#include "tabbarstyle_p.h"
#include "tabbarstyle_p_p.h"

TabBarStylePrivate::TabBarStylePrivate(TabBarStyle *parent) :
    BoxStylePrivate(parent),
    firstTab(0),
    lastTab(0),
    middleTab(0),
    scroller(0),
    selectedTab(0),
    tab(0),
    tear(0)
{
}

QString TabBarStylePrivate::firstTabBody() const {
    return firstTab ? firstTab->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::lastTabBody() const {
    return lastTab ? lastTab->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::middleTabBody() const {
    return middleTab ? middleTab->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::scrollerBody() const {
    return scroller ? scroller->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::selectedTabBody() const {
    return selectedTab ? selectedTab->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::tabBody() const {
    return tab ? tab->toStyleSheet()
                     : QString();
}

QString TabBarStylePrivate::tearBody() const {
    return tear ? tear->toStyleSheet()
                     : QString();
}

TabBarStyle::TabBarStyle(QObject *parent) :
    BoxStyle(*new TabBarStylePrivate(this), parent)
{
}

TabBarStyle::TabBarStyle(TabBarStylePrivate &dd, QObject *parent) :
    BoxStyle(dd, parent)
{
}

TabBarStyle::~TabBarStyle() {}

Style* TabBarStyle::firstTab() const {
    Q_D(const TabBarStyle);
    
    return d->firstTab;
}

void TabBarStyle::setFirstTab(Style *style) {
    if (style != this->firstTab()) {
        Q_D(TabBarStyle);
        
        if (d->firstTab) {
            this->disconnect(d->firstTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->firstTab = style;
        d->dirty = true;
        
        if (d->firstTab) {
            this->connect(d->firstTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetFirstTab() {
    this->setFirstTab(0);
}

Style* TabBarStyle::lastTab() const {
    Q_D(const TabBarStyle);
    
    return d->lastTab;
}

void TabBarStyle::setLastTab(Style *style) {
    if (style != this->lastTab()) {
        Q_D(TabBarStyle);
        
        if (d->lastTab) {
            this->disconnect(d->lastTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->lastTab = style;
        d->dirty = true;
        
        if (d->lastTab) {
            this->connect(d->lastTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetLastTab() {
    this->setLastTab(0);
}

Style* TabBarStyle::middleTab() const {
    Q_D(const TabBarStyle);
    
    return d->middleTab;
}

void TabBarStyle::setMiddleTab(Style *style) {
    if (style != this->middleTab()) {
        Q_D(TabBarStyle);
        
        if (d->middleTab) {
            this->disconnect(d->middleTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->middleTab = style;
        d->dirty = true;
        
        if (d->middleTab) {
            this->connect(d->middleTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetMiddleTab() {
    this->setMiddleTab(0);
}

Style* TabBarStyle::scroller() const {
    Q_D(const TabBarStyle);
    
    return d->scroller;
}

void TabBarStyle::setScroller(Style *style) {
    if (style != this->scroller()) {
        Q_D(TabBarStyle);
        
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

void TabBarStyle::resetScroller() {
    this->setScroller(0);
}

Style* TabBarStyle::selectedTab() const {
    Q_D(const TabBarStyle);
    
    return d->selectedTab;
}

void TabBarStyle::setSelectedTab(Style *style) {
    if (style != this->selectedTab()) {
        Q_D(TabBarStyle);
        
        if (d->selectedTab) {
            this->disconnect(d->selectedTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->selectedTab = style;
        d->dirty = true;
        
        if (d->selectedTab) {
            this->connect(d->selectedTab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetSelectedTab() {
    this->setSelectedTab(0);
}

Style* TabBarStyle::tab() const {
    Q_D(const TabBarStyle);
    
    return d->tab;
}

void TabBarStyle::setTab(Style *style) {
    if (style != this->tab()) {
        Q_D(TabBarStyle);
        
        if (d->tab) {
            this->disconnect(d->tab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->tab = style;
        d->dirty = true;
        
        if (d->tab) {
            this->connect(d->tab, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetTab() {
    this->setTab(0);
}

Style* TabBarStyle::tear() const {
    Q_D(const TabBarStyle);
    
    return d->tear;
}

void TabBarStyle::setTear(Style *style) {
    if (style != this->tear()) {
        Q_D(TabBarStyle);
        
        if (d->tear) {
            this->disconnect(d->tear, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->tear = style;
        d->dirty = true;
        
        if (d->tear) {
            this->connect(d->tear, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TabBarStyle::resetTear() {
    this->setTear(0);
}

QString TabBarStyle::toStyleSheet() const {
    Q_D(const TabBarStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s("QTabBar { " + d->mainBody() + " }");
    
    if (d->firstTab) {
        s += " QTabBar::tab:first { " + d->firstTabBody() + " }";
    }
    
    if (d->lastTab) {
        s += " QTabBar::tab:last { " + d->lastTabBody() + " }";
    }
    
    if (d->middleTab) {
        s += " QTabBar::tab:middle { " + d->middleTabBody() + " }";
    }
    
    if (d->selectedTab) {
        s += " QTabBar::tab:selected { " + d->selectedTabBody() + " }";
    }
    
    if (d->scroller) {
        s += " QTabBar::scroller { " + d->scrollerBody() + " }";
    }
    
    if (d->tab) {
        s += " QTabBar::tab { " + d->tabBody() + " }";
    }
    
    if (d->tear) {
        s += " QTabBar::tear { " + d->tearBody() + " }";
    }
    
    return s;
}

#include "moc_tabbarstyle_p.cpp"


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
#include "boxstyle_p_p.h"

class TabBarStylePrivate : public BoxStylePrivate
{

public:
    TabBarStylePrivate(TabBarStyle *parent);
    
    virtual QString firstTabBody() const;
    virtual QString lastTabBody() const;
    virtual QString middleTabBody() const;
    virtual QString scrollerBody() const;
    virtual QString selectedTabBody() const;
    virtual QString tabBody() const;
    virtual QString tearBody() const;
    
    Style *firstTab;
    Style *lastTab;
    Style *middleTab;
    Style *scroller;
    Style *selectedTab;
    Style *tab;
    Style *tear;
    
    Q_DECLARE_PUBLIC(TabBarStyle)
};


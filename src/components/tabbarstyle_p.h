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

#ifndef TABBARSTYLE_P_H
#define TABBARSTYLE_P_H

#include "boxstyle_p.h"

class TabBarStylePrivate;

class TabBarStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* firstTab READ firstTab WRITE setFirstTab RESET resetFirstTab NOTIFY changed)
    Q_PROPERTY(Style* lastTab READ lastTab WRITE setLastTab RESET resetLastTab NOTIFY changed)
    Q_PROPERTY(Style* middleTab READ middleTab WRITE setMiddleTab RESET resetMiddleTab NOTIFY changed)
    Q_PROPERTY(Style* scroller READ scroller WRITE setScroller RESET resetScroller NOTIFY changed)
    Q_PROPERTY(Style* selectedTab READ selectedTab WRITE setSelectedTab RESET resetSelectedTab NOTIFY changed)
    Q_PROPERTY(Style* tab READ tab WRITE setTab RESET resetTab NOTIFY changed)
    Q_PROPERTY(Style* tear READ tear WRITE setTear RESET resetTear NOTIFY changed)
    
public:
    explicit TabBarStyle(QObject *parent = 0);
    ~TabBarStyle();
    
    Style* firstTab() const;
    void setFirstTab(Style *style);
    void resetFirstTab();
    
    Style* lastTab() const;
    void setLastTab(Style *style);
    void resetLastTab();
    
    Style* middleTab() const;
    void setMiddleTab(Style *style);
    void resetMiddleTab();
    
    Style* scroller() const;
    void setScroller(Style *style);
    void resetScroller();
    
    Style* selectedTab() const;
    void setSelectedTab(Style *style);
    void resetSelectedTab();
    
    Style* tab() const;
    void setTab(Style *style);
    void resetTab();
    
    Style* tear() const;
    void setTear(Style *style);
    void resetTear();
    
    virtual QString toStyleSheet() const;
    
protected:
    TabBarStyle(TabBarStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(TabBarStyle)
    
private:
    Q_DISABLE_COPY(TabBarStyle)
};

QML_DECLARE_TYPE(TabBarStyle)

#endif // TABBARSTYLE_P_H


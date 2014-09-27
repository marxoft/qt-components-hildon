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

#ifndef MENUSTYLE_P_H
#define MENUSTYLE_P_H

#include "boxstyle_p.h"

class MenuStylePrivate;

class MenuStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* indicator READ indicator WRITE setIndicator RESET resetIndicator NOTIFY changed)
    Q_PROPERTY(Style* item READ item WRITE setItem RESET resetItem NOTIFY changed)
    Q_PROPERTY(Style* leftArrow READ leftArrow WRITE setLeftArrow RESET resetLeftArrow NOTIFY changed)
    Q_PROPERTY(Style* rightArrow READ rightArrow WRITE setRightArrow RESET resetRightArrow NOTIFY changed)
    Q_PROPERTY(Style* scroller READ scroller WRITE setScroller RESET resetScroller NOTIFY changed)
    Q_PROPERTY(Style* separator READ separator WRITE setSeparator RESET resetSeparator NOTIFY changed)
    Q_PROPERTY(Style* tearoff READ tearoff WRITE setTearoff RESET resetTearoff NOTIFY changed)
    
public:
    explicit MenuStyle(QObject *parent = 0);
    ~MenuStyle();
    
    Style* indicator() const;
    void setIndicator(Style *style);
    void resetIndicator();
    
    Style* item() const;
    void setItem(Style *style);
    void resetItem();
    
    Style* leftArrow() const;
    void setLeftArrow(Style *style);
    void resetLeftArrow();
    
    Style* rightArrow() const;
    void setRightArrow(Style *style);
    void resetRightArrow();
    
    Style* scroller() const;
    void setScroller(Style *style);
    void resetScroller();
    
    Style* separator() const;
    void setSeparator(Style *style);
    void resetSeparator();
    
    Style* tearoff() const;
    void setTearoff(Style *style);
    void resetTearoff();
    
    virtual QString toStyleSheet() const;
    
protected:
    MenuStyle(MenuStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(MenuStyle)
    
private:
    Q_DISABLE_COPY(MenuStyle)
};

QML_DECLARE_TYPE(MenuStyle)

#endif // MENUSTYLE_P_H


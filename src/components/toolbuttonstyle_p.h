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

#ifndef TOOLBUTTONSTYLE_P_H
#define TOOLBUTTONSTYLE_P_H

#include "boxstyle_p.h"

class ToolButtonStylePrivate;

class ToolButtonStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* menuButton READ menuButton WRITE setMenuButton RESET resetMenuButton NOTIFY changed)
    Q_PROPERTY(Style* menuIndicator READ menuIndicator WRITE setMenuIndicator RESET resetMenuIndicator NOTIFY changed)
    Q_PROPERTY(Style* downArrow READ downArrow WRITE setDownArrow RESET resetDownArrow NOTIFY changed)
    Q_PROPERTY(Style* leftArrow READ leftArrow WRITE setLeftArrow RESET resetLeftArrow NOTIFY changed)
    Q_PROPERTY(Style* rightArrow READ rightArrow WRITE setRightArrow RESET resetRightArrow NOTIFY changed)
    Q_PROPERTY(Style* upArrow READ upArrow WRITE setUpArrow RESET resetUpArrow NOTIFY changed)
    
public:
    explicit ToolButtonStyle(QObject *parent = 0);
    ~ToolButtonStyle();
    
    Style* menuButton() const;
    void setMenuButton(Style *style);
    void resetMenuButton();
    
    Style* menuIndicator() const;
    void setMenuIndicator(Style *style);
    void resetMenuIndicator();
    
    Style* downArrow() const;
    void setDownArrow(Style *style);
    void resetDownArrow();
    
    Style* leftArrow() const;
    void setLeftArrow(Style *style);
    void resetLeftArrow();
    
    Style* rightArrow() const;
    void setRightArrow(Style *style);
    void resetRightArrow();
    
    Style* upArrow() const;
    void setUpArrow(Style *style);
    void resetUpArrow();
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    ToolButtonStyle(ToolButtonStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(ToolButtonStyle)
    
private:
    Q_DISABLE_COPY(ToolButtonStyle)
};

QML_DECLARE_TYPE(ToolButtonStyle)

#endif // TOOLBUTTONSTYLE_P_H


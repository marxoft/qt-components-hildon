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

#ifndef TOOLBUTTONSTYLE_P_P_H
#define TOOLBUTTONSTYLE_P_P_H

#include "toolbuttonstyle_p.h"
#include "boxstyle_p_p.h"

class ToolButtonStylePrivate : public BoxStylePrivate
{

public:
    ToolButtonStylePrivate(ToolButtonStyle *parent);
    
    virtual QString menuButtonBody() const;
    virtual QString menuIndicatorBody() const;
    virtual QString downArrowBody() const;
    virtual QString leftArrowBody() const;
    virtual QString rightArrowBody() const;
    virtual QString upArrowBody() const;
    
    Style *menuButton;
    Style *menuIndicator;
    Style *downArrow;
    Style *leftArrow;
    Style *rightArrow;
    Style *upArrow;
    
    Q_DECLARE_PUBLIC(ToolButtonStyle)
};

#endif // TOOLBUTTONSTYLE_P_P_H


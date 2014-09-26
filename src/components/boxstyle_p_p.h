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

#include "boxstyle_p.h"
#include "style_p_p.h"

class BoxStylePrivate : public StylePrivate
{

public:
    BoxStylePrivate(BoxStyle *parent);
    
    virtual QString mainBody() const;
    
    QColor borderColor;
    QColor borderColorTop;
    QColor borderColorRight;
    QColor borderColorBottom;
    QColor borderColorLeft;
    
    QString borderImage;
    
    int borderRadius;
    int borderRadiusTopLeft;
    int borderRadiusTopRight;
    int borderRadiusBottomRight;
    int borderRadiusBottomLeft;
    
    BoxStyle::BorderStyle borderStyle;
    
    int borderWidth;
    int borderWidthTop;
    int borderWidthRight;
    int borderWidthBottom;
    int borderWidthLeft;
    
    QString image;
    
    Qt::Alignment imagePosition;
    
    int margin;
    int marginTop;
    int marginRight;
    int marginBottom;
    int marginLeft;
    
    int padding;
    int paddingTop;
    int paddingRight;
    int paddingBottom;
    int paddingLeft;
    
    QColor textColor;
    
    Q_DECLARE_PUBLIC(BoxStyle)
};


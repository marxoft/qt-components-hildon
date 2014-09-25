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
    BoxStylePrivate(BoxStyle *parent) :
        StylePrivate(parent),
        borderRadius(0),
        borderRadiusTopLeft(0),
        borderRadiusTopRight(0),
        borderRadiusBottomRight(0),
        borderRadiusBottomLeft(0),
        borderStyle(BoxStyle::None),
        borderWidth(0),
        borderWidthTop(0),
        borderWidthRight(0),
        borderWidthBottom(0),
        borderWidthLeft(0),
        margin(0),
        marginTop(0),
        marginRight(0),
        marginBottom(0),
        marginLeft(0),
        padding(0),
        paddingTop(0),
        paddingRight(0),
        paddingBottom(0),
        paddingLeft(0)
    {
    }
    
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


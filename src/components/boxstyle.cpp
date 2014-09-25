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
#include "boxstyle_p_p.h"

BoxStyle::BoxStyle(QObject *parent) :
    Style(*new BoxStylePrivate(this), parent)
{
}

BoxStyle::BoxStyle(BoxStylePrivate &dd, QObject *parent) :
    Style(dd, parent)
{
}

BoxStyle::~BoxStyle() {}

QColor BoxStyle::borderColor() const {
    Q_D(const BoxStyle);
    
    return d->borderColor;
}

void BoxStyle::setBorderColor(const QColor &color) {
    if (color != this->borderColor()) {
        Q_D(BoxStyle);
        d->borderColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor BoxStyle::borderColorTop() const {
    Q_D(const BoxStyle);
    
    return d->borderColorTop;
}

void BoxStyle::setBorderColorTop(const QColor &color) {
    if (color != this->borderColorTop()) {
        Q_D(BoxStyle);
        d->borderColorTop = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor BoxStyle::borderColorRight() const {
    Q_D(const BoxStyle);
    
    return d->borderColorRight;
}

void BoxStyle::setBorderColorRight(const QColor &color) {
    if (color != this->borderColorRight()) {
        Q_D(BoxStyle);
        d->borderColorRight = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor BoxStyle::borderColorBottom() const {
    Q_D(const BoxStyle);
    
    return d->borderColorBottom;
}

void BoxStyle::setBorderColorBottom(const QColor &color) {
    if (color != this->borderColorBottom()) {
        Q_D(BoxStyle);
        d->borderColorBottom = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor BoxStyle::borderColorLeft() const {
    Q_D(const BoxStyle);
    
    return d->borderColorLeft;
}

void BoxStyle::setBorderColorLeft(const QColor &color) {
    if (color != this->borderColorLeft()) {
        Q_D(BoxStyle);
        d->borderColorLeft = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString BoxStyle::borderImage() const {
    Q_D(const BoxStyle);
    
    return d->borderImage;
}

void BoxStyle::setBorderImage(const QString &source) {
    if (source != this->borderImage()) {
        Q_D(BoxStyle);
        d->borderImage = source;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderRadius() const {
    Q_D(const BoxStyle);
    
    return d->borderRadius;
}

void BoxStyle::setBorderRadius(int radius) {
    if (radius != this->borderRadius()) {
        Q_D(BoxStyle);
        d->borderRadius = radius;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderRadiusTopLeft() const {
    Q_D(const BoxStyle);
    
    return d->borderRadiusTopLeft;
}

void BoxStyle::setBorderRadiusTopLeft(int radius) {
    if (radius != this->borderRadiusTopLeft()) {
        Q_D(BoxStyle);
        d->borderRadiusTopLeft = radius;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderRadiusTopRight() const {
    Q_D(const BoxStyle);
    
    return d->borderRadiusTopRight;
}

void BoxStyle::setBorderRadiusTopRight(int radius) {
    if (radius != this->borderRadiusTopRight()) {
        Q_D(BoxStyle);
        d->borderRadiusTopRight = radius;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderRadiusBottomRight() const {
    Q_D(const BoxStyle);
    
    return d->borderRadiusBottomRight;
}

void BoxStyle::setBorderRadiusBottomRight(int radius) {
    if (radius != this->borderRadiusBottomRight()) {
        Q_D(BoxStyle);
        d->borderRadiusBottomRight = radius;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderRadiusBottomLeft() const {
    Q_D(const BoxStyle);
    
    return d->borderRadiusBottomLeft;
}

void BoxStyle::setBorderRadiusBottomLeft(int radius) {
    if (radius != this->borderRadiusBottomLeft()) {
        Q_D(BoxStyle);
        d->borderRadiusBottomLeft = radius;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

BoxStyle::BorderStyle BoxStyle::borderStyle() const {
    Q_D(const BoxStyle);
    
    return d->borderStyle;
}

void BoxStyle::setBorderStyle(BorderStyle style) {
    if (style != this->borderStyle()) {
        Q_D(BoxStyle);
        d->borderStyle = style;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderWidth() const {
    Q_D(const BoxStyle);
    
    return d->borderWidth;
}

void BoxStyle::setBorderWidth(int width) {
    if (width != this->borderWidth()) {
        Q_D(BoxStyle);
        d->borderWidth = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderWidthTop() const {
    Q_D(const BoxStyle);
    
    return d->borderWidthTop;
}

void BoxStyle::setBorderWidthTop(int width) {
    if (width != this->borderWidthTop()) {
        Q_D(BoxStyle);
        d->borderWidthTop = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderWidthRight() const {
    Q_D(const BoxStyle);
    
    return d->borderWidthRight;
}

void BoxStyle::setBorderWidthRight(int width) {
    if (width != this->borderWidthRight()) {
        Q_D(BoxStyle);
        d->borderWidthRight = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderWidthBottom() const {
    Q_D(const BoxStyle);
    
    return d->borderWidthBottom;
}

void BoxStyle::setBorderWidthBottom(int width) {
    if (width != this->borderWidthBottom()) {
        Q_D(BoxStyle);
        d->borderWidthBottom = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::borderWidthLeft() const {
    Q_D(const BoxStyle);
    
    return d->borderWidthLeft;
}

void BoxStyle::setBorderWidthLeft(int width) {
    if (width != this->borderWidthLeft()) {
        Q_D(BoxStyle);
        d->borderWidthLeft = width;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString BoxStyle::image() const {
    Q_D(const BoxStyle);
    
    return d->image;
}

void BoxStyle::setImage(const QString &source) {
    if (source != this->image()) {
        Q_D(BoxStyle);
        d->image = source;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::margin() const {
    Q_D(const BoxStyle);
    
    return d->margin;
}

void BoxStyle::setMargin(int m) {
    if (m != this->margin()) {
        Q_D(BoxStyle);
        d->margin = m;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::marginTop() const {
    Q_D(const BoxStyle);
    
    return d->marginTop;
}

void BoxStyle::setMarginTop(int m) {
    if (m != this->marginTop()) {
        Q_D(BoxStyle);
        d->marginTop = m;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::marginRight() const {
    Q_D(const BoxStyle);
    
    return d->marginRight;
}

void BoxStyle::setMarginRight(int m) {
    if (m != this->marginRight()) {
        Q_D(BoxStyle);
        d->marginRight = m;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::marginBottom() const {
    Q_D(const BoxStyle);
    
    return d->marginBottom;
}

void BoxStyle::setMarginBottom(int m) {
    if (m != this->marginBottom()) {
        Q_D(BoxStyle);
        d->marginBottom = m;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::marginLeft() const {
    Q_D(const BoxStyle);
    
    return d->marginLeft;
}

void BoxStyle::setMarginLeft(int m) {
    if (m != this->marginLeft()) {
        Q_D(BoxStyle);
        d->marginLeft = m;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::padding() const {
    Q_D(const BoxStyle);
    
    return d->padding;
}

void BoxStyle::setPadding(int p) {
    if (p != this->padding()) {
        Q_D(BoxStyle);
        d->padding = p;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::paddingTop() const {
    Q_D(const BoxStyle);
    
    return d->paddingTop;
}

void BoxStyle::setPaddingTop(int p) {
    if (p != this->paddingTop()) {
        Q_D(BoxStyle);
        d->paddingTop = p;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::paddingRight() const {
    Q_D(const BoxStyle);
    
    return d->paddingRight;
}

void BoxStyle::setPaddingRight(int p) {
    if (p != this->paddingRight()) {
        Q_D(BoxStyle);
        d->paddingRight = p;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::paddingBottom() const {
    Q_D(const BoxStyle);
    
    return d->paddingBottom;
}

void BoxStyle::setPaddingBottom(int p) {
    if (p != this->paddingBottom()) {
        Q_D(BoxStyle);
        d->paddingBottom = p;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::paddingLeft() const {
    Q_D(const BoxStyle);
    
    return d->paddingLeft;
}

void BoxStyle::setPaddingLeft(int p) {
    if (p != this->paddingLeft()) {
        Q_D(BoxStyle);
        d->paddingLeft = p;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor BoxStyle::textColor() const {
    Q_D(const BoxStyle);
    
    return d->textColor;
}

void BoxStyle::setTextColor(const QColor &color) {
    if (color != this->textColor()) {
        Q_D(BoxStyle);
        d->textColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString BoxStyle::toStyleSheet() const {
    Q_D(const BoxStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    QString s = Style::toStyleSheet();
    
    if (d->borderColor.isValid()) {
        s += "border-color: " + d->borderColor.name() + ";";
    }
    else {
        if (d->borderColorTop.isValid()) {
            s += "border-top-color: " + d->borderColorTop.name() + ";";
        }
        
        if (d->borderColorRight.isValid()) {
            s += "border-right-color: " + d->borderColorRight.name() + ";";
        }
        
        if (d->borderColorBottom.isValid()) {
            s += "border-bottom-color: " + d->borderColorBottom.name() + ";";
        }
        
        if (d->borderColorLeft.isValid()) {
            s += "border-left-color: " + d->borderColorLeft.name() + ";";
        }
    }
    
    if (!d->borderImage.isEmpty()) {
        s += "border-image: url(" + d->borderImage + ");";
    }
    
    if (d->borderRadius) {
        s += "border-radius: " + QString::number(d->borderRadius) + "px;";
    }
    else {
        if (d->borderRadiusTopLeft) {
            s += "border-top-left-radius: " + QString::number(d->borderRadiusTopLeft) + "px;";
        }
        
        if (d->borderRadiusTopRight) {
            s += "border-top-right-radius: " + QString::number(d->borderRadiusTopRight) + "px;";
        }
        
        if (d->borderRadiusBottomRight) {
            s += "border-bottom-right-radius: " + QString::number(d->borderRadiusBottomRight) + "px;";
        }
        
        if (d->borderRadiusBottomLeft) {
            s += "border-bottom-left-radius: " + QString::number(d->borderRadiusBottomLeft) + "px;";
        }
    }
    
    switch (d->borderStyle) {
    case Dashed:
        s += "border-style: dashed;";
        break;
    case DotDash:
        s += "border-style: dot-dash;";
        break;
    case DotDotDash:
        s += "border-style: dot-dot-dash;";
        break;
    case Dotted:
        s += "border-style: dotted;";
        break;
    case Double:
        s += "border-style: double;";
        break;
    case Groove:
        s += "border-style: groove;";
        break;
    case Inset:
        s += "border-style: inset;";
        break;
    case Outset:
        s += "border-style: outset;";
        break;
    case Ridge:
        s += "border-style: ridge;";
        break;
    case Solid:
        s += "border-style: solid;";
        break;
    case None:
        s += "border-style: none;";
        break;
    default:
        s += "border-style: none;";
        break;
    }
    
    if (d->borderWidth) {
        s += "border-width: " + QString::number(d->borderWidth) + "px;";
    }
    else {
        if (d->borderWidthTop) {
            s += "border-top-width: " + QString::number(d->borderWidthTop) + "px;";
        }
        
        if (d->borderWidthRight) {
            s += "border-right-width: " + QString::number(d->borderWidthRight) + "px;";
        }
        
        if (d->borderWidthBottom) {
            s += "border-bottom-width: " + QString::number(d->borderWidthBottom) + "px;";
        }
        
        if (d->borderWidthLeft) {
            s += "border-left-width: " + QString::number(d->borderWidthLeft) + "px;";
        }
    }
    
    if (!d->image.isEmpty()) {
        s += "image: url(" + d->image + ");";
    }
    
    if (d->margin) {
        s += "margin: " + QString::number(d->margin) + "px;";
    }
    else {
        if (d->marginTop) {
            s += "margin-top: " + QString::number(d->marginTop) + "px;";
        }
        
        if (d->marginRight) {
            s += "margin-right: " + QString::number(d->marginRight) + "px;";
        }
        
        if (d->marginBottom) {
            s += "margin-bottom: " + QString::number(d->marginBottom) + "px;";
        }
        
        if (d->marginLeft) {
            s += "margin-left: " + QString::number(d->marginLeft) + "px;";
        }
    }
    
    if (d->padding) {
        s += "padding: " + QString::number(d->padding) + "px;";
    }
    else {
        if (d->paddingTop) {
            s += "padding-top: " + QString::number(d->paddingTop) + "px;";
        }
        
        if (d->paddingRight) {
            s += "padding-right: " + QString::number(d->marginRight) + "px;";
        }
        
        if (d->paddingBottom) {
            s += "padding-bottom: " + QString::number(d->paddingBottom) + "px;";
        }
        
        if (d->paddingLeft) {
            s += "padding-left: " + QString::number(d->paddingLeft) + "px;";
        }
    }
    
    if (d->textColor.isValid()) {
        s += "color: " + d->textColor.name() + ";";
    }
    
    return s;
}

#include "moc_boxstyle_p.cpp"


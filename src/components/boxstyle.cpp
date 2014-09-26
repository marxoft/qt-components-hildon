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

BoxStylePrivate::BoxStylePrivate(BoxStyle *parent) :
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
    imagePosition(0),
    margin(0),
    marginTop(0),
    marginRight(0),
    marginBottom(0),
    marginLeft(0),
    minimumWidth(0),
    maximumWidth(0),
    minimumHeight(0),
    maximumHeight(0),
    padding(0),
    paddingTop(0),
    paddingRight(0),
    paddingBottom(0),
    paddingLeft(0)
{
}

QString BoxStylePrivate::mainBody() const {
    QString body = StylePrivate::mainBody();
    
    if (borderColor.isValid()) {
        body += "border-color: " + borderColor.name() + ";";
    }
    else {
        if (borderColorTop.isValid()) {
            body += "border-top-color: " + borderColorTop.name() + ";";
        }
        
        if (borderColorRight.isValid()) {
            body += "border-right-color: " + borderColorRight.name() + ";";
        }
        
        if (borderColorBottom.isValid()) {
            body += "border-bottom-color: " + borderColorBottom.name() + ";";
        }
        
        if (borderColorLeft.isValid()) {
            body += "border-left-color: " + borderColorLeft.name() + ";";
        }
    }
    
    if (!borderImage.isEmpty()) {
        body += "border-image: url(" + borderImage + ");";
    }
    
    if (borderRadius) {
        body += "border-radius: " + QString::number(borderRadius) + "px;";
    }
    else {
        if (borderRadiusTopLeft) {
            body += "border-top-left-radius: " + QString::number(borderRadiusTopLeft) + "px;";
        }
        
        if (borderRadiusTopRight) {
            body += "border-top-right-radius: " + QString::number(borderRadiusTopRight) + "px;";
        }
        
        if (borderRadiusBottomRight) {
            body += "border-bottom-right-radius: " + QString::number(borderRadiusBottomRight) + "px;";
        }
        
        if (borderRadiusBottomLeft) {
            body += "border-bottom-left-radius: " + QString::number(borderRadiusBottomLeft) + "px;";
        }
    }
    
    bool useBorderStyle = false;
    
    if (borderWidth) {
        body += "border-width: " + QString::number(borderWidth) + "px;";
        useBorderStyle = true;
    }
    else {
        if (borderWidthTop) {
            body += "border-top-width: " + QString::number(borderWidthTop) + "px;";
            useBorderStyle = true;
        }
        
        if (borderWidthRight) {
            body += "border-right-width: " + QString::number(borderWidthRight) + "px;";
            useBorderStyle = true;
        }
        
        if (borderWidthBottom) {
            body += "border-bottom-width: " + QString::number(borderWidthBottom) + "px;";
            useBorderStyle = true;
        }
        
        if (borderWidthLeft) {
            body += "border-left-width: " + QString::number(borderWidthLeft) + "px;";
            useBorderStyle = true;
        }
    }
    
    if (useBorderStyle) {
        switch (borderStyle) {
        case BoxStyle::Dashed:
            body += "border-style: dashed;";
            break;
        case BoxStyle::DotDash:
            body += "border-style: dot-dash;";
            break;
        case BoxStyle::DotDotDash:
            body += "border-style: dot-dot-dash;";
            break;
        case BoxStyle::Dotted:
            body += "border-style: dotted;";
            break;
        case BoxStyle::Double:
            body += "border-style: double;";
            break;
        case BoxStyle::Groove:
            body += "border-style: groove;";
            break;
        case BoxStyle::Inset:
            body += "border-style: inset;";
            break;
        case BoxStyle::Outset:
            body += "border-style: outset;";
            break;
        case BoxStyle::Ridge:
            body += "border-style: ridge;";
            break;
        case BoxStyle::Solid:
            body += "border-style: solid;";
            break;
        case BoxStyle::None:
            body += "border-style: none;";
            break;
        default:
            body += "border-style: none;";
            break;
        }
    }
    
    if (!image.isEmpty()) {
        body += "image: url(" + image + ");";
        
        if (imagePosition) {
            body += "image-position:";
            
            if (backgroundPosition & Qt::AlignCenter) {
                body += " center;";
            }
            else {
                if (backgroundPosition & Qt::AlignTop) {
                    body += " top";
                }
                else if (backgroundPosition & Qt::AlignBottom) {
                    body += " bottom";
                }
                else if (backgroundPosition & Qt::AlignVCenter) {
                    body += " center";
                }
                
                if (backgroundPosition & Qt::AlignLeft) {
                    body += " left";
                }
                else if (backgroundPosition & Qt::AlignRight) {
                    body += " right";
                }
                else if (backgroundPosition & Qt::AlignHCenter) {
                    body += " center";
                }
                
                body += ";";
            }
        }
    }
    
    if (margin) {
        body += "margin: " + QString::number(margin) + "px;";
    }
    else {
        if (marginTop) {
            body += "margin-top: " + QString::number(marginTop) + "px;";
        }
        
        if (marginRight) {
            body += "margin-right: " + QString::number(marginRight) + "px;";
        }
        
        if (marginBottom) {
            body += "margin-bottom: " + QString::number(marginBottom) + "px;";
        }
        
        if (marginLeft) {
            body += "margin-left: " + QString::number(marginLeft) + "px;";
        }
    }
    
    if (minimumWidth) {
        body += "min-width: " + QString::number(minimumWidth) + "px;";
    }
    
    if (maximumWidth) {
        body += "max-width: " + QString::number(maximumWidth) + "px;";
    }
    
    if (minimumHeight) {
        body += "min-height: " + QString::number(minimumHeight) + "px;";
    }
    
    if (maximumHeight) {
        body += "max-height: " + QString::number(maximumHeight) + "px;";
    }
    
    if (padding) {
        body += "padding: " + QString::number(padding) + "px;";
    }
    else {
        if (paddingTop) {
            body += "padding-top: " + QString::number(paddingTop) + "px;";
        }
        
        if (paddingRight) {
            body += "padding-right: " + QString::number(marginRight) + "px;";
        }
        
        if (paddingBottom) {
            body += "padding-bottom: " + QString::number(paddingBottom) + "px;";
        }
        
        if (paddingLeft) {
            body += "padding-left: " + QString::number(paddingLeft) + "px;";
        }
    }
    
    if (textColor.isValid()) {
        body += "color: " + textColor.name() + ";";
    }
    
    return body;
}

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

Qt::Alignment BoxStyle::imagePosition() const {
    Q_D(const BoxStyle);
    
    return d->imagePosition;
}

void BoxStyle::setImagePosition(Qt::Alignment align) {
    if (align != this->imagePosition()) {
        Q_D(BoxStyle);
        d->imagePosition = align;
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

int BoxStyle::minimumWidth() const {
    Q_D(const BoxStyle);
    
    return d->minimumWidth;
}

void BoxStyle::setMinimumWidth(int w) {
    if (w != this->minimumWidth()) {
        Q_D(BoxStyle);
        d->minimumWidth = w;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::maximumWidth() const {
    Q_D(const BoxStyle);
    
    return d->maximumWidth;
}

void BoxStyle::setMaximumWidth(int w) {
    if (w != this->maximumWidth()) {
        Q_D(BoxStyle);
        d->maximumWidth = w;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::minimumHeight() const {
    Q_D(const BoxStyle);
    
    return d->minimumHeight;
}

void BoxStyle::setMinimumHeight(int h) {
    if (h != this->minimumHeight()) {
        Q_D(BoxStyle);
        d->minimumHeight = h;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

int BoxStyle::maximumHeight() const {
    Q_D(const BoxStyle);
    
    return d->maximumHeight;
}

void BoxStyle::setMaximumHeight(int h) {
    if (h != this->maximumHeight()) {
        Q_D(BoxStyle);
        d->maximumHeight = h;
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
    
    return d->complete ? d->mainBody() : QString();
}

#include "moc_boxstyle_p.cpp"


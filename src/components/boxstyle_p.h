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

#ifndef BOXSTYLE_P_H
#define BOXSTYLE_P_H

#include "style_p.h"

class BoxStylePrivate;

class BoxStyle : public Style
{
    Q_OBJECT
    
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY changed)
    Q_PROPERTY(QColor borderColorTop READ borderColorTop WRITE setBorderColorTop NOTIFY changed)
    Q_PROPERTY(QColor borderColorRight READ borderColorRight WRITE setBorderColorRight NOTIFY changed)
    Q_PROPERTY(QColor borderColorBottom READ borderColorBottom WRITE setBorderColorBottom NOTIFY changed)
    Q_PROPERTY(QColor borderColorLeft READ borderColorLeft WRITE setBorderColorLeft NOTIFY changed)
    Q_PROPERTY(QString borderImage READ borderImage WRITE setBorderImage NOTIFY changed)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius NOTIFY changed)
    Q_PROPERTY(int borderRadiusTopLeft READ borderRadiusTopLeft WRITE setBorderRadiusTopLeft NOTIFY changed)
    Q_PROPERTY(int borderRadiusTopRight READ borderRadiusTopRight WRITE setBorderRadiusTopRight NOTIFY changed)
    Q_PROPERTY(int borderRadiusBottomRight READ borderRadiusBottomRight WRITE setBorderRadiusBottomRight NOTIFY changed)
    Q_PROPERTY(int borderRadiusBottomLeft READ borderRadiusBottomLeft WRITE setBorderRadiusBottomLeft NOTIFY changed)
    Q_PROPERTY(BorderStyle borderStyle READ borderStyle WRITE setBorderStyle NOTIFY changed)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY changed)
    Q_PROPERTY(int borderWidthTop READ borderWidthTop WRITE setBorderWidthTop NOTIFY changed)
    Q_PROPERTY(int borderWidthRight READ borderWidthRight WRITE setBorderWidthRight NOTIFY changed)
    Q_PROPERTY(int borderWidthBottom READ borderWidthBottom WRITE setBorderWidthBottom NOTIFY changed)
    Q_PROPERTY(int borderWidthLeft READ borderWidthLeft WRITE setBorderWidthLeft NOTIFY changed)
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY changed)
    Q_PROPERTY(Qt::Alignment imagePosition READ imagePosition WRITE setImagePosition NOTIFY changed)
    Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY changed)
    Q_PROPERTY(int marginTop READ marginTop WRITE setMarginTop NOTIFY changed)
    Q_PROPERTY(int marginRight READ marginRight WRITE setMarginRight NOTIFY changed)
    Q_PROPERTY(int marginBottom READ marginBottom WRITE setMarginBottom NOTIFY changed)
    Q_PROPERTY(int marginLeft READ marginLeft WRITE setMarginLeft NOTIFY changed)
    Q_PROPERTY(int minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY changed)
    Q_PROPERTY(int maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY changed)
    Q_PROPERTY(int minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY changed)
    Q_PROPERTY(int maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY changed)
    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY changed)
    Q_PROPERTY(int paddingTop READ paddingTop WRITE setPaddingTop NOTIFY changed)
    Q_PROPERTY(int paddingRight READ paddingRight WRITE setPaddingRight NOTIFY changed)
    Q_PROPERTY(int paddingBottom READ paddingBottom WRITE setPaddingBottom NOTIFY changed)
    Q_PROPERTY(int paddingLeft READ paddingLeft WRITE setPaddingLeft NOTIFY changed)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY changed)
    
    Q_ENUMS(BorderStyle)
    
public:
    enum BorderStyle {
        Dashed = 0,
        DotDash,
        DotDotDash,
        Dotted,
        Double,
        Groove,
        Inset,
        Outset,
        Ridge,
        Solid,
        None
    };
    
    explicit BoxStyle(QObject *parent = 0);
    ~BoxStyle();
    
    QColor borderColor() const;
    void setBorderColor(const QColor &color);
    QColor borderColorTop() const;
    void setBorderColorTop(const QColor &color);
    QColor borderColorRight() const;
    void setBorderColorRight(const QColor &color);
    QColor borderColorBottom() const;
    void setBorderColorBottom(const QColor &color);
    QColor borderColorLeft() const;
    void setBorderColorLeft(const QColor &color);
    
    QString borderImage() const;
    void setBorderImage(const QString &source);
    
    int borderRadius() const;
    void setBorderRadius(int radius);
    int borderRadiusTopLeft() const;
    void setBorderRadiusTopLeft(int radius);
    int borderRadiusTopRight() const;
    void setBorderRadiusTopRight(int radius);
    int borderRadiusBottomRight() const;
    void setBorderRadiusBottomRight(int radius);
    int borderRadiusBottomLeft() const;
    void setBorderRadiusBottomLeft(int radius);
    
    BorderStyle borderStyle() const;
    void setBorderStyle(BorderStyle style);
    
    int borderWidth() const;
    void setBorderWidth(int width);
    int borderWidthTop() const;
    void setBorderWidthTop(int width);
    int borderWidthRight() const;
    void setBorderWidthRight(int width);
    int borderWidthBottom() const;
    void setBorderWidthBottom(int width);
    int borderWidthLeft() const;
    void setBorderWidthLeft(int width);
    
    QString image() const;
    void setImage(const QString &source);
    
    Qt::Alignment imagePosition() const;
    void setImagePosition(Qt::Alignment align);
    
    int margin() const;
    void setMargin(int m);
    int marginTop() const;
    void setMarginTop(int m);
    int marginRight() const;
    void setMarginRight(int m);
    int marginBottom() const;
    void setMarginBottom(int m);
    int marginLeft() const;
    void setMarginLeft(int m);
    
    int minimumWidth() const;
    void setMinimumWidth(int w);
    int maximumWidth() const;
    void setMaximumWidth(int w);
    int minimumHeight() const;
    void setMinimumHeight(int h);
    int maximumHeight() const;
    void setMaximumHeight(int h);
    
    int padding() const;
    void setPadding(int p);
    int paddingTop() const;
    void setPaddingTop(int p);
    int paddingRight() const;
    void setPaddingRight(int p);
    int paddingBottom() const;
    void setPaddingBottom(int p);
    int paddingLeft() const;
    void setPaddingLeft(int p);
    
    QColor textColor() const;
    void setTextColor(const QColor &color);
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    BoxStyle(BoxStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(BoxStyle)
    
private:
    Q_DISABLE_COPY(BoxStyle)
};

QML_DECLARE_TYPE(BoxStyle)

#endif // BUTTONSTYLE_P_H


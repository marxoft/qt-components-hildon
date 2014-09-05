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

#include "borderimage_p.h"
#include "borderimage_p_p.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTransform>
#include <QMargins>
#include <QTileRules>

ImageBorder::ImageBorder(ImageBase *parent) :
    QObject(parent),
    m_left(0),
    m_right(0),
    m_top(0),
    m_bottom(0)
{
}

ImageBorder::~ImageBorder() {}

int ImageBorder::left() const {
    return m_left;
}

void ImageBorder::setLeft(int left) {
    if (left != this->left()) {
        m_left = left;
        emit leftChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetLeft() {
    this->setLeft(0);
}

int ImageBorder::right() const {
    return m_right;
}

void ImageBorder::setRight(int right) {
    if (right != this->right()) {
        m_right = right;
        emit rightChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetRight() {
    this->setRight(0);
}

int ImageBorder::top() const {
    return m_top;
}

void ImageBorder::setTop(int top) {
    if (top != this->top()) {
        m_top = top;
        emit topChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetTop() {
    this->setTop(0);
}

int ImageBorder::bottom() const {
    return m_bottom;
}

void ImageBorder::setBottom(int bottom) {
    if (bottom != this->bottom()) {
        m_bottom = bottom;
        emit bottomChanged();

        if (ImageBase *image = qobject_cast<ImageBase*>(this->parent())) {
            image->update();
        }
    }
}

void ImageBorder::resetBottom() {
    this->setBottom(0);
}

BorderImage::BorderImage(QWidget *parent) :
    ImageBase(*new BorderImagePrivate(this), parent)
{
}

BorderImage::BorderImage(BorderImagePrivate &dd, QWidget *parent) :
    ImageBase(dd, parent)
{
}

BorderImage::~BorderImage() {}

BorderImage::TileMode BorderImage::horizontalTileMode() const {
    Q_D(const BorderImage);

    return d->horizontalTileMode;
}

void BorderImage::setHorizontalTileMode(TileMode mode) {
    if (mode != this->horizontalTileMode()) {
        Q_D(BorderImage);
        d->horizontalTileMode = mode;
        emit horizontalTileModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

BorderImage::TileMode BorderImage::verticalTileMode() const {
    Q_D(const BorderImage);

    return d->verticalTileMode;
}

void BorderImage::paintEvent(QPaintEvent *) {
    Q_D(BorderImage);
    
    if ((d->pix.isNull()) || (this->width() < 0) || (this->height() < 0)) {
        return;
    }
    
    QPainter painter(this);
    painter.setOpacity(this->opacity());
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, this->smooth());
    
    if (this->mirror()) {
        QTransform mirror;
        mirror.translate(this->width(), 0).scale(-1, 1.0);
    }
    
    int left = d->imageBorder ? d->imageBorder->left() : 0;
    int right = d->imageBorder ? d->imageBorder->right() : 0;
    int borderWidth = left + right;
    
    if ((borderWidth > 0) && (this->width() < borderWidth)) {
        int diff = borderWidth - this->width() - 1;
        left -= qRound(diff * left / borderWidth);
        right -= qRound(diff * right / borderWidth);
    }
    
    int top = d->imageBorder ? d->imageBorder->top() : 0;
    int bottom = d->imageBorder ? d->imageBorder->bottom() : 0;
    int borderHeight = top + bottom;
    
    if ((borderHeight > 0) && (this->height() < borderHeight)) {
        int diff = borderHeight - this->height() - 1;
        top -= qRound(diff * top / borderHeight);
        bottom -= qRound(diff * bottom / borderHeight);
    }
    
    QMargins margins(left, top, right, bottom);
    QTileRules rules((Qt::TileRule)this->horizontalTileMode(), (Qt::TileRule)this->verticalTileMode());
    qDrawBorderPixmap(&painter, QRect(0, 0, this->width(), this->height()), margins, d->pix, d->pix.rect(), margins, rules);
}

void BorderImage::setVerticalTileMode(TileMode mode) {
    if (mode != this->verticalTileMode()) {
        Q_D(BorderImage);
        d->verticalTileMode = mode;
        emit verticalTileModeChanged();

        if ((d->complete) && (!this->source().isEmpty())) {
            d->load();
        }
    }
}

BorderImagePrivate::BorderImagePrivate(BorderImage *parent) :
    ImageBasePrivate(parent),
    imageBorder(0)
{
}

ImageBorder* BorderImagePrivate::border() {
    Q_Q(BorderImage);

    if (!imageBorder) {
        imageBorder = new ImageBorder(q);
    }

    return imageBorder;
}

#include "moc_borderimage_p.cpp"

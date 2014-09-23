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

#include "image_p.h"
#include "image_p_p.h"
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QTransform>

Image::Image(QWidget *parent) :
    ImageBase(*new ImagePrivate(this), parent)
{
}

Image::Image(ImagePrivate &dd, QWidget *parent) :
    ImageBase(dd, parent)
{
}

Image::~Image() {}

Image::FillMode Image::fillMode() const {
    Q_D(const Image);

    return d->fillMode;
}

void Image::setFillMode(FillMode mode) {
    if (mode != this->fillMode()) {
        Q_D(Image);
        d->fillMode = mode;
        this->update();
        d->updatePaintedGeometry();
        emit fillModeChanged();
    }
}

QPixmap Image::pixmap() const {
    Q_D(const Image);
    
    return d->pix.pixmap();
}

void Image::setPixmap(const QPixmap &p) {
    Q_D(Image);
    
    if (this->source().isEmpty()) {
        Q_D(Image);
        d->pix.setPixmap(p);
        d->pixmapChange();
        d->status = d->pix.isNull() ? Null : Ready;
        this->update();
    }
}

int Image::paintedWidth() const {
    Q_D(const Image);
    
    return d->paintedWidth;
}

int Image::paintedHeight() const {
    Q_D(const Image);
    
    return d->paintedHeight;
}

void Image::resizeEvent(QResizeEvent *event) {
    if (event->size().isValid()) {
        Q_D(Image);
        d->updatePaintedGeometry();
    }
    
    ImageBase::resizeEvent(event);
}

void Image::paintEvent(QPaintEvent *) {
    Q_D(Image);
    
    if (d->pix.pixmap().isNull()) {
        return;
    }
    
    QPainter painter(this);
    
    int drawWidth = this->width();
    int drawHeight = this->height();
    QTransform transform;
    qreal widthScale = this->width() / qreal (d->pix.width());
    qreal heightScale = this->height() / qreal (d->pix.height());
    
    if ((this->width() != d->pix.width()) || (this->height() != d->pix.height())) {
        if (this->fillMode() >= Tile) {
            if (this->fillMode() == TileVertically) {
                transform.scale(widthScale, 1.0);
                drawWidth = d->pix.width();
            }
            else if (this->fillMode() == TileHorizontally) {
                transform.scale(1.0, heightScale);
                drawHeight = d->pix.height();
            }
        }
        else {
            if (this->fillMode() == PreserveAspectFit) {
                if (widthScale <= heightScale) {
                    heightScale = widthScale;
                    transform.translate(0, (this->height() - heightScale * d->pix.height()) / 2);
                }
                else if (heightScale < widthScale) {
                    widthScale = heightScale;
                    transform.translate((this->width() - widthScale * d->pix.width()) / 2, 0);
                }
            }
            else if (this->fillMode() == PreserveAspectCrop) {
                if (widthScale < heightScale) {
                    widthScale = heightScale;
                    transform.translate((this->width() - widthScale * d->pix.width()) / 2, 0);
                }
                else if (heightScale < widthScale) {
                    heightScale = widthScale;
                    transform.translate(0, (this->height() - heightScale * d->pix.height()) / 2);
                }
            }
            
            transform.scale(widthScale, heightScale);
            drawWidth = d->pix.width();
            drawHeight = d->pix.height();
        }
    }
    
    painter.setOpacity(this->opacity());
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, this->smooth());
    
    if (this->mirror()) {
        transform.translate(drawWidth, 0).scale(-1.0, 1.0);
    }
    
    painter.setTransform(transform);
    
    if (this->fillMode() >= Tile) {
        painter.drawTiledPixmap(QRect(0, 0, drawWidth, drawHeight), d->pix);
    }
    else {
        painter.drawPixmap(QRect(0, 0, drawWidth, drawHeight), d->pix, QRect(0, 0, drawWidth, drawHeight));
    }
}

ImagePrivate::ImagePrivate(Image *parent) :
    ImageBasePrivate(parent),
    fillMode(Image::Stretch),
    paintedWidth(0),
    paintedHeight(0)
{
}

void ImagePrivate::updatePaintedGeometry() {
    Q_Q(Image);
    
    if (fillMode == Image::PreserveAspectFit) {
        if ((!pix.width()) || (!pix.height())) {
            return;
        }
        
        qreal w = q->width() > 0 ? q->width() : pix.width();
        qreal widthScale = w / pix.width();
        qreal h = q->height() > 0 ? q->height() : pix.height();
        qreal heightScale = h / pix.height();
        
        if (widthScale <= heightScale) {
            paintedWidth = w;
            paintedHeight = widthScale * pix.height();
        }
        else if (heightScale < widthScale) {
            paintedWidth = heightScale * pix.width();
            paintedHeight = h;
        }
    }
    else if (fillMode == Image::PreserveAspectCrop) {
        if ((!pix.width()) || (!pix.height())) {
            return;
        }
        
        qreal widthScale = qreal(q->width()) / pix.width();
        qreal heightScale = qreal(q->height()) / pix.height();
        
        if (widthScale < heightScale) {
            widthScale = heightScale;
        }
        else if (heightScale < widthScale) {
            heightScale = widthScale;
        }
        
        paintedWidth = widthScale * pix.width();
        paintedHeight = heightScale * pix.height();
    }
    else {
        paintedWidth = q->width();
        paintedHeight = q->height();
    }
    
    emit q->paintedGeometryChanged();
}

#include "moc_image_p.cpp"

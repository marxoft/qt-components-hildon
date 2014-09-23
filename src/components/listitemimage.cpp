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

#include "listitemimage_p.h"
#include "listitemimagebase_p_p.h"
#include <QPainter>
#include <QTransform>

class ListItemImagePrivate : public ListItemImageBasePrivate
{

public:
    ListItemImagePrivate(ListItemImage *parent) :
        ListItemImageBasePrivate(parent),
        fillMode(ListItemImage::Stretch),
        paintedWidth(0),
        paintedHeight(0)
    {
    }
    
    void updatePaintedGeometry() {
        Q_Q(ListItemImage);
        
        if (fillMode == ListItemImage::PreserveAspectFit) {
            if ((!pix.width()) || (!pix.height())) {
                return;
            }
            
            int w = q->width() > 0 ? q->width() : pix.width();
            int widthScale = w / pix.width();
            int h = q->height() > 0 ? q->height() : pix.height();
            int heightScale = h / pix.height();
            
            if (widthScale <= heightScale) {
                paintedWidth = w;
                paintedHeight = widthScale * pix.height();
            }
            else if (heightScale < widthScale) {
                paintedWidth = heightScale * pix.width();
                paintedHeight = h;
            }
        }
        else if (fillMode == ListItemImage::PreserveAspectCrop) {
            if ((!pix.width()) || (!pix.height())) {
                return;
            }
            
            int widthScale = q->width() / pix.width();
            int heightScale = q->height() / pix.height();
            
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

    ListItemImage::FillMode fillMode;
    
    int paintedWidth;
    int paintedHeight;

    Q_DECLARE_PUBLIC(ListItemImage)
};

ListItemImage::ListItemImage(QObject *parent) :
    ListItemImageBase(*new ListItemImagePrivate(this), parent)
{
}

ListItemImage::ListItemImage(ListItemImagePrivate &dd, QObject *parent) :
    ListItemImageBase(dd, parent)
{
}

ListItemImage::FillMode ListItemImage::fillMode() const {
    Q_D(const ListItemImage);

    return d->fillMode;
}

void ListItemImage::setFillMode(FillMode mode) {
    if (mode != this->fillMode()) {
        Q_D(ListItemImage);
        d->fillMode = mode;
        d->updatePaintedGeometry();
        emit fillModeChanged();
    }
}

QPixmap ListItemImage::pixmap() const {
    Q_D(const ListItemImage);
    
    return d->pix.pixmap();
}

void ListItemImage::setPixmap(const QPixmap &p) {
    Q_D(ListItemImage);
    
    if (this->source().isEmpty()) {
        Q_D(ListItemImage);
        d->pix.setPixmap(p);
        d->pixmapChange();
        d->status = d->pix.isNull() ? Null : Ready;
    }
}

int ListItemImage::paintedWidth() const {
    Q_D(const ListItemImage);
    
    return d->paintedWidth;
}

int ListItemImage::paintedHeight() const {
    Q_D(const ListItemImage);
    
    return d->paintedHeight;
}

void ListItemImage::paint(QPainter *painter, const QRect &rect) {
    Q_D(ListItemImage);

    if (d->load()) {
        painter->save();
        
        int drawWidth = this->width();
        int drawHeight = this->height();
        qreal widthScale = this->width() / qreal (d->pix.width());
        qreal heightScale = this->height() / qreal (d->pix.height());
        QTransform transform;
        transform.translate(rect.left() + this->x(), rect.top() + this->y());
        
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
                    
                    painter->setClipRect(QRect(rect.left() + this->x(), rect.top() + this->y(), this->width(), this->height()),
                                         Qt::IntersectClip);
                }
                
                transform.scale(widthScale, heightScale);
                drawWidth = d->pix.width();
                drawHeight = d->pix.height();
            }
        }
        
        painter->setOpacity(painter->opacity() * this->opacity());
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, this->smooth());
        
        if (this->mirror()) {
            transform.translate(drawWidth, 0).scale(-1.0, 1.0);
        }
        
        painter->setTransform(transform);
        
        if (this->fillMode() >= Tile) {
            painter->drawTiledPixmap(QRect(0, 0, drawWidth, drawHeight), d->pix);
        }
        else {
            painter->drawPixmap(QRect(0, 0, drawWidth, drawHeight), d->pix, QRect(0, 0, drawWidth, drawHeight));
        }
        
        painter->restore();
    }

    foreach (ListItemContent *content, d->contentList) {
        if (content->isVisible()) {
            content->paint(painter,
                           QRect(rect.left() + this->x(),
                                 rect.top() + this->y(),
                                 this->width(),
                                 this->height()));
        }
    }
}

#include "moc_listitemimage_p.cpp"

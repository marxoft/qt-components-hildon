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

#include "listitemborderimage_p.h"
#include "listitemimagebase_p_p.h"
#include "imageborder_p.h"
#include <QPainter>
#include <QTransform>
#include <QMargins>
#include <QTileRules>

class ListItemBorderImagePrivate : public ListItemImageBasePrivate
{

public:
    ListItemBorderImagePrivate(ListItemBorderImage *parent) :
        ListItemImageBasePrivate(parent),
        imageBorder(0)
    {
    }

    ImageBorder* border() {
        Q_Q(ListItemBorderImage);

        if (!imageBorder) {
            imageBorder = new ImageBorder(q);
        }

        return imageBorder;
    }
    
    ImageBorder* imageBorder;
    
    ListItemBorderImage::TileMode horizontalTileMode;
    ListItemBorderImage::TileMode verticalTileMode;
    
    Q_DECLARE_PUBLIC(ListItemBorderImage)
};

ListItemBorderImage::ListItemBorderImage(QObject *parent) :
    ListItemImageBase(*new ListItemBorderImagePrivate(this), parent)
{
}

ListItemBorderImage::ListItemBorderImage(ListItemBorderImagePrivate &dd, QObject *parent) :
    ListItemImageBase(dd, parent)
{
}

ListItemBorderImage::~ListItemBorderImage() {}

ListItemBorderImage::TileMode ListItemBorderImage::horizontalTileMode() const {
    Q_D(const ListItemBorderImage);

    return d->horizontalTileMode;
}

void ListItemBorderImage::setHorizontalTileMode(TileMode mode) {
    if (mode != this->horizontalTileMode()) {
        Q_D(ListItemBorderImage);
        d->horizontalTileMode = mode;
        emit horizontalTileModeChanged();
    }
}

ListItemBorderImage::TileMode ListItemBorderImage::verticalTileMode() const {
    Q_D(const ListItemBorderImage);

    return d->verticalTileMode;
}

void ListItemBorderImage::setVerticalTileMode(TileMode mode) {
    if (mode != this->verticalTileMode()) {
        Q_D(ListItemBorderImage);
        d->verticalTileMode = mode;
        emit verticalTileModeChanged();
    }
}

void ListItemBorderImage::paint(QPainter *painter, const QRect &rect) {
    Q_D(ListItemBorderImage);
    
    if ((d->load()) && (this->width() > 0) && (this->height() > 0)) {
        painter->save();
        painter->setOpacity(painter->opacity() * this->opacity());
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, this->smooth());
        
        if (this->mirror()) {
            QTransform mirror;
            mirror.translate(this->width(), 0).scale(-1, 1.0);
            painter->setTransform(mirror);
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
        qDrawBorderPixmap(painter, QRect(rect.left() + this->x(), 
                                         rect.top() + this->y(), 
                                         this->width(), 
                                         this->height()), 
                                         margins, d->pix, d->pix.rect(), margins, rules);
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

#include "moc_listitemborderimage_p.cpp"

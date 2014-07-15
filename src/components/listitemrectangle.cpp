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

#include "listitemrectangle_p.h"
#include "listitemcontent_p_p.h"
#include <QPainter>

class ListItemRectanglePrivate : public ListItemContentPrivate
{

public:
    ListItemRectanglePrivate(ListItemRectangle *parent) :
        ListItemContentPrivate(parent),
        rectBorder(0),
        rectGradient(0),
        color(Qt::white),
        radius(0.0)
    {
    }

    Border* border() {
        if (!rectBorder) {
            Q_Q(ListItemRectangle);
            rectBorder = new Border(q);
        }

        return rectBorder;
    }

    Gradient* gradient() {
        return rectGradient;
    }

    void setGradient(Gradient *gradient) {
        if (gradient == rectGradient) {
            return;
        }

        Q_Q(ListItemRectangle);

        Gradient *oldGradient = rectGradient;
        rectGradient = gradient;

        if (oldGradient) {
            delete oldGradient;
        }
    }

    void resetGradient() {
        this->setGradient(0);
    }

    Border *rectBorder;

    Gradient *rectGradient;

    QColor color;

    qreal radius;

    Q_DECLARE_PUBLIC(ListItemRectangle)
};

ListItemRectangle::ListItemRectangle(QObject *parent) :
    ListItemContent(*new ListItemRectanglePrivate(this), parent)
{
}

ListItemRectangle::ListItemRectangle(ListItemRectanglePrivate &dd, QObject *parent) :
    ListItemContent(dd, parent)
{
}

QColor ListItemRectangle::color() const {
    Q_D(const ListItemRectangle);

    return d->color;
}

void ListItemRectangle::setColor(const QColor &color) {
    if (color != this->color()) {
        Q_D(ListItemRectangle);
        d->color = color;
        emit colorChanged();
    }
}

qreal ListItemRectangle::radius() const {
    Q_D(const ListItemRectangle);

    return d->radius;
}

void ListItemRectangle::setRadius(qreal radius) {
    if (radius != this->radius()) {
        Q_D(ListItemRectangle);
        d->radius = radius;
        emit radiusChanged();
    }
}

void ListItemRectangle::paint(QPainter *painter, const QRect &rect) {
    Q_D(const ListItemRectangle);

    painter->save();
    painter->setOpacity(this->opacity());
    painter->setRenderHint(QPainter::Antialiasing, this->smooth());

    if (d->rectBorder) {
        painter->setPen(d->rectBorder->pen());
    }
    else {
        painter->setPen(Qt::transparent);
    }

    if ((d->rectGradient) && (!d->rectGradient->stops().isEmpty())) {
        QLinearGradient gradient(0, 0, 0, d->rectGradient->stops().last().first * this->height());
        gradient.setStops(d->rectGradient->stops());
        painter->setBrush(gradient);
    }
    else {
        painter->setBrush(this->color());
    }

    painter->drawRoundedRect(rect.left() + this->x(),
                             rect.top() + this->y(),
                             this->width(),
                             this->height(),
                             this->radius(),
                             this->radius());
    painter->restore();

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

#include "moc_listitemrectangle_p.cpp"

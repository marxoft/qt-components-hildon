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

#include "zoomarea_p.h"
#include "item_p_p.h"
#include <math.h>
#include <QMouseEvent>

class ZoomAreaPrivate : public ItemPrivate
{

public:
    ZoomAreaPrivate(ZoomArea *parent) :
        ItemPrivate(parent),
        pressed(false),
        ddirection(false),
        readyToSwirl(false),
        swirling(false),
        clockwise(false)
    {
    }

    bool pressed;
    bool ddirection;
    bool readyToSwirl;
    bool swirling;
    bool clockwise;

    QPointF pressPos;
    QPointF swirlPos;

    Q_DECLARE_PUBLIC(ZoomArea)
};

ZoomArea::ZoomArea(QWidget *parent) :
    Item(*new ZoomAreaPrivate(this), parent)
{
}

ZoomArea::ZoomArea(ZoomAreaPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
}

ZoomArea::~ZoomArea() {}

void ZoomArea::mousePressEvent(QMouseEvent *event) {
    Q_D(ZoomArea);

    d->pressPos = event->posF();
    Item::mousePressEvent(event);
}

void ZoomArea::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(ZoomArea);

    d->readyToSwirl = false;
    d->swirling = false;
    d->ddirection = false;
    Item::mouseReleaseEvent(event);
}

void ZoomArea::mouseMoveEvent(QMouseEvent *event) {
    Q_D(ZoomArea);

    if(!d->readyToSwirl){
        d->swirlPos = event->posF();
        QPointF vec1 = d->swirlPos - d->pressPos;
        qreal tmpLength1 = sqrt(vec1.x() * vec1.x() + vec1.y() * vec1.y());

        if(tmpLength1 > 100){
            d->readyToSwirl = true;
        }
    }
    else{
        QPointF pos3 = event->posF();
        QPointF vec1 = d->swirlPos - d->pressPos;
        QPointF vec2 = pos3 -d->swirlPos;
        qreal tmpLength2 = sqrt(vec2.x() * vec2.x() + vec2.y() * vec2.y());
        qreal tmpLength1 = sqrt(vec1.x() * vec1.x() + vec1.y() * vec1.y());

        if(tmpLength2 > 15){
            qreal dot = vec2.x() * vec1.x() + vec2.y() * vec1.y();
            qreal cos = dot / tmpLength1 / tmpLength2;

            if((cos > 0.3) && (cos < 0.75)){
                if(!d->ddirection){
                    if(qMax(pos3.y(), qMax(d->pressPos.y(), d->swirlPos.y())) == d->swirlPos.y()||
                            qMin(pos3.y(), qMin(d->pressPos.y(), d->swirlPos.y())) == d->swirlPos.y()) {

                        QPointF tmp1 = pos3 - d->pressPos;
                        qreal tmpb = tmp1.x() * vec1.y() + tmp1.y() * vec1.x();

                        if(tmpb < 0){
                            d->clockwise = true;
                        }
                        else{
                            d->clockwise = false;
                        }

                        d->ddirection = true;
                        d->swirling = true;
                    }
                }

                if (d->clockwise) {
                    emit zoomIn();
                }
                else {
                    emit zoomOut();
                }

                d->swirlPos = pos3;
                event->accept();
                return;
            }
        }

        d->ddirection = false;
        d->readyToSwirl = false;
        d->pressPos = d->swirlPos;
    }

    Item::mouseMoveEvent(event);
}

void ZoomArea::mouseDoubleClickEvent(QMouseEvent *event) {
    emit zoomAt(event->x(), event->y());
    event->accept();
}

#include "moc_zoomarea_p.cpp"

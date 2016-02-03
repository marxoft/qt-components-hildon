/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchgraphicsview.h"
#include <QDeclarativeItem>

class QchGraphicsViewPrivate
{

public:
    QchGraphicsViewPrivate(QchGraphicsView *parent) :
        q_ptr(parent),
        root(0)
    {
    }
    
    QchGraphicsView *q_ptr;
    QDeclarativeItem *root;
    
    Q_DECLARE_PUBLIC(QchGraphicsView)
};

QchGraphicsView::QchGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    d_ptr(new QchGraphicsViewPrivate(this))
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
    
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(0);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    viewport()->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);
    
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setStickyFocus(true);
}

QchGraphicsView::~QchGraphicsView() {}

void QchGraphicsView::addItem(QDeclarativeItem *item) {
    Q_D(QchGraphicsView);
    
    if (!d->root) {
        d->root = item;
    }
    
    scene()->addItem(item);
}

void QchGraphicsView::resizeEvent(QResizeEvent *e) {
    Q_D(QchGraphicsView);
    
    if (d->root) {
        if (!qFuzzyCompare(width(), d->root->width())) {
            d->root->setWidth(width());
        }

        if (!qFuzzyCompare(height(), d->root->height())) {
            d->root->setHeight(height());
        }

        setSceneRect(QRectF(0, 0, d->root->width(), d->root->height()));
    }
    
    updateGeometry();
    QGraphicsView::resizeEvent(e);
}

#include "moc_qchgraphicsview.cpp"

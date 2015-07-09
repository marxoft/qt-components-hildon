/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHGRAPHICSVIEW_H
#define QCHGRAPHICSVIEW_H

#include <QGraphicsView>

class QDeclarativeItem;
class QchGraphicsViewPrivate;

class QchGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit QchGraphicsView(QWidget *parent = 0);
    ~QchGraphicsView();
    
    void addItem(QDeclarativeItem *item);
    
protected:
    void resizeEvent(QResizeEvent *e);
    
    QScopedPointer<QchGraphicsViewPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchGraphicsView)
    
private:
    Q_DISABLE_COPY(QchGraphicsView)
};

#endif // QCHGRAPHICSVIEW_H

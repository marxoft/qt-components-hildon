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

#ifndef TABLEVIEW_P_P_H
#define TABLEVIEW_P_P_H

#include "item_p_p.h"
#include "tableview_p.h"
#include <QAbstractKineticScroller>

class VariantTableModel;

class TableViewPrivate : public ItemPrivate
{

public:
    TableViewPrivate(TableView *parent) :
        ItemPrivate(parent),
        kineticScroller(parent->property("kineticScroller").value<QAbstractKineticScroller*>()),
        variantModel(0),
        delegateComponent(0),
        scrollTimer(0),
        atXBeginning(true),
        atXEnd(true),
        atYBeginning(true),
        atYEnd(true)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    QDeclarativeListProperty<QObject> actions();

    QVariant model() const;
    void setModel(const QVariant &model);

    QVariant rootIndex() const;
    void setRootIndex(const QVariant &index);

    QVariant currentIndex() const;
    void setCurrentIndex(const QVariant &index);

    QDeclarativeComponent* delegate() const;
    void setDelegate(QDeclarativeComponent *delegate);

    void _q_onHorizontalScrollPositionChanged();
    void _q_onVerticalScrollPositionChanged();
    void _q_onScrollingStopped();

    QVariant modelVariant;

    QAbstractKineticScroller *kineticScroller;

    VariantTableModel *variantModel;

    QDeclarativeComponent *delegateComponent;

    QTimer *scrollTimer;

    bool atXBeginning;
    bool atXEnd;
    bool atYBeginning;
    bool atYEnd;

    Q_DECLARE_PUBLIC(TableView)
};

#endif // TABLEVIEW_P_P_H

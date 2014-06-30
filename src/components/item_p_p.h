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

#ifndef ITEM_P_P_H
#define ITEM_P_P_H

#include "item_p.h"
#include "anchors_p_p.h"

class ItemPrivate
{

public:
    ItemPrivate(QWidget *parent) :
        q_ptr(parent),
        keys(0),
        anc(0),
        left(AnchorLine(parent, AnchorLine::Left)),
        right(AnchorLine(parent, AnchorLine::Right)),
        top(AnchorLine(parent, AnchorLine::Top)),
        bottom(AnchorLine(parent, AnchorLine::Bottom)),
        horizontalCenter(AnchorLine(parent, AnchorLine::HCenter)),
        verticalCenter(AnchorLine(parent, AnchorLine::VCenter)),
        complete(false),
        qmlVis(true)
    {
    }

    virtual ~ItemPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    Keys* attachedKeys();

    Anchors* anchors();

    virtual QDeclarativeListProperty<QObject> data();

    virtual QDeclarativeListProperty<QWidget> children();

    virtual QDeclarativeListProperty<QObject> actions();

    bool qmlVisible() const;
    void setQmlVisible(bool visible);

    virtual void componentComplete();

    QWidget *q_ptr;

    Keys* keys;

    Anchors *anc;

    AnchorLine left;
    AnchorLine right;
    AnchorLine top;
    AnchorLine bottom;
    AnchorLine horizontalCenter;
    AnchorLine verticalCenter;

    bool complete;

    bool qmlVis;

    QList<QObject*> dataList;

    QList<QWidget*> childrenList;

    QList<QObject*> actionList;

    Q_DECLARE_PUBLIC(Item)
};

#endif // ITEM_P_P_H

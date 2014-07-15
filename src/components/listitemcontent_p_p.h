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

#ifndef LISTITEMCONTENT_P_P_H
#define LISTITEMCONTENT_P_P_H

#include "listitemcontent_p.h"
#include "anchors_p_p.h"

class ListItemContentPrivate
{

public:
    ListItemContentPrivate(ListItemContent *parent) :
        q_ptr(parent),
        anc(0),
        x(0),
        y(0),
        width(0),
        height(0),
        opacity(1.0),
        visible(true),
        smooth(false),
        left(AnchorLine(parent, AnchorLine::Left)),
        right(AnchorLine(parent, AnchorLine::Right)),
        top(AnchorLine(parent, AnchorLine::Top)),
        bottom(AnchorLine(parent, AnchorLine::Bottom)),
        horizontalCenter(AnchorLine(parent, AnchorLine::HCenter)),
        verticalCenter(AnchorLine(parent, AnchorLine::VCenter)),
        complete(false)
    {
    }

    virtual ~ListItemContentPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (ListItemContent *item = qobject_cast<ListItemContent*>(list->object)) {
            item->d_func()->dataList.append(obj);

            if (ListItemContent *content = qobject_cast<ListItemContent*>(obj)) {
                item->d_func()->contentList.append(content);
            }
        }
    }

    static void content_append(QDeclarativeListProperty<ListItemContent> *list, ListItemContent *contentItem) {
        if (!contentItem) {
            return;
        }

        if (ListItemContent *item = qobject_cast<ListItemContent*>(list->object)) {
            item->d_func()->dataList.append(contentItem);
            item->d_func()->contentList.append(contentItem);
        }
    }

    virtual QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, ListItemContentPrivate::data_append);
    }

    virtual QDeclarativeListProperty<ListItemContent> content() {
        return QDeclarativeListProperty<ListItemContent>(q_func(), 0, ListItemContentPrivate::content_append);
    }

    Anchors* anchors() {
        if (!anc) {
            Q_Q(ListItemContent);
            anc = new Anchors(q, q);
        }

        return anc;
    }

    virtual void componentComplete() {
        complete = true;

        if (anc) {
            anc->d_func()->onItemCompleted();
        }
    }

    ListItemContent *q_ptr;

    Anchors *anc;

    int x;
    int y;
    int width;
    int height;

    qreal opacity;

    bool visible;

    bool smooth;

    AnchorLine left;
    AnchorLine right;
    AnchorLine top;
    AnchorLine bottom;
    AnchorLine horizontalCenter;
    AnchorLine verticalCenter;

    bool complete;

    QList<QObject*> dataList;

    QList<ListItemContent*> contentList;

    Q_DECLARE_PUBLIC(ListItemContent)
};

#endif // LISTITEMCONTENT_P_P_H

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

#ifndef LISTVIEW_P_P_H
#define LISTVIEW_P_P_H

#include "item_p_p.h"
#include "listview_p.h"

class VariantListModel;

class ListViewPrivate : public ItemPrivate
{

public:
    ListViewPrivate(ListView *parent) :
        ItemPrivate(parent),
        variantModel(0)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QObject> actions();

    QVariant model() const;
    void setModel(const QVariant &model);

    QVariant rootIndex() const;
    void setRootIndex(const QVariant &index);

    QVariant currentIndex() const;
    void setCurrentIndex(const QVariant &index);

    ItemDelegate* delegate() const;
    void setDelegate(ItemDelegate *delegate);
    void resetDelegate();

    QVariant modelVariant;

    VariantListModel *variantModel;

    ItemDelegate *del;

    Q_DECLARE_PUBLIC(ListView)
};

#endif // LISTVIEW_P_P_H

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

#ifndef LOADER_P_P_H
#define LOADER_P_P_H

#include "loader_p.h"
#include <QUrl>

class LoaderPrivate
{

public:
    LoaderPrivate(Loader *parent) :
        q_ptr(parent),
        component(0),
        item(0),
        ownComponent(false),
        complete(false)
    {
    }

    virtual ~LoaderPrivate() {}

    void clear();

    void load();

    QWidget* parentWidget() const;

    void _q_sourceLoaded();

    Loader *q_ptr;

    QUrl source;

    QDeclarativeComponent *component;

    QWidget *item;

    bool ownComponent;

    bool complete;

    Q_DECLARE_PUBLIC(Loader)
};

#endif // LOADER_P_P_H

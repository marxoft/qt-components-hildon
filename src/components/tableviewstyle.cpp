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

#include "tableviewstyle_p.h"
#include "tableviewstyle_p_p.h"

TableViewStylePrivate::TableViewStylePrivate(TableViewStyle *parent) :
    ListViewStylePrivate(parent)
{
}

QString TableViewStylePrivate::mainBody() const {
    QString body = ListViewStylePrivate::mainBody();
    
    if (gridlineColor.isValid()) {
        body += "gridline-color: " + gridlineColor.name() + ";";
    }
    
    return body;
}

TableViewStyle::TableViewStyle(QObject *parent) :
    ListViewStyle(*new TableViewStylePrivate(this), parent)
{
}

TableViewStyle::TableViewStyle(TableViewStylePrivate &dd, QObject *parent) :
    ListViewStyle(dd, parent)
{
}

TableViewStyle::~TableViewStyle() {}

QColor TableViewStyle::gridlineColor() const {
    Q_D(const TableViewStyle);
    
    return d->gridlineColor;
}

void TableViewStyle::setGridlineColor(const QColor &color) {
    if (color != this->gridlineColor()) {
        Q_D(TableViewStyle);
        d->gridlineColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

#include "moc_tableviewstyle_p.cpp"


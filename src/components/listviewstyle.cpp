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

#include "listviewstyle_p.h"
#include "listviewstyle_p_p.h"

ListViewStylePrivate::ListViewStylePrivate(ListViewStyle *parent) :
    FlickableStylePrivate(parent),
    item(0),
    showDecorationSelected(true)
{
}

QString ListViewStylePrivate::itemBody() const {
    return item ? item->toStyleSheet() : QString();
}

QString ListViewStylePrivate::mainBody() const {
    QString body = FlickableStylePrivate::mainBody();
    
    if (alternateBackgroundColor.isValid()) {
        body += "alternate-background-color: " + alternateBackgroundColor.name() + ";";
    }
    
    if (selectionBackgroundColor.isValid()) {
        body += "selection-background-color: " + selectionBackgroundColor.name() + ";";
    }
    
    if (selectionColor.isValid()) {
        body += "selection-color: " + selectionColor.name() + ";";
    }
    
    body += "show-decoration-selected: " + QString::number(showDecorationSelected ? 1 : 0) + ";";
    
    return body;
}

ListViewStyle::ListViewStyle(QObject *parent) :
    FlickableStyle(*new ListViewStylePrivate(this), parent)
{
}

ListViewStyle::ListViewStyle(ListViewStylePrivate &dd, QObject *parent) :
    FlickableStyle(dd, parent)
{
}

ListViewStyle::~ListViewStyle() {}

Style* ListViewStyle::item() const {
    Q_D(const ListViewStyle);
    
    return d->item;
}

void ListViewStyle::setItem(Style *style) {
    if (style != this->item()) {
        Q_D(ListViewStyle);
        
        if (d->item) {
            this->disconnect(d->item, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->item = style;
        d->dirty = true;
        
        if (d->item) {
            this->connect(d->item, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void ListViewStyle::resetItem() {
    this->setItem(0);
}

QColor ListViewStyle::alternateBackgroundColor() const {
    Q_D(const ListViewStyle);
    
    return d->alternateBackgroundColor;
}

void ListViewStyle::setAlternateBackgroundColor(const QColor &color) {
    if (color != this->alternateBackgroundColor()) {
        Q_D(ListViewStyle);
        d->alternateBackgroundColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor ListViewStyle::selectionBackgroundColor() const {
    Q_D(const ListViewStyle);
    
    return d->selectionBackgroundColor;
}

void ListViewStyle::setSelectionBackgroundColor(const QColor &color) {
    if (color != this->selectionBackgroundColor()) {
        Q_D(ListViewStyle);
        d->selectionBackgroundColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QColor ListViewStyle::selectionColor() const {
    Q_D(const ListViewStyle);
    
    return d->selectionColor;
}

void ListViewStyle::setSelectionColor(const QColor &color) {
    if (color != this->selectionColor()) {
        Q_D(ListViewStyle);
        d->selectionColor = color;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

bool ListViewStyle::showDecorationSelected() const {
    Q_D(const ListViewStyle);
    
    return d->showDecorationSelected;
}

void ListViewStyle::setShowDecorationSelected(bool show) {
    if (show != this->showDecorationSelected()) {
        Q_D(ListViewStyle);
        d->showDecorationSelected = show;
        d->dirty = true;
        
        if (d->complete) {
            emit changed();
        }
    }
}

QString ListViewStyle::toStyleSheet() const {
    Q_D(const ListViewStyle);
    
    if (!d->complete) {
        return QString();
    }
    
    return d->item ? "QListView { " + d->mainBody() + " } QListView::item { " + d->itemBody() + " }" 
                        : d->mainBody();
}

#include "moc_listviewstyle_p.cpp"


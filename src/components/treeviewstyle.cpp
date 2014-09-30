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

#include "treeviewstyle_p.h"
#include "treeviewstyle_p_p.h"

TreeViewStylePrivate::TreeViewStylePrivate(TreeViewStyle *parent) :
    ListViewStylePrivate(parent),
    branch(0)
{
}

QString TreeViewStylePrivate::branchBody() const {
    return branch ? branch->toStyleSheet() : QString();
}

TreeViewStyle::TreeViewStyle(QObject *parent) :
    ListViewStyle(*new TreeViewStylePrivate(this), parent)
{
}

TreeViewStyle::TreeViewStyle(TreeViewStylePrivate &dd, QObject *parent) :
    ListViewStyle(dd, parent)
{
}

TreeViewStyle::~TreeViewStyle() {}

Style* TreeViewStyle::branch() const {
    Q_D(const TreeViewStyle);
    
    return d->branch;
}

void TreeViewStyle::setBranch(Style *style) {
    if (style != this->branch()) {
        Q_D(TreeViewStyle);
        
        if (d->branch) {
            this->disconnect(d->branch, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        d->branch = style;
        d->dirty = true;
        
        if (d->branch) {
            this->connect(d->branch, SIGNAL(changed()), this, SIGNAL(changed()));
        }
        
        if (d->complete) {
            emit changed();
        }
    }
}

void TreeViewStyle::resetBranch() {
    this->setBranch(0);
}

#include "moc_treeviewstyle_p.cpp"


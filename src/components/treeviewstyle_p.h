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

#ifndef TREEVIEWSTYLE_P_H
#define TREEVIEWSTYLE_P_H

#include "listviewstyle_p.h"

class TreeViewStylePrivate;

class TreeViewStyle : public ListViewStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* branch READ branch WRITE setBranch RESET resetBranch NOTIFY changed)
    
public:
    explicit TreeViewStyle(QObject *parent = 0);
    ~TreeViewStyle();
    
    Style* branch() const;
    void setBranch(Style *style);
    void resetBranch();
    
protected:
    TreeViewStyle(TreeViewStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(TreeViewStyle)
    
private:
    Q_DISABLE_COPY(TreeViewStyle)
};

QML_DECLARE_TYPE(TreeViewStyle)

#endif // TREEVIEWSTYLE_P_H


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

#ifndef LISTVIEWSTYLE_P_H
#define LISTVIEWSTYLE_P_H

#include "flickablestyle_p.h"

class ListViewStylePrivate;

class ListViewStyle : public FlickableStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* item READ item WRITE setItem RESET resetItem NOTIFY changed)
    Q_PROPERTY(QColor alternateBackgroundColor READ alternateBackgroundColor WRITE setAlternateBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor selectionBackgroundColor READ selectionBackgroundColor WRITE setSelectionBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor NOTIFY changed)
    Q_PROPERTY(bool showDecorationSelected READ showDecorationSelected WRITE setShowDecorationSelected NOTIFY changed)
    
public:
    explicit ListViewStyle(QObject *parent = 0);
    ~ListViewStyle();
    
    Style* item() const;
    void setItem(Style *style);
    void resetItem();
    
    QColor alternateBackgroundColor() const;
    void setAlternateBackgroundColor(const QColor &color);
    
    QColor selectionBackgroundColor() const;
    void setSelectionBackgroundColor(const QColor &color);
    
    QColor selectionColor() const;
    void setSelectionColor(const QColor &color);
    
    bool showDecorationSelected() const;
    void setShowDecorationSelected(bool show);
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    ListViewStyle(ListViewStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(ListViewStyle)
    
private:
    Q_DISABLE_COPY(ListViewStyle)
};

QML_DECLARE_TYPE(ListViewStyle)

#endif // LISTVIEWSTYLE_P_H


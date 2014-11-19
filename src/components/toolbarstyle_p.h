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

#ifndef TOOLBARSTYLE_P_H
#define TOOLBARSTYLE_P_H

#include "boxstyle_p.h"

class ToolBarStylePrivate;

class ToolBarStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* handle READ handle WRITE setHandle RESET resetHandle NOTIFY changed)
    Q_PROPERTY(Style* separator READ separator WRITE setSeparator RESET resetSeparator NOTIFY changed)
    
public:
    explicit ToolBarStyle(QObject *parent = 0);
    ~ToolBarStyle();
    
    Style* handle() const;
    void setHandle(Style *style);
    void resetHandle();
    
    Style* separator() const;
    void setSeparator(Style *style);
    void resetSeparator();
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    ToolBarStyle(ToolBarStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(ToolBarStyle)
    
private:
    Q_DISABLE_COPY(ToolBarStyle)
};

QML_DECLARE_TYPE(ToolBarStyle)

#endif // TOOLBARSTYLE_P_H


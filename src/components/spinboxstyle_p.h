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

#ifndef SPINBOXSTYLE_P_H
#define SPINBOXSTYLE_P_H

#include "boxstyle_p.h"

class SpinBoxStylePrivate;

class SpinBoxStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* downArrow READ downArrow WRITE setDownArrow RESET resetDownArrow NOTIFY changed)
    Q_PROPERTY(Style* downButton READ downButton WRITE setDownButton RESET resetDownButton NOTIFY changed)
    Q_PROPERTY(Style* upArrow READ upArrow WRITE setUpArrow RESET resetUpArrow NOTIFY changed)
    Q_PROPERTY(Style* upButton READ upButton WRITE setUpButton RESET resetUpButton NOTIFY changed)
    
public:
    explicit SpinBoxStyle(QObject *parent = 0);
    ~SpinBoxStyle();
    
    Style* downArrow() const;
    void setDownArrow(Style *style);
    void resetDownArrow();
    
    Style* downButton() const;
    void setDownButton(Style *style);
    void resetDownButton();
    
    Style* upArrow() const;
    void setUpArrow(Style *style);
    void resetUpArrow();
    
    Style* upButton() const;
    void setUpButton(Style *style);
    void resetUpButton();
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    SpinBoxStyle(SpinBoxStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(SpinBoxStyle)
    
private:
    Q_DISABLE_COPY(SpinBoxStyle)
};

QML_DECLARE_TYPE(SpinBoxStyle)

#endif // SPINBOXSTYLE_P_H


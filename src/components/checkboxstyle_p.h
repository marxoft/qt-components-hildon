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

#ifndef CHECKBOXSTYLE_P_H
#define CHECKBOXSTYLE_P_H

#include "buttonstyle_p.h"

class CheckBoxStylePrivate;

class CheckBoxStyle : public ButtonStyle
{
    Q_OBJECT
    
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY changed)
    
public:
    explicit CheckBoxStyle(QObject *parent = 0);
    ~CheckBoxStyle();
    
    int spacing() const;
    void setSpacing(int s);
    
    virtual QString toStyleSheet() const;
    
protected:
    CheckBoxStyle(CheckBoxStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(CheckBoxStyle)
    
private:
    Q_DISABLE_COPY(CheckBoxStyle)
    
};

QML_DECLARE_TYPE(CheckBoxStyle)

#endif // CHECKBOXSTYLE_P_H

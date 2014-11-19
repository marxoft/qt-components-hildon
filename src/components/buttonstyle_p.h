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

#ifndef BUTTONSTYLE_P_H
#define BUTTONSTYLE_P_H

#include "boxstyle_p.h"

class ButtonStylePrivate;

class ButtonStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Style* indicator READ indicator WRITE setIndicator RESET resetIndicator NOTIFY changed)
    Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment NOTIFY changed)
    
public:
    explicit ButtonStyle(QObject *parent = 0);
    ~ButtonStyle();
    
    Style* indicator() const;
    void setIndicator(Style *style);
    void resetIndicator();
    
    Qt::Alignment textAlignment() const;
    void setTextAlignment(Qt::Alignment align);
    
    virtual QString toStyleSheet() const;
    
signals:
    void changed();
    
protected:
    ButtonStyle(ButtonStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(ButtonStyle)
    
private:
    Q_DISABLE_COPY(ButtonStyle)
};

QML_DECLARE_TYPE(ButtonStyle)

#endif // BUTTONSTYLE_P_H


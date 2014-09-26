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

#ifndef FLICKABLESTYLE_P_H
#define FLICKABLESTYLE_P_H

#include "boxstyle_p.h"

class FlickableStylePrivate;

class FlickableStyle : public BoxStyle
{
    Q_OBJECT
    
    Q_PROPERTY(Attachment backgroundAttachment READ backgroundAttachment WRITE setBackgroundAttachment NOTIFY changed)
    
    Q_ENUMS(Attachment)
    
public:
    enum Attachment {
        Scroll = 0,
        Fixed
    };
    
    explicit FlickableStyle(QObject *parent = 0);
    ~FlickableStyle();
    
    Attachment backgroundAttachment() const;
    void setBackgroundAttachment(Attachment a);
    
protected:
    FlickableStyle(FlickableStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(FlickableStyle)

private:
    Q_DISABLE_COPY(FlickableStyle)
};

QML_DECLARE_TYPE(FlickableStyle)

#endif // FLICKABLESTYLE_P_H


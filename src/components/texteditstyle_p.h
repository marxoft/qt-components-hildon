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

#ifndef TEXTEDITSTYLE_P_H
#define TEXTEDITSTYLE_P_H

#include "flickablestyle_p.h"

class TextEditStylePrivate;

class TextEditStyle : public FlickableStyle
{
    Q_OBJECT
    
    Q_PROPERTY(QColor selectionBackgroundColor READ selectionBackgroundColor WRITE setSelectionBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor NOTIFY changed)
    
public:
    explicit TextEditStyle(QObject *parent = 0);
    ~TextEditStyle();
    
    QColor selectionBackgroundColor() const;
    void setSelectionBackgroundColor(const QColor &color);
    
    QColor selectionColor() const;
    void setSelectionColor(const QColor &color);
    
signals:
    void changed();
    
protected:
    TextEditStyle(TextEditStylePrivate &dd, QObject *parent = 0);
    
    Q_DECLARE_PRIVATE(TextEditStyle)

private:
    Q_DISABLE_COPY(TextEditStyle)
};

QML_DECLARE_TYPE(TextEditStyle)

#endif // TEXTEDITSTYLE_P_H


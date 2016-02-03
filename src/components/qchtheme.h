/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHTHEME_H
#define QCHTHEME_H

#include <QObject>

class QchTheme : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString gtkTheme READ gtkTheme NOTIFY changed)
    Q_PROPERTY(QString icon READ icon NOTIFY changed)
    Q_PROPERTY(QString iconTheme READ iconTheme NOTIFY changed)
    Q_PROPERTY(QString name READ name NOTIFY changed)

public:
    explicit QchTheme(QObject *parent = 0);
        
    QString gtkTheme() const;
    
    QString icon() const;
    
    QString iconTheme() const;
            
    QString name() const;

Q_SIGNALS:
    void changed();
};

#endif // QCHTHEME_H

/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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
 
#ifndef QCHMEDIATYPE_H
#define QCHMEDIATYPE_H

#include <QObject>
#include <qdeclarative.h>

class QchMediaType : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(Type)
   
public:
    enum Type {
        Audio = 0,
        Radio,
        Video
    };
    
private:
    QchMediaType() : QObject() {}
};

QML_DECLARE_TYPE(QchMediaType)

#endif // QCHMEDIATYPE_H

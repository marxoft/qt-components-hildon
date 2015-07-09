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
 
#ifndef QCHMEDIASTATUS_H
#define QCHMEDIASTATUS_H

#include <QObject>
#include <qdeclarative.h>

class QchMediaStatus : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(Status)
   
public:
    enum Status {
        Stopped = 0,
        Loading,
        Playing,
        Paused,
        EndOfMedia,
        Error
    };
    
private:
    QchMediaStatus() : QObject() {}
};

QML_DECLARE_TYPE(QchMediaStatus)

#endif // QCHMEDIASTATUS_H

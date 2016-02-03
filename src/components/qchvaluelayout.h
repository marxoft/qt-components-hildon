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

#ifndef QCHVALUELAYOUT_H
#define QCHVALUELAYOUT_H

#include <QObject>
#include <qdeclarative.h>

class QchValueLayout : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(Layout)

public:
    enum Layout {
        ValueBesideText = 0,
        ValueUnderText,
        ValueUnderTextCentered
    };
    
private:
    QchValueLayout() : QObject() {}
    
    Q_DISABLE_COPY(QchValueLayout)
};

QML_DECLARE_TYPE(QchValueLayout)

#endif // QCHVALUELAYOUT_H

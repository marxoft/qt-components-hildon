/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHINPUTMODE_H
#define QCHINPUTMODE_H

#include <QObject>
#include <qdeclarative.h>

class QchInputMode : public QObject
{
    Q_OBJECT
    
    Q_ENUMS(Mode)

public:
    enum Mode {
        TextInput = 0,
        MultiLineTextInput,
        IntInput,
        DoubleInput,
        ItemSelectInput
    };

private:
    QchInputMode() : QObject() {}
};

QML_DECLARE_TYPE(QchInputMode)

#endif // QCHINPUTMODE_H

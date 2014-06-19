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

#ifndef SEPARATOR_P_H
#define SEPARATOR_P_H

#include <QObject>
#include <qdeclarative.h>

class Separator : public QObject
{
    Q_OBJECT

public:
    explicit Separator(QObject *parent = 0);
    ~Separator();

private:
    Q_DISABLE_COPY(Separator)
};

QML_DECLARE_TYPE(Separator)

#endif // SEPARATOR_P_H

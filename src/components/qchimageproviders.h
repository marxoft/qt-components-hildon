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

#ifndef QCHIMAGEPROVIDERS_H
#define QCHIMAGEPROVIDERS_H

#include <QDeclarativeImageProvider>

class QchIconImageProvider : public QDeclarativeImageProvider
{

public:
    explicit QchIconImageProvider();

    virtual QPixmap requestPixmap(const QString &id, QSize *, const QSize &requestedSize);
};

class QchThemeImageProvider : public QDeclarativeImageProvider
{

public:
    explicit QchThemeImageProvider();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // QCHIMAGEPROVIDERS_H

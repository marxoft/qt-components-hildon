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

#include "qchimageproviders.h"
#include <QIcon>

QchIconImageProvider::QchIconImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
{
}

QPixmap QchIconImageProvider::requestPixmap(const QString &id, QSize *, const QSize &requestedSize) {
    return QIcon::fromTheme(id).pixmap(requestedSize);
}

QchThemeImageProvider::QchThemeImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
{
}

QPixmap QchThemeImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QPixmap pixmap(QString("/etc/hildon/theme/images/%1.png").arg(id));

    if (!pixmap.isNull()) {
        const int width = pixmap.width();
        const int height = pixmap.height();

        if (size) {
            *size = QSize(width, height);
        }

        if ((requestedSize.width() < width) || (requestedSize.height() < height)) {
            pixmap = pixmap.scaled(width, height);
        }
    }

    return pixmap;
}

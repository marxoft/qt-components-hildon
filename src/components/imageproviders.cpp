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

#include "imageproviders_p.h"
#include <QFileInfo>

ThemeImageProvider::ThemeImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
}

QString ThemeImageProvider::getFileName(QString id) {
    QString fileName;

    if (id.startsWith("icon/")) {
        fileName = "/usr/share/icons/hicolor/48x48/hildon/" + id;
    }
    else {
        fileName = "/etc/hildon/theme/images/" + id;
    }

    QFileInfo info(fileName + ".png");

    if (!info.exists()) {
        info.setFile(fileName + ".svg");

        if (!info.exists()) {
            info.setFile(fileName + ".jpg");
        }
    }

    return info.absoluteFilePath();
}

QImage ThemeImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    QString fileName = this->getFileName(id);
    QImage image(fileName);

    if (!image.isNull()) {
        int width = image.width();
        int height = image.height();

        if (size) {
            *size = QSize(width, height);
        }

        if ((requestedSize.width() < width) || (requestedSize.height() < height)) {
            image.scaled(width, height);
        }
    }

    return image;
}

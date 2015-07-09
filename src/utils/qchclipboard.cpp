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

#include "qchclipboard.h"
#include <QApplication>
#include <QClipboard>
#include <QPixmap>

QchClipboard::QchClipboard(QObject *parent) :
    QObject(parent)
{
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SIGNAL(dataChanged()));
}

QVariant QchClipboard::pixmap() const {
    return QVariant::fromValue(QApplication::clipboard()->pixmap());
}

void QchClipboard::setPixmap(const QVariant &pixmap) {
    QApplication::clipboard()->setPixmap(pixmap.value<QPixmap>());
}

QString QchClipboard::text() const {
    return QApplication::clipboard()->text();
}

void QchClipboard::setText(const QString &text) {
    QApplication::clipboard()->setText(text);
}

bool QchClipboard::hasPixmap() const {
    return pixmap().isValid();
}

bool QchClipboard::hasText() const {
    return !text().isEmpty();
}

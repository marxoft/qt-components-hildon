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

#include "clipboard_p.h"
#include <QApplication>
#include <QClipboard>
#include <QPixmap>

Clipboard::Clipboard(QObject *parent) :
    QObject(parent)
{
    this->connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SIGNAL(dataChanged()));
}

Clipboard::~Clipboard() {}

QVariant Clipboard::pixmap() const {
    return QVariant::fromValue(QApplication::clipboard()->pixmap());
}

void Clipboard::setPixmap(const QVariant &pixmap) {
    QApplication::clipboard()->setPixmap(pixmap.value<QPixmap>());
}

QString Clipboard::text() const {
    return QApplication::clipboard()->text();
}

void Clipboard::setText(const QString &text) {
    QApplication::clipboard()->setText(text);
}

bool Clipboard::hasPixmap() const {
    return this->pixmap().isValid();
}

bool Clipboard::hasText() const {
    return !this->text().isEmpty();
}

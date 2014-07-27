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

#ifndef CLIPBOARD_P_H
#define CLIPBOARD_P_H

#include <QObject>
#include <qdeclarative.h>

class Clipboard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant pixmap READ pixmap WRITE setPixmap NOTIFY dataChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY dataChanged)
    Q_PROPERTY(bool hasPixmap READ hasPixmap NOTIFY dataChanged)
    Q_PROPERTY(bool hasText READ hasText NOTIFY dataChanged)

public:
    explicit Clipboard(QObject *parent = 0);
    ~Clipboard();

    QVariant pixmap() const;
    void setPixmap(const QVariant &pixmap);

    QString text() const;
    void setText(const QString &text);

    bool hasPixmap() const;
    bool hasText() const;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(Clipboard)
};

QML_DECLARE_TYPE(Clipboard)

#endif // CLIPBOARD_P_H

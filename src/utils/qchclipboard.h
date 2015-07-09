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

#ifndef QCHCLIPBOARD_H
#define QCHCLIPBOARD_H

#include <QObject>
#include <qdeclarative.h>

class QchClipboard : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant pixmap READ pixmap WRITE setPixmap NOTIFY dataChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY dataChanged)
    Q_PROPERTY(bool hasPixmap READ hasPixmap NOTIFY dataChanged)
    Q_PROPERTY(bool hasText READ hasText NOTIFY dataChanged)

public:
    explicit QchClipboard(QObject *parent = 0);

    QVariant pixmap() const;
    void setPixmap(const QVariant &pixmap);

    QString text() const;
    void setText(const QString &text);

    bool hasPixmap() const;
    bool hasText() const;

Q_SIGNALS:
    void dataChanged();

private:
    Q_DISABLE_COPY(QchClipboard)
};

QML_DECLARE_TYPE(QchClipboard)

#endif // QCHCLIPBOARD_H

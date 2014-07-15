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

#ifndef LISTITEMTEXT_P_H
#define LISTITEMTEXT_P_H

#include "listitemcontent_p.h"

class ListItemTextPrivate;

class ListItemText : public ListItemContent
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit ListItemText(QObject *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    QFont font() const;
    void setFont(const QFont &font);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    QString text() const;
    void setText(const QString &text);

    void paint(QPainter *painter, const QRect &rect);

signals:
    void colorChanged();
    void fontChanged();
    void alignmentChanged();
    void textChanged();

protected:
    ListItemText(ListItemTextPrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(ListItemText)

private:
    Q_DISABLE_COPY(ListItemText)
};

QML_DECLARE_TYPE(ListItemText)

#endif // LISTITEMTEXT_P_H

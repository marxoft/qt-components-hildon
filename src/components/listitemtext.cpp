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

#include "listitemtext_p.h"
#include "listitemcontent_p_p.h"
#include "platformstyle_p.h"
#include <QFont>
#include <QPainter>

class ListItemTextPrivate : ListItemContentPrivate
{

public:
    ListItemTextPrivate(ListItemText *parent) :
        ListItemContentPrivate(parent),
        color(PlatformStyle::defaultTextColor()),
        alignment(Qt::AlignLeft | Qt::AlignTop)
    {
    }

    QColor color;

    QFont font;

    Qt::Alignment alignment;

    QString text;

    Q_DECLARE_PUBLIC(ListItemText)
};

ListItemText::ListItemText(QObject *parent) :
    ListItemContent(*new ListItemTextPrivate(this), parent)
{
}

ListItemText::ListItemText(ListItemTextPrivate &dd, QObject *parent) :
    ListItemContent(dd, parent)
{
}

QColor ListItemText::color() const {
    Q_D(const ListItemText);

    return d->color;
}

void ListItemText::setColor(const QColor &color) {
    if (color != this->color()) {
        Q_D(ListItemText);
        d->color = color;
        emit colorChanged();
    }
}

QFont ListItemText::font() const {
    Q_D(const ListItemText);

    return d->font;
}

void ListItemText::setFont(const QFont &font) {
    if (font != this->font()) {
        Q_D(ListItemText);
        d->font = font;
        emit fontChanged();
    }
}

Qt::Alignment ListItemText::alignment() const {
    Q_D(const ListItemText);

    return d->alignment;
}

void ListItemText::setAlignment(Qt::Alignment align) {
    if (align != this->alignment()) {
        Q_D(ListItemText);
        d->alignment = align;
        emit alignmentChanged();
    }
}

QString ListItemText::text() const {
    Q_D(const ListItemText);

    return d->text;
}

void ListItemText::setText(const QString &text) {
    if (text != this->text()) {
        Q_D(ListItemText);
        d->text = text;
        emit textChanged();
    }
}

void ListItemText::paint(QPainter *painter, const QRect &rect) {
    Q_D(const ListItemText);

    painter->save();
    painter->setOpacity(this->opacity());
    painter->setRenderHint(QPainter::Antialiasing, this->smooth());
    painter->setPen(this->color());
    painter->setFont(this->font());
    painter->drawText(rect.left() + this->x(),
                      rect.top() + this->y(),
                      this->width(),
                      this->height(),
                      this->alignment(),
                      this->text());
    painter->restore();

    foreach (ListItemContent *content, d->contentList) {
        if (content->isVisible()) {
            content->paint(painter,
                           QRect(rect.left() + this->x(),
                                 rect.top() + this->y(),
                                 this->width(),
                                 this->height()));
        }
    }
}

#include "moc_listitemtext_p.cpp"

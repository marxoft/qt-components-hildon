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

#include "listitemcontent_p.h"
#include "listitemcontent_p_p.h"
#include <QEvent>
#include <QRect>

ListItemContent::ListItemContent(QObject *parent) :
    QObject(parent),
    d_ptr(new ListItemContentPrivate(this))
{
}

ListItemContent::ListItemContent(ListItemContentPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

ListItemContent::~ListItemContent() {}

int ListItemContent::x() const {
    Q_D(const ListItemContent);

    return d->x;
}

void ListItemContent::setX(int x) {
    if (x != this->x()) {
        Q_D(ListItemContent);
        d->x = x;
        emit xChanged();
    }
}

int ListItemContent::y() const {
    Q_D(const ListItemContent);

    return d->y;
}

void ListItemContent::setY(int y) {
    if (y != this->y()) {
        Q_D(ListItemContent);
        d->y = y;
        emit yChanged();
    }
}

int ListItemContent::width() const {
    Q_D(const ListItemContent);

    return d->width;
}

void ListItemContent::setWidth(int w) {
    if (w != this->width()) {
        Q_D(ListItemContent);
        d->width = w;
        emit widthChanged();
    }
}

int ListItemContent::height() const {
    Q_D(const ListItemContent);

    return d->height;
}

void ListItemContent::setHeight(int h) {
    if (h != this->height()) {
        Q_D(ListItemContent);
        d->height = h;
        emit heightChanged();
    }
}

qreal ListItemContent::opacity() const {
    Q_D(const ListItemContent);

    return d->opacity;
}

void ListItemContent::setOpacity(qreal opacity) {
    if (opacity != this->opacity()) {
        Q_D(ListItemContent);
        d->opacity = opacity;
        emit opacityChanged();
    }
}

bool ListItemContent::isVisible() const {
    Q_D(const ListItemContent);

    return d->visible;
}

void ListItemContent::setVisible(bool visible) {
    if (visible != this->isVisible()) {
        Q_D(ListItemContent);
        d->visible = visible;
        emit visibleChanged();
    }
}

bool ListItemContent::isEnabled() const {
    Q_D(const ListItemContent);

    return d->enabled;
}

void ListItemContent::setEnabled(bool enabled) {
    if (enabled != this->isEnabled()) {
        Q_D(ListItemContent);
        d->enabled = enabled;
        emit enabledChanged();
    }
}

bool ListItemContent::smooth() const {
    Q_D(const ListItemContent);

    return d->smooth;
}

void ListItemContent::setSmooth(bool smooth) {
    if (smooth != this->smooth()) {
        Q_D(ListItemContent);
        d->smooth = smooth;
        emit smoothChanged();
    }
}

AnchorLine ListItemContent::left() const {
    Q_D(const ListItemContent);

    return d->left;
}

AnchorLine ListItemContent::right() const {
    Q_D(const ListItemContent);

    return d->right;
}

AnchorLine ListItemContent::top() const {
    Q_D(const ListItemContent);

    return d->top;
}

AnchorLine ListItemContent::bottom() const {
    Q_D(const ListItemContent);

    return d->bottom;
}

AnchorLine ListItemContent::horizontalCenter() const {
    Q_D(const ListItemContent);

    return d->horizontalCenter;
}

AnchorLine ListItemContent::verticalCenter() const {
    Q_D(const ListItemContent);

    return d->verticalCenter;
}

bool ListItemContent::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        Q_D(const ListItemContent);

        foreach (ListItemContent *content, d->contentList) {
            if (content->event(event)) {
                return true;
            }
        }

        break;
    }

    return QObject::event(event);
}

bool ListItemContent::editorEvent(QEvent *event, const QRect &rect) {
    Q_D(const ListItemContent);

    foreach (ListItemContent *content, d->contentList) {
        if (content->editorEvent(event, QRect(rect.left() + this->x(), rect.top() + this->y(), this->width(), this->height()))) {
            return true;
        }
    }

    return false;
}

void ListItemContent::paint(QPainter *painter, const QRect &rect) {
    Q_UNUSED(painter);
    Q_UNUSED(rect);
}

void ListItemContent::classBegin() {}

void ListItemContent::componentComplete() {
    Q_D(ListItemContent);

    d->componentComplete();
}

#include "moc_listitemcontent_p.cpp"

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

#include "listitem_p.h"
#include "listitemcontent_p.h"
#include "anchors_p_p.h"
#include <QEvent>
#include <QPainter>
#include <QHashIterator>

class ListItemPrivate
{

public:
    ListItemPrivate(ListItem *parent) :
        q_ptr(parent),
        anc(0),
        x(0),
        y(0),
        width(800),
        height(70),
        opacity(1.0),
        visible(true),
        left(AnchorLine(parent, AnchorLine::Left)),
        right(AnchorLine(parent, AnchorLine::Right)),
        top(AnchorLine(parent, AnchorLine::Top)),
        bottom(AnchorLine(parent, AnchorLine::Bottom)),
        horizontalCenter(AnchorLine(parent, AnchorLine::HCenter)),
        verticalCenter(AnchorLine(parent, AnchorLine::VCenter)),
        isCurrentItem(false),
        complete(false)
    {
    }

    virtual ~ListItemPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (ListItem *item = qobject_cast<ListItem*>(list->object)) {
            item->d_func()->dataList.append(obj);

            if (ListItemContent *content = qobject_cast<ListItemContent*>(obj)) {
                item->d_func()->contentList.append(content);
            }
        }
    }

    static void content_append(QDeclarativeListProperty<ListItemContent> *list, ListItemContent *contentItem) {
        if (!contentItem) {
            return;
        }

        if (ListItem *item = qobject_cast<ListItem*>(list->object)) {
            item->d_func()->dataList.append(contentItem);
            item->d_func()->contentList.append(contentItem);
        }
    }

    virtual QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, ListItemPrivate::data_append);
    }

    virtual QDeclarativeListProperty<ListItemContent> content() {
        return QDeclarativeListProperty<ListItemContent>(q_func(), 0, ListItemPrivate::content_append);
    }

    Anchors* anchors() {
        if (!anc) {
            Q_Q(ListItem);
            anc = new Anchors(q, q);
        }

        return anc;
    }

    virtual void componentComplete() {
        complete = true;

        if (anc) {
            anc->d_func()->onItemCompleted();
        }
    }

    ListItem *q_ptr;

    Anchors *anc;

    int x;
    int y;
    int width;
    int height;

    qreal opacity;

    bool visible;

    AnchorLine left;
    AnchorLine right;
    AnchorLine top;
    AnchorLine bottom;
    AnchorLine horizontalCenter;
    AnchorLine verticalCenter;

    mutable QModelIndex index;

    mutable bool isCurrentItem;

    mutable QVariantMap modelData;

    bool complete;

    QList<QObject*> dataList;

    QList<ListItemContent*> contentList;

    Q_DECLARE_PUBLIC(ListItem)
};

ListItem::ListItem(QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(new ListItemPrivate(this))
{
}

ListItem::ListItem(ListItemPrivate &dd, QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(&dd)
{
}

ListItem::~ListItem() {}

int ListItem::x() const {
    Q_D(const ListItem);

    return d->x;
}

void ListItem::setX(int x) {
    if (x != this->x()) {
        Q_D(ListItem);
        d->x = x;
        emit xChanged();
    }
}

int ListItem::y() const {
    Q_D(const ListItem);

    return d->y;
}

void ListItem::setY(int y) {
    if (y != this->y()) {
        Q_D(ListItem);
        d->y = y;
        emit yChanged();
    }
}

int ListItem::width() const {
    Q_D(const ListItem);

    return d->width;
}

void ListItem::setWidth(int w) {
    if (w != this->width()) {
        Q_D(ListItem);
        d->width = w;
        emit widthChanged();
    }
}

int ListItem::height() const {
    Q_D(const ListItem);

    return d->height;
}

void ListItem::setHeight(int h) {
    if (h != this->height()) {
        Q_D(ListItem);
        d->height = h;
        emit heightChanged();
    }
}

qreal ListItem::opacity() const {
    Q_D(const ListItem);

    return d->opacity;
}

void ListItem::setOpacity(qreal opacity) {
    if (opacity != this->opacity()) {
        Q_D(ListItem);
        d->opacity = opacity;
        emit opacityChanged();
    }
}

bool ListItem::isVisible() const {
    Q_D(const ListItem);

    return d->visible;
}

void ListItem::setVisible(bool visible) {
    if (visible != this->isVisible()) {
        Q_D(ListItem);
        d->visible = visible;
        emit visibleChanged();
    }
}

AnchorLine ListItem::left() const {
    Q_D(const ListItem);

    return d->left;
}

AnchorLine ListItem::right() const {
    Q_D(const ListItem);

    return d->right;
}

AnchorLine ListItem::top() const {
    Q_D(const ListItem);

    return d->top;
}

AnchorLine ListItem::bottom() const {
    Q_D(const ListItem);

    return d->bottom;
}

AnchorLine ListItem::horizontalCenter() const {
    Q_D(const ListItem);

    return d->horizontalCenter;
}

AnchorLine ListItem::verticalCenter() const {
    Q_D(const ListItem);

    return d->verticalCenter;
}

QVariant ListItem::index() const {
    Q_D(const ListItem);

    return QVariant::fromValue(d->index);
}   

int ListItem::row() const {
    Q_D(const ListItem);

    return d->index.row();
}

int ListItem::column() const {
    Q_D(const ListItem);

    return d->index.column();
}

bool ListItem::isCurrentItem() const {
    Q_D(const ListItem);

    return d->isCurrentItem;
}

QVariantMap ListItem::modelData() const {
    Q_D(const ListItem);

    return d->modelData;
}

bool ListItem::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    return QStyledItemDelegate::event(event);
}

void ListItem::classBegin() {}

void ListItem::componentComplete() {
    Q_D(ListItem);

    d->componentComplete();
}

void ListItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_D(const ListItem);

    QHashIterator<int, QByteArray> iterator(index.model()->roleNames());

    while (iterator.hasNext()) {
        iterator.next();
        d->modelData[iterator.value()] = index.data(iterator.key());
    }

    d->index = index;
    d->isCurrentItem = (option.state) & (QStyle::State_Selected) ? true : false;
    emit indexChanged();
    emit modelDataChanged();

    if (this->isCurrentItem()) {
        painter->drawImage(option.rect, QImage("/etc/hildon/theme/images/TouchListBackgroundPressed.png"));
    }
    else {
        painter->drawImage(option.rect, QImage("/etc/hildon/theme/images/TouchListBackgroundNormal.png"));
    }

    foreach (ListItemContent *content, d->contentList) {
        if (content->isVisible()) {
            content->paint(painter, option.rect);
        }
    }
}

bool ListItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    Q_D(const ListItem);

    foreach (ListItemContent *content, d->contentList) {
        if (content->editorEvent(event, option.rect)) {
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize ListItem::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(this->width(), this->height());
}

#include "moc_listitem_p.cpp"

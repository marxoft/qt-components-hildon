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

#ifndef LISTITEM_P_H
#define LISTITEM_P_H

#include "anchors_p.h"
#include "modelindex_p.h"
#include <QStyledItemDelegate>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class ListItemContent;
class ListItemPrivate;

class ListItem : public QStyledItemDelegate, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(ListItem::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PROPERTY(QVariant index READ index NOTIFY indexChanged)
    Q_PROPERTY(int row READ row NOTIFY indexChanged)
    Q_PROPERTY(int column READ column NOTIFY indexChanged)
    Q_PROPERTY(bool isCurrentItem READ isCurrentItem NOTIFY indexChanged)
    Q_PROPERTY(QVariantMap modelData READ modelData NOTIFY modelDataChanged)
    Q_PRIVATE_PROPERTY(ListItem::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(ListItem::d_func(), QDeclarativeListProperty<ListItemContent> content READ content)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ListItem(QObject *parent = 0);
    ~ListItem();

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int width() const;
    void setWidth(int w);

    int height() const;
    void setHeight(int h);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    bool isVisible() const;
    void setVisible(bool visible);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

    QVariant index() const;
    int row() const;
    int column() const;

    bool isCurrentItem() const;

    QVariantMap modelData() const;

    bool event(QEvent *event);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void indexChanged() const;
    void modelDataChanged() const;

protected:
    ListItem(ListItemPrivate &dd, QObject *parent = 0);    

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<ListItemPrivate> d_ptr;

    Q_DECLARE_PRIVATE(ListItem)

private:
    Q_DISABLE_COPY(ListItem)
};

QML_DECLARE_TYPE(ListItem)

#endif // LISTITEM_P_H

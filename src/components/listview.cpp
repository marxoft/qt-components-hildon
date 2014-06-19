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

#include "listview_p.h"
#include "listview_p_p.h"
#include "variantlistmodel_p.h"
#include "itemdelegate_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>

ListView::ListView(QWidget *parent) :
    QListView(parent),
    d_ptr(new ListViewPrivate(this))
{
}

ListView::ListView(ListViewPrivate &dd, QWidget *parent) :
    QListView(parent),
    d_ptr(&dd)
{
}

ListView::~ListView() {}

void ListView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void ListView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

AnchorLine ListView::left() const {
    Q_D(const ListView);

    return d->left;
}

AnchorLine ListView::right() const {
    Q_D(const ListView);

    return d->right;
}

AnchorLine ListView::top() const {
    Q_D(const ListView);

    return d->top;
}

AnchorLine ListView::bottom() const {
    Q_D(const ListView);

    return d->bottom;
}

AnchorLine ListView::horizontalCenter() const {
    Q_D(const ListView);

    return d->horizontalCenter;
}

AnchorLine ListView::verticalCenter() const {
    Q_D(const ListView);

    return d->verticalCenter;
}

void ListView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QListView::changeEvent(event);
}

void ListView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QListView::moveEvent(event);
}

void ListView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QListView::resizeEvent(event);
}

void ListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    for (int i = topLeft.row(); i <= bottomRight.row(); i++) {
        if (QAbstractItemDelegate *del = this->itemDelegateForRow(i)) {
            del->setProperty("display", this->model()->data(this->model()->index(i, 0)));
        }
    }
}

void ListView::classBegin() {}

void ListView::componentComplete() {
    Q_D(ListView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void ListViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ListView *view = qobject_cast<ListView*>(list->object)) {
        view->d_func()->dataList.append(obj);
    }
}

void ListViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ListView *view = qobject_cast<ListView*>(list->object)) {
        view->d_func()->actionList.append(obj);

        if (!view->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            view->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            view->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> ListViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ListViewPrivate::data_append);
}

QDeclarativeListProperty<QObject> ListViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ListViewPrivate::actions_append);
}

QVariant ListViewPrivate::model() const {
    return modelVariant;
}

void ListViewPrivate::setModel(const QVariant &model) {
    Q_Q(ListView);

    if (model == this->model()) {
        return;
    }

    VariantListModel *oldModel = variantModel;
    variantModel = 0;
    modelVariant = model;
    QObject *obj = qvariant_cast<QObject*>(model);
    QAbstractItemModel *itemModel = 0;

    if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
        q->setModel(itemModel);
    }
    else {
        variantModel = new VariantListModel(q);
        variantModel->setVariant(model);
        q->setModel(variantModel);
    }

    if (oldModel) {
        delete oldModel;
    }
}

QVariant ListViewPrivate::rootIndex() const {
    Q_Q(const ListView);

    return QVariant::fromValue<QModelIndex>(q->rootIndex());
}

void ListViewPrivate::setRootIndex(const QVariant &index) {
    Q_Q(ListView);

    q->setRootIndex(index.value<QModelIndex>());
}

QVariant ListViewPrivate::currentIndex() const {
    Q_Q(const ListView);

    return QVariant::fromValue<QModelIndex>(q->currentIndex());
}

void ListViewPrivate::setCurrentIndex(const QVariant &index) {
    Q_Q(ListView);

    q->setCurrentIndex(index.value<QModelIndex>());
}

ItemDelegate* ListViewPrivate::delegate() const {
    return del;
}

void ListViewPrivate::setDelegate(ItemDelegate *delegate) {
    if (delegate != del) {
        Q_Q(ListView);
        del = delegate;

        if (delegate) {
            q->setItemDelegate(delegate);
        }
        else {
            q->setItemDelegate(new QStyledItemDelegate(q));
        }
    }
}

void ListViewPrivate::resetDelegate() {
    this->setDelegate(0);
}

#include "moc_listview_p.cpp"

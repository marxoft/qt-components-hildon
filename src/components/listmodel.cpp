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

#include "listmodel_p.h"

class ListModelPrivate
{

public:
    ListModelPrivate(ListModel *parent) :
        q_ptr(parent),
        complete(false)
    {
    }

    virtual ~ListModelPrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (ListModel *model = qobject_cast<ListModel*>(list->object)) {
            model->d_func()->dataList.append(obj);
        }
    }

    virtual QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, ListModelPrivate::data_append);
    }

    void setRoleNames() {
        if (items.isEmpty()) {
            return;
        }

        roleNames.clear();

        QMapIterator<QString, QVariant> iterator(items.first());
        int role = Qt::UserRole + 1;

        while (iterator.hasNext()) {
            iterator.next();
            roleNames[role] = iterator.key().toUtf8();
            role++;
        }

        Q_Q(ListModel);
        q->setRoleNames(roleNames);
    }

    ListModel *q_ptr;

    QList<QVariantMap> items;

    QHash<int, QByteArray> roleNames;

    bool complete;

    QList<QObject*> dataList;

    Q_DECLARE_PUBLIC(ListModel)
};

ListModel::ListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new ListModelPrivate(this))
{
}

ListModel::ListModel(ListModelPrivate &dd, QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(&dd)
{
}

ListModel::~ListModel() {}

int ListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    Q_D(const ListModel);

    return d->items.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const {
    Q_D(const ListModel);

    return this->get(index).value(d->roleNames.value(role));
}

QVariant ListModel::property(const QModelIndex &index, const QString &name) const {
    return this->get(index).value(name);
}

QVariant ListModel::property(int row, const QString &name) const {
    return this->get(row).value(name);
}

void ListModel::setProperty(const QModelIndex &index, const QString &name, const QVariant &value) {
    this->setProperty(index.row(), name, value);
}

void ListModel::setProperty(int row, const QString &name, const QVariant &value) {
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        d->items[row].insert(name, value);
        const QModelIndex index = this->index(row);
        emit dataChanged(index, index);
    }
}

QVariantMap ListModel::get(const QModelIndex &index) const {
    return this->get(index.row());
}

QVariantMap ListModel::get(int row) const {
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(const ListModel);
        return d->items.at(row);
    }

    return QVariantMap();
}

void ListModel::set(const QModelIndex &index, const QVariantMap &item) {
    this->set(index.row(), item);
}

void ListModel::set(int row, const QVariantMap &item) {
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        QMapIterator<QString, QVariant> iterator(item);

        while (iterator.hasNext()) {
            iterator.next();
            d->items[row].insert(iterator.key(), iterator.value());
        }

        const QModelIndex index = this->index(row);
        emit dataChanged(index, index);
    }
}

void ListModel::append(const QVariantMap &item) {
    Q_D(ListModel);

    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    d->items.append(item);

    if (d->items.size() == 1) {
        d->setRoleNames();
    }

    this->endInsertRows();
    emit countChanged();
}

void ListModel::insert(const QModelIndex &index, const QVariantMap &item) {
    this->insert(index.row(), item);
}

void ListModel::insert(int row, const QVariantMap &item) {
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        this->beginInsertRows(QModelIndex(), row, row);
        d->items.insert(row, item);

        if (d->items.size() == 1) {
            d->setRoleNames();
        }

        this->endInsertRows();
        emit countChanged();
    }
    else {
        this->append(item);
    }
}

void ListModel::move(const QModelIndex &from, const QModelIndex &to, int count) {
    this->move(from.row(), to.row(), count);
}

void ListModel::move(int from, int to, int count) {
    if ((from >= 0) && ((from + count) < this->rowCount()) && (to >= 0)) {
        Q_D(ListModel);
        this->beginMoveRows(QModelIndex(), from, from + count, QModelIndex(), to);

        for (int i = 0; i < count; i++) {
            d->items.move(from, to + i);
        }

        this->endMoveRows();
    }
}

void ListModel::remove(const QModelIndex &index) {
    this->remove(index.row());
}

void ListModel::remove(int row) {
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        this->beginRemoveRows(QModelIndex(), row, row);
        d->items.removeAt(row);
        this->endRemoveRows();
        emit countChanged();
    }
}

void ListModel::clear() {
    if (this->rowCount() > 0) {
        Q_D(ListModel);
        this->beginResetModel();
        d->items.clear();
        this->endResetModel();
        emit countChanged();
    }
}

void ListModel::classBegin() {}

void ListModel::componentComplete() {
    Q_D(ListModel);

    d->complete = true;
    d->setRoleNames();
}

#include "moc_listmodel_p.cpp"

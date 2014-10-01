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
#include "listelement_p.h"

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
            
            if (ListElement *element = static_cast<ListElement*>(obj)) {
                model->d_func()->elements.append(element);
            }
        }
    }

    virtual QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, ListModelPrivate::data_append);
    }
    
    ListElement* createElement(const QVariantMap &properties) {
        Q_Q(ListModel);
        
        ListElement *element = new ListElement(q);
        QMapIterator<QString, QVariant> iterator(properties);
        
        while (iterator.hasNext()) {
            iterator.next();
            element->insert(iterator.key(), iterator.value());
        }
        
        return element;
    }

    void setRoleNames() {
        if (elements.isEmpty()) {
            return;
        }

        roleNames.clear();
        
        ListElement *element = elements.first();
        int role = Qt::UserRole + 1;
        
        foreach (QString key, element->keys()) {
            roleNames[role] = key.toUtf8();
            role++;
        }
        
        Q_Q(ListModel);
        q->setRoleNames(roleNames);
    }

    ListModel *q_ptr;

    QList<ListElement*> elements;

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

    return d->elements.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const {
    if (ListElement *element = this->get(index)) {
        return element->value(this->roleNames().value(role));
    }
    
    return QVariant();
}

QVariant ListModel::modelIndex(int row, int column, const QModelIndex &parent) const {
    return QVariant::fromValue(this->index(row, column, parent));
}

QVariant ListModel::property(const QModelIndex &index, const QString &name) const {
    if (ListElement *element = this->get(index)) {
        return element->value(name);
    }
    
    return QVariant();
}

void ListModel::setProperty(const QModelIndex &index, const QString &name, const QVariant &value) {
    if (ListElement *element = this->get(index)) {
        element->insert(name, value);
        emit dataChanged(index, index);
    }
}

ListElement* ListModel::get(const QModelIndex &index) const {
    const int row = index.row();
    
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(const ListModel);
        return d->elements.at(row);
    }

    return 0;
}

void ListModel::set(const QModelIndex &index, const QVariantMap &properties) {
    if (ListElement *element = this->get(index)) {
        QMapIterator<QString, QVariant> iterator(properties);

        while (iterator.hasNext()) {
            iterator.next();
            element->insert(iterator.key(), iterator.value());
        }
        
        emit dataChanged(index, index);
    }
}

void ListModel::append(const QVariantMap &properties) {
    Q_D(ListModel);

    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    
    if (ListElement *element = d->createElement(properties)) {
        d->elements.append(element);

        if (d->elements.size() == 1) {
            d->setRoleNames();
        }

        this->endInsertRows();
        emit countChanged();
    }
}

void ListModel::insert(const QModelIndex &index, const QVariantMap &properties) {
    const int row = index.row();
    
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        
        if (ListElement *element = d->createElement(properties)) {
            d->elements.insert(row, element);

            if (d->elements.size() == 1) {
                d->setRoleNames();
            }

            this->endInsertRows();
            emit countChanged();
        }
    }
    else {
        this->append(properties);
    }
}

void ListModel::move(const QModelIndex &fromIndex, const QModelIndex &toIndex, int count) {
    const int from = fromIndex.row();
    const int to = toIndex.row();
    
    if ((from >= 0) && ((from + count) < this->rowCount()) && (to >= 0)) {
        Q_D(ListModel);
        this->beginMoveRows(QModelIndex(), from, from + count, QModelIndex(), to);

        for (int i = 0; i < count; i++) {
            d->elements.move(from, to + i);
        }

        this->endMoveRows();
    }
}

void ListModel::remove(const QModelIndex &index) {
    const int row = index.row();
    
    if ((row >= 0) && (row < this->rowCount())) {
        Q_D(ListModel);
        this->beginRemoveRows(QModelIndex(), row, row);
        delete d->elements.takeAt(row);
        this->endRemoveRows();
        emit countChanged();
    }
}

void ListModel::clear() {
    if (this->rowCount() > 0) {
        Q_D(ListModel);
        this->beginResetModel();
        qDeleteAll(d->elements);
        d->elements.clear();
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


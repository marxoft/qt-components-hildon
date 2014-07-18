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

#include "varianttablemodel_p.h"
#include <QMetaProperty>

class VariantTableModelPrivate
{

public:
    VariantTableModelPrivate(VariantTableModel *parent) :
        q_ptr(parent)
    {
    }

    virtual ~VariantTableModelPrivate() {}

    void updateRoleNames() {
        Q_Q(VariantTableModel);

        if (variantList.isEmpty()) {
            return;
        }

        QHash<int, QByteArray> roles;
        roles[Qt::DisplayRole] = "display";
        roles[Qt::DecorationRole] = "decoration";
        roles[Qt::UserRole] = "modelData";


        QVariant variant = variantList.first();

        switch (variant.type()) {
        case QVariant::Map:
        {
            int role = Qt::UserRole + 1;

            foreach (QString key, variant.toMap().keys()) {
                roles[role] = key.toUtf8();
                role++;
            }

            break;
        }
        case QVariant::List:
        {
            const int size = variant.toList().size();
            int role = Qt::UserRole + 1;

            for (int i = 0; i < size; i++) {
                roles[role] = QByteArray::number(role);
                role++;
            }

            break;
        }
        default:
            if (QObject *obj = qvariant_cast<QObject*>(variant)) {
                const QMetaObject *metaObject = obj->metaObject();
                const int offset = metaObject->propertyOffset();
                const int count = metaObject->propertyCount();
                int role = Qt::UserRole + 1;

                for (int i = offset; i < count; i++) {
                    roles[role] = metaObject->property(i).name();
                    role++;
                }
            }

            break;
        }

        q->setRoleNames(roles);
    }

    void _q_onObjectPropertyChanged() {
        Q_Q(VariantTableModel);

        if (QObject *obj = q->sender()) {
            const int i = variantList.indexOf(QVariant::fromValue(obj));

            if (i != -1) {
                emit q->dataChanged(q->index(i, 0), q->index(i, q->columnCount() - 1));
            }
        }
    }

    VariantTableModel *q_ptr;

    QVariant modelVariant;

    QVariantList variantList;

    Q_DECLARE_PUBLIC(VariantTableModel)
};

VariantTableModel::VariantTableModel(QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(new VariantTableModelPrivate(this))
{
}

VariantTableModel::VariantTableModel(VariantTableModelPrivate &dd, QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(&dd)
{
}

VariantTableModel::~VariantTableModel() {}

QVariant VariantTableModel::variant() const {
    Q_D(const VariantTableModel);

    return d->modelVariant;
}

void VariantTableModel::setVariant(const QVariant &variant) {
    Q_D(VariantTableModel);

    if (variant == d->modelVariant) {
        return;
    }

    this->clear();

    d->modelVariant = variant;

    if (variant.isNull()) {
        return;
    }

    switch (variant.type()) {
    case QVariant::List:
    case QVariant::StringList:
        this->beginResetModel();
        d->variantList = variant.toList();
        this->endResetModel();
        break;
    case QVariant::Int:
        if (variant.toInt() > 0) {
            this->beginInsertRows(QModelIndex(), 0, variant.toInt() - 1);

            for (int i = 0; i < variant.toInt(); i++) {
                d->variantList.append(i);
            }

            this->endInsertRows();
        }

        break;
    case QVariant::String:
    {
        QString string = variant.toString();
        int size = string.size();
        this->beginInsertRows(QModelIndex(), 0, size - 1);

        for (int i = 0; i < size; i++) {
            d->variantList.append(string.at(i));
        }

        this->endInsertRows();
        break;
    }
    default:
        d->variantList.append(variant);
        break;
    }

    d->updateRoleNames();
}

QVariant VariantTableModel::get(const QModelIndex &index) const {
    return this->get(index.row());
}

QVariant VariantTableModel::get(int row) const {
    Q_D(const VariantTableModel);

    if ((row >= 0) && (row < d->variantList.size())) {
        return d->variantList.at(row);
    }

    return QVariant();
}

void VariantTableModel::clear() {
    Q_D(VariantTableModel);

    this->beginResetModel();
    d->variantList.clear();
    this->endResetModel();
}

int VariantTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    Q_D(const VariantTableModel);

    return d->variantList.size();
}

int VariantTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    return this->roleNames().size() - 1;
}

QVariant VariantTableModel::data(const QModelIndex &index, int role) const {
    const int column = index.column();
    int i = role ;

    switch (role) {
    case Qt::DisplayRole:
        i = Qt::UserRole + column;
        break;
    default:
        if (role < Qt::UserRole) {
            return QVariant();
        }

        break;
    }

    QVariant variant = this->get(index);

    switch (variant.type()) {
    case QVariant::Map:
        return variant.toMap().value(this->roleNames().value(i));
    case QVariant::List:
    {
        QVariantList list = variant.toList();

        if ((column >= 0) && (column < list.size())) {
            return list.at(column);
        }

        break;
    }
    default:
        if (QObject *obj = qvariant_cast<QObject*>(variant)) {
            return obj->property(this->roleNames().value(i));
        }

        break;
    }

    return variant;
}

#include "moc_varianttablemodel_p.cpp"

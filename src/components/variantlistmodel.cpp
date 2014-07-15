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

#include "variantlistmodel_p.h"
#include "variantlistmodel_p_p.h"
#include <QMetaProperty>

VariantListModel::VariantListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new VariantListModelPrivate(this))
{
}

VariantListModel::VariantListModel(VariantListModelPrivate &dd, QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(&dd)
{
}

VariantListModel::~VariantListModel() {}

QVariant VariantListModel::variant() const {
    Q_D(const VariantListModel);

    return d->modelVariant;
}

void VariantListModel::setVariant(const QVariant &variant) {
    Q_D(VariantListModel);

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

QVariant VariantListModel::get(const QModelIndex &index) const {
    return this->get(index.row());
}

QVariant VariantListModel::get(int row) const {
    Q_D(const VariantListModel);

    if ((row >= 0) && (row < d->variantList.size())) {
        return d->variantList.at(row);
    }

    return QVariant();
}

void VariantListModel::clear() {
    Q_D(VariantListModel);

    this->beginResetModel();
    d->variantList.clear();
    this->endResetModel();
}

int VariantListModel::rowCount(const QModelIndex &parent) const {
    Q_D(const VariantListModel);

    return d->variantList.size();
}

QVariant VariantListModel::data(const QModelIndex &index, int role) const {
    QByteArray roleName = this->roleNames().value(role);
    return roleName.isEmpty() ? QVariant() : this->data(index, roleName);
}

QVariant VariantListModel::data(const QModelIndex &index, const QByteArray &roleName) const {
    QVariant variant = this->get(index);

    if (roleName == "modelData") {
        return variant;
    }

    switch (variant.type()) {
    case QVariant::Map:
        return variant.toMap().value(roleName);
    default:
        if (QObject *obj = qvariant_cast<QObject*>(variant)) {
            return obj->property(roleName);
        }

        break;
    }

    return variant;
}

void VariantListModelPrivate::updateRoleNames() {
    Q_Q(VariantListModel);

    if (variantList.isEmpty()) {
        return;
    }

    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[Qt::DecorationRole] = "decoration";
    roles[Qt::UserRole + 1] = "modelData";

    QVariant variant = variantList.first();

    switch (variant.type()) {
    case QVariant::Map:
    {
        int role = Qt::UserRole + 2;

        foreach (QString key, variant.toMap().keys()) {
            roles[role] = key.toUtf8();
            role++;
        }

        break;
    }
    default:
        if (QObject *obj = qvariant_cast<QObject*>(variant)) {
            const QMetaObject *metaObject = obj->metaObject();
            const int offset = metaObject->propertyOffset();
            const int count = metaObject->propertyCount();
            int role = Qt::UserRole + 2;

            for (int i = offset; i < count; i++) {
                roles[role] = metaObject->property(i).name();
                role++;
            }
        }

        break;
    }

    q->setRoleNames(roles);
}

#include "moc_variantlistmodel_p.cpp"

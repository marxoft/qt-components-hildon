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

    return d->variant;
}

void VariantListModel::setVariant(const QVariant &variant) {
    Q_D(VariantListModel);

    this->clear();

    d->variant = variant;

    if (variant.isNull()) {
        return;
    }

    switch (variant.type()) {
    case QVariant::List:
    case QVariant::StringList:
        this->beginResetModel();
        d->variantList = variant.toList();
        this->endResetModel();
        return;
    case QVariant::Int:
        if (variant.toInt() > 0) {
            this->beginInsertRows(QModelIndex(), 0, variant.toInt() - 1);

            for (int i = 0; i < variant.toInt(); i++) {
                d->variantList.append(i);
            }

            this->endInsertRows();
        }

        return;
    case QVariant::String:
    {
        QString string = variant.toString();
        int size = string.size();
        this->beginInsertRows(QModelIndex(), 0, size - 1);

        for (int i = 0; i < size; i++) {
            d->variantList.append(string.at(i));
        }

        this->endInsertRows();
        return;
    }
    default:
        return;
    }
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
    Q_UNUSED(parent);
    Q_D(const VariantListModel);

    return d->variantList.size();
}

QVariant VariantListModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case Qt::DisplayRole:
        return this->get(index);
    default:
        return QVariant();
    }
}

#include "moc_variantlistmodel_p.cpp"

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

#include "sortfilterproxymodel_p.h"
#include "variantlistmodel_p.h"

class SortFilterProxyModelPrivate
{

public:
    SortFilterProxyModelPrivate(SortFilterProxyModel *parent) :
        q_ptr(parent),
        variantModel(0),
        complete(false)
    {
    }
    
    QVariant sourceModel() const {
        return modelVariant;
    }
    
    void setSourceModel(const QVariant &model) {
        Q_Q(SortFilterProxyModel);

        if (model == this->sourceModel()) {
            return;
        }
        
        const int filterRole = q->filterRole();
        const int sortRole = q->sortRole();

        VariantListModel *oldModel = variantModel;
        variantModel = 0;
        modelVariant = model;
        QObject *obj = qvariant_cast<QObject*>(model);
        QAbstractItemModel *itemModel = 0;

        if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
            q->setSourceModel(itemModel);
        }
        else {
            variantModel = new VariantListModel(q);
            variantModel->setVariant(model);
            q->setSourceModel(variantModel);
        }
        
        if (filterProperty.isEmpty()) {
            q->setFilterRole(filterRole);
        }
        else {
            q->setFilterRole(q->roleNames().key(filterProperty.toUtf8()));
        }
        
        if (sortProperty.isEmpty()) {
            q->setSortRole(sortRole);
        }
        else {
            q->setSortRole(q->roleNames().key(sortProperty.toUtf8()));
        }

        if (oldModel) {
            delete oldModel;
        }

        emit q->sourceModelChanged();
    }
    
    SortFilterProxyModel *q_ptr;

    QVariant modelVariant;

    VariantListModel *variantModel;
    
    QString filterProperty;
    QString sortProperty;
    
    bool complete;
    
    Q_DECLARE_PUBLIC(SortFilterProxyModel)
};

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    d_ptr(new SortFilterProxyModelPrivate(this))
{
}

SortFilterProxyModel::SortFilterProxyModel(SortFilterProxyModelPrivate &dd, QObject *parent) :
    QSortFilterProxyModel(parent),
    d_ptr(&dd)
{
}

SortFilterProxyModel::~SortFilterProxyModel() {}

QString SortFilterProxyModel::filterProperty() const {
    Q_D(const SortFilterProxyModel);
    
    return d->filterProperty;
}

void SortFilterProxyModel::setFilterProperty(const QString &property) {
    if (property != this->filterProperty()) {
        Q_D(SortFilterProxyModel);
        d->filterProperty = property;
        emit filterPropertyChanged();
        
        if (this->sourceModel()) {
            this->setFilterRole(this->roleNames().key(property.toUtf8()));
        }
    }
}

void SortFilterProxyModel::setQmlFilterRegExp(const QRegExp &regExp) {
    if (regExp != this->filterRegExp()) {
        this->setFilterRegExp(regExp);
        emit filterRegExpChanged();
    }
}

void SortFilterProxyModel::resetQmlFilterRegExp() {
    this->setQmlFilterRegExp(QRegExp());
}

QString SortFilterProxyModel::sortProperty() const {
    Q_D(const SortFilterProxyModel);
    
    return d->sortProperty;
}

void SortFilterProxyModel::setSortProperty(const QString &property) {
    if (property != this->sortProperty()) {
        Q_D(SortFilterProxyModel);
        d->sortProperty = property;
        emit sortPropertyChanged();
        
        if (this->sourceModel()) {
            this->setSortRole(this->roleNames().key(property.toUtf8()));
        }
    }
}

QVariant SortFilterProxyModel::mapFromSourceModelIndex(const QModelIndex &sourceIndex) const {
    Q_D(const SortFilterProxyModel);
    
    return d->complete ? QVariant::fromValue(QSortFilterProxyModel::mapFromSource(sourceIndex))
                       : QVariant();
}

QVariant SortFilterProxyModel::mapToSourceModelIndex(const QModelIndex &proxyIndex) const {
    Q_D(const SortFilterProxyModel);
    
    return d->complete ? QVariant::fromValue(QSortFilterProxyModel::mapToSource(proxyIndex))
                       : QVariant();
}

void SortFilterProxyModel::sort(int column, Qt::SortOrder order) {
    QSortFilterProxyModel::sort(column, order);
}

void SortFilterProxyModel::classBegin() {}

void SortFilterProxyModel::componentComplete() {
    Q_D(SortFilterProxyModel);
    d->complete = true;
}

#include "moc_sortfilterproxymodel_p.cpp"

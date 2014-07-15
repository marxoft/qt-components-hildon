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

#ifndef VARIANTLISTMODEL_P_H
#define VARIANTLISTMODEL_P_H

#include <QAbstractListModel>

class VariantListModelPrivate;

class VariantListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VariantListModel(QObject *parent = 0);
    ~VariantListModel();

    QVariant variant() const;
    void setVariant(const QVariant &variant);

    QVariant get(const QModelIndex &index) const;
    QVariant get(int row) const;

    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant data(const QModelIndex &index, const QByteArray &roleName) const;

private:
    VariantListModel(VariantListModelPrivate &dd, QObject *parent = 0);

    QScopedPointer<VariantListModelPrivate> d_ptr;

    Q_DISABLE_COPY(VariantListModel)
    Q_DECLARE_PRIVATE(VariantListModel)
};

#endif // VARIANTLISTMODEL_P_H

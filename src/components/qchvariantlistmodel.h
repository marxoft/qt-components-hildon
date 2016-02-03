/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHVARIANTLISTMODEL_H
#define QCHVARIANTLISTMODEL_H

#include <QAbstractListModel>

class QchVariantListModelPrivate;

class QchVariantListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QchVariantListModel(QObject *parent = 0);
    ~QchVariantListModel();
    
    QVariant sourceVariant() const;
    void setSourceVariant(const QVariant &variant);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    
    virtual QVariant data(const QModelIndex &index, int role = Qt::UserRole + 1) const;
    
private:
    QScopedPointer<QchVariantListModelPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchVariantListModel)
    Q_DISABLE_COPY(QchVariantListModel)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onObjectDestroyed(QObject*))
};

#endif // QCHVARIANTLISTMODEL_H

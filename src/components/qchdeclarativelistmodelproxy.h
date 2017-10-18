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

#ifndef QCHDECLARATIVELISTMODELPROXY_H
#define QCHDECLARATIVELISTMODELPROXY_H

#include <QAbstractListModel>

class QchDeclarativeListModelProxyPrivate;

class QchDeclarativeListModelProxy : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QchDeclarativeListModelProxy(QObject *parent = 0);
    ~QchDeclarativeListModelProxy();
    
    QObject* sourceModel() const;
    void setSourceModel(QObject *model);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    
    virtual QVariant data(const QModelIndex &index, int role) const;
    
Q_SIGNALS:
    void roleNamesChanged();

private:
    QScopedPointer<QchDeclarativeListModelProxyPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchDeclarativeListModelProxy)
    Q_DISABLE_COPY(QchDeclarativeListModelProxy)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsInserted(int, int))
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsRemoved(int, int))
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsMoved(int, int, int));
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsChanged(int, int));
};

#endif // QCHDECLARATIVELISTMODELPROXY_H

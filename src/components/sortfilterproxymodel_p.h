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

#ifndef SORTFILTERPROXYMODEL_P_H
#define SORTFILTERPROXYMODEL_P_H

#include <QSortFilterProxyModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class SortFilterProxyModelPrivate;

class SortFilterProxyModel : public QSortFilterProxyModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QString filterProperty READ filterProperty WRITE setFilterProperty)
    Q_PROPERTY(QString sortProperty READ sortProperty WRITE setSortProperty)
    Q_PRIVATE_PROPERTY(SortFilterProxyModel::d_func(), QVariant sourceModel READ sourceModel WRITE setSourceModel NOTIFY sourceModelChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    explicit SortFilterProxyModel(QObject *parent = 0);
    ~SortFilterProxyModel();
    
    QString filterProperty() const;
    void setFilterProperty(const QString &property);
    
    QString sortProperty() const;
    void setSortProperty(const QString &property);
    
    Q_INVOKABLE virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    Q_INVOKABLE virtual QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    
    Q_INVOKABLE virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    
signals:
    void sourceModelChanged();
    
protected:
    SortFilterProxyModel(SortFilterProxyModelPrivate &dd, QObject *parent = 0);
    
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<SortFilterProxyModelPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(SortFilterProxyModel)
    
private:
    Q_DISABLE_COPY(SortFilterProxyModel)
};
    
QML_DECLARE_TYPE(SortFilterProxyModel)

#endif // SORTFILTERPROXYMODEL_P_H

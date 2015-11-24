/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHSORTFILTERPROXYMODEL_H
#define QCHSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchSortFilterProxyModelPrivate;

class QchSortFilterProxyModel : public QSortFilterProxyModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(QString filterRole READ filterRoleName WRITE setFilterRoleName NOTIFY filterRoleChanged)
    Q_PROPERTY(QString filterFixedString READ filterFixedString WRITE setFilterFixedString)
    Q_PROPERTY(QString filterWildcard READ filterWildcard WRITE setFilterWildcard)
    Q_PROPERTY(int sortColumn READ sortColumn WRITE setSortColumn NOTIFY sortColumnChanged)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(QString sortRole READ sortRoleName WRITE setSortRoleName NOTIFY sortRoleChanged)
    Q_PROPERTY(QVariant sourceModel READ sourceModelVariant WRITE setSourceModelVariant NOTIFY sourceModelChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit QchSortFilterProxyModel(QObject *parent = 0);
    ~QchSortFilterProxyModel();
    
    QString filterRoleName() const;
    void setFilterRoleName(const QString &roleName);
    
    QString filterFixedString() const;    
    QString filterWildcard() const;
    
    int sortColumn() const;
    void setSortColumn(int column);
    
    Qt::SortOrder sortOrder() const;
    void setSortOrder(Qt::SortOrder order);
    
    QString sortRoleName() const;
    void setSortRoleName(const QString &roleName);
    
    QVariant sourceModelVariant() const;
    void setSourceModelVariant(const QVariant &variant);

public Q_SLOTS:
    QVariant mapIndexToSource(const QVariant &proxyIndex) const;
    int mapRowToSource(int proxyRow) const;
    
    virtual void sort();
        
Q_SIGNALS:
    void countChanged();
    void filterRoleChanged();
    void sortColumnChanged();
    void sortOrderChanged();
    void sortRoleChanged();
    void sourceModelChanged();

private:
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<QchSortFilterProxyModelPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchSortFilterProxyModel)
    Q_DISABLE_COPY(QchSortFilterProxyModel)    
};

QML_DECLARE_TYPE(QchSortFilterProxyModel)
Q_DECLARE_METATYPE(QModelIndex)

#endif // QCHSORTFILTERPROXYMODEL_H

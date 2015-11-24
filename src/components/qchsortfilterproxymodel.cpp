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

#include "qchsortfilterproxymodel.h"
#include "qchdeclarativelistmodelproxy.h"
#include "qchvariantlistmodel.h"
#include <QDeclarativeInfo>

class QchSortFilterProxyModelPrivate
{

public:
    QchSortFilterProxyModelPrivate(QchSortFilterProxyModel *parent) :
        q_ptr(parent),
        filterRoleName("modelData"),
        sortRoleName("modelData"),
        sortColumn(0),
        sortOrder(Qt::AscendingOrder),
        ownModel(false),
        complete(false)
    {
    }
    
    void loadSourceModel() {                
        Q_Q(QchSortFilterProxyModel);
        QAbstractItemModel *oldModel = q->sourceModel();
                
        if (QObject *obj = qvariant_cast<QObject*>(sourceModelVariant)) {
            if (QAbstractItemModel *itemModel = qobject_cast<QAbstractItemModel*>(obj)) {
                q->setSourceModel(itemModel);
                
                if ((ownModel) && (oldModel)) {
                    oldModel->deleteLater();
                }
                
                ownModel = false;
            }
            else if ((obj->inherits("QDeclarativeListModel")) || (obj->inherits("QDeclarativeXmlListModel"))) {
                QchDeclarativeListModelProxy *proxy = new QchDeclarativeListModelProxy(q);
                proxy->setSourceModel(obj);
                q->setSourceModel(proxy);
                
                if ((ownModel) && (oldModel)) {
                    oldModel->deleteLater();
                }
                
                ownModel = true;
            }
            else {
                qmlInfo(q) << QchSortFilterProxyModel::tr("Source model type is not supported");
                return;
            }
        }
        else {
            QchVariantListModel *model = new QchVariantListModel(q);            
            model->setSourceVariant(sourceModelVariant);
            q->setSourceModel(model);
            
            if ((ownModel) && (oldModel)) {
                oldModel->deleteLater();
            }
            
            ownModel = true;
        }
        
        q->setFilterRole(q->roleNames().key(filterRoleName.toUtf8()));
        q->setSortRole(q->roleNames().key(sortRoleName.toUtf8()));
        
        if (q->dynamicSortFilter()) {
            q->sort();
        }
    }
    
    QchSortFilterProxyModel *q_ptr;
    
    QVariant sourceModelVariant;
    
    QString filterRoleName;
    QString sortRoleName;
    
    int sortColumn;
    
    Qt::SortOrder sortOrder;
    
    bool ownModel;
    bool complete;
    
    Q_DECLARE_PUBLIC(QchSortFilterProxyModel)
};

/*!
    \class SortFilterProxyModel
    \brief Provides support for sorting and filtering data passed between another model and a view.
    
    \ingroup components
    
    SortFilterProxyModel can be used for sorting items, filtering out items, or both. The model transforms the 
    structure of a source model by mapping the model indexes it supplies to new indexes, corresponding to different 
    locations, for views to use. This approach allows a given source model to be restructured as far as views are 
    concerned without requiring any transformations on the underlying data, and without duplicating the data in memory.
    
    \snippet sortfilter.qml SortFilterProxyModel
*/
QchSortFilterProxyModel::QchSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    d_ptr(new QchSortFilterProxyModelPrivate(this))
{
    connect(this, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SIGNAL(countChanged()));
    connect(this, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SIGNAL(countChanged()));
}

QchSortFilterProxyModel::~QchSortFilterProxyModel() {}

/*!
    \property bool SortFilterProxyModel::dynamicSortFilter
    \brief Whether the proxy model is dynamically sorted and filtered whenever the contents of the source model change.
    
    The default value is \c false.
*/

/*!
    \property enumeration SortFilterProxyModel::filterCaseSensitivity
    \brief The case sensitivity of the QRegExp pattern used to filter the contents of the source model.
    
    The possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.CaseSensitive</td>
            <td>The filter is case sensitive (default).</td>
        </tr>
        <tr>
            <td>Qt.CaseInsensitive</td>
            <td>The filter is not case sensitive.</td>
        </tr>
    </table>
    
    /sa filterRegExp, sortCaseSensitivity
*/

/*!
    \property int SortFilterProxyModel::filterKeyColumn
    \brief The column where the key used to filter the contents of the source model is read from.
    
    The default value is \c 0. If the value is \c -1, the keys will be read from all columns.
*/

/*!
    \property QRegExp SortFilterProxyModel::filterRegExp
    \brief The regular expression used to filter the contents of the source model.
    
    \sa filterFixedString, filterWildcard
*/

/*!
    \property bool SortFilterProxyModel::isSortLocaleAware
    \brief The locale aware setting used for comparing strings when sorting.
    
    The default value is \c false.
*/

/*!
    \property enumeration SortFilterProxyModel::sortCaseSensitivity
    \brief The case sensitivity setting used for comparing strings when sorting.
    
    The possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.CaseSensitive</td>
            <td>The sorting is case sensitive (default).</td>
        </tr>
        <tr>
            <td>Qt.CaseInsensitive</td>
            <td>The sorting is not case sensitive.</td>
        </tr>
    </table>
    
    /sa filterCaseSensitivity
*/

/*!
    \property string SortFilterProxyModel::filterRole
    \brief The item role that is used to query the source model's data when filtering items.
    
    The default value is \c modelData.
*/
QString QchSortFilterProxyModel::filterRoleName() const {
    Q_D(const QchSortFilterProxyModel);
    return d->filterRoleName;
}

void QchSortFilterProxyModel::setFilterRoleName(const QString &roleName) {
    if (roleName != filterRoleName()) {
        Q_D(QchSortFilterProxyModel);
        d->filterRoleName = roleName;
        emit filterRoleChanged();
        
        if (sourceModel()) {
            setFilterRole(roleNames().key(roleName.toUtf8()));
        }
    }
}

/*!
    \brief The fixed string used to filter the contents of the source model.
    
    \sa filterRegExp, filterWildcard
*/
QString QchSortFilterProxyModel::filterFixedString() const {
    return filterRegExp().pattern();
}

/*!
    \brief The wildcard expression used to filter the contents of the source model.
    
    \sa filterRegExp, filterFixedString
*/
QString QchSortFilterProxyModel::filterWildcard() const {
    return filterRegExp().pattern();
}

/*!
    \brief The column to which any sorting should be applied.
    
    The default value is \c 0.
    
    \sa sortOrder, sortRole, sort()
*/
int QchSortFilterProxyModel::sortColumn() const {
    Q_D(const QchSortFilterProxyModel);
    return d->sortColumn;
}

void QchSortFilterProxyModel::setSortColumn(int column) {
    if (column != sortColumn()) {
        Q_D(QchSortFilterProxyModel);
        d->sortColumn = column;
        emit sortColumnChanged();
    }
}

/*!
    \brief The order in which any sorting should be applied.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.AscendingOrder</td>
            <td>The items are sorted in ascending order (default).</td>
        </tr>
        <tr>
            <td>Qt.DescendingOrder</td>
            <td>The items are sorted in descending order.</td>
        </tr>
    </table>
    
    \sa sortColumn, sortRole, sort()
*/
Qt::SortOrder QchSortFilterProxyModel::sortOrder() const {
    Q_D(const QchSortFilterProxyModel);
    return d->sortOrder;
}

void QchSortFilterProxyModel::setSortOrder(Qt::SortOrder order) {
    if (order != sortOrder()) {
        Q_D(QchSortFilterProxyModel);
        d->sortOrder = order;
        emit sortOrderChanged();
    }
}

/*!
    \property string SortFilterProxyModel::sortRole
    \brief The item role that is used to query the source model's data when sorting items.
    
    The default value is \c modelData.
    
    \sa sortColumn, sortOrder, sort()
*/
QString QchSortFilterProxyModel::sortRoleName() const {
    Q_D(const QchSortFilterProxyModel);
    return d->sortRoleName;
}

void QchSortFilterProxyModel::setSortRoleName(const QString &roleName) {
    if (roleName != sortRoleName()) {
        Q_D(QchSortFilterProxyModel);
        d->sortRoleName = roleName;
        emit sortRoleChanged();
        
        if (sourceModel()) {
            setSortRole(roleNames().key(roleName.toUtf8()));
        }
    }
}

/*!
    \property variant SortFilterProxyModel::sourceModel
    \brief The model that contains the data that is available through the proxy model.
    
    The model can be any one of the following:
    
    \li \c QML ListModel or XmlListModel.
    \li \c A subclass of QAbstractItemModel.
    \li \c A simple list.
    \li \c An integer.
    \li \c A string.
    
    The default value is \c null.
*/
QVariant QchSortFilterProxyModel::sourceModelVariant() const {
    Q_D(const QchSortFilterProxyModel);
    return d->sourceModelVariant;
}

void QchSortFilterProxyModel::setSourceModelVariant(const QVariant &variant) {
    if (variant != sourceModelVariant()) {
        Q_D(QchSortFilterProxyModel);
        d->sourceModelVariant = variant;
        emit sourceModelChanged();
        
        if (d->complete) {
            d->loadSourceModel();
        }        
    }
}

/*!
    \brief Maps \a proxyIndex to the source model.
*/
QVariant QchSortFilterProxyModel::mapIndexToSource(const QVariant &proxyIndex) const {
    return QVariant::fromValue(mapToSource(qvariant_cast<QModelIndex>(proxyIndex)));
}

/*!
    \brief Maps \a proxyRow to the source model.
*/
int QchSortFilterProxyModel::mapRowToSource(int proxyRow) const {
    return mapToSource(index(proxyRow, 0, QModelIndex())).row();
}

/*!
    \brief Sorts the items according to the sortColumn, sortOrder and sortRole.
    
    \sa sortColumn, sortOrder, sortRole
*/
void QchSortFilterProxyModel::sort() {
    QSortFilterProxyModel::sort(sortColumn(), sortOrder());
}

void QchSortFilterProxyModel::classBegin() {}

void QchSortFilterProxyModel::componentComplete() {
    Q_D(QchSortFilterProxyModel);
    d->complete = true;
    
    if (!d->sourceModelVariant.isNull()) {
        d->loadSourceModel();
    }
}

#include "moc_qchsortfilterproxymodel.cpp"

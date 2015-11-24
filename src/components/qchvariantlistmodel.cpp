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

#include "qchvariantlistmodel.h"
#include <QDeclarativeInfo>
#include <QMetaMethod>
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>

class QchVariantListModelPrivate
{

public:
    QchVariantListModelPrivate(QchVariantListModel *parent) :
        q_ptr(parent)
    {
    }
    
    void setSourceVariant(const QVariant &variant) {
        if (variant == sourceVariant) {
            return;
        }
        
        unloadData();
        
        sourceVariant = variant;
        Q_Q(QchVariantListModel);
        
        switch (sourceVariant.type()) {
        case QVariant::List:
            loadDataFromList(sourceVariant.toList());
            break;
        case QVariant::StringList:
            loadDataFromStringList(sourceVariant.toStringList());
            break;
        case QVariant::String:
        case QVariant::ByteArray:
            loadDataFromStringList(sourceVariant.toString().split(""));
            break;
        case QVariant::Int:
        case QVariant::Double:
            loadDataFromInteger(sourceVariant.toInt());
            break;
        default:
            qmlInfo(q) << QchVariantListModel::tr("Cannot load model from unsupported type %1")
                                                 .arg(sourceVariant.typeName());
            return;
        }
    }
    
    void loadDataFromList(const QVariantList &variantlist) {
        foreach (QVariant v, variantlist) {
            if (QObject *obj = qvariant_cast<QObject*>(v)) {
                appendObjectToModel(obj);
            }
            else {
                appendVariantToModel(v);
            }
        }
    }
    
    void loadDataFromStringList(const QStringList &stringlist) {
        foreach (QString s, stringlist) {
            appendVariantToModel(s);
        }
    }
    
    void loadDataFromInteger(int length) {
        for (int i = 0; i < length; i++) {
            appendVariantToModel(i);
        }
    }
    
    void appendVariantToModel(const QVariant &v) {
        Q_Q(QchVariantListModel);
        const int size = list.size();
        q->beginInsertRows(QModelIndex(), size, size);
        list << v;
        q->endInsertRows();
    }
    
    void appendObjectToModel(QObject *obj) {
        Q_Q(QchVariantListModel);
        const int size = list.size();
        q->beginInsertRows(QModelIndex(), size, size);
        list << QVariant::fromValue(obj);
        q->endInsertRows();
        
        const QMetaObject *mo = obj->metaObject();
        
        for (int i = mo->propertyOffset(); i < mo->propertyCount(); i++) {
            const QMetaProperty property = mo->property(i);
            
            if (property.hasNotifySignal()) {
                q->connect(obj, property.notifySignal().signature(), q, SLOT(_q_onObjectPropertyChanged()));
            }
        }
        
        q->connect(obj, SIGNAL(destroyed(QObject*)), q, SLOT(_q_onObjectDestroyed(QObject*)));
    }
    
    void unloadData() {
        if (list.isEmpty()) {
            return;
        }
        
        Q_Q(QchVariantListModel);
        
        foreach (QVariant v, list) {
            if (QObject *obj = qvariant_cast<QObject*>(v)) {
                q->disconnect(obj, 0, q, SLOT(_q_onObjectPropertyChanged()));
                q->disconnect(obj, SIGNAL(destroyed(QObject*)), q, SLOT(_q_onObjectDestroyed(QObject*)));
            }
        }
        
        q->beginResetModel();
        list.clear();
        q->endResetModel();
    }
    
    void _q_onObjectPropertyChanged() {
        Q_Q(QchVariantListModel);
        QObject *obj = q->sender();
        
        if (!obj) {
            return;
        }
        
        const int i = list.indexOf(QVariant::fromValue(obj));
        
        if (i != -1) {
            const QModelIndex index = q->index(i);
            emit q->dataChanged(index, index);
        }
    }
    
    void _q_onObjectDestroyed(QObject *obj) {
        if (!obj) {
            return;
        }
        
        const int i = list.indexOf(QVariant::fromValue(obj));
        
        if (i != -1) {
            Q_Q(QchVariantListModel);
            q->beginRemoveRows(QModelIndex(), i, i);
            list.removeAt(i);
            q->endRemoveRows();
        }
    }
    
    QchVariantListModel *q_ptr;
    
    QVariant sourceVariant;
    QVariantList list;
    
    Q_DECLARE_PUBLIC(QchVariantListModel)
};

QchVariantListModel::QchVariantListModel(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new QchVariantListModelPrivate(this))
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "modelData";
    setRoleNames(roles);
}

QchVariantListModel::~QchVariantListModel() {}

QVariant QchVariantListModel::sourceVariant() const {
    Q_D(const QchVariantListModel);
    return d->sourceVariant;
}

void QchVariantListModel::setSourceVariant(const QVariant &variant) {
    Q_D(QchVariantListModel);
    d->setSourceVariant(variant);
}

int QchVariantListModel::rowCount(const QModelIndex &) const {
    Q_D(const QchVariantListModel);
    return d->list.size();
}

QVariant QchVariantListModel::data(const QModelIndex &index, int role) const {
    if ((!index.isValid()) || (role != Qt::UserRole + 1)) {
        return QVariant();
    }
    
    Q_D(const QchVariantListModel);
    return d->list.at(index.row());
}

#include "moc_qchvariantlistmodel.cpp"

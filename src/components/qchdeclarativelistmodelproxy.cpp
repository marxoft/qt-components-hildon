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

#include "qchdeclarativelistmodelproxy.h"
#include <QDeclarativeInfo>
#include <QMetaObject>
#include <QScriptValueIterator>

class QchDeclarativeListModelProxyPrivate
{

public:
    QchDeclarativeListModelProxyPrivate(QchDeclarativeListModelProxy *parent) :
        q_ptr(parent),
        model(0)
    {
    }
    
    void connectSignals() {
        if (!model) {
            return;
        }
        
        Q_Q(QchDeclarativeListModelProxy);
                
        if ((!q->connect(model, SIGNAL(itemsInserted(int, int)), q, SLOT(_q_onItemsInserted(int, int))))
            || (!q->connect(model, SIGNAL(itemsRemoved(int, int)), q, SLOT(_q_onItemsRemoved(int, int))))
            || (!q->connect(model, SIGNAL(itemsMoved(int, int, int)), q, SLOT(_q_onItemsMoved(int, int, int))))
            || (!q->connect(model, SIGNAL(itemsChanged(int, int, QList<int>)), q, SLOT(_q_onItemsChanged(int, int))))) {
            qmlInfo(q) << QchDeclarativeListModelProxy::tr("Source model type is not supported");
        }
    }
    
    void disconnectSignals() {
        if (!model) {
            return;
        }
        
        Q_Q(QchDeclarativeListModelProxy);
        q->disconnect(model, 0, q, 0);
    }
    
    void setRoleNames() {
        if (!model) {
            return;
        }
        
        QScriptValue val;
        QMetaObject::invokeMethod(model, "get", Qt::DirectConnection, Q_RETURN_ARG(QScriptValue, val), Q_ARG(int, 0));
        
        if ((!val.isValid()) || (val.isNull())) {
            return;
        }
        
        Q_Q(QchDeclarativeListModelProxy);
        QHash<int, QByteArray> roles;
        int role = Qt::UserRole + 1;
        QScriptValueIterator iterator(val);
        
        while (iterator.hasNext()) {
            iterator.next();
            roles[role++] = iterator.name().toUtf8();
        }
        
        q->setRoleNames(roles);
        emit q->roleNamesChanged();
    }
    
    void _q_onItemsInserted(int index, int count) {
        Q_Q(QchDeclarativeListModelProxy);
        
        if (q->rowCount() == count) {
            // Set role names when first items are added
            setRoleNames();
        }
        
        q->beginInsertRows(QModelIndex(), index, index + count - 1);
        q->endInsertRows();
    }
    
    void _q_onItemsRemoved(int index, int count) {
        Q_Q(QchDeclarativeListModelProxy);
        q->beginRemoveRows(QModelIndex(), index, index + count - 1);
        q->endRemoveRows();
    }
    
    void _q_onItemsMoved(int from, int to, int count) {
        Q_Q(QchDeclarativeListModelProxy);
        q->beginMoveRows(QModelIndex(), from, from + count - 1, QModelIndex(), to);
        q->endMoveRows();
    }
    
    void _q_onItemsChanged(int index, int count) {
        Q_Q(QchDeclarativeListModelProxy);
        emit q->dataChanged(q->index(index, 0, QModelIndex()), q->index(index + count - 1, 0, QModelIndex()));
    }
    
    QchDeclarativeListModelProxy *q_ptr;
    QObject *model;
    
    Q_DECLARE_PUBLIC(QchDeclarativeListModelProxy)
};

QchDeclarativeListModelProxy::QchDeclarativeListModelProxy(QObject *parent) :
    QAbstractListModel(parent),
    d_ptr(new QchDeclarativeListModelProxyPrivate(this))
{
}

QchDeclarativeListModelProxy::~QchDeclarativeListModelProxy() {}

QObject* QchDeclarativeListModelProxy::sourceModel() const {
    Q_D(const QchDeclarativeListModelProxy);
    return d->model;
}

void QchDeclarativeListModelProxy::setSourceModel(QObject *model) {
    if (model != sourceModel()) {
        Q_D(QchDeclarativeListModelProxy);
        d->disconnectSignals();
        d->model = model;
        d->connectSignals();
        d->setRoleNames();
    }
}

int QchDeclarativeListModelProxy::rowCount(const QModelIndex &) const {
    return sourceModel() ? sourceModel()->property("count").toInt() : 0;
}

QVariant QchDeclarativeListModelProxy::data(const QModelIndex &index, int role) const {
    if ((!index.isValid()) || (!sourceModel())) {
        return QVariant();
    }
    
    QScriptValue val;
    QMetaObject::invokeMethod(sourceModel(), "get", Qt::DirectConnection, Q_RETURN_ARG(QScriptValue, val),
                              Q_ARG(int, index.row()));
    
    if ((!val.isValid()) || (val.isNull())) {
        return QVariant();
    }
    
    return val.property(QString::fromUtf8(roleNames().value(role))).toVariant();
}

#include "moc_qchdeclarativelistmodelproxy.cpp"

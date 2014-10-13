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

#ifndef MODELINDEX_P_H
#define MODELINDEX_P_H

#include <QObject>
#include <QModelIndex>
#include <qdeclarative.h>

/*!
    \class ModelIndex
    \brief Insert description here

    \ingroup org-hildon-components
    \ingroup qml-data-components
*/

class ModelIndex : public QObject
{
    Q_OBJECT

public:
    explicit ModelIndex(QObject *parent = 0) :
        QObject(parent)
    {
    }

    Q_INVOKABLE inline static bool isValid(const QModelIndex &index) {
        return index.isValid();
    }

    Q_INVOKABLE inline static int row(const QModelIndex &index) {
        return index.row();
    }

    Q_INVOKABLE inline static int column(const QModelIndex &index) {
        return index.column();
    }

    Q_INVOKABLE inline static const QAbstractItemModel* model(const QModelIndex &index) {
        return index.model();
    }

    Q_INVOKABLE inline static QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) {
        return index.data(role);
    }

    Q_INVOKABLE inline static QVariant data(const QModelIndex &index, const QByteArray &roleName) {
        if (const QAbstractItemModel *model = index.model()) {
            return index.data(model->roleNames().key(roleName));
        }

        return QVariant();
    }

    Q_INVOKABLE inline static Qt::ItemFlags flags(const QModelIndex &index) {
        return index.flags();
    }

    Q_INVOKABLE inline static QModelIndex parent(const QModelIndex &index) {
        return index.parent();
    }

    Q_INVOKABLE inline static QModelIndex child(const QModelIndex &index, int row, int column) {
        return index.child(row, column);
    }

    Q_INVOKABLE inline static QModelIndex sibling(const QModelIndex &index, int row, int column) {
        return index.sibling(row, column);
    }

private:
    Q_DISABLE_COPY(ModelIndex)
};

QML_DECLARE_TYPE(ModelIndex)
Q_DECLARE_METATYPE(QModelIndex)

#endif // MODELINDEX_P_H

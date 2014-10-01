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

#ifndef LISTMODEL_P_H
#define LISTMODEL_P_H

#include "modelindex_p.h"
#include <QAbstractListModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class ListElement;
class ListModelPrivate;

class ListModel : public QAbstractListModel, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PRIVATE_PROPERTY(ListModel::d_func(), QDeclarativeListProperty<QObject> data READ data)

    Q_INTERFACES(QDeclarativeParserStatus)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ListModel(QObject *parent = 0);
    ~ListModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    
    Q_INVOKABLE QVariant modelIndex(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE QVariant property(const QModelIndex &index, const QString &name) const;

    Q_INVOKABLE void setProperty(const QModelIndex &index, const QString &name, const QVariant &value);

    Q_INVOKABLE ListElement* get(const QModelIndex &index) const;

    Q_INVOKABLE void set(const QModelIndex &index, const QVariantMap &properties);

    Q_INVOKABLE void append(const QVariantMap &properties);

    Q_INVOKABLE void insert(const QModelIndex &index, const QVariantMap &properties);

    Q_INVOKABLE void move(const QModelIndex &fromIndex, const QModelIndex &toIndex, int count);

    Q_INVOKABLE void remove(const QModelIndex &index);

    Q_INVOKABLE void clear();

signals:
    void countChanged();

protected:
    ListModel(ListModelPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<ListModelPrivate> d_ptr;

    Q_DECLARE_PRIVATE(ListModel)

private:
    Q_DISABLE_COPY(ListModel)
};

QML_DECLARE_TYPE(ListModel)

#endif // LISTMODEL_P_H

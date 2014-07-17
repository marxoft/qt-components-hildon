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

#ifndef REPEATER_P_H
#define REPEATER_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>
#include <qdeclarative.h>

class QModelIndex;
class QDeclarativeComponent;
class RepeaterPrivate;

class Repeater : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QDeclarativeComponent* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "delegate")

public:
    explicit Repeater(QObject *parent = 0);
    ~Repeater();

    QVariant model() const;
    void setModel(const QVariant &model);

    QDeclarativeComponent* delegate() const;
    void setDelegate(QDeclarativeComponent *delegate);

    int count() const;

    Q_INVOKABLE QWidget* itemAt(int index) const;

signals:
    void parentChanged();
    void modelChanged();
    void delegateChanged();
    void countChanged();
    void itemAdded(int index, QWidget *item);
    void itemRemoved(int index, QWidget *item);

private:
    Repeater(RepeaterPrivate &dd, QObject *parent = 0);

    void classBegin();
    void componentComplete();

    bool event(QEvent *event);

    QScopedPointer<RepeaterPrivate> d_ptr;

    Q_DISABLE_COPY(Repeater)
    Q_DECLARE_PRIVATE(Repeater)

    Q_PRIVATE_SLOT(d_func(), void _q_onRowsInserted(QModelIndex,int,int))
    Q_PRIVATE_SLOT(d_func(), void _q_onRowsRemoved(QModelIndex,int,int))
    Q_PRIVATE_SLOT(d_func(), void _q_onRowsMoved(QModelIndex,int,int,QModelIndex,int))
    Q_PRIVATE_SLOT(d_func(), void _q_onDataChanged(QModelIndex,QModelIndex))
};

QML_DECLARE_TYPE(Repeater)

#endif // REPEATER_P_H

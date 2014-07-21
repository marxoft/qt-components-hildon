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

#ifndef LISTSELECTOR_P_H
#define LISTSELECTOR_P_H

#include "valueselector_p.h"
#include <QStyledItemDelegate>

class ListSelectorPrivate;

class ListSelector : public ValueSelector
{
    Q_OBJECT

    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int modelColumn READ modelColumn WRITE setModelColumn NOTIFY modelColumnChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)

public:
    explicit ListSelector(QObject *parent = 0);
    ~ListSelector();

    QVariant model() const;
    void setModel(const QVariant &model);

    int modelColumn() const;
    void setModelColumn(int column);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QString currentValueText() const;

signals:
    void modelChanged();
    void modelColumnChanged();
    void currentIndexChanged();
    void selected(const QString &text);

protected:
    ListSelector(ListSelectorPrivate &dd, QObject *parent = 0);

    virtual void componentComplete();

    Q_DECLARE_PRIVATE(ListSelector)

private:
    Q_DISABLE_COPY(ListSelector)
};

class ListPickDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ListPickDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    Q_DISABLE_COPY(ListPickDelegate)
};

QML_DECLARE_TYPE(ListSelector)

#endif // LISTSELECTOR_P_H

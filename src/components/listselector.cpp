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

#include "listselector_p.h"
#include "listselector_p_p.h"
#include "variantlistmodel_p.h"
#include <QMaemo5ListPickSelector>

ListSelector::ListSelector(QObject *parent) :
    ValueSelector(*new ListSelectorPrivate(this), parent)
{
    Q_D(ListSelector);

    d->selector = new QMaemo5ListPickSelector(this);
    this->connect(d->selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

ListSelector::ListSelector(ListSelectorPrivate &dd, QObject *parent) :
    ValueSelector(dd, parent)
{
    Q_D(ListSelector);

    if (!d->selector) {
        d->selector = new QMaemo5ListPickSelector(this);
    }

    this->connect(d->selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

ListSelector::~ListSelector() {}

QVariant ListSelector::model() const {
    Q_D(const ListSelector);

    return d->modelVariant;
}

void ListSelector::setModel(const QVariant &model) {
    Q_D(ListSelector);

    if (model == this->model()) {
        return;
    }

    QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector);

    if (!selector) {
        return;
    }

    VariantListModel *oldModel = d->variantModel;
    d->variantModel = 0;
    d->modelVariant = model;
    QObject *obj = qvariant_cast<QObject*>(model);
    QAbstractItemModel *itemModel = 0;

    if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
        selector->setModel(itemModel);
    }
    else {
        d->variantModel = new VariantListModel(this);
        d->variantModel->setVariant(model);
        selector->setModel(d->variantModel);
        selector->setModelColumn(d->modelColumn);
        selector->setCurrentIndex(d->currentIndex);
    }

    if (oldModel) {
        delete oldModel;
    }
}

int ListSelector::modelColumn() const {
    Q_D(const ListSelector);

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        return selector->modelColumn();
    }
}

void ListSelector::setModelColumn(int column) {
    Q_D(ListSelector);

    d->modelColumn = column;

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        selector->setModelColumn(column);
    }
}

int ListSelector::currentIndex() const {
    Q_D(const ListSelector);

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        return selector->currentIndex();
    }
}

void ListSelector::setCurrentIndex(int index) {
    Q_D(ListSelector);

    d->currentIndex = index;

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        selector->setCurrentIndex(index);
    }
}

QString ListSelector::currentValueText() const {
    Q_D(const ListSelector);

    return d->selector->currentValueText();
}

#include "moc_listselector_p.cpp"

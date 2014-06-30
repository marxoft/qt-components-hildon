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

#include "informationbox_p.h"
#include "informationbox_p_p.h"
#include <QActionGroup>
#include <QEvent>

InformationBox::InformationBox(QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(new InformationBoxPrivate(this))
{
    Item *item = new Item(this);
    item->setMinimumHeight(30);
    this->setWidget(item);
}

InformationBox::InformationBox(InformationBoxPrivate &dd, QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(&dd)
{
    Item *item = new Item(this);
    item->setMinimumHeight(30);
    this->setWidget(item);
}

InformationBox::~InformationBox() {}

void InformationBox::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMaemo5InformationBox::changeEvent(event);
}

void InformationBox::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QMaemo5InformationBox::showEvent(event);
}

void InformationBox::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QMaemo5InformationBox::hideEvent(event);
}

void InformationBox::classBegin() {}

void InformationBox::componentComplete() {
    Q_D(InformationBox);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Dialog);
    }
}

void InformationBoxPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->dataList.append(obj);
    }
}

void InformationBoxPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->actionList.append(obj);

        if (!box->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            box->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            box->addActions(group->actions());
        }
    }
}

void InformationBoxPrivate::content_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (InformationBox *box = qobject_cast<InformationBox*>(list->object)) {
        box->d_func()->contentList.append(obj);
        obj->setParent(box->widget());
    }
}

QDeclarativeListProperty<QObject> InformationBoxPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, InformationBoxPrivate::data_append);
}

QDeclarativeListProperty<QObject> InformationBoxPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, InformationBoxPrivate::actions_append);
}

QDeclarativeListProperty<QObject> InformationBoxPrivate::content() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, InformationBoxPrivate::content_append);
}

#include "moc_informationbox_p.cpp"

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

#include "actiongroup_p.h"
#include "actiongroup_p_p.h"

ActionGroup::ActionGroup(QObject *parent) :
    QActionGroup(parent),
    d_ptr(new ActionGroupPrivate(this))
{
}

ActionGroup::ActionGroup(ActionGroupPrivate &dd, QObject *parent) :
    QActionGroup(parent),
    d_ptr(&dd)
{
}

ActionGroup::~ActionGroup() {}

void ActionGroup::classBegin() {}

void ActionGroup::componentComplete() {
    Q_D(ActionGroup);

    d->componentComplete();
}

void ActionGroupPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (ActionGroup *group = qobject_cast<ActionGroup*>(list->object)) {
        group->d_func()->dataList.append(obj);

        if (!group->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            group->addAction(action);
        }
    }
}

QDeclarativeListProperty<QObject> ActionGroupPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, ActionGroupPrivate::data_append);
}

void ActionGroupPrivate::componentComplete() {
    Q_Q(ActionGroup);

    complete = true;

    foreach (QObject *obj, dataList) {
        if (QAction *action = qobject_cast<QAction*>(obj)) {
            q->addAction(action);
        }
    }
}

#include "moc_actiongroup_p.cpp"

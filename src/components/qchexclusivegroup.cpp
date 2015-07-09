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

#include "qchexclusivegroup.h"
#include "qchmenuitem.h"

class QchExclusiveGroupPrivate
{

public:
    QchExclusiveGroupPrivate(QchExclusiveGroup *parent) :
        q_ptr(parent)
    {
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchExclusiveGroup *group = qobject_cast<QchExclusiveGroup*>(list->object)) {
            obj->setParent(obj);
            
            if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
                item->setCheckable(true);
                group->addAction(item->toQAction());
            }
            else if (QAction *action = qobject_cast<QAction*>(obj)) {
                action->setCheckable(true);
                group->addAction(action);
            }
        }
    }
    
    QchExclusiveGroup *q_ptr;
    
    Q_DECLARE_PUBLIC(QchExclusiveGroup)
};

QchExclusiveGroup::QchExclusiveGroup(QObject *parent) :
    QActionGroup(parent),
    d_ptr(new QchExclusiveGroupPrivate(this))
{
    setExclusive(true);
    connect(this, SIGNAL(triggered(QAction*)), this, SIGNAL(currentChanged()));
}

QchExclusiveGroup::~QchExclusiveGroup() {}

QDeclarativeListProperty<QObject> QchExclusiveGroup::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchExclusiveGroupPrivate::data_append);
}

#include "moc_qchexclusivegroup.cpp"

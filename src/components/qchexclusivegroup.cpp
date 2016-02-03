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

#include "qchexclusivegroup.h"
#include <QDeclarativeInfo>

#define CHECKED_PROPERTY "checked"

static bool isChecked(const QObject *obj) {
    if (!obj) {
        return false;
    }
    
    const QVariant checked = obj->property(CHECKED_PROPERTY).toBool();
    return (checked.isValid()) && (checked.toBool());
}

class QchExclusiveGroupPrivate
{

public:
    QchExclusiveGroupPrivate(QchExclusiveGroup *parent) :
        q_ptr(parent),
        current(0)
    {
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }
        
        if (QchExclusiveGroup *group = qobject_cast<QchExclusiveGroup*>(list->object)) {
            obj->setParent(group);
            group->addCheckable(obj);
        }
    }
    
    void _q_updateCurrent() {
        Q_Q(QchExclusiveGroup);
        QObject *object = q->sender();
        
        if (isChecked(object)) {
            q->setCurrent(object);
        }
    }
    
    QchExclusiveGroup *q_ptr;
    
    QObject* current;
                
    Q_DECLARE_PUBLIC(QchExclusiveGroup)
};

/*!
    \class ExclusiveGroup
    \brief Automatically updates the checked status of checkable items.
    
    \snippet actions.qml ExclusiveGroup
    
    \ingroup components
    
    \sa AbstractButton, Action, MenuItem
*/
QchExclusiveGroup::QchExclusiveGroup(QObject *parent) :
    QObject(parent),
    d_ptr(new QchExclusiveGroupPrivate(this))
{
}

QchExclusiveGroup::~QchExclusiveGroup() {}

/*!
    \brief The currently checked item.
    
    The default value is \c null.
*/
QObject* QchExclusiveGroup::current() const {
    Q_D(const QchExclusiveGroup);
    return d->current;
}

void QchExclusiveGroup::setCurrent(QObject *obj) {    
    if (obj != current()) {
        Q_D(QchExclusiveGroup);
        
        if (d->current) {
            d->current->setProperty(CHECKED_PROPERTY, false);
        }
        
        d->current = obj;
        
        if (obj) {
            obj->setProperty(CHECKED_PROPERTY, true);
        }
        
        emit currentChanged();
    }
}

/*!
    \brief The children of the group.
*/
QDeclarativeListProperty<QObject> QchExclusiveGroup::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchExclusiveGroupPrivate::data_append);
}

/*!
    \brief Adds a checkable item to the group.
*/
void QchExclusiveGroup::addCheckable(QObject *obj) {
    if (!obj) {
        return;
    }
        
    if (connect(obj, SIGNAL(toggled(bool)), this, SLOT(_q_updateCurrent()), Qt::UniqueConnection)) {
        connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(removeCheckable(QObject*)), Qt::UniqueConnection);

        if (isChecked(obj)) {
            setCurrent(obj);
        }
    } 
    else {
        qmlInfo(this) << "The object has no toggled() signal.";
    }
}

/*!
    \brief Removes an existing item from the group.
*/
void QchExclusiveGroup::removeCheckable(QObject *obj) {
    if (!obj) {
        return;
    }
        
    if (disconnect(obj, SIGNAL(toggled(bool)), this, SLOT(_q_updateCurrent()))) {
        disconnect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(removeCheckable(QObject*)));
    }
    
    if (obj == current()) {
        setCurrent(0);
    }
}

#include "moc_qchexclusivegroup.cpp"

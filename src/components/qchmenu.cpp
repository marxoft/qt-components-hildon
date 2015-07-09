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

#include "qchmenu.h"
#include "qchmenuitem.h"
#include <QCursor>

class QchMenuPrivate
{

public:
    QchMenuPrivate(QchMenu *parent) :
        q_ptr(parent)
    {
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchMenu *menu = qobject_cast<QchMenu*>(list->object)) {
            obj->setParent(obj);
            
            if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
                menu->addAction(item->toQAction());
            }
            else if (QAction *action = qobject_cast<QAction*>(obj)) {
                menu->addAction(action);
            }
            else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
                menu->addActions(group->actions());
            }
        }
    }
        
    QchMenu *q_ptr;
    
    Q_DECLARE_PUBLIC(QchMenu)
};

QchMenu::QchMenu(QWidget *parent) :
    QMenu(parent),
    d_ptr(new QchMenuPrivate(this))
{
}

QchMenu::~QchMenu() {}

QDeclarativeListProperty<QObject> QchMenu::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuPrivate::data_append);
}

void QchMenu::popup() {
    QMenu::popup(QCursor::pos());
}

#include "moc_qchmenu.cpp"

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
#include <QMenu>
#include <QCursor>

class QchMenuPrivate
{

public:
    QchMenuPrivate(QchMenu *parent) :
        q_ptr(parent),
        menu(0),
        complete(false)
    {
    }
    
    QWidget *findParentWidget() const {
        Q_Q(const QchMenu);
        QObject *p = q->parent();
        
        while (p) {
            if (p->isWidgetType()) {
                return qobject_cast<QWidget*>(p);
            }
            
            p = p->parent();
        }
        
        return 0;
    }
    
    void init() {
        complete = true;
        menu = new QMenu(findParentWidget());
        Q_Q(const QchMenu);
        
        const QObjectList list = q->children();
        
        for (int i = 0; i < list.size(); i++) {
            addAction(list.at(i));
        }
    }
    
    void addAction(QObject *obj) {
        if (!menu) {
            return;
        }
          
        if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
            if (QAction *action = item->toQAction()) {
                menu->addAction(action);
            }
        }
        else if (QAction *action = qobject_cast<QAction*>(obj)) {
            menu->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            menu->addActions(group->actions());
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchMenu *menu = qobject_cast<QchMenu*>(list->object)) {
            obj->setParent(menu);
            
            if (menu->d_func()->complete) {
                menu->d_func()->addAction(obj);
            }
        }
    }
        
    QchMenu *q_ptr;
    QMenu *menu;
    
    bool complete;
    
    Q_DECLARE_PUBLIC(QchMenu)
};

QchMenu::QchMenu(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuPrivate(this))
{
}

QchMenu::~QchMenu() {
    Q_D(QchMenu);
    
    if (d->menu) {
        delete d->menu;
        d->menu = 0;
    }
}

QDeclarativeListProperty<QObject> QchMenu::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuPrivate::data_append);
}

void QchMenu::popup() {
    Q_D(QchMenu);
    
    if (d->menu) {
        d->menu->popup(QCursor::pos());
    }
}

void QchMenu::classBegin() {}

void QchMenu::componentComplete() {
    Q_D(QchMenu);
    d->init();
}

#include "moc_qchmenu.cpp"

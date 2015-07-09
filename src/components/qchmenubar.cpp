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

#include "qchmenubar.h"
#include "qchmenuitem.h"
#include <QMainWindow>
#include <QMenuBar>

class QchMenuBarPrivate
{

public:
    QchMenuBarPrivate(QchMenuBar *parent) :
        q_ptr(parent)
    {
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchMenuBar *menu = qobject_cast<QchMenuBar*>(list->object)) {
            obj->setParent(obj);
            
            QObject *p = menu->parent();
            
            while (p) {
                if (QMainWindow *window = qobject_cast<QMainWindow*>(p)) {
                    if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
                        window->menuBar()->addAction(item->toQAction());
                    }
                    else if (QAction *action = qobject_cast<QAction*>(obj)) {
                        window->menuBar()->addAction(action);
                    }
                    else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
                        window->menuBar()->addActions(group->actions());
                    }
                    
                    return;
                }
                
                p = p->parent();
            }
        }
    }
        
    QchMenuBar *q_ptr;
    
    Q_DECLARE_PUBLIC(QchMenuBar)
};

QchMenuBar::QchMenuBar(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuBarPrivate(this))
{
}

QchMenuBar::~QchMenuBar() {}

QDeclarativeListProperty<QObject> QchMenuBar::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuBarPrivate::data_append);
}

#include "moc_qchmenubar.cpp"

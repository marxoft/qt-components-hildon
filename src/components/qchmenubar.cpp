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
        q_ptr(parent),
        menuBar(0)
    {
    }
    
    QMenuBar* findMenuBar() const {
        Q_Q(const QchMenuBar);
        
        QObject *p = q->parent();
        
        while (p) {
            if (QMainWindow *window = qobject_cast<QMainWindow*>(p)) {
                return window->menuBar();
            }
            
            p = p->parent();
        }
        
        return 0;
    }
    
    void init() {
        menuBar = findMenuBar();
        
        if (menuBar) {
            Q_Q(const QchMenuBar);
            
            const QObjectList list = q->children();
            
            for (int i = 0; i < list.size(); i++) {
                addAction(list.at(i));
            }
        }
    }
    
    void addAction(QObject *obj) {
        if (!menuBar) {
            return;
        }
                
        if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
            if (QAction *action = item->toQAction()) {
                menuBar->addAction(action);
            }
        }
        else if (QAction *action = qobject_cast<QAction*>(obj)) {
            menuBar->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            menuBar->addActions(group->actions());
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchMenuBar *menu = qobject_cast<QchMenuBar*>(list->object)) {
            obj->setParent(menu);
            
            if (menu->d_func()->menuBar) {
                menu->d_func()->addAction(obj);
            }
        }
    }
        
    QchMenuBar *q_ptr;
    QMenuBar *menuBar;
    
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

void QchMenuBar::classBegin() {}

void QchMenuBar::componentComplete() {
    Q_D(QchMenuBar);
    d->init();
}

#include "moc_qchmenubar.cpp"

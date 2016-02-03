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

#include "qchmenubar.h"
#include "qchmenuitem.h"
#include <QActionGroup>
#include <QDeclarativeInfo>
#include <QMainWindow>
#include <QMenuBar>

class QchMenuBarPrivate
{

public:
    QchMenuBarPrivate(QchMenuBar *parent) :
        q_ptr(parent),
        menuBar(0),
        filterGroup(0),
        filtersExclusive(true)
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
        if (menuBar) {
            return;
        }
        
        Q_Q(QchMenuBar);
        menuBar = findMenuBar();
        
        if (menuBar) {
            filterGroup = new QActionGroup(q);
            filterGroup->setExclusive(filtersExclusive);
            
            for (int i = 0; i < filters.size(); i++) {
                filterGroup->addAction(filters.at(i)->toQAction());
                menuBar->addAction(filters.at(i)->toQAction());
            }
            
            for (int i = 0; i < items.size(); i++) {
                menuBar->addAction(items.at(i)->toQAction());
            }
        }
        else {
            qmlInfo(q) << QchMenuBar::tr("No QMenuBar instance found.");
        }
    }
        
    static void filters_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }
        
        if (QchMenuBar *menu = qobject_cast<QchMenuBar*>(list->object)) {            
            if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {            
                item->setParent(menu);
                item->setCheckable(true);
                menu->d_func()->filters << item;
                menu->connect(item, SIGNAL(destroyed(QObject*)), menu, SLOT(removeItem(QObject*)));
                
                if (menu->d_func()->filterGroup) {
                    menu->d_func()->filterGroup->addAction(item->toQAction());
                    
                    if (menu->d_func()->menuBar) {
                        menu->d_func()->menuBar->addAction(item->toQAction());
                    }
                }
            }
            else {
                qmlInfo(menu) << QchMenuBar::tr("Children of MenuBar must be of type MenuItem.");
            }
        }
    }
    
    static void items_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }
        
        if (QchMenuBar *menu = qobject_cast<QchMenuBar*>(list->object)) {
            if (QchMenuItem *item = qobject_cast<QchMenuItem*>(obj)) {
                item->setParent(menu);
                menu->d_func()->items << item;
                menu->connect(item, SIGNAL(destroyed(QObject*)), menu, SLOT(removeItem(QObject*)));
                
                if (menu->d_func()->menuBar) {
                    menu->d_func()->menuBar->addAction(item->toQAction());
                }
            }
            else {
                qmlInfo(menu) << QchMenuBar::tr("Children of MenuBar must be of type MenuItem.");
            }
        }
    }
        
    QchMenuBar *q_ptr;
    QMenuBar *menuBar;
    QActionGroup *filterGroup;
    
    bool filtersExclusive;
    
    QList<QchMenuItem*> filters;
    QList<QchMenuItem*> items;
    
    Q_DECLARE_PUBLIC(QchMenuBar)
};

/*!
    \class MenuBar
    \brief A container for menu items in a Window.
    
    \ingroup components
    
    The MenuBar component is used as a container for adding menu items to a Window.
    
    \snippet menus.qml MenuBar
    
    \sa MenuItem, Window
*/
QchMenuBar::QchMenuBar(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuBarPrivate(this))
{
}

QchMenuBar::~QchMenuBar() {}

/*!
    \brief Whether enabling a filter disables the remaining filters.
    
    The default value is \c true.
*/
bool QchMenuBar::filtersExclusive() const {
    Q_D(const QchMenuBar);
    return d->filtersExclusive;
}

void QchMenuBar::setFiltersExclusive(bool exclusive) {
    if (exclusive != filtersExclusive()) {
        Q_D(QchMenuBar);
        d->filtersExclusive = exclusive;
        
        if (d->filterGroup) {
            d->filterGroup->setExclusive(exclusive);
        }
        
        emit filtersExclusiveChanged();
    }
}

/*!
    \brief The filters of the menu bar.
*/
QDeclarativeListProperty<QObject> QchMenuBar::filters() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuBarPrivate::filters_append);
}

/*!
    \brief The items of the menu bar.
*/
QDeclarativeListProperty<QObject> QchMenuBar::items() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuBarPrivate::items_append);
}

/*!
    \brief Adds a MenuItem filter with \a text and returns it.
*/
QchMenuItem* QchMenuBar::addFilter(const QString &text) {
    Q_D(QchMenuBar);
    QchMenuItem* item = new QchMenuItem(this);
    item->setText(text);
    item->setCheckable(true);
    
    if (!d->menuBar) {
        d->init();
    }
    
    d->filters << item;
    d->filterGroup->addAction(item->toQAction());
    d->menuBar->addAction(item->toQAction());
    connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    return item;
}

/*!
    \brief Inserts a MenuItem filter with \a text before the item at index \a before and returns it.
*/
QchMenuItem* QchMenuBar::insertFilter(int before, const QString &text) {
    Q_D(QchMenuBar);
    
    if (!d->menuBar) {
        d->init();
    }
    
    
    if ((before >= 0) && (before < d->filters.size())) {
        QchMenuItem* item = new QchMenuItem(this);
        item->setText(text);
        item->setCheckable(true);
        d->filterGroup->addAction(item->toQAction());
        d->menuBar->insertAction(d->filters.at(before)->toQAction(), item->toQAction());
        d->filters.insert(before, item);
        connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
        return item;
    }
    
    return addItem(text);
}

/*!
    \brief Adds a MenuItem with \a text and returns it.
*/
QchMenuItem* QchMenuBar::addItem(const QString &text) {
    Q_D(QchMenuBar);
    QchMenuItem* item = new QchMenuItem(this);
    item->setText(text);
    
    if (!d->menuBar) {
        d->init();
    }
    
    d->items << item;
    d->menuBar->addAction(item->toQAction());
    connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    return item;
}

/*!
    \brief Inserts a MenuItem with \a text before the item at index \a before and returns it.
*/
QchMenuItem* QchMenuBar::insertItem(int before, const QString &text) {
    Q_D(QchMenuBar);
    
    if (!d->menuBar) {
        d->init();
    }
        
    if ((before >= 0) && (before < d->items.size())) {
        QchMenuItem* item = new QchMenuItem(this);
        item->setText(text);
        d->menuBar->insertAction(d->items.at(before)->toQAction(), item->toQAction());
        d->items.insert(before, item);
        connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
        return item;
    }
    
    return addItem(text);
}

/*!
    \brief Removes the \a item from the menu.
*/
void QchMenuBar::removeItem(QObject *item) {
    if ((!item) || (item->parent() != this)) {
        qmlInfo(this) << tr("Item not found in this menu bar.");
        return;
    }
    
    if (QchMenuItem *menuItem = qobject_cast<QchMenuItem*>(item)) {
        Q_D(QchMenuBar);
        d->filters.removeOne(menuItem);
        d->items.removeOne(menuItem);
        d->filterGroup->removeAction(menuItem->toQAction());
        d->menuBar->removeAction(menuItem->toQAction());
        disconnect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    }
    else {
        qmlInfo(this) << tr("Item not found in this menu bar.");
    }
} 

void QchMenuBar::classBegin() {}

void QchMenuBar::componentComplete() {
    Q_D(QchMenuBar);
    d->init();
}

#include "moc_qchmenubar.cpp"

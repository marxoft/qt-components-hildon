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

#include "qchmenu.h"
#include "qchmenuitem.h"
#include <QDeclarativeInfo>
#include <QMenu>
#include <QCursor>
#include <QEvent>

class QchMenuPrivate
{

public:
    QchMenuPrivate(QchMenu *parent) :
        q_ptr(parent),
        menu(0),
        enabled(true),
        visible(true),
        submenu(false),
        complete(false)
    {
    }
    
    ~QchMenuPrivate() {
        if (menu) {
            delete menu;
            menu = 0;
        }
    }
    
    void init() {
        if (complete) {
            return;
        }
        
        complete = true;
        menu = new QMenu;
        menu->setEnabled(enabled);
        menu->setTitle(title);        
        
        if (!iconSource.isEmpty()) {
            menu->setIcon(QIcon(iconSource));
        }
        else if (!iconName.isEmpty()) {
            menu->setIcon(QIcon::fromTheme(iconName));
        }
        
        if ((!visible) || (submenu)) {
            menu->setVisible(visible);
        }
                
        Q_Q(QchMenu);
        
        const QObjectList list = q->children();
        
        for (int i = 0; i < list.size(); i++) {
            addItem(list.at(i));
        }
        
        q->connect(menu, SIGNAL(aboutToHide()), q, SIGNAL(aboutToHide()));
        q->connect(menu, SIGNAL(aboutToShow()), q, SIGNAL(aboutToShow()));
    }
    
    void addItem(QObject *obj) {
        if (!menu) {
            return;
        }
        
        Q_Q(QchMenu);
                  
        if (QchMenuItem *i = qobject_cast<QchMenuItem*>(obj)) {
            menu->addAction(i->toQAction());
            q->connect(i, SIGNAL(destroyed(QObject*)), q, SLOT(removeItem(QObject*)));
        }
        else if (QchMenu *m = qobject_cast<QchMenu*>(obj)) {
            m->d_func()->submenu = true;
            menu->addMenu(m->d_func()->menu);
            q->connect(m, SIGNAL(destroyed(QObject*)), q, SLOT(removeItem(QObject*)));
        }
        else {
            qmlInfo(q) << QchMenu::tr("Children of Menu must be of type MenuItem or Menu.");
        }
    }
    
    static void items_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }
        
        if (QchMenu *menu = qobject_cast<QchMenu*>(list->object)) {
            obj->setParent(menu);
            
            if (menu->d_func()->complete) {
                menu->d_func()->addItem(obj);
            }
        }
    }
        
    QchMenu *q_ptr;
    QMenu *menu;
    
    bool enabled;
    bool visible;
    bool submenu;
    bool complete;
    
    QString iconName;
    QString iconSource;
    QString title;    
    
    Q_DECLARE_PUBLIC(QchMenu)
};

/*!
    \class Menu
    \brief A popup menu.
    
    \ingroup components
    
    The Menu component is used to display a popup context menu.
    
    \snippet menus.qml Menu
    
    \sa MenuItem
*/
QchMenu::QchMenu(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuPrivate(this))
{
}

QchMenu::~QchMenu() {}

/*!
    \property bool Menu::enabled
    \brief Whether the menu is enabled.
    
    The default value is \c true.
*/
bool QchMenu::isEnabled() const {
    Q_D(const QchMenu);
    return d->enabled;
}

void QchMenu::setEnabled(bool e) {
    if (e != isEnabled()) {
        Q_D(QchMenu);
        d->enabled = e;
        
        if (d->menu) {
            d->menu->setEnabled(e);
        }
        
        emit enabledChanged();        
    }
}

/*!
    \brief The name of the icon to be used.
    
    \sa iconSource
*/
QString QchMenu::iconName() const {
    Q_D(const QchMenu);
    return d->iconName;
}

void QchMenu::setIconName(const QString &name) {
    if (name != iconName()) {
        Q_D(QchMenu);
        d->iconName = name;
        
        if (d->menu) {
            d->menu->setIcon(QIcon::fromTheme(name));
        }
        
        emit iconChanged();
    }
}

/*!
    \brief The source of the icon to be used.
    
    \sa iconName
*/
QString QchMenu::iconSource() const { 
    Q_D(const QchMenu);
    return d->iconSource;
}

void QchMenu::setIconSource(const QString &source) {
    if (source != iconSource()) {
        Q_D(QchMenu);
        d->iconSource = source;
        
        if (d->menu) {
            d->menu->setIcon(QIcon(source));
        }
        
        emit iconChanged();
    }
}


/*!
    \brief The items of the menu.
*/
QDeclarativeListProperty<QObject> QchMenu::items() {
    return QDeclarativeListProperty<QObject>(this, 0, QchMenuPrivate::items_append);
}

/*!
    \brief The display title of the menu.
*/
QString QchMenu::title() const {
    Q_D(const QchMenu);
    return d->title;
}

void QchMenu::setTitle(const QString &t) {
    if (t != title()) {
        Q_D(QchMenu);
        d->title = t;
        
        if (d->menu) {
            d->menu->setTitle(t);
        }
        
        emit titleChanged();
    }
}

/*!
    \property bool Menu::visible
    \brief Whether the menu should be visible as a submenu of another Menu.
    
    The default value is \c true.
*/
bool QchMenu::isVisible() const {
    Q_D(const QchMenu);
    return d->visible;
}

void QchMenu::setVisible(bool v) {
    if (v != isVisible()) {
        Q_D(QchMenu);
        d->visible = v;
        
        if ((d->menu) && (d->submenu)) {
            d->menu->setVisible(v);
        }
        
        emit visibleChanged();
    }
}

/*!
    \brief Adds a MenuItem with \a text and returns it.
*/
QchMenuItem* QchMenu::addItem(const QString &text) {
    Q_D(QchMenu);
    QchMenuItem* item = new QchMenuItem(this);
    item->setText(text);
    
    if (!d->menu) {
        d->init();
    }
    
    d->menu->addAction(item->toQAction());
    connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    return item;
}

/*!
    \brief Inserts a MenuItem with \a text before the item at index \a before and returns it.
*/
QchMenuItem* QchMenu::insertItem(int before, const QString &text) {
    Q_D(QchMenu);
    
    if (!d->menu) {
        d->init();
    }
    
    const QList<QAction*> actions = d->menu->actions();
    
    if ((before >= 0) && (before < actions.size())) {
        QchMenuItem* item = new QchMenuItem(this);
        item->setText(text);
        d->menu->insertAction(actions.at(before), item->toQAction());
        connect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
        return item;
    }
    
    return addItem(text);
}

/*!
    \brief Adds a Menu with \a title and returns it.
*/
QchMenu* QchMenu::addMenu(const QString &title) {
    Q_D(QchMenu);
    QchMenu *menu = new QchMenu(this);
    menu->setTitle(title);
    menu->d_func()->submenu = true;
    menu->d_func()->init();
    
    if (!d->menu) {
        d->init();
    }
    
    d->menu->addMenu(menu->d_func()->menu);
    connect(menu, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    return menu;
}


/*!
    \brief Inserts a Menu with \a title before the item at index \a before and returns it.
*/
QchMenu* QchMenu::insertMenu(int before, const QString &title) {
    Q_D(QchMenu);
    
    if (!d->menu) {
        d->init();
    }
    
    const QList<QAction*> actions = d->menu->actions();
    
    if ((before >= 0) && (before < actions.size())) {
        QchMenu *menu = new QchMenu(this);
        menu->setTitle(title);
        menu->d_func()->submenu = true;
        menu->d_func()->init();
        d->menu->insertMenu(actions.at(before), menu->d_func()->menu);
        connect(menu, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
        return menu;
    }
    
    return addMenu(title);
}

/*!
    \brief Removes the \a item from the menu.
*/
void QchMenu::removeItem(QObject *item) {
    if ((!item) || (item->parent() != this)) {
        qmlInfo(this) << tr("Item not found in this menu.");
        return;
    }
    
    Q_D(QchMenu);
    QAction *action = 0;
    
    if (QchMenuItem *menuItem = qobject_cast<QchMenuItem*>(item)) {
        action = menuItem->toQAction();
    }
    else if (QchMenu *menu = qobject_cast<QchMenu*>(item)) {
        menu->d_func()->submenu = false;
        action = menu->d_func()->menu->menuAction();
    }
    
    if (action) {
        d->menu->removeAction(action);
        disconnect(item, SIGNAL(destroyed(QObject*)), this, SLOT(removeItem(QObject*)));
    }
}    

/*!
    \brief Displays the menu at the current cursor position.
*/
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

bool QchMenu::event(QEvent *e) {    
    if (e->type() == QEvent::ParentChange) {
        emit parentChanged();
    }
    
    return QObject::event(e);
}

/*!
    \fn void Menu::aboutToHide()
    \brief Emitted when the menu is about to be hidden.
    
    \sa aboutToShow()
*/

/*!
    \fn void Menu::aboutToShow()
    \brief Emitted when the menu is about to be displayed.
    
    \sa aboutToHide()
*/

#include "moc_qchmenu.cpp"

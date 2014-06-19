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

#include "menu_p.h"
#include "menu_p_p.h"
#include "separator_p.h"
#include <QActionGroup>
#include <QEvent>

Menu::Menu(QWidget *parent) :
    QMenu(parent),
    d_ptr(new MenuPrivate(this))
{
}

Menu::Menu(MenuPrivate &dd, QWidget *parent) :
    QMenu(parent),
    d_ptr(&dd)
{
}

Menu::~Menu() {}

void Menu::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Menu::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

QString Menu::iconSource() const {
    return this->icon().name();
}

void Menu::setIconSource(const QString &source) {
    if (source != this->iconSource()) {
        this->setIcon(QIcon(source));
    }
}

void Menu::open(const QPoint &pos) {
    this->popup(pos);
}

void Menu::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMenu::changeEvent(event);
}

void Menu::classBegin() {}

void Menu::componentComplete() {
    Q_D(Menu);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Popup);
    }
}

void MenuPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Menu *menu = qobject_cast<Menu*>(list->object)) {
        menu->d_func()->dataList.append(obj);

        if (!menu->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            menu->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            menu->addActions(group->actions());
        }
        else if (qobject_cast<Separator*>(obj)) {
            menu->addSeparator();
        }
    }
}

QDeclarativeListProperty<QObject> MenuPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, MenuPrivate::data_append);
}

void MenuPrivate::componentComplete() {
    Q_Q(Menu);

    complete = true;

    foreach (QObject *obj, dataList) {
        if (QAction *action = qobject_cast<QAction*>(obj)) {
            q->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            q->addActions(group->actions());
        }
        else if (qobject_cast<Separator*>(obj)) {
            q->addSeparator();
        }
    }
}

#include "moc_menu_p.cpp"

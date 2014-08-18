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

#include "itemaction_p.h"
#include <QAbstractButton>
#include <QEvent>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeInfo>

class ItemActionPrivate {

public:
    ItemActionPrivate(ItemAction *parent) :
        q_ptr(parent),
        item(0)
    {
    }

    ItemAction *q_ptr;

    QDeclarativeComponent *item;

    Q_DECLARE_PUBLIC(ItemAction)
};

ItemAction::ItemAction(QObject *parent) :
    QWidgetAction(parent),
    d_ptr(new ItemActionPrivate(this))
{
}

ItemAction::ItemAction(ItemActionPrivate &dd, QObject *parent) :
    QWidgetAction(parent),
    d_ptr(&dd)
{
}

ItemAction::~ItemAction() {}

QString ItemAction::iconSource() const {
    return this->icon().name();
}

void ItemAction::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
        emit iconChanged();
    }
}

QString ItemAction::shortcutString() const {
    return this->shortcut().toString();
}

void ItemAction::setShortcutString(const QString &shortcut) {
    if (shortcut != this->shortcutString()) {
        this->setShortcut(QKeySequence(shortcut));
        emit shortcutChanged();
    }
}

QDeclarativeComponent* ItemAction::item() const {
    Q_D(const ItemAction);

    return d->item;
}

void ItemAction::setItem(QDeclarativeComponent *item) {
    Q_D(ItemAction);

    if (item != d->item) {
        QDeclarativeComponent *oldItem = d->item;
        d->item = item;

        if (d->item) {
            d->item->setParent(this);
        }

        if (oldItem) {
            delete oldItem;
        }

        emit itemChanged();
    }
}

QWidget* ItemAction::createWidget(QWidget *parent) {
    Q_D(ItemAction);

    if (!d->item) {
        qmlInfo(this) << tr("'item' property not set");
        return 0;
    }

    QDeclarativeContext *creationContext = d->item->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->item->beginCreate(context)) {
        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            widget->setParent(parent);
            context->setParent(widget);
            d->item->completeCreate();

            // Hotfix. For some reason, QMaemo5ApplicationMenu is not closing when a button widget is clicked.
            if (QAbstractButton *button = qobject_cast<QAbstractButton*>(widget)) {
                if (parent) {
                    this->connect(button, SIGNAL(clicked()), parent, SLOT(close()));
                }
            }

            return widget;
        }

        qmlInfo(this) << tr("'item' property must be a visual item");
        delete obj;
        delete context;
    }
    else {
        delete context;
    }

    return 0;
}

bool ItemAction::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    return QWidgetAction::event(event);
}

#include "moc_itemaction_p.cpp"

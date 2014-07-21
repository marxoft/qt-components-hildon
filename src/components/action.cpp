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

#include "action_p.h"
#include <QEvent>

Action::Action(QObject *parent) :
    QAction(parent)
{
}

Action::~Action() {}

QString Action::iconSource() const {
    return this->icon().name();
}

void Action::setIconSource(const QString &source) {
    if (source != this->icon().name()) {
        this->setIcon(source.contains('/') ? QIcon(source) : QIcon::fromTheme(source));
        emit iconChanged();
    }
}

QString Action::shortcutString() const {
    return this->shortcut().toString();
}

void Action::setShortcutString(const QString &shortcut) {
    if (shortcut != this->shortcutString()) {
        this->setShortcut(QKeySequence(shortcut));
        emit shortcutChanged();
    }
}

bool Action::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    return QAction::event(event);
}

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

#include "screen_p.h"
#include "screen_p_p.h"
#include <QDBusConnection>
#include <QApplication>
#include <QDesktopWidget>

Screen* Screen::self = 0;

Screen::Screen(QObject *parent) :
    QObject(parent),
    d_ptr(new ScreenPrivate(this))
{
    if (!self) {
        self = this;
    }

    this->connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(_q_onResized()));

    QDBusConnection::systemBus().connect("",
                                         "/com/nokia/mce/signal",
                                         "com.nokia.mce.signal",
                                         "tklock_mode_ind",
                                         this,
                                         SLOT(_q_onLockStateChanged(QString)));
}

Screen::Screen(ScreenPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (!self) {
        self = this;
    }

    this->connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(_q_onResized()));

    QDBusConnection::systemBus().connect("",
                                         "/com/nokia/mce/signal",
                                         "com.nokia.mce.signal",
                                         "tklock_mode_ind",
                                         this,
                                         SLOT(_q_onLockStateChanged(QString)));
}

Screen::~Screen() {}

Screen* Screen::instance() {
    return !self ? new Screen : self;
}

int Screen::width() const {
    return QApplication::desktop()->screenGeometry().width();
}

int Screen::height() const {
    return QApplication::desktop()->screenGeometry().height();
}

Screen::Orientation Screen::orientationLock() const {
    Q_D(const Screen);

    return d->orientationLock;
}

void Screen::setOrientationLock(Orientation lock) {
    if (lock != this->orientationLock()) {
        Q_D(Screen);
        d->orientationLock = lock;
        emit orientationLockChanged(lock);
    }
}

Screen::Orientation Screen::currentOrientation() const {
    Q_D(const Screen);

    return d->currentOrientation;
}

bool Screen::covered() const {
    Q_D(const Screen);

    return d->covered;
}

void ScreenPrivate::_q_onResized() {
    Q_Q(Screen);

    QRect geometry = QApplication::desktop()->screenGeometry();

    if (geometry.height() > geometry.width()) {
        currentOrientation = Screen::PortraitOrientation;
    }
    else {
        currentOrientation = Screen::LandscapeOrientation;
    }

    emit q->widthChanged(geometry.width());
    emit q->heightChanged(geometry.height());
    emit q->currentOrientationChanged(currentOrientation);
}

void ScreenPrivate::_q_onLockStateChanged(const QString &state) {
    Q_Q(Screen);

    if (state == "locked") {
        covered = true;
        emit q->coveredChanged(true);
    }
    else if (state == "unlocked") {
        covered = false;
        emit q->coveredChanged(false);
    }
}

#include "moc_screen_p.cpp"

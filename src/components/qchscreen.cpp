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

#include "qchscreen.h"
#include <QDBusConnection>
#include <QApplication>
#include <QDesktopWidget>

class QchScreenPrivate
{

public:
    QchScreenPrivate(QchScreen *parent) :
        q_ptr(parent),
        orientationLock(Qt::WA_Maemo5LandscapeOrientation),
        currentOrientation(Qt::WA_Maemo5LandscapeOrientation),
        covered(false)
    {
    }

    void _q_onResized() {
        Q_Q(QchScreen);

        QRect geometry = QApplication::desktop()->screenGeometry();

        if (geometry.height() > geometry.width()) {
            currentOrientation = Qt::WA_Maemo5PortraitOrientation;
        }
        else {
            currentOrientation = Qt::WA_Maemo5LandscapeOrientation;
        }

        emit q->widthChanged(geometry.width());
        emit q->heightChanged(geometry.height());
        emit q->currentOrientationChanged(currentOrientation);
    }

    void _q_onLockStateChanged(const QString &state) {
        Q_Q(QchScreen);

        if (state.endsWith("unlocked")) {
            covered = false;
            emit q->coveredChanged(false);
        }
        else {
            covered = true;
            emit q->coveredChanged(true);
        }
    }

    QchScreen *q_ptr;
    
    int orientationLock;
    int currentOrientation;

    bool covered;

    Q_DECLARE_PUBLIC(QchScreen)
};

QchScreen* QchScreen::self = 0;

QchScreen::QchScreen(QObject *parent) :
    QObject(parent),
    d_ptr(new QchScreenPrivate(this))
{
    if (!self) {
        self = this;
    }

    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(_q_onResized()));

    QDBusConnection::systemBus().connect("",
                                         "/com/nokia/mce/signal",
                                         "com.nokia.mce.signal",
                                         "tklock_mode_ind",
                                         this,
                                         SLOT(_q_onLockStateChanged(QString)));
}

QchScreen::~QchScreen() {
    if (self == this) {
        self = 0;
    }
}

QchScreen* QchScreen::instance() {
    return self;
}

int QchScreen::width() const {
    return QApplication::desktop()->screenGeometry().width();
}

int QchScreen::height() const {
    return QApplication::desktop()->screenGeometry().height();
}

int QchScreen::orientationLock() const {
    Q_D(const QchScreen);
    return d->orientationLock;
}

void QchScreen::setOrientationLock(int lock) {
    if (lock != orientationLock()) {
        Q_D(QchScreen);
        d->orientationLock = lock;
        emit orientationLockChanged(lock);
    }
}

int QchScreen::currentOrientation() const {
    Q_D(const QchScreen);
    return d->currentOrientation;
}

bool QchScreen::isCovered() const {
    Q_D(const QchScreen);
    return d->covered;
}

#include "moc_qchscreen.cpp"

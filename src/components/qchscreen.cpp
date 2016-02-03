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

/*!
    \class Screen
    \brief Provides access to various screen properties.
    
    \ingroup components
    
    \note Screen is a context property and cannot be created in QML.
*/  
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

/*!
    \brief The current width of the screen.
    
    This property changes when the current orientation changes.
    
    \sa currentOrientation
*/
int QchScreen::width() const {
    return QApplication::desktop()->screenGeometry().width();
}

/*!
    \brief The current height of the screen.
    
    This property changes when the current orientation changes.
    
    \sa currentOrientation
*/
int QchScreen::height() const {
    return QApplication::desktop()->screenGeometry().height();
}

/*!
    \brief The current orientation lock of the screen.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.WA_Maemo5AutoOrientation</td>
            <td>Application windows will rotate when the device is rotated.</td>
        </tr>
        <tr>
            <td>Qt.WA_Maemo5LandscapeOrientation</td>
            <td>Application windows will be locked to landscape orientation (default).</td>
        </tr>
        <tr>
            <td>Qt.WA_Maemo5PortraitOrientation</td>
            <td>Application windows will be locked to portrait orientation.</td>
        </tr>
    </table>
    
    \sa currentOrientation
*/
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

/*!
    \brief The current orientation of the screen.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.WA_Maemo5LandscapeOrientation</td>
            <td>The current application window is in landscape orientation.</td>
        </tr>
        <tr>
            <td>Qt.WA_Maemo5PortraitOrientation</td>
            <td>The current application window is in portrait orientation.</td>
        </tr>
    </table>
    
    \sa orientationLock
*/
int QchScreen::currentOrientation() const {
    Q_D(const QchScreen);
    return d->currentOrientation;
}

/*!
    \property bool Screen::covered
    \brief Whether the screen is covered/blanked.
*/
bool QchScreen::isCovered() const {
    Q_D(const QchScreen);
    return d->covered;
}

#include "moc_qchscreen.cpp"

/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchvolumekeys.h"
#include <QDeclarativeInfo>
#include <QEvent>
#include <QWidget>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

static bool acquireVolumeKeys(WId windowId, bool acquire = true) {
    if (windowId) {
        unsigned long val = (acquire ? 1 : 0);
        Atom atom = XInternAtom(QX11Info::display(), "_HILDON_ZOOM_KEY_ATOM", False);

        if (atom) {
            XChangeProperty(QX11Info::display(), windowId, atom, XA_INTEGER, 32, PropModeReplace,
                    reinterpret_cast<unsigned char*>(&val), 1);
            return true;
        }
    }

    return false;
}

/*!
    \class VolumeKeys
    \brief An attached property used to enable handling of volume key events.

    \ingroup components

    The VolumeKeys attached property is used to enable handling of volume key events
    in a Window. When enabled, the item receives a key event with key Qt.Key_F7 or Qt.Key_F8 
    when the volume up or down keys are pressed.

    \include volumekeys.qml

    \note VolumeKeys is an attached property and cannot be created in QML.
*/
QchVolumeKeys::QchVolumeKeys(QObject *parent) :
    QObject(parent),
    m_enabled(false),
    m_complete(false)
{
}

QchVolumeKeys::~QchVolumeKeys() {
    if ((m_complete) && (isEnabled())) {
        if (const QWidget *w = qobject_cast<QWidget*>(parent())) {
            acquireVolumeKeys(w->winId(), false);
        }
    }
}

/*!
    \brief Whether handling of volume key events should be enabled.
*/
bool QchVolumeKeys::isEnabled() const {
    return m_enabled;
}

void QchVolumeKeys::setEnabled(bool enabled) {
    if (enabled != isEnabled()) {
        m_enabled = enabled;
        emit enabledChanged(enabled);

        if (QWidget *w = qobject_cast<QWidget*>(parent())) {
            if (w->isVisible()) {
                m_complete = true;
            }

            if ((enabled) && (!m_complete)) {
                w->installEventFilter(this);
            }

            if ((!m_complete) || (acquireVolumeKeys(w->winId(), enabled))) {
                return;
            }
        }

        qmlInfo(this) << tr("Unable to acquire volume keys.");
   }
}

QchVolumeKeys* QchVolumeKeys::qmlAttachedProperties(QObject *obj) {
    return new QchVolumeKeys(obj);
}

bool QchVolumeKeys::eventFilter(QObject *obj, QEvent *event) {
    if ((!m_complete) && (event->type() == 17)) {
        m_complete = true;
        obj->removeEventFilter(this);

        if (isEnabled()) {
            if (const QWidget *w = qobject_cast<QWidget*>(obj)) {
                if (acquireVolumeKeys(w->winId(), true)) {
                    return QObject::eventFilter(obj, event);
                }
            }

            qmlInfo(this) << tr("Unable to aqcuire volume keys.");
        }
    }

    return QObject::eventFilter(obj, event);
}

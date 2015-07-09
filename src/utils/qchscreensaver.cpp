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

#include "qchscreensaver.h"
#include <QApplication>
#include <QWidget>
#include <QDeclarativeInfo>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>

class QchScreenSaverPrivate
{

public:
    QchScreenSaverPrivate(QchScreenSaver *parent) :
        q_ptr(parent),
        windowId(0),
        inhibited(false),
        complete(false)
    {
    }
    
    QchScreenSaver *q_ptr;

    WId windowId;

    bool inhibited;

    bool complete;

    Q_DECLARE_PUBLIC(QchScreenSaver)
};

QchScreenSaver::QchScreenSaver(QObject *parent) :
    QObject(parent),
    d_ptr(new QchScreenSaverPrivate(this))
{
}

QchScreenSaver::QchScreenSaver(QchScreenSaverPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

QchScreenSaver::~QchScreenSaver() {
    setScreenSaverInhibited(false);
}

bool QchScreenSaver::screenSaverInhibited() const {
    Q_D(const QchScreenSaver);

    return d->inhibited;
}

void QchScreenSaver::setScreenSaverInhibited(bool inhibited) {
    Q_D(QchScreenSaver);

    d->inhibited = inhibited;

    if ((!d->complete) || (!d->windowId)) {
        return;
    }

    Atom atom = XInternAtom(QX11Info::display() , "_HILDON_DO_NOT_DISTURB", False);

    if (inhibited) {
        long state = 1;
        XChangeProperty(
                    QX11Info::display(),
                    d->windowId,
                    atom,
                    XA_INTEGER,
                    32,
                    PropModeReplace,
                    (unsigned char *) &state,
                    1);
    }
    else {
        XDeleteProperty(QX11Info::display(), d->windowId, atom);
    }
}

void QchScreenSaver::classBegin() {}

void QchScreenSaver::componentComplete() {
    Q_D(QchScreenSaver);
    d->complete = true;
    
    if (QWidget *window = QApplication::activeWindow()) {
        d->windowId = window->winId();
        setScreenSaverInhibited(d->inhibited);
    }
    else {
        qmlInfo(this) << tr("Could not find window id");
    }
}

#include "moc_qchscreensaver.cpp"

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

#include "screensaver_p.h"
#include "screensaver_p_p.h"
#include <QApplication>
#include <QDesktopWidget>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>

ScreenSaver::ScreenSaver(QObject *parent) :
    QObject(parent),
    d_ptr(new ScreenSaverPrivate(this))
{
}

ScreenSaver::ScreenSaver(ScreenSaverPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

ScreenSaver::~ScreenSaver() {
    this->setScreenSaverInhibited(false);
}

bool ScreenSaver::screenSaverInhibited() const {
    Q_D(const ScreenSaver);

    return d->inhibited;
}

void ScreenSaver::setScreenSaverInhibited(bool inhibited) {
    QDesktopWidget *desktop = QApplication::desktop();

    if (!desktop) {
        return;
    }

    Q_D(ScreenSaver);

    d->inhibited = inhibited;

    Atom atom = XInternAtom(QX11Info::display() , "_HILDON_DO_NOT_DISTURB", False);

    if (inhibited) {
        long state = 1;
        XChangeProperty(
                    QX11Info::display(),
                    desktop->winId(),
                    atom,
                    XA_INTEGER,
                    32,
                    PropModeReplace,
                    (unsigned char *) &state,
                    1);
    }
    else {
        XDeleteProperty(QX11Info::display(), desktop->winId(), atom);
    }
}

#include "moc_screensaver_p.cpp"

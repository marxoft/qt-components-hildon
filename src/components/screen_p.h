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

#ifndef SCREEN_P_H
#define SCREEN_P_H

#include <QObject>
#include <qdeclarative.h>

class ScreenPrivate;

class Screen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(Orientation orientationLock READ orientationLock WRITE setOrientationLock NOTIFY orientationLockChanged)
    Q_PROPERTY(Orientation currentOrientation READ currentOrientation NOTIFY currentOrientationChanged)
    Q_PROPERTY(bool covered READ covered NOTIFY coveredChanged)

    Q_ENUMS(Orientation)

public:
    enum Orientation {
        LandscapeOrientation = Qt::WA_Maemo5LandscapeOrientation,
        PortraitOrientation = Qt::WA_Maemo5PortraitOrientation,
        AutoOrientation = Qt::WA_Maemo5AutoOrientation
    };

    ~Screen();

    static Screen* instance();

    int width() const;
    int height() const;

    Orientation orientationLock() const;
    void setOrientationLock(Orientation lock);

    Orientation currentOrientation() const;

    bool covered() const;

signals:
    void widthChanged(int width);
    void heightChanged(int height);
    void orientationLockChanged(Screen::Orientation lock);
    void currentOrientationChanged(Screen::Orientation current);
    void coveredChanged(bool covered);

private:
    Screen();

    static Screen *self;

    QScopedPointer<ScreenPrivate> d_ptr;

    Q_DISABLE_COPY(Screen)
    Q_DECLARE_PRIVATE(Screen)

    Q_PRIVATE_SLOT(d_func(), void _q_onResized())
    Q_PRIVATE_SLOT(d_func(), void _q_onLockStateChanged(QString))
};

QML_DECLARE_TYPE(Screen)

#endif // SCREEN_P_H

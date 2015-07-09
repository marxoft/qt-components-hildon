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

#ifndef QCHSCREEN_H
#define QCHSCREEN_H

#include <QObject>
#include <qdeclarative.h>

class QchScreenPrivate;

class QchScreen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(int orientationLock READ orientationLock WRITE setOrientationLock NOTIFY orientationLockChanged)
    Q_PROPERTY(int currentOrientation READ currentOrientation NOTIFY currentOrientationChanged)
    Q_PROPERTY(bool covered READ isCovered NOTIFY coveredChanged)

public:
    explicit QchScreen(QObject *parent = 0);
    ~QchScreen();

    static QchScreen* instance();

    int width() const;
    int height() const;

    int orientationLock() const;
    void setOrientationLock(int lock);

    int currentOrientation() const;

    bool isCovered() const;

Q_SIGNALS:
    void widthChanged(int width);
    void heightChanged(int height);
    void orientationLockChanged(int lock);
    void currentOrientationChanged(int current);
    void coveredChanged(bool covered);

protected:
    static QchScreen *self;

    QScopedPointer<QchScreenPrivate>d_ptr;

    Q_DECLARE_PRIVATE(QchScreen)

    Q_PRIVATE_SLOT(d_func(), void _q_onResized())
    Q_PRIVATE_SLOT(d_func(), void _q_onLockStateChanged(QString))

private:
    Q_DISABLE_COPY(QchScreen)
};

QML_DECLARE_TYPE(QchScreen)

#endif // QCHSCREEN_H

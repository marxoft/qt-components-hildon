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

#ifndef QCHSCREENSAVER_H
#define QCHSCREENSAVER_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchScreenSaverPrivate;

class QchScreenSaver : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(bool screenSaverInhibited READ screenSaverInhibited WRITE setScreenSaverInhibited)

    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit QchScreenSaver(QObject *parent = 0);
    ~QchScreenSaver();

    bool screenSaverInhibited() const;
    void setScreenSaverInhibited(bool inhibited);

protected:
    QchScreenSaver(QchScreenSaverPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<QchScreenSaverPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchScreenSaver)

private:
    Q_DISABLE_COPY(QchScreenSaver)
};

QML_DECLARE_TYPE(QchScreenSaver)

#endif // QCHSCREENSAVER_H

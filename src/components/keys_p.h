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

#ifndef KEYS_P_H
#define KEYS_P_H

#include <QObject>
#include <QDeclarativeListProperty>
#include <qdeclarative.h>

class KeysPrivate;

class Keys : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PRIVATE_PROPERTY(Keys::d_func(), QDeclarativeListProperty<QObject> forwardTo READ forwardTo)

    Q_ENUMS(Priority)

public:
    enum Priority {
        BeforeItem = 0,
        AfterItem
    };

    explicit Keys(QObject *parent = 0);
    ~Keys();

    bool enabled() const;
    void setEnabled(bool enabled);

    Priority priority() const;
    void setPriority(Priority priority);

    bool event(QEvent *event);

signals:
    void enabledChanged();
    void priorityChanged();

    void asteriskPressed();
    void backPressed();
    void backtabPressed();
    void callPressed();
    void cancelPressed();
    void context1Pressed();
    void context2Pressed();
    void context3Pressed();
    void context4Pressed();
    void deletePressed();
    void digit0Pressed();
    void digit1Pressed();
    void digit2Pressed();
    void digit3Pressed();
    void digit4Pressed();
    void digit5Pressed();
    void digit6Pressed();
    void digit7Pressed();
    void digit8Pressed();
    void digit9Pressed();
    void downPressed();
    void enterPressed();
    void escapePressed();
    void flipPressed();
    void hangupPressed();
    void leftPressed();
    void menuPressed();
    void noPressed();
    void pressed();
    void released();
    void returnPressed();
    void rightPressed();
    void selectPressed();
    void spacePressed();
    void tabPressed();
    void upPressed();
    void volumeDownPressed();
    void volumeUpPressed();
    void yesPressed();

private:
    Keys(KeysPrivate &dd, QObject *parent = 0);

    QScopedPointer<KeysPrivate> d_ptr;

    Q_DISABLE_COPY(Keys)
    Q_DECLARE_PRIVATE(Keys)
};

QML_DECLARE_TYPE(Keys)

#endif // KEYS_P_H

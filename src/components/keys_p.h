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
#include <QKeyEvent>
#include <QDeclarativeListProperty>
#include <qdeclarative.h>

class KeysPrivate;

class KeyEvent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
    Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat CONSTANT)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int key READ key CONSTANT)
    Q_PROPERTY(int modifiers READ modifiers CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)

public:
    explicit KeyEvent(QKeyEvent *event, QObject *parent = 0);
    ~KeyEvent();

    bool isAccepted() const;
    void setAccepted(bool accept);

    bool isAutoRepeat() const;

    int count() const;

    int key() const;

    int modifiers() const;

    QString text() const;

private:
    QKeyEvent *m_event;

    Q_DISABLE_COPY(KeyEvent)
};

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

    bool eventFilter(QObject *obj, QEvent *event);

    static Keys* qmlAttachedProperties(QObject *obj);

signals:
    void enabledChanged();
    void priorityChanged();

    void asteriskPressed(KeyEvent *event);
    void backPressed(KeyEvent *event);
    void backtabPressed(KeyEvent *event);
    void callPressed(KeyEvent *event);
    void cancelPressed(KeyEvent *event);
    void context1Pressed(KeyEvent *event);
    void context2Pressed(KeyEvent *event);
    void context3Pressed(KeyEvent *event);
    void context4Pressed(KeyEvent *event);
    void deletePressed(KeyEvent *event);
    void digit0Pressed(KeyEvent *event);
    void digit1Pressed(KeyEvent *event);
    void digit2Pressed(KeyEvent *event);
    void digit3Pressed(KeyEvent *event);
    void digit4Pressed(KeyEvent *event);
    void digit5Pressed(KeyEvent *event);
    void digit6Pressed(KeyEvent *event);
    void digit7Pressed(KeyEvent *event);
    void digit8Pressed(KeyEvent *event);
    void digit9Pressed(KeyEvent *event);
    void downPressed(KeyEvent *event);
    void enterPressed(KeyEvent *event);
    void escapePressed(KeyEvent *event);
    void flipPressed(KeyEvent *event);
    void hangupPressed(KeyEvent *event);
    void leftPressed(KeyEvent *event);
    void menuPressed(KeyEvent *event);
    void noPressed(KeyEvent *event);
    void returnPressed(KeyEvent *event);
    void rightPressed(KeyEvent *event);
    void selectPressed(KeyEvent *event);
    void spacePressed(KeyEvent *event);
    void tabPressed(KeyEvent *event);
    void upPressed(KeyEvent *event);
    void volumeDownPressed(KeyEvent *event);
    void volumeUpPressed(KeyEvent *event);
    void yesPressed(KeyEvent *event);

    void pressed(KeyEvent *event);
    void released(KeyEvent *event);

protected:
    Keys(KeysPrivate &dd, QObject *parent = 0);

    void timerEvent(QTimerEvent *event);

    QScopedPointer<KeysPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Keys)

private:
    Q_DISABLE_COPY(Keys)
};

QML_DECLARE_TYPE(KeyEvent)
QML_DECLARE_TYPE(Keys)
QML_DECLARE_TYPEINFO(Keys, QML_HAS_ATTACHED_PROPERTIES)

#endif // KEYS_P_H

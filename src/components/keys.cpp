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

#include "keys_p.h"
#include "keys_p_p.h"
#include <QKeyEvent>

Keys::Keys(QObject *parent) :
    QObject(parent),
    d_ptr(new KeysPrivate(this))
{
}

Keys::Keys(KeysPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Keys::~Keys() {}

bool Keys::enabled() const {
    Q_D(const Keys);

    return d->enabled;
}

void Keys::setEnabled(bool enabled) {
    if (enabled != this->enabled()) {
        Q_D(Keys);
        d->enabled = enabled;
        emit enabledChanged();
    }
}

Keys::Priority Keys::priority() const {
    Q_D(const Keys);

    return d->priority;
}

void Keys::setPriority(Priority priority) {
    if (priority != this->priority()) {
        Q_D(Keys);
        d->priority = priority;
        emit priorityChanged();
    }
}

bool Keys::event(QEvent *event) {
    if (!this->enabled()) {
        return false;
    }

    switch (event->type()) {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
        break;
    default:
        return false;
    }

    if (QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event)) {
        switch (keyEvent->type()) {
        case QKeyEvent::KeyPress:
            emit pressed();
            break;
        case QKeyEvent::KeyRelease:
            emit released();
            return true;
        }

        switch (keyEvent->key()) {
        case Qt::Key_Asterisk:
            emit asteriskPressed();
            break;
        case Qt::Key_Back:
            emit backPressed();
            break;
        case Qt::Key_Backtab:
            emit backtabPressed();
            break;
        case Qt::Key_Call:
            emit callPressed();
            break;
        case Qt::Key_Cancel:
            emit cancelPressed();
            break;
        case Qt::Key_Context1:
            emit context1Pressed();
            break;
        case Qt::Key_Context2:
            emit context2Pressed();
            break;
        case Qt::Key_Context3:
            emit context3Pressed();
            break;
        case Qt::Key_Context4:
            emit context4Pressed();
            break;
        case Qt::Key_Delete:
            emit deletePressed();
            break;
        case Qt::Key_0:
            emit digit0Pressed();
            break;
        case Qt::Key_1:
            emit digit1Pressed();
            break;
        case Qt::Key_2:
            emit digit2Pressed();
            break;
        case Qt::Key_3:
            emit digit3Pressed();
            break;
        case Qt::Key_4:
            emit digit4Pressed();
            break;
        case Qt::Key_5:
            emit digit5Pressed();
            break;
        case Qt::Key_6:
            emit digit6Pressed();
            break;
        case Qt::Key_7:
            emit digit7Pressed();
            break;
        case Qt::Key_8:
            emit digit8Pressed();
            break;
        case Qt::Key_9:
            emit digit9Pressed();
            break;
        case Qt::Key_Down:
            emit downPressed();
            break;
        case Qt::Key_Enter:
            emit enterPressed();
            break;
        case Qt::Key_Escape:
            emit escapePressed();
            break;
        case Qt::Key_Flip:
            emit flipPressed();
            break;
        case Qt::Key_Hangup:
            emit hangupPressed();
            break;
        case Qt::Key_Left:
            emit leftPressed();
            break;
        case Qt::Key_Menu:
            emit menuPressed();
            break;
        case Qt::Key_No:
            emit noPressed();
            break;
        case Qt::Key_Return:
            emit returnPressed();
            break;
        case Qt::Key_Right:
            emit rightPressed();
            break;
        case Qt::Key_Select:
            emit selectPressed();
            break;
        case Qt::Key_Space:
            emit spacePressed();
            break;
        case Qt::Key_Tab:
            emit tabPressed();
            break;
        case Qt::Key_Up:
            emit upPressed();
            break;
        case Qt::Key_VolumeDown:
            emit volumeDownPressed();
            break;
        case Qt::Key_VolumeUp:
            emit volumeUpPressed();
            break;
        case Qt::Key_Yes:
            emit yesPressed();
            break;
        default:
            break;
        }

        Q_D(Keys);

        foreach (QObject *object, d->forwardtoList) {
            if (object->event(keyEvent)) {
                break;
            }
        }

        return true;
    }

    return false;
}

void KeysPrivate::forwardto_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Keys *keys = qobject_cast<Keys*>(list->object)) {
        keys->d_func()->forwardtoList.append(obj);
    }
}

QDeclarativeListProperty<QObject> KeysPrivate::forwardTo() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, KeysPrivate::forwardto_append);
}

#include "moc_keys_p.cpp"

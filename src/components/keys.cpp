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
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeInfo>
#include <QWidget>
#include <QApplication>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

static const QList<int> KEYS = QList<int>() << Qt::Key_Asterisk
                                            << Qt::Key_Back
                                            << Qt::Key_Backtab
                                            << Qt::Key_Call
                                            << Qt::Key_Cancel
                                            << Qt::Key_Context1
                                            << Qt::Key_Context2
                                            << Qt::Key_Context3
                                            << Qt::Key_Context4
                                            << Qt::Key_Delete
                                            << Qt::Key_0
                                            << Qt::Key_1
                                            << Qt::Key_2
                                            << Qt::Key_3
                                            << Qt::Key_4
                                            << Qt::Key_5
                                            << Qt::Key_6
                                            << Qt::Key_7
                                            << Qt::Key_8
                                            << Qt::Key_9
                                            << Qt::Key_Down
                                            << Qt::Key_Enter
                                            << Qt::Key_Escape
                                            << Qt::Key_Flip
                                            << Qt::Key_Hangup
                                            << Qt::Key_Left
                                            << Qt::Key_Menu
                                            << Qt::Key_No
                                            << Qt::Key_Return
                                            << Qt::Key_Right
                                            << Qt::Key_Select
                                            << Qt::Key_Space
                                            << Qt::Key_Tab
                                            << Qt::Key_Up
                                            << Qt::Key_F8 // Volume Down
                                            << Qt::Key_F7 // Volume Up
                                            << Qt::Key_Yes;

KeyEvent::KeyEvent(QKeyEvent *event, QObject *parent) :
    QObject(parent),
    m_event(event)
{
}

KeyEvent::~KeyEvent() {}

bool KeyEvent::isAccepted() const {
    return (m_event) && (m_event->isAccepted());
}

void KeyEvent::setAccepted(bool accept) {
    if (m_event) {
        m_event->setAccepted(accept);
    }
}

bool KeyEvent::isAutoRepeat() const {
    return (m_event) && (m_event->isAutoRepeat());
}

int KeyEvent::count() const {
    return m_event ? m_event->count() : 0;
}

int KeyEvent::key() const {
    return m_event ? m_event->key() : 0;
}

int KeyEvent::modifiers() const {
    return m_event ? m_event->modifiers() : Qt::NoModifier;
}

QString KeyEvent::text() const {
    return m_event ? m_event->text() : QString();
}

class KeysPrivate
{

public:
    KeysPrivate(Keys *parent) :
        q_ptr(parent),
        enabled(true),
        volumeKeysEnabled(false),
        priority(Keys::BeforeItem)
    {
    }

    virtual ~KeysPrivate() {
        if ((volumeKeysEnabled) && (volumeKeysReferenceCount == 1)) {
            grabVolumeKeys(windowId, false);
        }
    }

    static void grabVolumeKeys(WId windowId, bool grab) {
        if (!windowId) {
            qWarning("Can't grab keys unless we have a window id");
            return;
        }

        unsigned long val = (grab) ? 1 : 0;
        Atom atom = XInternAtom(QX11Info::display(), "_HILDON_ZOOM_KEY_ATOM", False);

        if (!atom) {
            qWarning("Unable to obtain _HILDON_ZOOM_KEY_ATOM. This example will only work "
                     "on a Maemo 5 device!");
            return;
        }

        XChangeProperty (QX11Info::display(),
                         windowId,
                         atom,
                         XA_INTEGER,
                         32,
                         PropModeReplace,
                         reinterpret_cast<unsigned char *>(&val),
                         1);

        if (grab) {
            volumeKeysReferenceCount++;
        }
        else {
            volumeKeysReferenceCount--;
        }
    }

    static void forwardto_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (Keys *keys = qobject_cast<Keys*>(list->object)) {
            keys->d_func()->forwardtoList.append(obj);
        }
    }

    QDeclarativeListProperty<QObject> forwardTo() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, KeysPrivate::forwardto_append);
    }

    Keys *q_ptr;

    bool enabled;
    bool volumeKeysEnabled;

    WId windowId;

    Keys::Priority priority;

    QList<QObject*> forwardtoList;

    QHash<int, QMetaMethod> connections;

    static int volumeKeysReferenceCount;

    Q_DECLARE_PUBLIC(Keys)
};

int KeysPrivate::volumeKeysReferenceCount = 0;

Keys::Keys(QObject *parent) :
    QObject(parent),
    d_ptr(new KeysPrivate(this))
{
    if (parent) {
        parent->installEventFilter(this);
    }

    const QMetaObject *metaObject = this->metaObject();
    const int begin = metaObject->indexOfSignal("asteriskPressed(KeyEvent*)");
    const int end = metaObject->indexOfSignal("yesPressed(KeyEvent*)");

    Q_D(Keys);

    for (int i = begin; i <= end; i++) {
        QMetaMethod signal = metaObject->method(i);

        if (signal.methodType() == QMetaMethod::Signal) {
            const int key = (i - begin);

            if ((key >= 0) && (key < KEYS.size())) {
                d->connections[KEYS.at(key)] = signal;
            }
        }
    }

    this->startTimer(1000);
}

Keys::Keys(KeysPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (parent) {
        parent->installEventFilter(this);
    }

    const QMetaObject *metaObject = this->metaObject();
    const int begin = metaObject->indexOfSignal("asteriskPressed(KeyEvent*)");
    const int end = metaObject->indexOfSignal("yesPressed(KeyEvent*)");

    Q_D(Keys);

    for (int i = begin; i <= end; i++) {
        QMetaMethod signal = metaObject->method(i);

        if (signal.methodType() == QMetaMethod::Signal) {
            const int key = (i - begin);

            if ((i >= 0) && (i < KEYS.size())) {
                d->connections[KEYS.at(key)] = signal;
            }
        }
    }

    this->startTimer(1000);
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

bool Keys::eventFilter(QObject *obj, QEvent *event) {
    if (!this->enabled()) {
        return false;
    }

    switch (event->type()) {
    case 7: // QEvent::KeyPress
    case 8: // QEvent::KeyRelease
        break;
    default:
        return false;
    }

    switch (this->priority()) {
    case AfterItem:
        if (obj->event(event)) {
            return false;
        }

        break;
    default:
        break;
    }

    Q_D(Keys);

    foreach (QObject *object, d->forwardtoList) {
        if (object->event(event)) {
            return false;
        }
    }

    if (QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event)) {
        switch (keyEvent->type()) {
        case 7: // QKeyEvent::KeyPress
        {
            KeyEvent *ke = new KeyEvent(keyEvent);
            QDeclarativeEngine::setObjectOwnership(ke, QDeclarativeEngine::JavaScriptOwnership);
            const int key = keyEvent->key();

            if (d->connections.contains(key)) {
                QMetaMethod signal = d->connections.value(key);
                QByteArray signature(signal.signature());

                if (this->receivers("2" + signature) > 0) {
                    keyEvent->accept();
                    signal.invoke(this, Q_ARG(KeyEvent*, ke));
                }
            }

            if (this->receivers(SIGNAL(pressed(KeyEvent*)))) {
                emit pressed(ke);
            }

            if (keyEvent->isAccepted()) {
                return true;
            }

            break;
        }
        case 8: // QKeyEvent::KeyRelease
            if (this->receivers(SIGNAL(released(KeyEvent*)))) {
                KeyEvent *ke = new KeyEvent(keyEvent);
                QDeclarativeEngine::setObjectOwnership(ke, QDeclarativeEngine::JavaScriptOwnership);
                emit released(ke);
            }

            break;
        }

        return !obj->event(keyEvent);
    }

    return false;
}

void Keys::timerEvent(QTimerEvent *event) {
    this->killTimer(event->timerId());

    if ((this->receivers(SIGNAL(volumeDownPressed(KeyEvent*))) > 0) || (this->receivers(SIGNAL(volumeUpPressed(KeyEvent*))) > 0)) {
        if (QWidget *window = QApplication::activeWindow()) {
            Q_D(Keys);
            d->volumeKeysEnabled = true;
            d->windowId = window->winId();
            d->grabVolumeKeys(d->windowId, true);
        }
        else {
            qmlInfo(this) << tr("Could not find window id to grab volume keys");
        }
    }
}

Keys* Keys::qmlAttachedProperties(QObject *obj) {
    Keys* keys = new Keys(obj);

    if (QDeclarativeContext *parentContext = qmlContext(obj)) {
        QDeclarativeContext *context = new QDeclarativeContext(parentContext, keys);
        qmlEngine(obj)->setContextForObject(keys, context);
    }

    return keys;
}

#include "moc_keys_p.cpp"

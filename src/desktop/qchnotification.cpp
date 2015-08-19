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

#include <hildon-notify/hildon/hildon-notification.h>
#include "qchnotification.h"
#include <QCoreApplication>

#define QGSTRING(x) (x.toLatin1().data())

class QchNotificationPrivate
{

public:
    QchNotificationPrivate(QchNotification *parent) :
        q_ptr(parent),
        notification(NULL),
        timeout(NOTIFY_EXPIRES_DEFAULT),
        isRejectable(false),
        isVisible(false),
        showOnInit(false)
    {
    }
    
    ~QchNotificationPrivate() {
        g_object_unref(notification);
    }

    void init() {
        if (!notify_is_initted()) {
            notify_init(QGSTRING(QCoreApplication::applicationName()));
        }
        
        Q_Q(QchNotification);
        notification = hildon_notification_new(QGSTRING(title), QGSTRING(text), QGSTRING(iconSource), NULL);
        notify_notification_add_action(NOTIFY_NOTIFICATION(notification), "default",
                                       QGSTRING(QCoreApplication::applicationName()),
                                       NOTIFY_ACTION_CALLBACK(onNotificationClicked), q, NULL);
        g_signal_connect(G_OBJECT(notification), "closed", G_CALLBACK(onNotificationClosed), q);
        
        setNotificationCategory();
        setNotificationHints();
        setNotificationSound();
        setNotificationTimeout();
        
        if (showOnInit) {
            showNotification();
        }
    }
    
    void hideNotification() {
        showOnInit = false;
        
        if ((notification) && (isVisible) && (notify_notification_close(NOTIFY_NOTIFICATION(notification), NULL))) {
            isRejectable = false;
        }
    }
    
    void showNotification() {
        showOnInit = true;
        
        if ((notification) && (!isVisible) && (notify_notification_show(NOTIFY_NOTIFICATION(notification), NULL))) {
            Q_Q(QchNotification);
            isRejectable = true;
            isVisible = true;
            emit q->visibleChanged();
        }
    }
    
    void setNotificationCategory() {
        if (notification) {
            notify_notification_set_category(NOTIFY_NOTIFICATION(notification), QGSTRING(category));
        }
    }
    
    void setNotificationHints() {
        if (notification) {
            notify_notification_clear_hints(NOTIFY_NOTIFICATION(notification));
            
            if (!hints.isEmpty()) {
                QMapIterator<QString, QVariant> iterator(hints);
            
                while (iterator.hasNext()) {
                    iterator.next();
                    
                    switch (iterator.value().type()) {
                    case QVariant::Int:
                    case QVariant::Double:
                        notify_notification_set_hint_int32(NOTIFY_NOTIFICATION(notification), QGSTRING(iterator.key()),
                                                           iterator.value().toInt());
                        break;
                    default:
                        notify_notification_set_hint_string(NOTIFY_NOTIFICATION(notification), QGSTRING(iterator.key()),
                                                            QGSTRING(iterator.value().toString()));
                        break;
                    }
                }
            }
        }
    }
    
    void setNotificationSound() {
        if (notification) {
            hildon_notification_set_sound(notification, QGSTRING(soundSource));
        }
    }
    
    void setNotificationTimeout() {
        if (notification) {
            notify_notification_set_timeout(NOTIFY_NOTIFICATION(notification), timeout);
        }
    }
    
    void updateNotification() {
        if (notification) {
            notify_notification_update(NOTIFY_NOTIFICATION(notification), QGSTRING(title), QGSTRING(text),
                                       QGSTRING(iconSource));
        }
    }
    
    static void onNotificationClicked(NotifyNotification*, gchar*, gpointer user_data) {
        if (QchNotification *n = static_cast<QchNotification*>(user_data)) {
            n->d_func()->isRejectable = false;
            emit n->accepted();
        }
    }
    
    static void onNotificationClosed(NotifyNotification *, gpointer user_data) {
        if (QchNotification *n = static_cast<QchNotification*>(user_data)) {
            if (n->d_func()->isRejectable) {
                emit n->rejected();
            }
            
            n->d_func()->isVisible = false;
            emit n->visibleChanged();            
        }
    }
    
    QchNotification *q_ptr;
    
    HildonNotification *notification;
    
    QString category;
    
    QVariantMap hints;
    
    QString iconSource;
    
    QString soundSource;
    
    QString text;
    
    int timeout;
    
    QString title;
    
    bool isRejectable;
    bool isVisible;
    bool showOnInit;
        
    Q_DECLARE_PUBLIC(QchNotification)
};

QchNotification::QchNotification(QObject *parent) :
    QObject(parent),
    d_ptr(new QchNotificationPrivate(this))
{
}

QchNotification::~QchNotification() {}

QString QchNotification::category() const {
    Q_D(const QchNotification);
    return d->category;
}

void QchNotification::setCategory(const QString &c) {
    if (c != category()) {
        Q_D(QchNotification);
        d->category = c;
        d->setNotificationCategory();
        emit categoryChanged();
    }
}

QVariantMap QchNotification::hints() const {
    Q_D(const QchNotification);
    return d->hints;
}

void QchNotification::setHints(const QVariantMap &h) {
    Q_D(QchNotification);
    d->hints = h;
    d->setNotificationHints();
    emit hintsChanged();
}

QString QchNotification::iconSource() const {
    Q_D(const QchNotification);
    return d->iconSource;
}

void QchNotification::setIconSource(const QString &i) {
    if (i != iconSource()) {
        Q_D(QchNotification);
        d->iconSource = i;
        d->updateNotification();
        emit iconSourceChanged();
    }
}

QString QchNotification::soundSource() const {
    Q_D(const QchNotification);
    return d->iconSource;
}

void QchNotification::setSoundSource(const QString &s) {
    if (s != soundSource()) {
        Q_D(QchNotification);
        d->soundSource = s;
        d->setNotificationSound();
        emit soundSourceChanged();
    }
}

QString QchNotification::text() const {
    Q_D(const QchNotification);
    return d->text;
}

void QchNotification::setText(const QString &t) {
    if (t != text()) {
        Q_D(QchNotification);
        d->text = t;
        d->updateNotification();
        emit textChanged();
    }
}

int QchNotification::timeout() const {
    Q_D(const QchNotification);
    return d->timeout;
}

void QchNotification::setTimeout(int t) {
    if (t != timeout()) {
        Q_D(QchNotification);
        
        switch (t) {
        case DefaultTimeout:
            d->timeout = NOTIFY_EXPIRES_DEFAULT;
            break;
        case NoTimeout:
            d->timeout = NOTIFY_EXPIRES_NEVER;
            break;
        default:
            d->timeout = t;
            break;
        }
        
        d->setNotificationTimeout();
        emit timeoutChanged();
    }
}

QString QchNotification::title() const {
    Q_D(const QchNotification);
    return d->title;
}

void QchNotification::setTitle(const QString &t) {
    if (t != title()) {
        Q_D(QchNotification);
        d->title = t;
        d->updateNotification();
        emit titleChanged();
    }
}

bool QchNotification::isVisible() const {
    Q_D(const QchNotification);
    return d->isVisible;
}

void QchNotification::setVisible(bool v) {
    if (v != isVisible()) {
        if (v) {
            show();
        }
        else {
            hide();
        }
    }
}

void QchNotification::hide() {
    Q_D(QchNotification);
    d->hideNotification();
}

void QchNotification::open() {
    show();
}

void QchNotification::show() {
    Q_D(QchNotification);
    d->showNotification();
}

void QchNotification::classBegin() {}

void QchNotification::componentComplete() {
    Q_D(QchNotification);
    d->init();
}

#include "moc_qchnotification.cpp"

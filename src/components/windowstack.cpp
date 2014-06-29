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

#include "windowstack_p.h"
#include "windowstack_p_p.h"
#include "window_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeInfo>

WindowStack* WindowStack::self = 0;

WindowStack::WindowStack(QObject *parent) :
    QObject(parent),
    d_ptr(new WindowStackPrivate(this))
{
    if (!self) {
        self = this;
    }
}

WindowStack::WindowStack(WindowStackPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (!self) {
        self = this;
    }
}

WindowStack::~WindowStack() {}

WindowStack*  WindowStack::instance() {
    return !self ? new WindowStack : self;
}

int WindowStack::depth() const {
    Q_D(const WindowStack);

    return d->stack.size();
}

Window* WindowStack::currentWindow() const {
    Q_D(const WindowStack);

    return d->stack.isEmpty() ? 0 : d->stack.last();
}

Window* WindowStack::rootWindow() const {
    Q_D(const WindowStack);

    return d->stack.isEmpty() ? 0 : d->stack.first();
}

void WindowStack::push(QObject *window) {
    if (Window *w = qobject_cast<Window*>(window)) {
        if (!w->parent()) {
            w->setParent(this->currentWindow());
        }

        w->show();
    }
}

void WindowStack::push(const QUrl &url) {
    Q_D(WindowStack);

    if ((d->component) && (d->component->status() == QDeclarativeComponent::Loading)) {
        return;
    }

    d->data.clear();
    d->component = new QDeclarativeComponent(qmlEngine(this->currentWindow()));
    this->connect(d->component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(_q_onWindowStatusChanged(QDeclarativeComponent::Status)));
    d->component->loadUrl(url);
}

void WindowStack::push(const QUrl &url, const QVariantMap &data) {
    Q_D(WindowStack);

    if ((d->component) && (d->component->status() == QDeclarativeComponent::Loading)) {
        return;
    }

    d->data = data;
    d->component = new QDeclarativeComponent(qmlEngine(this->currentWindow()));
    this->connect(d->component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(_q_onWindowStatusChanged(QDeclarativeComponent::Status)));
    d->component->loadUrl(url);
}

void WindowStack::pop() {
    Q_D(WindowStack);

    if (!d->stack.isEmpty()) {
        d->stack.last()->close();
        emit countChanged();
        emit currentWindowChanged();
    }
}

void WindowStack::pop(QObject *window) {
    Q_D(WindowStack);

    if (d->stack.isEmpty()) {
        return;
    }

    for (int i = d->stack.size() - 1; i > 0; i--) {
        if (d->stack.at(i) != window) {
            d->stack.at(i)->close();
        }
    }

    emit countChanged();
    emit currentWindowChanged();
}

void WindowStack::pop(const QString &objectName) {
    Q_D(WindowStack);

    if (d->stack.isEmpty()) {
        return;
    }

    for (int i = d->stack.size() - 1; i > 0; i--) {
        if (d->stack.at(i)->objectName() != objectName) {
            d->stack.at(i)->close();
        }
    }

    emit countChanged();
    emit currentWindowChanged();
}

void WindowStackPrivate::_q_onWindowStatusChanged(QDeclarativeComponent::Status status) {
    if (!component) {
        return;
    }

    Q_Q(WindowStack);

    switch (status) {
    case QDeclarativeComponent::Ready:
        if (QObject *obj = component->beginCreate(qmlEngine(q->currentWindow())->contextForObject(q->currentWindow()))) {
            if (!data.isEmpty()) {
                foreach (QString key, data.keys()) {
                    obj->setProperty(key.toUtf8(), data.value(key));
                }
            }

            component->completeCreate();

            if (component->isError()) {
                if (!component->errors().isEmpty()) {
                    qmlInfo(q, component->errors());
                }
            }
            else {
                q->push(obj);
            }
        }

        return;
    case QDeclarativeComponent::Error:
        if (!component->errors().isEmpty()) {
            qmlInfo(q, component->errors());
        }

        return;
    default:
        return;
    }
}

#include "moc_windowstack_p.cpp"

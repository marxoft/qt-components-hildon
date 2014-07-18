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

#include "loader_p.h"
#include "loader_p_p.h"
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QDeclarativeContext>
#include <QWidget>
#include <QEvent>

Loader::Loader(QObject *parent) :
    QObject(parent),
    d_ptr(new LoaderPrivate(this))
{
}

Loader::Loader(LoaderPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Loader::~Loader() {}

QUrl Loader::source() const {
    Q_D(const Loader);

    return d->source;
}

void Loader::setSource(const QUrl &url) {
    Q_D(Loader);

    if (d->source == url) {
        return;
    }

    d->clear();

    d->source = url;

    if (d->source.isEmpty()) {
        emit sourceChanged();
        emit statusChanged();
        emit progressChanged();
        emit itemChanged();
        return;
    }

    d->component = new QDeclarativeComponent(qmlEngine(this), d->source, this);
    d->ownComponent = true;

    if (d->complete) {
        d->load();
    }
}

QDeclarativeComponent* Loader::sourceComponent() const {
    Q_D(const Loader);

    return d->component;
}

void Loader::setSourceComponent(QDeclarativeComponent *component) {
    Q_D(Loader);

    if (component == d->component) {
        return;
    }

    d->clear();

    d->component = component;
    d->ownComponent = false;

    if (!d->component) {
        emit sourceChanged();
        emit statusChanged();
        emit progressChanged();
        emit itemChanged();
        return;
    }

    if (d->complete) {
        d->load();
    }
}

void Loader::resetSourceComponent() {
    this->setSourceComponent(0);
}

Loader::Status Loader::status() const {
    Q_D(const Loader);

    if (d->component) {
        return static_cast<Loader::Status>(d->component->status());
    }

    if (d->item) {
        return Ready;
    }

    return d->source.isEmpty() ? Null : Error;
}

qreal Loader::progress() const {
    Q_D(const Loader);

    if (d->item) {
        return 1.0;
    }

    if (d->component) {
        return d->component->progress();
    }

    return 0.0;
}

QWidget* Loader::item() const {
    Q_D(const Loader);

    return d->item;
}

void Loader::classBegin() {}

void Loader::componentComplete() {
    Q_D(Loader);

    d->complete = true;
    d->load();
}

bool Loader::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    return QObject::event(event);
}

void LoaderPrivate::clear() {
    if (ownComponent) {
        component->deleteLater();
        component = 0;
        ownComponent = false;
    }

    source = QUrl();

    if (item) {
        item->hide();
        item->deleteLater();
        item = 0;
    }
}

void LoaderPrivate::load() {
    Q_Q(Loader);

    if ((!complete) || (!component)) {
        return;
    }

    if (!component->isLoading()) {
        this->_q_sourceLoaded();
    }
    else {
        q->connect(component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), q, SLOT(_q_sourceLoaded()));
        q->connect(component, SIGNAL(progressChanged(qreal)), q, SIGNAL(progressChanged()));
        emit q->statusChanged();
        emit q->progressChanged();
        emit q->sourceChanged();
        emit q->itemChanged();
    }
}

QWidget* LoaderPrivate::parentWidget() const {
    Q_Q(const Loader);

    bool isWidget = false;
    QObject *parent = q->parent();

    while ((parent) && (!isWidget)) {
        isWidget = parent->isWidgetType();

        if (!isWidget) {
            parent = parent->parent();
        }
    }

    if ((parent) && (isWidget)) {
        return qobject_cast<QWidget*>(parent);
    }

    return 0;
}

void LoaderPrivate::_q_sourceLoaded() {
    Q_Q(Loader);

    if (component) {
        if (!component->errors().isEmpty()) {
            qmlInfo(q, component->errors());
            emit q->sourceChanged();
            emit q->statusChanged();
            emit q->progressChanged();
            return;
        }

        QDeclarativeContext *creationContext = component->creationContext();

        if (!creationContext) {
            creationContext = qmlContext(q);
        }

        QDeclarativeContext *context = new QDeclarativeContext(creationContext);
        context->setContextObject(q);

        QObject *obj = component->beginCreate(context);

        if (obj) {
            item = qobject_cast<QWidget*>(obj);

            if (item) {
                context->setParent(item);
                item->setParent(this->parentWidget());
            }
            else {
                qmlInfo(q) << Loader::tr("Loader does not support loading non-visual elements.");
                delete obj;
                delete context;
            }
        }
        else {
            if (!component->errors().isEmpty()) {
                qmlInfo(q, component->errors());
            }

            delete obj;
            delete context;
            source = QUrl();
        }

        component->completeCreate();
        emit q->sourceChanged();
        emit q->statusChanged();
        emit q->progressChanged();
        emit q->itemChanged();
        emit q->loaded();
    }
}

#include "moc_loader_p.cpp"

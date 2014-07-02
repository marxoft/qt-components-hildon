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

#include "pagestack_p.h"
#include "pagestack_p_p.h"
#include <QWidget>
#include <QDeclarativeEngine>
#include <QDeclarativeInfo>

PageStack* PageStack::self = 0;

PageStack::PageStack(QObject *parent) :
    QObject(parent),
    d_ptr(new PageStackPrivate(this))
{
    if (!self) {
        self = this;
    }
}

PageStack::PageStack(PageStackPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (!self) {
        self = this;
    }
}

PageStack::~PageStack() {}

PageStack*  PageStack::instance() {
    return self;
}

int PageStack::depth() const {
    Q_D(const PageStack);

    return d->stack.size();
}

QWidget* PageStack::currentPage() const {
    Q_D(const PageStack);

    return d->stack.isEmpty() ? 0 : d->stack.last();
}

QWidget* PageStack::rootPage() const {
    Q_D(const PageStack);

    return d->stack.isEmpty() ? 0 : d->stack.first();
}

void PageStack::push(QObject *page) {
    if (QWidget *w = qobject_cast<QWidget*>(page)) {
        if (!w->parent()) {
            w->setParent(this->currentPage());
        }

        w->show();
    }
}

void PageStack::push(const QUrl &url) {
    Q_D(PageStack);

    if ((d->component) && (d->component->status() == QDeclarativeComponent::Loading)) {
        return;
    }

    d->data.clear();
    d->component = this->currentPage() ? new QDeclarativeComponent(qmlEngine(this->currentPage())) : new QDeclarativeComponent(qmlEngine(this));
    this->connect(d->component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(_q_onPageStatusChanged(QDeclarativeComponent::Status)));
    d->component->loadUrl(url);
}

void PageStack::push(const QUrl &url, const QVariantMap &data) {
    Q_D(PageStack);

    if ((d->component) && (d->component->status() == QDeclarativeComponent::Loading)) {
        return;
    }

    d->data = data;
    d->component = this->currentPage() ? new QDeclarativeComponent(qmlEngine(this->currentPage())) : new QDeclarativeComponent(qmlEngine(this));
    this->connect(d->component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(_q_onPageStatusChanged(QDeclarativeComponent::Status)));
    d->component->loadUrl(url);
}

void PageStack::pop() {
    Q_D(PageStack);

    if (!d->stack.isEmpty()) {
        d->stack.last()->close();
        emit countChanged();
        emit currentPageChanged();
    }
}

void PageStack::pop(QObject *page) {
    Q_D(PageStack);

    if (d->stack.isEmpty()) {
        return;
    }

    for (int i = d->stack.size() - 1; i > 0; i--) {
        if (d->stack.at(i) != page) {
            d->stack.at(i)->close();
        }
    }

    emit countChanged();
    emit currentPageChanged();
}

void PageStack::pop(const QString &objectName) {
    Q_D(PageStack);

    if (d->stack.isEmpty()) {
        return;
    }

    for (int i = d->stack.size() - 1; i > 0; i--) {
        if (d->stack.at(i)->objectName() != objectName) {
            d->stack.at(i)->close();
        }
    }

    emit countChanged();
    emit currentPageChanged();
}

void PageStackPrivate::_q_onPageStatusChanged(QDeclarativeComponent::Status status) {
    if (!component) {
        return;
    }

    Q_Q(PageStack);

    switch (status) {
    case QDeclarativeComponent::Ready:
        if (QObject *obj = component->beginCreate(q->currentPage() ? qmlEngine(q->currentPage())->contextForObject(q->currentPage()) : qmlEngine(q)->contextForObject(q))) {
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

#include "moc_pagestack_p.cpp"

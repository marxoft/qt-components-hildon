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
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeInfo>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>

PageStack::PageStack(QWidget *parent) :
    QObject(parent),
    d_ptr(new PageStackPrivate(this))
{
    if (parent) {
        this->push(parent);
    }
}

PageStack::PageStack(PageStackPrivate &dd, QWidget *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (parent) {
        this->push(parent);
    }
}

PageStack::~PageStack() {}

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

void PageStack::push(QWidget *page) {
    Q_D(PageStack);
    
    d->stack.append(page);
    this->connect(page, SIGNAL(destroyed(QObject*)), this, SLOT(_q_onPageClosed(QObject*)));
    emit countChanged();
    emit currentPageChanged();
}

void PageStack::push(const QUrl &url) {
    this->push(url, QVariantMap());
}

void PageStack::push(const QUrl &url, const QVariantMap &data) {
    Q_D(PageStack);

    if ((d->component) && (d->component->status() == QDeclarativeComponent::Loading)) {
        return;
    }

    d->data = data;

    if (!d->component) {
        d->component = new QDeclarativeComponent(qmlEngine(this->currentPage()), this);
        this->connect(d->component, SIGNAL(statusChanged(QDeclarativeComponent::Status)), this, SLOT(_q_onPageStatusChanged()));
    }

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

void PageStack::pop(QWidget *page) {
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

void PageStackPrivate::_q_onPageStatusChanged() {
    if (!component) {
        return;
    }

    Q_Q(PageStack);

    switch (component->status()) {
    case QDeclarativeComponent::Ready:
        if (QObject *obj = component->beginCreate(q->currentPage() ? qmlContext(q->currentPage()) : qmlContext(q))) {
            if (!data.isEmpty()) {
                QMapIterator<QString, QVariant> iterator(data);
                
                while (iterator.hasNext()) {
                    iterator.next();
                    obj->setProperty(iterator.key().toUtf8(), iterator.value());
                }
            }
            
            if (obj->isWidgetType()) {
                QWidget *page = qobject_cast<QWidget*>(obj);
                page->setParent(q->currentPage());
                page->setWindowFlags(Qt::Window);
                page->setAttribute(Qt::WA_Maemo5StackedWindow, true);
                const int pos = stack.size();
                XChangeProperty(QX11Info::display(), page->winId(), 
                                XInternAtom(QX11Info::display() , "_HILDON_STACKABLE_WINDOW", True), 
                                XA_INTEGER, 32, PropModeReplace, (unsigned char *) &pos, 1);
                
                component->completeCreate();

                if (component->isError()) {
                    if (!component->errors().isEmpty()) {
                        qmlInfo(q, component->errors());
                    }
                }
                else {
                    q->push(page);
                }
            }
            else {
                qmlInfo(q) << "Page must be a visual item";
                delete obj;
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

void PageStackPrivate::_q_onPageClosed(QObject *page) {
    if (QWidget *w = qobject_cast<QWidget*>(page)) {
        stack.removeOne(w);
    }
}

#include "moc_pagestack_p.cpp"

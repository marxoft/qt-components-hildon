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

#include "qchwindowstack.h"
#include "qchwindow.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeInfo>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <QX11Info>

class QchWindowStackPrivate
{

public:
    QchWindowStackPrivate(QchWindowStack *parent) :
        q_ptr(parent)
    {
    }
    
    void _q_onWindowHidden(QchWindow *window) {
        Q_Q(QchWindowStack);
        stack.removeOne(window);
        emit q->currentChanged();
    }
    
    QchWindowStack *q_ptr;
        
    QList<QchWindow*> stack;
    
    QHash<QUrl, QDeclarativeComponent*> componentCache;
    
    Q_DECLARE_PUBLIC(QchWindowStack)
};

QchWindowStack::QchWindowStack(QObject *parent) :
    QObject(parent),
    d_ptr(new QchWindowStackPrivate(this))
{
}

QchWindowStack::~QchWindowStack() {}

QchWindow* QchWindowStack::currentWindow() const {
    Q_D(const QchWindowStack);
    return d->stack.isEmpty() ? 0 : d->stack.last();
}

QchWindow* QchWindowStack::rootWindow() const {
    Q_D(const QchWindowStack);
    return d->stack.isEmpty() ? 0 : d->stack.first();
}

void QchWindowStack::setRootWindow(QchWindow *root) {
    if (root != rootWindow()) {
        Q_D(QchWindowStack);
        d->stack.clear();
        d->stack.append(root);
        emit currentChanged();
    }
}

int QchWindowStack::depth() const {
    Q_D(const QchWindowStack);
    return d->stack.size();
}

QchWindow* QchWindowStack::push(QDeclarativeComponent* component, const QVariantMap &properties) {
    QchWindow *current = currentWindow();    
    QDeclarativeContext *context = new QDeclarativeContext(qmlContext(current));
    context->setContextObject(current);
    
    if (QObject *obj = component->beginCreate(context)) {
        if (QchWindow *window = qobject_cast<QchWindow*>(obj)) {
            Q_D(QchWindowStack);
            context->setParent(window);
            window->setParent(current);
            window->setWindowFlags(Qt::Window);
            window->setAttribute(Qt::WA_Maemo5StackedWindow, true);
            
            const int pos = d->stack.size();
            XChangeProperty(QX11Info::display(), window->winId(), 
                            XInternAtom(QX11Info::display() , "_HILDON_STACKABLE_WINDOW", True), 
                            XA_INTEGER, 32, PropModeReplace, (unsigned char *) &pos, 1);
                        
            component->completeCreate();
            
            if (!properties.isEmpty()) {
                QMapIterator<QString, QVariant> iterator(properties);
                
                while (iterator.hasNext()) {
                    iterator.next();
                    window->setProperty(iterator.key().toUtf8(), iterator.value());
                }
            }
            
            d->stack.append(window);
            window->show();
            connect(window, SIGNAL(hidden(QchWindow*)), this, SLOT(_q_onWindowHidden(QchWindow*)));
            emit currentChanged();
            return window;
        }
        
        qmlInfo(this) << tr("Only Window items can be pushed onto the stack.");
        delete obj;
        delete context;
    }
    
    if (!component->errors().isEmpty()) {
        qmlInfo(this, component->errors());
    }
    
    return 0;
}

QchWindow* QchWindowStack::push(const QUrl &url, const QVariantMap &properties) {
    Q_D(QchWindowStack);
    QDeclarativeComponent *component = d->componentCache.value(url, 0);
    
    if (!component) {
        component = new QDeclarativeComponent(qmlEngine(this), url, this);
    }
    
    if (QchWindow *window = push(component, properties)) {
        d->componentCache.insert(url, component);
        return window;
    }
    
    delete component;
    return 0;
}

void QchWindowStack::pop(QchWindow* toWindow) {
    Q_D(QchWindowStack);
    const int start = d->stack.size() - 1;
    const int end = toWindow ? qMax(1, d->stack.indexOf(toWindow) + 1) : start;
    
    for (int i = start; i >= end; i--) {
        if (QchWindow *window = d->stack.at(i)) {
            window->close();
        }
    }
}

void QchWindowStack::clear() {
    pop(rootWindow());
}

#include "moc_qchwindowstack.cpp"

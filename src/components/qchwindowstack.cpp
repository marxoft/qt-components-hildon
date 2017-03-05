/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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
    
    QchWindow* push(QDeclarativeComponent *component, const QVariantMap &properties) {
        Q_Q(QchWindowStack);
        QchWindow *current = q->currentWindow();
        QDeclarativeContext *context = component->creationContext();
        bool setContextParent = false;
        
        if (!context) {
            context = new QDeclarativeContext(qmlContext(current));
            context->setContextObject(current);
            setContextParent = true;
        }
    
        if (QObject *obj = component->beginCreate(context)) {
            if (QchWindow *window = qobject_cast<QchWindow*>(obj)) {
                if (setContextParent) {
                    context->setParent(window);
                }
                
                window->setParent(current);
                window->setWindowFlags(Qt::Window);
                window->setAttribute(Qt::WA_Maemo5StackedWindow, true);
            
                const int pos = stack.size();
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
            
                stack.append(window);
                window->show();
                q->connect(window, SIGNAL(hidden(QchWindow*)), q, SLOT(_q_onWindowHidden(QchWindow*)));
                emit q->currentChanged();
                return window;
            }
        
            qmlInfo(q) << QchWindowStack::tr("Only Window items can be pushed onto the stack.");
            delete obj;
            delete context;
        }
    
        if (!component->errors().isEmpty()) {
            qmlInfo(q, component->errors());
        }
    
        return 0;
    }
    
    QchWindow* push(const QUrl &url, const QVariantMap &properties) {
        Q_Q(QchWindowStack);
        QDeclarativeComponent *component = componentCache.value(url, 0);
        
        if (!component) {
            component = new QDeclarativeComponent(qmlEngine(q), url, q);
        }
        
        if (QchWindow *window = push(component, properties)) {
            componentCache.insert(url, component);
            return window;
        }
        
        delete component;
        return 0;
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

/*!
    \class WindowStack
    \brief A component for managing stacked windows.
    
    \ingroup components
    
    You do not normally need to instantiate this component, since you can simply use the ApplicationWindow component, 
    which already has a window stack.
    
    \include window.qml
    
    \sa ApplicationWindow, Window
*/
QchWindowStack::QchWindowStack(QObject *parent) :
    QObject(parent),
    d_ptr(new QchWindowStackPrivate(this))
{
}

QchWindowStack::~QchWindowStack() {}

/*!
    \brief The window that is currently active.
*/
QchWindow* QchWindowStack::currentWindow() const {
    Q_D(const QchWindowStack);
    return d->stack.isEmpty() ? 0 : d->stack.last();
}

/*!
    \brief The initial window on the stack.
*/
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

/*!
    \brief The number of windows on the stack.
*/
int QchWindowStack::depth() const {
    Q_D(const QchWindowStack);
    return d->stack.size();
}

/*!
    \brief Pushes a window created from \a variant onto the stack, and optionally sets \a properties.
    
    The \a variant can be either a url or an instance of QDeclartiveComponent.
*/
QchWindow* QchWindowStack::push(const QVariant &variant, const QVariantMap &properties) {
    Q_D(QchWindowStack);
    
    if (QObject *obj = qvariant_cast<QObject*>(variant)) {
        if (QDeclarativeComponent *component = qobject_cast<QDeclarativeComponent*>(obj)) {
            return d->push(component, properties);
        }
        
        return 0;
    }
    
    return d->push(variant.toString(), properties);
}

/*!
    \brief Pops a window from the stack.
    
    If \a toWindow is specified, windows will be popped from the stack until \a toWindow becomes the current window.
*/
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

/*!
    \brief Pops all windows until the root window becomes the current window.
    
    \sa pop()
*/
void QchWindowStack::clear() {
    pop(rootWindow());
}

#include "moc_qchwindowstack.cpp"

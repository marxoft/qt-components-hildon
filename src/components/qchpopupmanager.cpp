/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchpopupmanager.h"
#include "qchdialogstatus.h"
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeInfo>

class QchPopupManagerPrivate
{

public:
    QchPopupManagerPrivate(QchPopupManager *parent) :
        q_ptr(parent)
    {
    }
    
    void setProperties(QObject *obj, const QVariantMap &properties) {        
        if (!properties.isEmpty()) {
            QMapIterator<QString, QVariant> iterator(properties);
            
            while (iterator.hasNext()) {
                iterator.next();
                obj->setProperty(iterator.key().toUtf8(), iterator.value());
            }
        }
    }
    
    void launch(QObject *obj, bool deleteOnClose) {
        if (QMetaObject::invokeMethod(obj, "open")) {
            if (deleteOnClose) {
                Q_Q(QchPopupManager);
                if (!q->connect(obj, SIGNAL(statusChanged()), q, SLOT(_q_onPopupStatusChanged()))) {
                    qmlInfo(q) << QchPopupManager::tr("The object has no statusChanged() signal.");
                }
            }
        }
        else {
            Q_Q(QchPopupManager);
            qmlInfo(q) << QchPopupManager::tr("The object has no open() method.");
        }        
    }
        
    QObject* open(QObject *obj, QObject *parent, const QVariantMap &properties, bool deleteOnClose) {
        obj->setParent(parent);
        setProperties(obj, properties);
        launch(obj, deleteOnClose);
        return obj;
    }
    
    QObject* open(QDeclarativeComponent *component, QObject *parent, const QVariantMap &properties) {
        Q_Q(QchPopupManager);
        QDeclarativeContext *context;
        
        if (parent) {
            context = new QDeclarativeContext(qmlContext(parent));
            context->setContextObject(parent);
        }
        else {
            QDeclarativeEngine *engine = qobject_cast<QDeclarativeEngine*>(q->parent());
        
            if (!engine) {
                qmlInfo(q) << QchPopupManager::tr("No QDeclarativeEngine instance found");
                return 0;
            }
            
            context = new QDeclarativeContext(engine);
        }        
    
        if (QObject *popup = component->beginCreate(context)) {
            popup->setParent(parent);
            context->setParent(popup);
            component->completeCreate();
            setProperties(popup, properties);            
            launch(popup, true);
            return popup;
        }
    
        if (!component->errors().isEmpty()) {
            qmlInfo(q, component->errors());
        }
        
        delete context;
        return 0;
    }
    
    QObject* open(const QUrl &url, QObject *parent, const QVariantMap &properties) {
        Q_Q(QchPopupManager);
        QDeclarativeEngine *engine = qobject_cast<QDeclarativeEngine*>(q->parent());
        
        if (!engine) {
            qmlInfo(q) << QchPopupManager::tr("No QDeclarativeEngine instance found");
            return 0;
        }
        
        QDeclarativeComponent *component = componentCache.value(url, 0);
        
        if (!component) {
            component = new QDeclarativeComponent(engine, url, q);
        }
        
        if (QObject *popup = open(component, parent, properties)) {
            componentCache.insert(url, component);
            return popup;
        }
        
        delete component;
        return 0;
    }
    
    void _q_onPopupStatusChanged() {
        Q_Q(QchPopupManager);
        
        if (QObject *popup = q->sender()) {
            if (QchDialogStatus::Status(popup->property("status").toInt()) == QchDialogStatus::Closed) {
                popup->deleteLater();
            }
        }
    }
    
    QchPopupManager *q_ptr;
    
    QHash<QUrl, QDeclarativeComponent*> componentCache;
    
    Q_DECLARE_PUBLIC(QchPopupManager)
};

/*!
    \class PopupManager
    
    \ingroup components
*/
QchPopupManager::QchPopupManager(QDeclarativeEngine *engine) :
    QObject(engine),
    d_ptr(new QchPopupManagerPrivate(this))
{
}

QchPopupManager::~QchPopupManager() {}

/*!
    \brief Opens the \a popup, assigns its parent to \a parent and sets the \a properties.
    
    The \a popup can be either a QDeclarativeComponent, a QObject or a QUrl. If \a popup is not a QObject,
    the resulting popup will be deleted when its status changes to DialogStatus.Closed.
*/
QObject* QchPopupManager::open(const QVariant &popup, QObject *parent, const QVariantMap &properties) {
    Q_D(QchPopupManager);
    
    if (QObject *obj = qvariant_cast<QObject*>(popup)) {
        if (QDeclarativeComponent *component = qobject_cast<QDeclarativeComponent*>(obj)) {
            return d->open(component, parent, properties);
        }
        
        return d->open(obj, parent, properties, false);
    }
    
    return d->open(popup.toString(), parent, properties);
}

#include "moc_qchpopupmanager.cpp"

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

#include "qchitemaction.h"
#include "qchgraphicsview.h"
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeItem>

class QchItemActionPrivate
{

public:
    QchItemActionPrivate(QchItemAction *parent) :
        q_ptr(parent),
        component(0)
    {
    }
        
    QchItemAction *q_ptr;
    QDeclarativeComponent *component;
    
    Q_DECLARE_PUBLIC(QchItemAction)
};

QchItemAction::QchItemAction(QObject *parent) :
    QWidgetAction(parent),
    d_ptr(new QchItemActionPrivate(this))
{
}

QchItemAction::~QchItemAction() {}

QDeclarativeComponent* QchItemAction::component() const {
    Q_D(const QchItemAction);
    return d->component;
}

void QchItemAction::setComponent(QDeclarativeComponent *c) {
    Q_D(QchItemAction);
    
    if (c != d->component) {
        QDeclarativeComponent *oldComponent = d->component;
        d->component = c;

        if (d->component) {
            d->component->setParent(this);
        }

        if (oldComponent) {
            delete oldComponent;
        }
    }
}

QWidget* QchItemAction::createWidget(QWidget *parent) {
    Q_D(QchItemAction);
    
    if (!d->component) {
        return 0;
    }
    
    QDeclarativeContext *creationContext = d->component->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));
    
    if (QObject *obj = d->component->beginCreate(context)) {
        if (QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(obj)) {
            QchGraphicsView *view = new QchGraphicsView(parent);
            view->addItem(item);
            view->setFixedHeight(70);
            context->setParent(item);
            d->component->completeCreate();
            return view;
        }

        delete obj;
        delete context;
    }
    else {
        delete context;
    }

    return 0;
}

#include "moc_qchitemaction.cpp"

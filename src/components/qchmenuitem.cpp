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

#include "qchmenuitem.h"
#include "qchexclusivegroup.h"
#include "qchitemaction.h"

class QchMenuItemPrivate
{

public:
    QchMenuItemPrivate(QchMenuItem *parent) :
        q_ptr(parent),
        qaction(0),
        component(0),
        group(0),
        checkable(false),
        checked(false),
        enabled(true),
        visible(true)
    {
    }
    
    QchMenuItem *q_ptr;
    QAction *qaction;
    QDeclarativeComponent *component;
    QchExclusiveGroup *group;
    
    bool checkable;
    bool checked;
    bool enabled;
    bool visible;
    
    QString iconName;
    QString iconSource;
    QString text;
    
    QVariant shortcut;
    
    Q_DECLARE_PUBLIC(QchMenuItem)
};

QchMenuItem::QchMenuItem(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuItemPrivate(this))
{
}

QchMenuItem::~QchMenuItem() {}

bool QchMenuItem::isCheckable() const {
    Q_D(const QchMenuItem);
    return d->checkable;
}

void QchMenuItem::setCheckable(bool c) {
    if (c != isCheckable()) {
        Q_D(QchMenuItem);
        d->checkable = c;
        emit checkableChanged();
                
        if (d->qaction) {
            d->qaction->setCheckable(c);
        }
        
        if (!c) {
            setChecked(false);
        }
    }
}

bool QchMenuItem::isChecked() const {
    Q_D(const QchMenuItem);
    return d->qaction ? d->qaction->isChecked() : d->checked;
}

void QchMenuItem::setChecked(bool c) {
    if (c != isChecked()) {
        Q_D(QchMenuItem);
        d->checked = c;
        
        if (d->qaction) {
            d->qaction->setChecked(c);
        }
        else {
            emit toggled(c);
        }
    }
}

QDeclarativeComponent* QchMenuItem::component() const {
    Q_D(const QchMenuItem);
    return d->component;
}

void QchMenuItem::setComponent(QDeclarativeComponent *c) {
    Q_D(QchMenuItem);
    
    if (c != d->component) {
        d->component = c;
        emit componentChanged();
        
        if (d->qaction) {
            if (QchItemAction *da = qobject_cast<QchItemAction*>(d->qaction)) {
                da->setComponent(c);
            }
        }
    }
}

bool QchMenuItem::isEnabled() const {
    Q_D(const QchMenuItem);
    return d->enabled;
}

void QchMenuItem::setEnabled(bool e) {
    if (e != isEnabled()) {
        Q_D(QchMenuItem);
        d->enabled = e;
        emit enabledChanged();
        
        if (d->qaction) {
            d->qaction->setEnabled(e);
        }
    }
}

QchExclusiveGroup* QchMenuItem::exclusiveGroup() const {
    Q_D(const QchMenuItem);
    return d->group;
}

void QchMenuItem::setExclusiveGroup(QchExclusiveGroup *group) {
    if (group != exclusiveGroup()) {
        Q_D(QchMenuItem);
        d->group = group;
        emit exclusiveGroupChanged();
        
        if (d->qaction) {
            d->qaction->setActionGroup(group);
        }
    }
}

QString QchMenuItem::iconName() const {
    Q_D(const QchMenuItem);
    return d->iconName;
}

void QchMenuItem::setIconName(const QString &name) {
    if (name != iconName()) {
        Q_D(QchMenuItem);
        d->iconName = name;
        emit iconChanged();
        
        if (d->qaction) {
            d->qaction->setIcon(QIcon::fromTheme(name));
        }
    }
}

QString QchMenuItem::iconSource() const { 
    Q_D(const QchMenuItem);
    return d->iconSource;
}

void QchMenuItem::setIconSource(const QString &source) {
    if (source != iconSource()) {
        Q_D(QchMenuItem);
        d->iconSource = source;
        emit iconChanged();
        
        if (d->qaction) {
            d->qaction->setIcon(QIcon(source));
        }
    }
}

QVariant QchMenuItem::shortcut() const {
    Q_D(const QchMenuItem);
    return d->shortcut;
}

void QchMenuItem::setShortcut(const QVariant &s) {
    if (s != shortcut()) {
        Q_D(QchMenuItem);
        d->shortcut = s;
        emit shortcutChanged();
        
        if (d->qaction) {
            switch (s.type()) {
            case QVariant::String:
                d->qaction->setShortcut(s.toString());
                break;
            case QVariant::Int:
            case QVariant::Double:
                d->qaction->setShortcut(s.toInt());
                break;
            default:
                break;
            }
        }
    }
}

QString QchMenuItem::text() const {
    Q_D(const QchMenuItem);
    return d->text;
}

void QchMenuItem::setText(const QString &t) {
    if (t != text()) {
        Q_D(QchMenuItem);
        d->text = t;
        emit textChanged();
        
        if (d->qaction) {
            d->qaction->setText(t);
        }
    }
}

bool QchMenuItem::isVisible() const {
    Q_D(const QchMenuItem);
    return d->visible;
}

void QchMenuItem::setVisible(bool v) {
    if (v != isVisible()) {
        Q_D(QchMenuItem);
        d->visible = v;
        emit visibleChanged();
        
        if (d->qaction) {
            d->qaction->setVisible(v);
        }
    }
}

QAction* QchMenuItem::toQAction() {
    Q_D(QchMenuItem);
    
    if (!d->qaction) {
        if (d->component) {
            QchItemAction *da = new QchItemAction(this);
            da->setComponent(d->component);
            d->qaction = da;
        }
        else {
            d->qaction = new QAction(this);
        }
        
        d->qaction->setCheckable(d->checkable);
        d->qaction->setChecked(d->checked);
        d->qaction->setEnabled(d->enabled);
        
        if (!d->iconSource.isEmpty()) {
            d->qaction->setIcon(QIcon(d->iconSource));
        }
        else if (!d->iconName.isEmpty()) {
            d->qaction->setIcon(QIcon::fromTheme(d->iconName));
        }
        
        if (d->group) {
            d->qaction->setActionGroup(d->group);
        }
        
        if (!d->shortcut.isNull()) {
            switch (d->shortcut.type()) {
            case QVariant::String:
                d->qaction->setShortcut(d->shortcut.toString());
                break;
            case QVariant::Int:
            case QVariant::Double:
                d->qaction->setShortcut(d->shortcut.toInt());
                break;
            default:
                break;
            }
        }
        
        d->qaction->setText(d->text);
        d->qaction->setVisible(d->visible);
        
        connect(d->qaction, SIGNAL(triggered()), this, SIGNAL(triggered()));
        connect(d->qaction, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
    }
    
    return d->qaction;
}

void QchMenuItem::toggle() {
    setChecked(!isChecked());
}

void QchMenuItem::trigger() {    
    if (isCheckable()) {
        setChecked(!isChecked());
    }
    
    Q_D(QchMenuItem);
    
    if (d->qaction) {
        d->qaction->trigger();
    }
    else {
        emit triggered();
    }
}

#include "moc_qchmenuitem.cpp"

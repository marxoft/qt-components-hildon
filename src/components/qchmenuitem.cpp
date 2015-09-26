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
#include "qchaction.h"
#include "qchexclusivegroup.h"
#include "qchitemaction.h"

class QchMenuItemPrivate
{

public:
    QchMenuItemPrivate(QchMenuItem *parent) :
        q_ptr(parent),
        action(0),
        qaction(0),
        component(0),
        group(0),
        autoRepeat(true),
        checkable(false),
        checked(false),
        enabled(true),
        visible(true)
    {
    }
    
    void _q_onActionCheckableChanged() {
        if ((action) && (qaction)) {
            qaction->setCheckable(action->isCheckable());
            Q_Q(QchMenuItem);
            emit q->checkableChanged();
        }
    }
        
    void _q_onActionEnabledChanged() {
        if ((action) && (qaction)) {
            qaction->setEnabled(action->isEnabled());
            Q_Q(QchMenuItem);
            emit q->enabledChanged();
        }
    }
    
    void _q_onActionIconChanged() {
        if ((action) && (iconName.isEmpty()) && (iconSource.isEmpty())) {
            if (!action->iconSource().isEmpty()) {
                Q_Q(QchMenuItem);
                q->setIconSource(action->iconSource());
            }
            else if (!action->iconName().isEmpty()) {
                Q_Q(QchMenuItem);
                q->setIconName(action->iconName());
            }
        }
    }
    
    void _q_onActionTextChanged() {
        if ((action) && (text.isEmpty())) {
            Q_Q(QchMenuItem);
            q->setText(action->text());
        }
    }
    
    void _q_onActionToggled(bool isChecked) {
        if ((action) && (qaction)) {
            qaction->setChecked(isChecked);
        }
    }
    
    void _q_onActionVisibleChanged() {
        if ((action) && (qaction)) {
            qaction->setVisible(action->isVisible());
            Q_Q(QchMenuItem);
            emit q->visibleChanged();
        }
    }
    
    void _q_onQActionToggled(bool isChecked) {
        checked = isChecked;
        
        if (!action) {
            Q_Q(QchMenuItem);
            emit q->toggled(isChecked);
        }
    }
    
    void _q_onQActionTriggered() {
        if (action) {
            action->trigger();
        }
        else {
            Q_Q(QchMenuItem);
            emit q->triggered();
        }
    }
        
        
    QchMenuItem *q_ptr;
    QchAction *action;
    QAction *qaction;
    QDeclarativeComponent *component;
    QchExclusiveGroup *group;
    
    bool autoRepeat;
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

/*!
    \class MenuItem
    \brief Represents an action in a Menu or MenuBar.
    
    \ingroup components
    
    The MenuItem is used to add an action to a Menu or MenuBar. MenuItem can also be used to display a 
    visual item that is declared as its child.
    
    \snippet menus.qml Menu
    
    \snippet menus.qml MenuBar
    
    \sa Menu, MenuBar
*/
QchMenuItem::QchMenuItem(QObject *parent) :
    QObject(parent),
    d_ptr(new QchMenuItemPrivate(this))
{
}

QchMenuItem::~QchMenuItem() {}

/*!
    \brief The Action associated with the menu item.
    
    The default value is \c null.
    
    \sa Action
*/
QchAction* QchMenuItem::action() const {
    Q_D(const QchMenuItem);
    return d->action;
}

void QchMenuItem::setAction(QchAction *a) {
    if (a != action()) {
        Q_D(QchMenuItem);
        
        if (d->action) {
            disconnect(d->action, 0, this, 0);
        }
        
        d->action = a;
        
        if (a) {
            connect(a, SIGNAL(checkableChanged()), this, SLOT(_q_onActionCheckableChanged()));
            connect(a, SIGNAL(enabledChanged()), this, SLOT(_q_onActionEnabledChanged()));
            connect(a, SIGNAL(iconChanged()), this, SLOT(_q_onActionIconChanged()));
            connect(a, SIGNAL(textChanged()), this, SLOT(_q_onActionTextChanged()));
            connect(a, SIGNAL(toggled(bool)), this, SLOT(_q_onActionToggled(bool)));
            connect(a, SIGNAL(triggered()), this, SIGNAL(triggered()));
            connect(a, SIGNAL(visibleChanged()), this, SLOT(_q_onActionVisibleChanged()));
                        
            d->_q_onActionCheckableChanged();
            d->_q_onActionEnabledChanged();
            d->_q_onActionIconChanged();
            d->_q_onActionTextChanged();
            d->_q_onActionVisibleChanged();
        }
        
        emit actionChanged();
    }
}

/*!
    \brief Whether the menu item should accept auto-repeated key events.
    
    The default value is \c true.
*/
bool QchMenuItem::autoRepeat() const {
    Q_D(const QchMenuItem);
    return d->autoRepeat;
}

void QchMenuItem::setAutoRepeat(bool a) {
    if (a != autoRepeat()) {
        Q_D(QchMenuItem);
        d->autoRepeat = a;

        if (d->qaction) {
            d->qaction->setAutoRepeat(a);
        }
        
        emit autoRepeatChanged();
    }
}

/*!
    \property bool MenuItem::checkable
    \brief Whether the menu item is checkable.
    
    The default value is \c false.
*/
bool QchMenuItem::isCheckable() const {
    Q_D(const QchMenuItem);
    return d->action ? d->action->isCheckable() : d->checkable;
}

void QchMenuItem::setCheckable(bool c) {
    if (c != isCheckable()) {
        Q_D(QchMenuItem);
        d->checkable = c;
                
        if (!c) {
            setChecked(false);
        }
        
        if (d->action) {
            return;
        }
        
        if (d->qaction) {
            d->qaction->setCheckable(c);
        }
        
        emit checkableChanged();
    }
}

/*!
    \property bool MenuItem::checked
    \brief Whether the menu item is checked.
    
    The default value is \c false.
*/
bool QchMenuItem::isChecked() const {
    Q_D(const QchMenuItem);
    return d->action ? d->action->isChecked() : d->checked;
}

void QchMenuItem::setChecked(bool c) {
    if ((c != isChecked()) && ((!c) || (isCheckable()))) {
        Q_D(QchMenuItem);
        d->checked = c;
        
        if (d->action) {
            return;
        }
        
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
            if (QchItemAction *ia = qobject_cast<QchItemAction*>(d->qaction)) {
                ia->setComponent(c);
            }
        }
    }
}

/*!
    \property bool MenuItem::enabled
    \brief Whether the menu item is enabled.
    
    The default value is \c true.
*/
bool QchMenuItem::isEnabled() const {
    Q_D(const QchMenuItem);
    return d->action ? d->action->isEnabled() : d->enabled;
}

void QchMenuItem::setEnabled(bool e) {
    if (e != isEnabled()) {
        Q_D(QchMenuItem);
        d->enabled = e;
        
        if (d->action) {
            return;
        }
        
        if (d->qaction) {
            d->qaction->setEnabled(e);
        }
        
        emit enabledChanged();
    }
}

/*!
    \brief The exclusive group to which the menu item belongs.
    
    The default value is \c null.
    
    \sa ExclusiveGroup
*/
QchExclusiveGroup* QchMenuItem::exclusiveGroup() const {
    Q_D(const QchMenuItem);
    return d->group;
}

void QchMenuItem::setExclusiveGroup(QchExclusiveGroup *group) {
    if (group != exclusiveGroup()) {
        Q_D(QchMenuItem);
        
        if (d->group) {
            d->group->removeCheckable(this);
        }
        
        d->group = group;
        
        if (group) {
            group->addCheckable(this);
        }
        
        emit exclusiveGroupChanged();      
    }
}

/*!
    \brief The name of the icon to be used.
    
    \sa iconSource
*/
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

/*!
    \brief The source of the icon to be used.
    
    \sa iconName
*/
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

/*!
    \brief The keyboard shorcut used to trigger the menu item.
*/
QVariant QchMenuItem::shortcut() const {
    Q_D(const QchMenuItem);
    return d->shortcut;
}

void QchMenuItem::setShortcut(const QVariant &s) {
    if (s != shortcut()) {
        Q_D(QchMenuItem);
        d->shortcut = s;
        
        if (d->qaction) {
            switch (s.type()) {
            case QVariant::Int:
            case QVariant::Double:
                d->qaction->setShortcut(s.toInt());
                break;
            default:
                d->qaction->setShortcut(s.toString());
                break;
            }
        }
        
        emit shortcutChanged();
    }
}

/*!
    \brief The text to be displayed in the menu item.
*/
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

/*!
    \property bool MenuItem::visible
    \brief Whether the menu item is visible in the menu.
    
    The default value is \c true.
*/
bool QchMenuItem::isVisible() const {
    Q_D(const QchMenuItem);
    return d->action ? d->action->isVisible() : d->visible;
}

void QchMenuItem::setVisible(bool v) {
    if (v != isVisible()) {
        Q_D(QchMenuItem);
        d->visible = v;
        
        if (d->action) {
            return;
        }
                
        if (d->qaction) {
            d->qaction->setVisible(v);
        }
        
        emit visibleChanged();
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
        
        d->qaction->setAutoRepeat(autoRepeat());
        d->qaction->setCheckable(isCheckable());
        d->qaction->setChecked(isChecked());
        d->qaction->setEnabled(isEnabled());
        
        if (!iconSource().isEmpty()) {
            d->qaction->setIcon(QIcon(iconSource()));
        }
        else if (!iconName().isEmpty()) {
            d->qaction->setIcon(QIcon::fromTheme(iconName()));
        }
                
        if (!shortcut().isNull()) {
            switch (shortcut().type()) {
            case QVariant::Int:
            case QVariant::Double:
                d->qaction->setShortcut(shortcut().toInt());
                break;
            default:
                d->qaction->setShortcut(shortcut().toString());
                break;
            }
        }
        
        d->qaction->setText(text());
        d->qaction->setVisible(isVisible());
        
        connect(d->qaction, SIGNAL(triggered()), this, SLOT(_q_onQActionTriggered()));
        connect(d->qaction, SIGNAL(toggled(bool)), this, SLOT(_q_onQActionToggled(bool)));
    }
    
    return d->qaction;
}

/*!
    \brief Toggle the \link checked\endlink property, if the menu item is \link checkable\endlink.
    
    \sa checkable, checked
*/
void QchMenuItem::toggle() {
    setChecked(!isChecked());
}

/*!
    \fn void MenuItem::triggered()
    \brief Emitted when the trigger() slot is called.
    
    \sa trigger()
*/

/*!
    \brief Triggers the menu item.
    
    \sa triggered()
*/
void QchMenuItem::trigger() {    
    Q_D(QchMenuItem);
    
    if (d->action) {
        d->action->trigger();
    }
    else if (d->qaction) {
        d->qaction->trigger();
    }
    else {
        if (isCheckable()) {
            setChecked(!isChecked());
        }
        
        emit triggered();
    }
}

#include "moc_qchmenuitem.cpp"

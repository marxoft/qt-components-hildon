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

#include "qchaction.h"
#include "qchexclusivegroup.h"
#include <QDeclarativeInfo>
#include <QShortcut>

class QchActionPrivate
{

public:
    QchActionPrivate(QchAction *parent) :
        q_ptr(parent),
        shortcut(0),
        group(0),
        checkable(false),
        checked(false),
        enabled(true),
        visible(true),
        complete(false)
    {
    }
    
    ~QchActionPrivate() {
        if (shortcut) {
            delete shortcut;
            shortcut = 0;
        }
    }
    
    void initShortcut() {
        Q_Q(QchAction);
        QWidget *widget = findParentWidget();
        
        if (!widget) {
            qmlInfo(q) << QchAction::tr("No widget found for QShortcut instance.");
            return;
        }
        
        shortcut = new QShortcut(widget);
        shortcut->setAutoRepeat(autoRepeat);
        shortcut->setEnabled(enabled);
        
        switch (shortcutKey.type()) {
        case QVariant::Int:
        case QVariant::Double:
            shortcut->setKey(shortcutKey.toInt());
            break;
        default:
            shortcut->setKey(shortcutKey.toString());
            break;
        }
        
        q->connect(shortcut, SIGNAL(activated()), q, SLOT(trigger()));
    }
    
    QWidget *findParentWidget() const {
        Q_Q(const QchAction);
        QObject *p = q->parent();
        
        while (p) {
            if (p->isWidgetType()) {
                return qobject_cast<QWidget*>(p);
            }
            
            p = p->parent();
        }
        
        return 0;
    }
    
    QchAction *q_ptr;
    QShortcut *shortcut;
    QchExclusiveGroup *group;
    
    bool autoRepeat;
    bool checkable;
    bool checked;
    bool enabled;
    bool visible;
    bool complete;
    
    QString iconName;
    QString iconSource;
    QString text;
    
    QVariant shortcutKey;
    
    Q_DECLARE_PUBLIC(QchAction)
};

/*!
    \class Action
    \brief Defines a common action that can be shared amongst interactive items.
    
    \ingroup components
        
    \include actions.qml
    
    \sa AbstractButton, MenuItem
*/
QchAction::QchAction(QObject *parent) :
    QObject(parent),
    d_ptr(new QchActionPrivate(this))
{
}

QchAction::~QchAction() {}

/*!
    \brief Whether the keyboard shortcut accepts auto-repeated events.
    
    The default value is \c true.
*/
bool QchAction::autoRepeat() const {
    Q_D(const QchAction);
    return d->autoRepeat;
}

void QchAction::setAutoRepeat(bool a) {
    if (a != autoRepeat()) {
        Q_D(QchAction);
        d->autoRepeat = a;
        emit autoRepeatChanged();
        
        if (d->shortcut) {
            d->shortcut->setAutoRepeat(a);
        }
    }
}

/*!
    \property bool Action::checkable
    \brief Whether the menu item is checkable.
    
    The default value is \c false.
*/
bool QchAction::isCheckable() const {
    Q_D(const QchAction);
    return d->checkable;
}

void QchAction::setCheckable(bool c) {
    if (c != isCheckable()) {
        Q_D(QchAction);
        d->checkable = c;
        emit checkableChanged();
    }
}

/*!
    \property bool Action::checked
    \brief Whether the menu item is checked.
    
    The default value is \c false.
*/
bool QchAction::isChecked() const {
    Q_D(const QchAction);
    return d->checked;
}

void QchAction::setChecked(bool c) {
    if ((c != isChecked()) && ((!c) || (isCheckable()))) {
        Q_D(QchAction);
        d->checked = c;
        emit toggled(c);
    }
}

/*!
    \property bool Action::enabled
    \brief Whether the action is enabled.
    
    The default value is \c true.
*/
bool QchAction::isEnabled() const {
    Q_D(const QchAction);
    return d->enabled;
}

void QchAction::setEnabled(bool e) {
    if (e != isEnabled()) {
        Q_D(QchAction);
        d->enabled = e;
        emit enabledChanged();
        
        if (d->shortcut) {
            d->shortcut->setEnabled(e);
        }
    }
}

/*!
    \brief The ExclusiveGroup to which the action belongs.
    
    The default value is \c null.
    
    \sa ExclusiveGroup
*/
QchExclusiveGroup* QchAction::exclusiveGroup() const {
    Q_D(const QchAction);
    return d->group;
}

void QchAction::setExclusiveGroup(QchExclusiveGroup *group) {
    if (group != exclusiveGroup()) {
        Q_D(QchAction);
        
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
QString QchAction::iconName() const {
    Q_D(const QchAction);
    return d->iconName;
}

void QchAction::setIconName(const QString &name) {
    if (name != iconName()) {
        Q_D(QchAction);
        d->iconName = name;
        emit iconChanged();
    }
}

/*!
    \brief The source of the icon to be used.
    
    \sa iconName
*/
QString QchAction::iconSource() const { 
    Q_D(const QchAction);
    return d->iconSource;
}

void QchAction::setIconSource(const QString &source) {
    if (source != iconSource()) {
        Q_D(QchAction);
        d->iconSource = source;
        emit iconChanged();
    }
}

/*!
    \brief The keyboard shorcut used to trigger the action.
*/
QVariant QchAction::shortcut() const {
    Q_D(const QchAction);
    return d->shortcutKey;
}

void QchAction::setShortcut(const QVariant &s) {
    if (s != shortcut()) {
        Q_D(QchAction);
        d->shortcutKey = s;
        emit shortcutChanged();
        
        if (d->shortcut) {
            switch (s.type()) {
            case QVariant::Int:
            case QVariant::Double:
                d->shortcut->setKey(s.toInt());
                break;
            default:
                d->shortcut->setKey(s.toString());
                break;
            }
        }
        else if ((d->complete) && (!s.isNull())) {
            d->initShortcut();
        }
    }
}

/*!
    \brief The text to be displayed.
*/
QString QchAction::text() const {
    Q_D(const QchAction);
    return d->text;
}

void QchAction::setText(const QString &t) {
    if (t != text()) {
        Q_D(QchAction);
        d->text = t;
        emit textChanged();
    }
}

/*!
    \property bool Action::visible
    \brief Whether the items using the action should be visible.
    
    The default value is \c true.
*/
bool QchAction::isVisible() const {
    Q_D(const QchAction);
    return d->visible;
}

void QchAction::setVisible(bool v) {
    if (v != isVisible()) {
        Q_D(QchAction);
        d->visible = v;
        emit visibleChanged();
        
        if (d->shortcut) {
            d->shortcut->setEnabled(v);
        }
    }
}

/*!
    \brief Toggle the \link checked\endlink property, if the action is \link checkable\endlink.
    
    \sa checkable, checked
*/
void QchAction::toggle() {
    setChecked(!isChecked());
}

/*!
    \fn void Action::triggered()
    \brief Emitted when the trigger() slot is called.
    
    \sa trigger()
*/

/*!
    \brief Triggers the action.
    
    \sa triggered()
*/
void QchAction::trigger() {
    if (isCheckable()) {
        setChecked(!isChecked());
    }
    
    emit triggered();
}

void QchAction::classBegin() {}

void QchAction::componentComplete() {
    Q_D(QchAction);
    d->complete = true;
    
    if (!d->shortcutKey.isNull()) {
        d->initShortcut();
    }
}

#include "moc_qchaction.cpp"

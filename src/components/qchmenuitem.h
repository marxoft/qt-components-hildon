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

#ifndef QCHMENUITEM_H
#define QCHMENUITEM_H

#include <QObject>
#include <qdeclarative.h>

class QAction;
class QDeclarativeComponent;
class QchExclusiveGroup;
class QchMenuItemPrivate;

class QchMenuItem : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable NOTIFY checkableChanged)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(QDeclarativeComponent* component READ component WRITE setComponent NOTIFY componentChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QchExclusiveGroup* exclusiveGroup READ exclusiveGroup WRITE setExclusiveGroup NOTIFY exclusiveGroupChanged)
    Q_PROPERTY(QString iconName READ iconName WRITE setIconName NOTIFY iconChanged)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY iconChanged)
    Q_PROPERTY(QVariant shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    
    Q_CLASSINFO("DefaultProperty", "component")

public:
    explicit QchMenuItem(QObject *parent = 0);
    ~QchMenuItem();
    
    bool isCheckable() const;
    void setCheckable(bool c);
    
    bool isChecked() const;
    void setChecked(bool c);
        
    QDeclarativeComponent* component() const;
    void setComponent(QDeclarativeComponent *c);
    
    bool isEnabled() const;
    void setEnabled(bool e);
    
    QchExclusiveGroup* exclusiveGroup() const;
    void setExclusiveGroup(QchExclusiveGroup *group);
    
    QString iconName() const;
    void setIconName(const QString &name);
    
    QString iconSource() const;
    void setIconSource(const QString &source);
    
    QVariant shortcut() const;
    void setShortcut(const QVariant &s);
    
    QString text() const;
    void setText(const QString &t);
    
    bool isVisible() const;
    void setVisible(bool v);
    
    QAction* toQAction();

public Q_SLOTS:
    void toggle();
    void trigger();

Q_SIGNALS:
    void checkableChanged();
    void componentChanged();
    void enabledChanged();
    void exclusiveGroupChanged();
    void iconChanged();
    void shortcutChanged();
    void textChanged();
    void toggled(bool checked);
    void triggered();
    void visibleChanged();

protected:
    QScopedPointer<QchMenuItemPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchMenuItem)

private:
    Q_DISABLE_COPY(QchMenuItem)
};

QML_DECLARE_TYPE(QchMenuItem)

#endif // QCHMENUITEM_H

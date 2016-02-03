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

#ifndef QCHMENU_H
#define QCHMENU_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchMenuItem;
class QchMenuPrivate;

class QchMenu : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString iconName READ iconName WRITE setIconName NOTIFY iconChanged)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY iconChanged)
    Q_PROPERTY(QDeclarativeListProperty<QObject> items READ items)
    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
    Q_CLASSINFO("DefaultProperty", "items")
    
public:
    explicit QchMenu(QObject *parent = 0);
    ~QchMenu();
    
    QDeclarativeListProperty<QObject> items();
    
    bool isEnabled() const;
    void setEnabled(bool e);
    
    QString iconName() const;
    void setIconName(const QString &name);
    
    QString iconSource() const;
    void setIconSource(const QString &source);
    
    QString title() const;
    void setTitle(const QString &t);
    
    bool isVisible() const;
    void setVisible(bool v);

public Q_SLOTS:
    QchMenuItem* addItem(const QString &text);
    QchMenuItem* insertItem(int before, const QString &text);
    
    QchMenu* addMenu(const QString &title);
    QchMenu* insertMenu(int before, const QString &title);
    
    void removeItem(QObject *item);
    
    void popup();

Q_SIGNALS:
    void aboutToHide();
    void aboutToShow();
    void enabledChanged();
    void iconChanged();
    void parentChanged();
    void titleChanged();
    void visibleChanged();
    
protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual bool event(QEvent *e);
    
    QScopedPointer<QchMenuPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchMenu)

private:
    Q_DISABLE_COPY(QchMenu)
};

QML_DECLARE_TYPE(QchMenu)
    
#endif // QCHMENU_H

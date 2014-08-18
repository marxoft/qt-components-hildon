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

#ifndef ITEMACTION_P_H
#define ITEMACTION_P_H

#include <QWidgetAction>
#include <qdeclarative.h>

class QDeclarativeComponent;
class ItemActionPrivate;

class ItemAction : public QWidgetAction
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString icon READ iconSource WRITE setIconSource NOTIFY iconChanged)
    Q_PROPERTY(QString shortcut READ shortcutString WRITE setShortcutString NOTIFY shortcutChanged)
    Q_PROPERTY(QDeclarativeComponent* item READ item WRITE setItem NOTIFY itemChanged)

public:
    explicit ItemAction(QObject *parent = 0);
    ~ItemAction();

    QString iconSource() const;
    void setIconSource(const QString &source);

    QString shortcutString() const;
    void setShortcutString(const QString &shortcut);

    QDeclarativeComponent* item() const;
    void setItem(QDeclarativeComponent *item);

signals:
    void enabledChanged();
    void iconChanged();
    void shortcutChanged();
    void itemChanged();

protected:
    virtual QWidget* createWidget(QWidget *parent);

    virtual bool event(QEvent *event);

    ItemAction(ItemActionPrivate &dd, QObject *parent = 0);

    QScopedPointer<ItemActionPrivate> d_ptr;

    Q_DECLARE_PRIVATE(ItemAction)

private:
    Q_DISABLE_COPY(ItemAction)
};

QML_DECLARE_TYPE(ItemAction)

#endif // ITEMACTION_P_H

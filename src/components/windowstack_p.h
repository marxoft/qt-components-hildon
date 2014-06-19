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

#ifndef WINDOWSTACK_P_H
#define WINDOWSTACK_P_H

#include <QObject>
#include <QVariantMap>
#include <QDeclarativeComponent>

class Window;
class WindowStackPrivate;

class WindowStack : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int depth READ depth NOTIFY countChanged)
    Q_PROPERTY(Window* currentWindow READ currentWindow NOTIFY currentWindowChanged)

public:
    ~WindowStack();

    static WindowStack* instance();

    int depth() const;

    Window* currentWindow() const;
    Window* rootWindow() const;
        
public slots:
    void push(QObject *window);
    void push(const QUrl &url);
    void push(const QUrl &url, const QVariantMap &data);

    void pop();
    void pop(QObject *window);
    void pop(const QString &objectName);

signals:
    void countChanged();
    void currentWindowChanged();
    
private:
    WindowStack();

    static WindowStack *self;

    QScopedPointer<WindowStackPrivate> d_ptr;

    friend class Window;
    friend class Plugin;

    Q_DISABLE_COPY(WindowStack)
    Q_DECLARE_PRIVATE(WindowStack)

    Q_PRIVATE_SLOT(d_func(), void _q_onWindowStatusChanged(QDeclarativeComponent::Status))
};

#endif // WINDOWSTACK_P_H

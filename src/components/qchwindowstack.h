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

#ifndef QCHWINDOWSTACK_H
#define QCHWINDOWSTACK_H

#include <QObject>
#include <qdeclarative.h>

class QDeclarativeComponent;
class QchWindow;
class QchWindowStackPrivate;

class QchWindowStack : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QchWindow* currentWindow READ currentWindow NOTIFY currentChanged)
    Q_PROPERTY(QchWindow* rootWindow READ rootWindow WRITE setRootWindow)
    Q_PROPERTY(int depth READ depth NOTIFY currentChanged)

public:
    explicit QchWindowStack(QObject *parent = 0);
    ~QchWindowStack();
    
    QchWindow* currentWindow() const;
    QchWindow* rootWindow() const;
    void setRootWindow(QchWindow *root);
    
    int depth() const;
    
public Q_SLOTS:
    QchWindow* push(QDeclarativeComponent* component, const QVariantMap &properties = QVariantMap());
    QchWindow* push(const QUrl &url, const QVariantMap &properties = QVariantMap());
    
    void pop(QchWindow *toWindow = 0);
    
    void clear();

Q_SIGNALS:
    void currentChanged();

protected:
    QScopedPointer<QchWindowStackPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchWindowStack)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onWindowHidden(QchWindow*));

private:
    Q_DISABLE_COPY(QchWindowStack)
};

QML_DECLARE_TYPE(QchWindowStack)

#endif // QCHWINDOWSTACK_H

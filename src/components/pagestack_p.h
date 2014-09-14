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

#ifndef PAGESTACK_P_H
#define PAGESTACK_P_H

#include <QObject>
#include <QVariantMap>
#include <qdeclarative.h>

class QWidget;
class PageStackPrivate;

class PageStack : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int depth READ depth NOTIFY countChanged)
    Q_PROPERTY(QWidget* currentPage READ currentPage NOTIFY currentPageChanged)
    Q_PROPERTY(QWidget* rootPage READ rootPage CONSTANT)

public:
    explicit PageStack(QWidget *parent);
    ~PageStack();

    int depth() const;

    QWidget* currentPage() const;
    QWidget* rootPage() const;
        
public slots:
    void push(QWidget *page);
    void push(const QUrl &url);
    void push(const QUrl &url, const QVariantMap &data);

    void pop();
    void pop(QWidget *page);
    void pop(const QString &objectName);

signals:
    void countChanged();
    void currentPageChanged();
    
protected:
    PageStack(PageStackPrivate &dd, QWidget *parent);

    QScopedPointer<PageStackPrivate> d_ptr;

    Q_DECLARE_PRIVATE(PageStack)

    Q_PRIVATE_SLOT(d_func(), void _q_onPageStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onPageClosed(QObject*))

private:
    Q_DISABLE_COPY(PageStack)
};

QML_DECLARE_TYPE(PageStack)

#endif // PAGESTACK_P_H

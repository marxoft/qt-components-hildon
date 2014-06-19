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

#ifndef MENU_P_H
#define MENU_P_H

#include <QMenu>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class MenuPrivate;

class Menu : public QMenu, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)
    Q_PROPERTY(int width READ width WRITE setFixedWidth)
    Q_PROPERTY(int height READ height WRITE setFixedHeight)
    Q_PROPERTY(QString icon READ iconSource WRITE setIconSource)
    Q_PRIVATE_PROPERTY(Menu::d_func(), QDeclarativeListProperty<QObject> data READ data)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

    void setX(int x);
    void setY(int y);

    QString iconSource() const;
    void setIconSource(const QString &source);

    QDeclarativeListProperty<QObject> data();

public slots:
    void open(const QPoint &pos);

signals:
    void parentChanged();

private:
    Menu(MenuPrivate &dd, QWidget *parent);

    void changeEvent(QEvent *event);

    void classBegin();
    void componentComplete();

    QScopedPointer<MenuPrivate> d_ptr;

    Q_DISABLE_COPY(Menu)
    Q_DECLARE_PRIVATE(Menu)
};

QML_DECLARE_TYPE(Menu)

#endif // MENU_P_H

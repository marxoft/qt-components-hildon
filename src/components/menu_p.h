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
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString icon READ iconSource WRITE setIconSource NOTIFY iconChanged)
    Q_PRIVATE_PROPERTY(Menu::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(Menu::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)
    Q_PRIVATE_PROPERTY(Menu::d_func(), Style* style READ style WRITE setStyle RESET resetStyle)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    QString iconSource() const;
    void setIconSource(const QString &source);

    QDeclarativeListProperty<QObject> data();

public slots:
    void open(const QPoint &pos);

signals:
    void parentChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();
    void iconChanged();

protected:
    Menu(MenuPrivate &dd, QWidget *parent);

    virtual void changeEvent(QEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<MenuPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Menu)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onStyleChanged());

private:
    Q_DISABLE_COPY(Menu)
};

QML_DECLARE_TYPE(Menu)

#endif // MENU_P_H

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

#include "tabbar_p.h"
#include "tabbar_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

TabButton::TabButton(QObject *parent) :
    QObject(parent),
    m_index(0)
{
}

TabButton::~TabButton() {}

QString TabButton::text() const {
    return m_text;
}

void TabButton::setText(const QString &text) {
    if (text != this->text()) {
        m_text = text;

        if (QTabBar *bar = qobject_cast<QTabBar*>(this->parent())) {
            bar->setTabText(m_index, text);
        }

        emit textChanged();
    }
}

QString TabButton::icon() const {
    return m_icon;
}

void TabButton::setIcon(const QString &icon) {
    if (icon != this->icon()) {
        m_icon = icon;

        if (QTabBar *bar = qobject_cast<QTabBar*>(this->parent())) {
            bar->setTabIcon(m_index, QIcon(icon));
        }

        emit iconChanged();
    }
}

TabBar::TabBar(QWidget *parent) :
    QTabBar(parent),
    d_ptr(new TabBarPrivate(this))
{
}

TabBar::TabBar(TabBarPrivate &dd, QWidget *parent) :
    QTabBar(parent),
    d_ptr(&dd)
{
}

TabBar::~TabBar() {}

void TabBar::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void TabBar::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal TabBar::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void TabBar::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine TabBar::left() const {
    Q_D(const TabBar);

    return d->left;
}

AnchorLine TabBar::right() const {
    Q_D(const TabBar);

    return d->right;
}

AnchorLine TabBar::top() const {
    Q_D(const TabBar);

    return d->top;
}

AnchorLine TabBar::bottom() const {
    Q_D(const TabBar);

    return d->bottom;
}

AnchorLine TabBar::horizontalCenter() const {
    Q_D(const TabBar);

    return d->horizontalCenter;
}

AnchorLine TabBar::verticalCenter() const {
    Q_D(const TabBar);

    return d->verticalCenter;
}

void TabBar::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QTabBar::changeEvent(event);
}

void TabBar::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QTabBar::moveEvent(event);
}

void TabBar::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QTabBar::resizeEvent(event);
}

void TabBar::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QTabBar::showEvent(event);
}

void TabBar::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QTabBar::hideEvent(event);
}

void TabBar::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QTabBar::focusInEvent(event);
}

void TabBar::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QTabBar::focusOutEvent(event);
}

void TabBar::classBegin() {}

void TabBar::componentComplete() {
    Q_D(TabBar);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    foreach (QObject *obj, d->dataList) {
        if (TabButton *button = qobject_cast<TabButton*>(obj)) {
           button->m_index = this->addTab(QIcon(button->icon()), button->text());
        }
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void TabBarPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TabBar *bar = qobject_cast<TabBar*>(list->object)) {
        bar->d_func()->dataList.append(obj);


        if (QWidget *widget = qobject_cast<QWidget*>(obj)) {
            bar->d_func()->childrenList.append(widget);
        }

        if (!bar->d_func()->complete) {
            return;
        }

        if (TabButton *button = qobject_cast<TabButton*>(obj)) {
            button->m_index = bar->addTab(QIcon(button->icon()), button->text());
        }
    }
}

void TabBarPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (TabBar *bar = qobject_cast<TabBar*>(list->object)) {
        bar->d_func()->childrenList.append(widget);
        bar->d_func()->dataList.append(widget);
    }
}

void TabBarPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (TabBar *bar = qobject_cast<TabBar*>(list->object)) {
        bar->d_func()->actionList.append(obj);
        bar->d_func()->dataList.append(obj);

        if (!bar->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            bar->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            bar->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> TabBarPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TabBarPrivate::data_append);
}

QDeclarativeListProperty<QWidget> TabBarPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, TabBarPrivate::children_append);
}

QDeclarativeListProperty<QObject> TabBarPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, TabBarPrivate::actions_append);
}

#include "moc_tabbar_p.cpp"

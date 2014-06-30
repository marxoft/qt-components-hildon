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

#include "window_p.h"
#include "window_p_p.h"
#include "windowstack_p_p.h"
#include "separator_p.h"
#include <QMenuBar>
#include <QToolBar>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

Window::Window(QWidget *parent) :
    QMainWindow(!parent ? WindowStack::instance()->currentWindow() : parent),
    d_ptr(new WindowPrivate(this))
{
    this->setAttribute(Qt::WA_Maemo5StackedWindow, true);
    this->setAttribute(Qt::WA_DeleteOnClose, WindowStack::instance()->depth() > 0);
    this->setOrientationLock(Screen::instance()->orientationLock());
    this->connect(Screen::instance(), SIGNAL(orientationLockChanged(Screen::Orientation)), this, SLOT(setOrientationLock(Screen::Orientation)));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Screen::Orientation)), this, SIGNAL(inPortraitChanged()));
}

Window::Window(WindowPrivate &dd, QWidget *parent) :
    QMainWindow(!parent ? WindowStack::instance()->currentWindow() : parent),
    d_ptr(&dd)
{
    this->setAttribute(Qt::WA_Maemo5StackedWindow, true);
    this->setAttribute(Qt::WA_DeleteOnClose, WindowStack::instance()->depth() > 0);
    this->setOrientationLock(Screen::instance()->orientationLock());
    this->connect(Screen::instance(), SIGNAL(orientationLockChanged(Screen::Orientation)), this, SLOT(setOrientationLock(Screen::Orientation)));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Screen::Orientation)), this, SIGNAL(inPortraitChanged()));
}

Window::~Window() {}

Screen::Orientation Window::orientationLock() const {
    Q_D(const Window);

    return d->orientation;
}

void Window::setOrientationLock(Screen::Orientation orientation) {
    if (orientation != this->orientationLock()) {
        Q_D(Window);
        d->orientation = orientation;
        this->setAttribute(Qt::WidgetAttribute(orientation), true);
        emit orientationLockChanged();
    }
}

bool Window::inPortrait() const {
    return Screen::instance()->currentOrientation() == Screen::PortraitOrientation;
}

void Window::setFullScreen(bool fullScreen) {
    if (fullScreen) {
        this->showFullScreen();
    }
    else {
        this->showMaximized();
    }
}

bool Window::showingProgressIndicator() const {
    return this->testAttribute(Qt::WA_Maemo5ShowProgressIndicator);
}

void Window::showProgressIndicator(bool show) {
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, show);
}

void Window::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Window::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Window::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Window::setOpacity(qreal opacity) {
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

AnchorLine Window::left() const {
    Q_D(const Window);

    return d->left;
}

AnchorLine Window::right() const {
    Q_D(const Window);

    return d->right;
}

AnchorLine Window::top() const {
    Q_D(const Window);

    return d->top;
}

AnchorLine Window::bottom() const {
    Q_D(const Window);

    return d->bottom;
}

AnchorLine Window::horizontalCenter() const {
    Q_D(const Window);

    return d->horizontalCenter;
}

AnchorLine Window::verticalCenter() const {
    Q_D(const Window);

    return d->verticalCenter;
}

void Window::showEvent(QShowEvent *event) {
    if (WindowStack::instance()->currentWindow() != this) {
        WindowStack::instance()->d_func()->stack.append(this);
        emit WindowStack::instance()->currentWindowChanged();
        emit WindowStack::instance()->countChanged();
    }

    emit visibleChanged();
    QMainWindow::showEvent(event);
}

void Window::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QMainWindow::hideEvent(event);
}

void Window::closeEvent(QCloseEvent *event) {
    WindowStack::instance()->d_func()->stack.removeOne(this);
    QMainWindow::closeEvent(event);
}

void Window::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    default:
        break;
    }

    QMainWindow::changeEvent(event);
}

void Window::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QMainWindow::moveEvent(event);
}

void Window::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QMainWindow::resizeEvent(event);
}

void Window::classBegin() {}

void Window::componentComplete() {
    Q_D(Window);

    d->componentComplete();

    if (WindowStack::instance()->depth() == 0) {
        this->showMaximized();
    }
    else if (d->qmlVisible()) {
        this->show();
    }
}

void WindowPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Window *window = qobject_cast<Window*>(list->object)) {
        window->d_func()->dataList.append(obj);
    }
}

void WindowPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Window *window = qobject_cast<Window*>(list->object)) {
        window->d_func()->actionList.append(obj);

        if (!window->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            window->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            window->addActions(group->actions());
        }
    }
}

void WindowPrivate::tools_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Window *window = qobject_cast<Window*>(list->object)) {
        window->d_func()->toolList.append(obj);

        if (!window->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            window->menuBar()->addAction(action);
        }
        else if (QMenu *menu = qobject_cast<QMenu*>(obj)) {
            window->menuBar()->addMenu(menu);
        }
        else if (QToolBar *toolBar = qobject_cast<QToolBar*>(obj)) {
            window->addToolBar(Qt::BottomToolBarArea, toolBar);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            window->menuBar()->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> WindowPrivate::tools() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WindowPrivate::tools_append);
}

QDeclarativeListProperty<QObject> WindowPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WindowPrivate::data_append);
}

QDeclarativeListProperty<QObject> WindowPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WindowPrivate::actions_append);
}

void WindowPrivate::componentComplete() {
    Q_Q(Window);

    foreach (QObject *obj, toolList) {
        if (QAction *action = qobject_cast<QAction*>(obj)) {
            q->menuBar()->addAction(action);
        }
        else if (QMenu *menu = qobject_cast<QMenu*>(obj)) {
            q->menuBar()->addMenu(menu);
        }
        else if (QToolBar *toolBar = qobject_cast<QToolBar*>(obj)) {
            q->addToolBar(Qt::BottomToolBarArea, toolBar);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            q->menuBar()->addActions(group->actions());
        }
    }

    ItemPrivate::componentComplete();
}

#include "moc_window_p.cpp"

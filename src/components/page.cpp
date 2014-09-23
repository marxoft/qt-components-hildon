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

#include "page_p.h"
#include "page_p_p.h"
#include "separator_p.h"
#include <QMenuBar>
#include <QToolBar>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>

Page::Page(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new PagePrivate(this))
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setOrientationLock(Screen::instance()->orientationLock());
    this->connect(Screen::instance(), SIGNAL(orientationLockChanged(Screen::Orientation)), this, SLOT(setOrientationLock(Screen::Orientation)));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Screen::Orientation)), this, SIGNAL(inPortraitChanged()));
}

Page::Page(PagePrivate &dd, QWidget *parent) :
    QMainWindow(parent),
    d_ptr(&dd)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setOrientationLock(Screen::instance()->orientationLock());
    this->connect(Screen::instance(), SIGNAL(orientationLockChanged(Screen::Orientation)), this, SLOT(setOrientationLock(Screen::Orientation)));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Screen::Orientation)), this, SIGNAL(inPortraitChanged()));
}

Page::~Page() {}

Screen::Orientation Page::orientationLock() const {
    Q_D(const Page);

    return d->orientation;
}

void Page::setOrientationLock(Screen::Orientation orientation) {
    if (orientation != this->orientationLock()) {
        Q_D(Page);
        d->orientation = orientation;
        this->setAttribute(Qt::WidgetAttribute(orientation), true);
        emit orientationLockChanged();
    }
}

bool Page::inPortrait() const {
    return Screen::instance()->currentOrientation() == Screen::PortraitOrientation;
}

void Page::setFullScreen(bool fullScreen) {
    if (this->isFullScreen() != fullScreen) {
        if (fullScreen) {
            this->showFullScreen();
        }
        else {
            this->showMaximized();
        }

        emit fullScreenChanged();
    }
}

bool Page::showingProgressIndicator() const {
    return this->testAttribute(Qt::WA_Maemo5ShowProgressIndicator);
}

void Page::showProgressIndicator(bool show) {
    this->setAttribute(Qt::WA_Maemo5ShowProgressIndicator, show);
}

bool Page::autoClose() const {
    Q_D(const Page);
    
    return d->autoClose;
}

void Page::setAutoClose(bool close) {
    if (close != this->autoClose()) {
        Q_D(Page);
        d->autoClose = close;
        emit autoCloseChanged();
    }
}

void Page::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void Page::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal Page::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void Page::setOpacity(qreal opacity) {
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

AnchorLine Page::left() const {
    Q_D(const Page);

    return d->left;
}

AnchorLine Page::right() const {
    Q_D(const Page);

    return d->right;
}

AnchorLine Page::top() const {
    Q_D(const Page);

    return d->top;
}

AnchorLine Page::bottom() const {
    Q_D(const Page);

    return d->bottom;
}

AnchorLine Page::horizontalCenter() const {
    Q_D(const Page);

    return d->horizontalCenter;
}

AnchorLine Page::verticalCenter() const {
    Q_D(const Page);

    return d->verticalCenter;
}

void Page::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QMainWindow::showEvent(event);
}

void Page::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QMainWindow::hideEvent(event);
}

void Page::closeEvent(QCloseEvent *event) {
    if (this->autoClose()) {
        QMainWindow::closeEvent(event);
    }
    else {
        event->ignore();
        emit closeRequest();
    }
}

void Page::changeEvent(QEvent *event) {
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

    QMainWindow::changeEvent(event);
}

void Page::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QMainWindow::moveEvent(event);
}

void Page::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QMainWindow::resizeEvent(event);
}

void Page::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QMainWindow::focusInEvent(event);
}

void Page::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QMainWindow::focusOutEvent(event);
}

void Page::classBegin() {}

void Page::componentComplete() {
    Q_D(Page);

    d->componentComplete();

    if (d->qmlVisible()) {
        this->show();
    }
}

void PagePrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Page *page = qobject_cast<Page*>(list->object)) {
        page->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            page->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void PagePrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (Page *page = qobject_cast<Page*>(list->object)) {
        page->d_func()->childrenList.append(widget);
        page->d_func()->dataList.append(widget);
    }
}

void PagePrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Page *page = qobject_cast<Page*>(list->object)) {
        page->d_func()->actionList.append(obj);
        page->d_func()->dataList.append(obj);

        if (!page->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            page->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            page->addActions(group->actions());
        }
    }
}

void PagePrivate::tools_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (Page *page = qobject_cast<Page*>(list->object)) {
        page->d_func()->toolList.append(obj);
        page->d_func()->dataList.append(obj);

        if (!page->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            page->menuBar()->addAction(action);
        }
        else if (QMenu *menu = qobject_cast<QMenu*>(obj)) {
            page->menuBar()->addMenu(menu);
        }
        else if (QToolBar *toolBar = qobject_cast<QToolBar*>(obj)) {
            page->addToolBar(Qt::BottomToolBarArea, toolBar);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            page->menuBar()->addActions(group->actions());
        }
    }
}

QDeclarativeListProperty<QObject> PagePrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, PagePrivate::data_append);
}

QDeclarativeListProperty<QWidget> PagePrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, PagePrivate::children_append);
}

QDeclarativeListProperty<QObject> PagePrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, PagePrivate::actions_append);
}

QDeclarativeListProperty<QObject> PagePrivate::tools() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, PagePrivate::tools_append);
}

void PagePrivate::componentComplete() {
    Q_Q(Page);

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

#include "moc_page_p.cpp"

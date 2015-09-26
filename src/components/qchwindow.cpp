/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchwindow.h"
#include "qchcloseevent.h"
#include "qchgraphicsview.h"
#include "qchmenubar.h"
#include "qchscreen.h"
#include <QDeclarativeItem>
#include <QCloseEvent>

class QchWindowPrivate
{

public:
    QchWindowPrivate(QchWindow *parent) :
        q_ptr(parent),
        menu(0),
        view(0),
        root(0),
        orientationLock(Qt::WA_Maemo5LandscapeOrientation),
        status(QchWindowStatus::Inactive)
    {
    }
    
    static void children_append(QDeclarativeListProperty<QDeclarativeItem> *list, QDeclarativeItem *item) {        
        if (!item) {
            return;
        }
        
        if (QchWindow *window = qobject_cast<QchWindow*>(list->object)) {
            if (QDeclarativeItem *root = window->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }
        
        if (QchWindow *window = qobject_cast<QchWindow*>(list->object)) {
            if (obj->isWidgetType()) {
                obj->setParent(window);
            }
            else if (QDeclarativeItem *root = window->d_func()->root) {
                obj->setParent(root);
                
                if (QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(obj)) {
                    item->setParentItem(root);
                }
            }
        }
    }
    
    void init() {
        Q_Q(QchWindow);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        root->setParent(view);
        view->addItem(root);
        q->setCentralWidget(view);
        q->setOrientationLock(QchScreen::instance()->orientationLock());
        q->connect(QchScreen::instance(), SIGNAL(orientationLockChanged(int)), q, SLOT(setOrientationLock(int)));
    }
    
    QchMenuBar* menuBar() const {
        return menu;
    }
    
    void setMenuBar(QchMenuBar *m) {
        menu = m;
    }
        
    QchWindow *q_ptr;
    
    QchMenuBar *menu;
    
    QchGraphicsView *view;
    QDeclarativeItem *root;
    
    int orientationLock;
    
    QchWindowStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchWindow)
};

/*!
    \class Window
    \brief A window component that can be stacked or used as a top-level window.
    
    \ingroup components
    
    \sa ApplicationWindow, WindowStack
*/
QchWindow::QchWindow(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new QchWindowPrivate(this))
{
    setAttribute(Qt::WA_Maemo5StackedWindow, true);
    Q_D(QchWindow);
    d->init();
}

QchWindow::~QchWindow() {}

/*!
    \brief The visual children of the window.
*/
QDeclarativeListProperty<QDeclarativeItem> QchWindow::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchWindowPrivate::children_append);
}

/*!
    \brief The children of the window.
*/
QDeclarativeListProperty<QObject> QchWindow::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchWindowPrivate::data_append);
}

/*!
    \brief The window's content item.
*/
QDeclarativeItem* QchWindow::contentItem() const {
    Q_D(const QchWindow);
    return d->root;
}

/*!
    \brief The current orientation lock of the window.
    
    \sa Screen::orientationLock
*/
int QchWindow::orientationLock() const {
    Q_D(const QchWindow);
    return d->orientationLock;
}

void QchWindow::setOrientationLock(int orientation) {
    if (orientation != orientationLock()) {
        Q_D(QchWindow);
        d->orientationLock = orientation;
        setAttribute(Qt::WidgetAttribute(orientation), true);
        emit orientationLockChanged();
    }
}

/*!
    \brief Whether the progress indicator should be visible.
    
    The default value is \c false.
*/
bool QchWindow::showProgressIndicator() const {
    return testAttribute(Qt::WA_Maemo5ShowProgressIndicator);
}

void QchWindow::setShowProgressIndicator(bool enabled) {
    if (enabled != showProgressIndicator()) {
        setAttribute(Qt::WA_Maemo5ShowProgressIndicator, enabled);
        emit showProgressIndicatorChanged();
    }
}

/*!
    \brief The current status of the window.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>WindowStatus.Inactive</td>
            <td>The window is inactive (default).</td>
        </tr>
        <tr>
            <td>WindowStatus.Activating</td>
            <td>The window is being activated.</td>
        </tr>
        <tr>
            <td>WindowStatus.Active</td>
            <td>The window is active, i.e. it is the current window.</td>
        </tr>
        <tr>
            <td>WindowStatus.Deactivating</td>
            <td>The window is being de-activated.</td>
        </tr>
    </table>
*/
QchWindowStatus::Status QchWindow::status() const {
    Q_D(const QchWindow);
    return d->status;
}

/*!
    \brief Activates the window.
*/
void QchWindow::activate() {
    activateWindow();
}

void QchWindow::showEvent(QShowEvent *e) {
    Q_D(QchWindow);
    d->status = QchWindowStatus::Activating;
    emit statusChanged();
    QMainWindow::showEvent(e);
    d->status = QchWindowStatus::Active;
    emit statusChanged();
    emit visibleChanged();
}

void QchWindow::hideEvent(QHideEvent *e) {
    Q_D(QchWindow);
    d->status = QchWindowStatus::Deactivating;
    emit statusChanged();
    QMainWindow::hideEvent(e);
    d->status = QchWindowStatus::Inactive;
    emit statusChanged();
    emit visibleChanged();
    emit hidden(this);
}

void QchWindow::closeEvent(QCloseEvent *e) {
    QchCloseEvent ce;
    emit closing(&ce);
    
    if (ce.isAccepted()) {
        QMainWindow::closeEvent(e);
        deleteLater();
    }
    else {
        e->ignore();
    }
}

void QchWindow::resizeEvent(QResizeEvent *e) {
    QMainWindow::resizeEvent(e);
    emit sizeChanged();
}

void QchWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    
    switch (e->type()) {
    case QEvent::WindowStateChange:
        emit windowStateChanged();
        break;
    case QEvent::WindowTitleChange:
        emit titleChanged();
        break;
    default:
        break;
    }
}

#include "moc_qchwindow.cpp"

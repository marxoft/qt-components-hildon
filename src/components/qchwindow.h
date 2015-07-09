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

#ifndef QCHWINDOW_H
#define QCHWINDOW_H

#include "qchwindowstatus.h"
#include <QMainWindow>
#include <qdeclarative.h>

class QDeclarativeItem;
class QchCloseEvent;
class QchMenuBar;
class QchWindowPrivate;

class QchWindow : public QMainWindow
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(QDeclarativeItem* contentItem READ contentItem CONSTANT)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(int orientationLock READ orientationLock WRITE setOrientationLock
               NOTIFY orientationLockChanged)
    Q_PROPERTY(bool showProgressIndicator READ showProgressIndicator WRITE setShowProgressIndicator
               NOTIFY showProgressIndicatorChanged)
    Q_PROPERTY(QchWindowStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    Q_PRIVATE_PROPERTY(QchWindow::d_func(), QchMenuBar* menuBar READ menuBar WRITE setMenuBar)
    
    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchWindow(QWidget *parent = 0);
    ~QchWindow();
        
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    QDeclarativeItem* contentItem() const;
        
    int orientationLock() const;
        
    bool showProgressIndicator() const;
    void setShowProgressIndicator(bool enabled);
    
    QchWindowStatus::Status status() const;

public Q_SLOTS:
    void setOrientationLock(int orientation);

Q_SIGNALS:
    void closing(QchCloseEvent *close);
    void hidden(QchWindow *window);
    void orientationLockChanged();
    void sizeChanged();
    void showProgressIndicatorChanged();
    void statusChanged();
    void titleChanged();
    void visibleChanged();
    
protected:
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);
    virtual void closeEvent(QCloseEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void changeEvent(QEvent *e);
    
    QScopedPointer<QchWindowPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchWindow)

private:    
    Q_DISABLE_COPY(QchWindow)
};

QML_DECLARE_TYPE(QchWindow)
    
#endif // QCHWINDOW_H

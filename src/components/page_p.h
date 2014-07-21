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

#ifndef PAGE_P_H
#define PAGE_P_H

#include "anchors_p.h"
#include "screen_p.h"
#include <QMainWindow>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class PagePrivate;

class Page : public QMainWindow, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(Screen::Orientation orientationLock READ orientationLock WRITE setOrientationLock NOTIFY orientationLockChanged)
    Q_PROPERTY(bool inPortrait READ inPortrait NOTIFY inPortraitChanged)
    Q_PROPERTY(bool fullScreen READ isFullScreen WRITE setFullScreen NOTIFY fullScreenChanged)
    Q_PROPERTY(bool showProgressIndicator READ showingProgressIndicator WRITE showProgressIndicator)
    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(Page::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(Page::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(Page::d_func(), QDeclarativeListProperty<QObject> tools READ tools)
    Q_PRIVATE_PROPERTY(Page::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(Page::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit Page(QWidget *parent = 0);
    ~Page();

    Screen::Orientation orientationLock() const;

    bool inPortrait() const;

    void setFullScreen(bool fullScreen);

    bool showingProgressIndicator() const;
    void showProgressIndicator(bool show);

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

public slots:
    void setOrientationLock(Screen::Orientation orientation);

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();
    void orientationLockChanged();
    void inPortraitChanged();
    void fullScreenChanged();

protected:
    Page(PagePrivate &dd, QWidget *parent = 0);

    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<PagePrivate> d_ptr;

    Q_DECLARE_PRIVATE(Page)

private:
    Q_DISABLE_COPY(Page)
};

QML_DECLARE_TYPE(Page)

#endif // PAGE_P_H

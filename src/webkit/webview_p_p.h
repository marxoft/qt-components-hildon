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

#ifndef WEBVIEW_P_P_H
#define WEBVIEW_P_P_H

#include "item_p_p.h"
#include "webview_p.h"
#include <QMouseEvent>

class WebViewSelectionSuppressor : public QObject
{
    Q_OBJECT

public:
    WebViewSelectionSuppressor(WebView *v) :
        QObject(v),
        view(v),
        enabled(false),
        mousePressed(false)
    {
        Q_ASSERT(view);

        this->enable();
    }

    inline void enable() {
        if (enabled) {
            return;
        }

        view->installEventFilter(this);
        enabled = true;
    }

    inline void disable() {
        if (!enabled) {
            return;
        }

        view->removeEventFilter(this);
        enabled = false;
    }

    inline bool isEnabled() const {
        return enabled;
    }

protected:
    inline bool eventFilter(QObject *, QEvent *e);

private:
    WebView *view;

    bool enabled;
    bool mousePressed;
};

bool WebViewSelectionSuppressor::eventFilter(QObject *, QEvent *e) {
    switch (e->type()) {
    case QEvent::MouseButtonPress:
        if (static_cast<QMouseEvent *>(e)->button() == Qt::LeftButton) {
            mousePressed = true;
        }

        break;
    case QEvent::MouseButtonRelease:
        if (static_cast<QMouseEvent *>(e)->button() == Qt::LeftButton) {
            mousePressed = false;
        }

        break;
    case QEvent::MouseMove:
        if (mousePressed) {
            return true;
        }

        break;
    default:
        break;
    }

    return false;
}

class WebViewPrivate : public ItemPrivate
{

public:
    WebViewPrivate(WebView *parent) :
        ItemPrivate(parent),
        suppressor(0),
        progress(0),
        status(WebView::Null)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    static void children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget);

    static void actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QWidget> children();

    QDeclarativeListProperty<QObject> actions();

    void _q_onLoadStarted();
    void _q_onLoadFinished(bool ok);
    void _q_onLoadProgress(int p);

    WebViewSelectionSuppressor *suppressor;

    int progress;

    WebView::Status status;

    Q_DECLARE_PUBLIC(WebView)
};

#endif // WEBVIEW_P_P_H

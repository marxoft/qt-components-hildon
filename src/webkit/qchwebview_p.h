/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHWEBVIEW_P_H
#define QCHWEBVIEW_P_H

#include "qchwebview.h"
#include <QMouseEvent>
#include <QAbstractKineticScroller>

class QchWebViewSelectionSuppressor : public QObject
{
    Q_OBJECT

public:
    QchWebViewSelectionSuppressor(QchWebView *v) :
        QObject(v),
        view(v),
        enabled(false),
        mousePressed(false)
    {
        Q_ASSERT(view);
        enable();
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
    QchWebView *view;

    bool enabled;
    bool mousePressed;
};

bool QchWebViewSelectionSuppressor::eventFilter(QObject *, QEvent *e) {
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

class QchWebViewPrivate
{

public:
    QchWebViewPrivate(QchWebView *parent) :
        q_ptr(parent),
        suppressor(0),
        kineticScroller(parent->property("kineticScroller").value<QAbstractKineticScroller*>()),
        webPage(0),
        webHistory(0),
        webSettings(0),
        windowComponent(0),
        windowParent(0),
        progress(0),
        status(QchWebView::Null),
        scrollTimer(0),
        atXBeginning(true),
        atXEnd(true),
        atYBeginning(true),
        atYEnd(true)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj);
    
    static void jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj);

    QDeclarativeListProperty<QObject> data();

    QDeclarativeListProperty<QObject> jsObjects();

    QchWebPage* page() const;
    void setPage(QchWebPage *page);

    QchWebHistory* history();

    QchWebSettings* settings();

    void _q_onLoadStarted();
    void _q_onLoadFinished(bool ok);
    void _q_onLoadProgress(int p);

    void _q_onStatusBarMessage(const QString &message);

    void _q_onDownloadRequested(const QNetworkRequest &request);

    void _q_onUnsupportedContent(QNetworkReply *reply);

    void _q_onJavaScriptWindowObjectCleared();

    void _q_onScrollRequested();
    void _q_onScrollingStopped();
    
    QchWebView *q_ptr;

    QchWebViewSelectionSuppressor *suppressor;

    QAbstractKineticScroller *kineticScroller;

    QchWebPage *webPage;

    QchWebHistory *webHistory;

    QchWebSettings *webSettings;

    QDeclarativeComponent *windowComponent;

    QDeclarativeItem *windowParent;

    int progress;

    QchWebView::Status status;

    QString statusText;

    QTimer *scrollTimer;

    bool atXBeginning;
    bool atXEnd;
    bool atYBeginning;
    bool atYEnd;

    QList<QObject*> jsObjectList;

    Q_DECLARE_PUBLIC(QchWebView)
};

#endif // QCHWEBVIEW_P_H

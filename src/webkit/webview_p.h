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

#ifndef WEBVIEW_P_H
#define WEBVIEW_P_H

#include "anchors_p.h"
#include <QWebView>
#include <QWebPage>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeComponent;
class WebHistory;
class WebSettings;
class WebViewPrivate;

class WebView : public QWebView, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PRIVATE_PROPERTY(WebView::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString icon READ iconSource NOTIFY iconChanged)
    Q_PROPERTY(bool textSelectionEnabled READ textSelectionEnabled WRITE setTextSelectionEnabled NOTIFY textSelectionEnabledChanged)
    Q_PROPERTY(QWebPage::LinkDelegationPolicy linkDelegationPolicy READ linkDelegationPolicy WRITE setLinkDelegationPolicy NOTIFY linkDelegationPolicyChanged)
    Q_PROPERTY(bool moving READ moving NOTIFY movingChanged)
    Q_PROPERTY(bool atXBeginning READ atXBeginning NOTIFY contentXChanged)
    Q_PROPERTY(bool atXEnd READ atXEnd NOTIFY contentXChanged)
    Q_PROPERTY(bool atYBeginning READ atYBeginning NOTIFY contentYChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd NOTIFY contentYChanged)
    Q_PROPERTY(int contentX READ contentX WRITE setContentX NOTIFY contentXChanged)
    Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    Q_PROPERTY(qreal flickDeceleration READ flickDeceleration WRITE setFlickDeceleration NOTIFY flickDecelerationChanged)
    Q_PROPERTY(qreal maximumFlickVelocity READ maximumFlickVelocity WRITE setMaximumFlickVelocity NOTIFY maximumFlickVelocityChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QDeclarativeComponent* newWindowComponent READ newWindowComponent WRITE setNewWindowComponent NOTIFY newWindowComponentChanged)
    Q_PROPERTY(QWidget* newWindowParent READ newWindowParent WRITE setNewWindowParent NOTIFY newWindowParentChanged)
    Q_PRIVATE_PROPERTY(WebView::d_func(), WebHistory* history READ history CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(WebView::d_func(), WebSettings* settings READ settings CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(WebView::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(WebView::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(WebView::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(WebView::d_func(), QDeclarativeListProperty<QObject> javaScriptWindowObjects READ jsObjects)
    Q_PRIVATE_PROPERTY(WebView::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(WebView::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)

    Q_ENUMS(Status QWebPage::LinkDelegationPolicy)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    enum Status {
        Null = 0,
        Loading,
        Ready,
        Error
    };

    explicit WebView(QWidget *parent = 0);
    ~WebView();

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

    QString iconSource() const;

    bool textSelectionEnabled() const;
    void setTextSelectionEnabled(bool enabled);

    QWebPage::LinkDelegationPolicy linkDelegationPolicy() const;
    void setLinkDelegationPolicy(QWebPage::LinkDelegationPolicy policy);

    bool moving() const;

    bool atXBeginning() const;
    bool atXEnd() const;

    bool atYBeginning() const;
    bool atYEnd() const;

    int contentX() const;
    void setContentX(int x);

    int contentY() const;
    void setContentY(int y);

    qreal flickDeceleration() const;
    void setFlickDeceleration(qreal deceleration);

    qreal maximumFlickVelocity() const;
    void setMaximumFlickVelocity(qreal maximum);

    int progress() const;

    Status status() const;

    QString statusText() const;

    QDeclarativeComponent* newWindowComponent() const;
    void setNewWindowComponent(QDeclarativeComponent *component);

    QWidget* newWindowParent() const;
    void setNewWindowParent(QWidget *parent);

    Q_INVOKABLE bool findText(const QString &text);

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
    void titleChanged();
    void urlChanged();
    void textSelectionEnabledChanged();
    void linkDelegationPolicyChanged();
    void movingChanged();
    void contentXChanged();
    void contentYChanged();
    void flickDecelerationChanged();
    void maximumFlickVelocityChanged();
    void progressChanged();
    void statusChanged();
    void statusTextChanged();
    void newWindowComponentChanged();
    void newWindowParentChanged();
    void linkClicked(const QUrl &link);

protected:
    WebView(WebViewPrivate &dd, QWidget *parent = 0);

    virtual QWebView* createWindow(QWebPage::WebWindowType type);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<WebViewPrivate> d_ptr;

    Q_DECLARE_PRIVATE(WebView)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoadStarted())
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadFinished(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadProgress(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusBarMessage(QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onJavaScriptWindowObjectCleared())

private:
    Q_DISABLE_COPY(WebView)
};

QML_DECLARE_TYPE(WebView)

#endif // WEBVIEW_P_H

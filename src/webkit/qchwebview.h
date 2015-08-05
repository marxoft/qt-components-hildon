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

#include "qchwebpage.h"
#include <QGraphicsWebView>
#include <QWebPage>
#include <qdeclarative.h>

class QDeclarativeComponent;
class QDeclarativeItem;
class QchWebHistory;
class QchWebSettings;
class QchWebViewPrivate;

class QchWebView : public QGraphicsWebView
{
    Q_OBJECT

    Q_PROPERTY(int preferredWidth READ preferredWidth WRITE setPreferredWidth NOTIFY preferredWidthChanged)
    Q_PROPERTY(int preferredHeight READ preferredHeight WRITE setPreferredHeight NOTIFY preferredHeightChanged)
    Q_PROPERTY(QString html READ toHtml WRITE setHtml NOTIFY statusChanged)
    Q_PROPERTY(QString text READ toPlainText WRITE setText NOTIFY statusChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectedTextChanged)
    Q_PROPERTY(QString selectedText READ selectedText NOTIFY selectedTextChanged)
    Q_PROPERTY(QWebPage::LinkDelegationPolicy linkDelegationPolicy READ linkDelegationPolicy
               WRITE setLinkDelegationPolicy NOTIFY linkDelegationPolicyChanged)
    Q_PROPERTY(bool forwardUnsupportedContent READ forwardUnsupportedContent WRITE setForwardUnsupportedContent
               NOTIFY forwardUnsupportedContentChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent NOTIFY userAgentChanged)
    Q_PROPERTY(QDeclarativeComponent* newWindowComponent READ newWindowComponent WRITE setNewWindowComponent
               NOTIFY newWindowComponentChanged)
    Q_PROPERTY(QDeclarativeItem* newWindowParent READ newWindowParent WRITE setNewWindowParent
               NOTIFY newWindowParentChanged)
    Q_PRIVATE_PROPERTY(QchWebView::d_func(), QchWebPage* page READ page WRITE setPage NOTIFY pageChanged)
    Q_PRIVATE_PROPERTY(QchWebView::d_func(), QchWebHistory* history READ history CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(QchWebView::d_func(), QchWebSettings* settings READ settings CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(QchWebView::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(QchWebView::d_func(), QDeclarativeListProperty<QObject> javaScriptWindowObjects READ jsObjects)    

    Q_ENUMS(Status QWebPage::LinkDelegationPolicy)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    enum Status {
        Null = 0,
        Loading,
        Ready,
        Error
    };

    explicit QchWebView(QGraphicsItem *parent = 0);
    ~QchWebView();
    
    int preferredWidth() const;
    void setPreferredWidth(int w);
    
    int preferredHeight() const;
    void setPreferredHeight(int h);
    
    QString toHtml() const;

    QString toPlainText() const;
    void setText(const QString &text);

    bool hasSelection() const;
    
    QString selectedText() const;

    QWebPage::LinkDelegationPolicy linkDelegationPolicy() const;
    void setLinkDelegationPolicy(QWebPage::LinkDelegationPolicy policy);

    bool forwardUnsupportedContent() const;
    void setForwardUnsupportedContent(bool forward);

    int progress() const;

    Status status() const;

    QString statusText() const;

    QString userAgent() const;
    void setUserAgent(const QString &agent);

    QDeclarativeComponent* newWindowComponent() const;
    void setNewWindowComponent(QDeclarativeComponent *component);

    QDeclarativeItem* newWindowParent() const;
    void setNewWindowParent(QDeclarativeItem *parent);

    Q_INVOKABLE QVariant hitTestContent(int x, int y);

public Q_SLOTS:
    bool findText(const QString &text);
    bool findAllText(const QString &text);

    void copy();
    void cut();
    void paste();

Q_SIGNALS:
    void preferredWidthChanged();
    void preferredHeightChanged();
    void selectedTextChanged();
    void linkDelegationPolicyChanged();
    void forwardUnsupportedContentChanged();
    void progressChanged();
    void statusChanged();
    void statusTextChanged();
    void userAgentChanged();
    void newWindowComponentChanged();
    void newWindowParentChanged();
    void pageChanged();
    void downloadRequested(const QVariant &request);
    void unsupportedContent(const QVariant &content);

protected:
    QchWebView(QchWebViewPrivate &dd, QGraphicsItem *parent = 0);

    virtual QGraphicsWebView* createWindow(QWebPage::WebWindowType type);

    virtual void keyPressEvent(QKeyEvent *event);

    QScopedPointer<QchWebViewPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchWebView)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoadStarted())
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadFinished(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadProgress(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusBarMessage(QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onDownloadRequested(QNetworkRequest))
    Q_PRIVATE_SLOT(d_func(), void _q_onUnsupportedContent(QNetworkReply*))
    Q_PRIVATE_SLOT(d_func(), void _q_onJavaScriptWindowObjectCleared())

private:
    Q_DISABLE_COPY(QchWebView)
};

QML_DECLARE_TYPE(QchWebView)

#endif // WEBVIEW_P_H

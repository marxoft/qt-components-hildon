/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHWEBPAGE_H
#define QCHWEBPAGE_H

#include <QWebPage>
#include <QWebElement>
#include <QWebFrame>
#include <QDeclarativeListProperty>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeComponent;
class QchWebHistory;
class QchWebSettings;
class QchWebPagePrivate;

class QchWebPage : public QWebPage, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl baseUrl READ baseUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl requestedUrl READ requestedUrl NOTIFY urlChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QWebElement documentElement READ documentElement NOTIFY statusChanged)
    Q_PROPERTY(QString html READ toHtml WRITE setHtml NOTIFY urlChanged)
    Q_PROPERTY(QString text READ toPlainText WRITE setText NOTIFY urlChanged)
    Q_PROPERTY(bool forwardUnsupportedContent READ forwardUnsupportedContent CONSTANT)
    Q_PROPERTY(int contentWidth READ contentWidth NOTIFY contentSizeChanged)
    Q_PROPERTY(int contentHeight READ contentHeight NOTIFY contentSizeChanged)
    Q_PROPERTY(int preferredWidth READ preferredWidth WRITE setPreferredWidth NOTIFY preferredWidthChanged)
    Q_PROPERTY(int preferredHeight READ preferredHeight WRITE setPreferredHeight NOTIFY preferredHeightChanged)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor WRITE setZoomFactor NOTIFY zoomFactorChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QString selectedText READ selectedText NOTIFY selectedTextChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectedTextChanged)
    Q_PROPERTY(QString userAgent READ userAgent WRITE setUserAgent NOTIFY userAgentChanged)
    Q_PROPERTY(QDeclarativeComponent* newWindowComponent READ newWindowComponent WRITE setNewWindowComponent
               NOTIFY newWindowComponentChanged)
    Q_PRIVATE_PROPERTY(QchWebPage::d_func(), QchWebHistory* history READ history CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(QchWebPage::d_func(), QchWebSettings* settings READ settings CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(QchWebPage::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(QchWebPage::d_func(), QDeclarativeListProperty<QObject> javaScriptWindowObjects READ jsObjects)
    
    Q_ENUMS(Status)
    
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    enum Status {
        Null = 0,
        Loading,
        Ready,
        Error
    };

    explicit QchWebPage(QObject *parent = 0);
    ~QchWebPage();

    QUrl url() const;
    void setUrl(const QUrl &url);

    QUrl baseUrl() const;
    QUrl requestedUrl() const;

    QString icon() const;

    QString title() const;
    
    QWebElement documentElement() const;

    QString toHtml() const;
    void setHtml(const QString &html, const QUrl &baseUrl = QUrl());

    QString toPlainText() const;
    void setText(const QString &text);

    int contentWidth() const;
    int contentHeight() const;

    int preferredWidth() const;
    void setPreferredWidth(int width);
    int preferredHeight() const;
    void setPreferredHeight(int height);

    qreal zoomFactor() const;
    void setZoomFactor(qreal zoom);

    int progress() const;

    Status status() const;

    QString statusText() const;

    bool hasSelection() const;

    QString userAgent() const;
    void setUserAgent(const QString &agent);

    QDeclarativeComponent* newWindowComponent() const;
    void setNewWindowComponent(QDeclarativeComponent *component);

    QObject* newWindowParent() const;
    void setNewWindowParent(QObject *parent);

    Q_INVOKABLE QWebHitTestResult hitTestContent(int x, int y);

public Q_SLOTS:
    bool findText(const QString &text);
    bool findAllText(const QString &text);

    void load(const QUrl &url);
    void reload();
    void stop();

    void back();
    void forward();

    void copy();
    void cut();
    void paste();
    
    virtual void triggerAction(QWebPage::WebAction action, bool checked = false);

Q_SIGNALS:
    void urlChanged();
    void iconChanged();
    void titleChanged();
    void contentSizeChanged();
    void preferredWidthChanged();
    void preferredHeightChanged();
    void zoomFactorChanged();
    void progressChanged();
    void statusChanged();
    void statusTextChanged();
    void selectedTextChanged();
    void userAgentChanged();
    void newWindowComponentChanged();
    void newWindowParentChanged();

protected:
    QchWebPage(QchWebPagePrivate &dd, QObject *parent = 0);

    virtual QWebPage* createWindow(WebWindowType type);

    virtual QString userAgentForUrl(const QUrl &url) const;
    
    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<QchWebPagePrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchWebPage)

    Q_PRIVATE_SLOT(d_func(), void _q_onLoadStarted())
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadFinished(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onLoadProgress(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusBarMessage(QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onUnsupportedContent(QNetworkReply*))
    Q_PRIVATE_SLOT(d_func(), void _q_onJavaScriptWindowObjectCleared())

private:
    Q_DISABLE_COPY(QchWebPage)
};

QML_DECLARE_TYPE(QchWebPage)

#endif // QCHWEBPAGE_H

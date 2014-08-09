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

#include "webpage_p.h"
#include "webhistory_p.h"
#include "websettings_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QNetworkReply>

class WebPagePrivate
{

public:
    WebPagePrivate(WebPage *parent) :
        q_ptr(parent),
        webHistory(0),
        webSettings(0),
        windowComponent(0),
        windowParent(0),
        progress(0),
        status(WebPage::Null)
    {
    }

    virtual ~WebPagePrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (WebPage *page = qobject_cast<WebPage*>(list->object)) {
            page->d_func()->dataList.append(obj);
        }
    }

    static void jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (WebPage *page = qobject_cast<WebPage*>(list->object)) {
            page->d_func()->jsObjectList.append(obj);
            page->d_func()->dataList.append(obj);
            page->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }

    QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, WebPagePrivate::data_append);
    }

    QDeclarativeListProperty<QObject> jsObjects() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, WebPagePrivate::jsobjects_append);
    }

    WebHistory* history() {
        Q_Q(WebPage);

        if (!webHistory) {
            webHistory = new WebHistory(q->history(), q);
        }

        return webHistory;
    }

    WebSettings* settings() {
        Q_Q(WebPage);

        if (!webSettings) {
            webSettings = new WebSettings(q->settings(), q);
        }

        return webSettings;
    }

    void _q_onLoadStarted() {
        Q_Q(WebPage);

        status = WebPage::Loading;
        emit q->statusChanged();
        emit q->urlChanged();
        emit q->titleChanged();
    }

    void _q_onLoadFinished(bool ok) {
        Q_Q(WebPage);

        status = ok ? WebPage::Ready : WebPage::Error;
        emit q->statusChanged();
        emit q->urlChanged();
        emit q->titleChanged();
    }

    void _q_onLoadProgress(int p) {
        Q_Q(WebPage);

        progress = p;
        emit q->progressChanged();
    }

    void _q_onStatusBarMessage(const QString &message) {
        if (message != statusText) {
            statusText = message;
            Q_Q(WebPage);
            emit q->statusTextChanged();
        }
    }

    void _q_onDownloadRequested(const QNetworkRequest &request) {
        Q_Q(WebPage);

        QVariantMap map;
        QVariantMap headers;
        map["url"] = request.url();

        foreach (QByteArray header, request.rawHeaderList()) {
            headers[header] = request.rawHeader(header);
        }

        map["headers"] = headers;
        emit q->downloadRequested(map);
    }

    void _q_onUnsupportedContent(QNetworkReply *reply) {
        Q_Q(WebPage);

        QVariantMap map;
        QVariantMap headers;
        map["url"] = reply->url();

        foreach (QByteArray header, reply->rawHeaderList()) {
            headers[header] = reply->rawHeader(header);
        }

        map["headers"] = headers;
        emit q->unsupportedContent(map);
        reply->deleteLater();
    }

    void _q_onJavaScriptWindowObjectCleared() {
        Q_Q(WebPage);

        foreach (QObject *obj, jsObjectList) {
            q->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }

    WebPage *q_ptr;

    WebHistory *webHistory;

    WebSettings *webSettings;

    QDeclarativeComponent *windowComponent;

    QObject *windowParent;

    int progress;

    WebPage::Status status;

    QString statusText;

    QString userAgent;

    QList<QObject*> dataList;
    QList<QObject*> jsObjectList;

    Q_DECLARE_PUBLIC(WebPage)
};

WebPage::WebPage(QObject *parent) :
    QWebPage(parent),
    d_ptr(new WebPagePrivate(this))
{
    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(this->mainFrame(), SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this->mainFrame(), SIGNAL(iconChanged()), this, SIGNAL(iconChanged()));
    this->connect(this->mainFrame(), SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
    this->connect(this, SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    this->connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    this->connect(this->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

WebPage::WebPage(WebPagePrivate &dd, QObject *parent) :
    QWebPage(parent),
    d_ptr(&dd)
{
    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(this->mainFrame(), SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this->mainFrame(), SIGNAL(iconChanged()), this, SIGNAL(iconChanged()));
    this->connect(this->mainFrame(), SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
    this->connect(this, SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    this->connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    this->connect(this->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

WebPage::~WebPage() {}

QUrl WebPage::url() const {
    return this->mainFrame()->url();
}

void WebPage::setUrl(const QUrl &url) {
    this->mainFrame()->setUrl(url);
}

QUrl WebPage::baseUrl() const {
    return this->mainFrame()->baseUrl();
}

QUrl WebPage::requestedUrl() const {
    return this->mainFrame()->requestedUrl();
}

QString WebPage::icon() const {
    return this->mainFrame()->icon().name();
}

QString WebPage::title() const {
    return this->mainFrame()->title();
}

QString WebPage::toHtml() const {
    return this->mainFrame()->toHtml();
}

void WebPage::setHtml(const QString &html, const QUrl &baseUrl) {
    this->mainFrame()->setHtml(html, baseUrl);
}

QString WebPage::toPlainText() const {
    return this->mainFrame()->toPlainText();
}

void WebPage::setText(const QString &text) {
    this->mainFrame()->setContent(text.toUtf8(), "text/plain");
}

int WebPage::contentWidth() const {
    return this->mainFrame()->contentsSize().width();
}

int WebPage::contentHeight() const {
    return this->mainFrame()->contentsSize().height();
}

int WebPage::preferredWidth() const {
    return this->preferredContentsSize().width();
}

void WebPage::setPreferredWidth(int width) {
    if (width != this->preferredWidth()) {
        this->setPreferredContentsSize(QSize(width, this->preferredHeight()));
        emit preferredWidthChanged();
    }
}

int WebPage::preferredHeight() const {
    return this->preferredContentsSize().height();
}

void WebPage::setPreferredHeight(int height) {
    if (height != this->preferredHeight()) {
        this->setPreferredContentsSize(QSize(this->preferredWidth(), height));
        emit preferredHeightChanged();
    }
}

qreal WebPage::zoomFactor() const {
    return this->currentFrame()->zoomFactor();
}

void WebPage::setZoomFactor(qreal zoom) {
    if (zoom != this->zoomFactor()) {
        this->currentFrame()->setZoomFactor(zoom);
        emit zoomFactorChanged();
    }
}

int WebPage::progress() const {
    Q_D(const WebPage);

    return d->progress;
}

WebPage::Status WebPage::status() const {
    Q_D(const WebPage);

    return d->status;
}

QString WebPage::statusText() const {
    Q_D(const WebPage);

    return d->statusText;
}

bool WebPage::hasSelection() const {
    return !this->selectedText().isEmpty();
}

QString WebPage::userAgent() const {
    Q_D(const WebPage);

    return d->userAgent;
}

void WebPage::setUserAgent(const QString &agent) {
    if (agent != this->userAgent()) {
        Q_D(WebPage);
        d->userAgent = agent;
        emit userAgentChanged();
    }
}

QDeclarativeComponent* WebPage::newWindowComponent() const {
    Q_D(const WebPage);

    return d->windowComponent;
}

void WebPage::setNewWindowComponent(QDeclarativeComponent *component) {
    if (component != this->newWindowComponent()) {
        Q_D(WebPage);
        d->windowComponent = component;
        emit newWindowComponentChanged();
    }
}

QObject* WebPage::newWindowParent() const {
    Q_D(const WebPage);

    return d->windowParent;
}

void WebPage::setNewWindowParent(QObject *parent) {
    if (parent != this->newWindowParent()) {
        Q_D(WebPage);
        d->windowParent = parent;
        emit newWindowParentChanged();
    }
}

QVariant WebPage::hitTestContent(int x, int y) {
    QWebHitTestResult result = this->currentFrame()->hitTestContent(QPoint(x, y));
    QVariantMap content;
    content["isNull"] = result.isNull();

    if (!result.isNull()) {
        content["x"] = result.boundingRect().left();
        content["y"] = result.boundingRect().top();
        content["width"] = result.boundingRect().width();
        content["height"] = result.boundingRect().height();
        content["isNull"] = result.isNull();
        content["alternateText"] = result.alternateText();
        content["imageUrl"] = result.imageUrl();
        content["isContentEditable"] = result.isContentEditable();
        content["isContentSelected"] = result.isContentSelected();
        content["linkText"] = result.linkText();
        content["linkTitle"] = result.linkTitle();
        content["linkUrl"] = result.linkUrl();
        content["title"] = result.title();
    }

    return content;
}

bool WebPage::findText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument);
}

bool WebPage::findAllText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument | QWebPage::HighlightAllOccurrences);
}

void WebPage::load(const QUrl &url) {
    this->mainFrame()->load(url);
}

void WebPage::reload() {
    this->triggerAction(QWebPage::Reload);
}

void WebPage::stop() {
    this->triggerAction(QWebPage::Stop);
}

void WebPage::back() {
    this->triggerAction(QWebPage::Back);
}

void WebPage::forward() {
    this->triggerAction(QWebPage::Forward);
}

void WebPage::copy() {
    this->triggerAction(QWebPage::Copy);
}

void WebPage::cut() {
    this->triggerAction(QWebPage::Cut);
}

void WebPage::paste() {
    this->triggerAction(QWebPage::Paste);
}

QWebPage* WebPage::createWindow(WebWindowType type) {
    Q_UNUSED(type);
    Q_D(WebPage);

    if (!d->windowComponent) {
        return 0;
    }

    WebPage *page = 0;
    QDeclarativeContext *creationContext = d->windowComponent->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->windowComponent->create(context)) {
        page = qobject_cast<WebPage*>(obj);

        if (!page) {
            page = obj->findChild<WebPage*>();
        }

        if (page) {
            page->setParent(d->windowParent);
        }
        else {
            qmlInfo(this) << tr("No WebPage found in window component");
            delete obj;
            delete context;
        }
    }
    else {
        delete context;
    }

    return page;
}

QString WebPage::userAgentForUrl(const QUrl &url) const {
    return this->userAgent().isEmpty() ? QWebPage::userAgentForUrl(url) : this->userAgent();
}

#include "moc_webpage_p.cpp"

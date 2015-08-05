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

#include "qchwebpage.h"
#include "qchwebhistory.h"
#include "qchwebsettings.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QNetworkReply>

class QchWebPagePrivate
{

public:
    QchWebPagePrivate(QchWebPage *parent) :
        q_ptr(parent),
        webHistory(0),
        webSettings(0),
        windowComponent(0),
        windowParent(0),
        progress(0),
        status(QchWebPage::Null)
    {
    }

    virtual ~QchWebPagePrivate() {}

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (QchWebPage *page = qobject_cast<QchWebPage*>(list->object)) {
            page->d_func()->dataList.append(obj);
        }
    }

    static void jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (QchWebPage *page = qobject_cast<QchWebPage*>(list->object)) {
            page->d_func()->jsObjectList.append(obj);
            page->d_func()->dataList.append(obj);
            page->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }

    QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, QchWebPagePrivate::data_append);
    }

    QDeclarativeListProperty<QObject> jsObjects() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, QchWebPagePrivate::jsobjects_append);
    }

    QchWebHistory* history() {
        Q_Q(QchWebPage);

        if (!webHistory) {
            webHistory = new QchWebHistory(q->history(), q);
        }

        return webHistory;
    }

    QchWebSettings* settings() {
        Q_Q(QchWebPage);

        if (!webSettings) {
            webSettings = new QchWebSettings(q->settings(), q);
        }

        return webSettings;
    }

    void _q_onLoadStarted() {
        Q_Q(QchWebPage);

        status = QchWebPage::Loading;
        emit q->statusChanged();
        emit q->urlChanged();
        emit q->titleChanged();
    }

    void _q_onLoadFinished(bool ok) {
        Q_Q(QchWebPage);

        status = ok ? QchWebPage::Ready : QchWebPage::Error;
        emit q->statusChanged();
        emit q->urlChanged();
        emit q->titleChanged();
    }

    void _q_onLoadProgress(int p) {
        Q_Q(QchWebPage);

        progress = p;
        emit q->progressChanged();
    }

    void _q_onStatusBarMessage(const QString &message) {
        if (message != statusText) {
            statusText = message;
            Q_Q(QchWebPage);
            emit q->statusTextChanged();
        }
    }

    void _q_onDownloadRequested(const QNetworkRequest &request) {
        Q_Q(QchWebPage);

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
        Q_Q(QchWebPage);

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
        Q_Q(QchWebPage);

        foreach (QObject *obj, jsObjectList) {
            q->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }

    QchWebPage *q_ptr;

    QchWebHistory *webHistory;

    QchWebSettings *webSettings;

    QDeclarativeComponent *windowComponent;

    QObject *windowParent;

    int progress;

    QchWebPage::Status status;

    QString statusText;

    QString userAgent;

    QList<QObject*> dataList;
    QList<QObject*> jsObjectList;

    Q_DECLARE_PUBLIC(QchWebPage)
};

QchWebPage::QchWebPage(QObject *parent) :
    QWebPage(parent),
    d_ptr(new QchWebPagePrivate(this))
{
    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        setNetworkAccessManager(engine->networkAccessManager());
    }

    mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(mainFrame(), SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    connect(mainFrame(), SIGNAL(iconChanged()), this, SIGNAL(iconChanged()));
    connect(mainFrame(), SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    connect(this, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
    connect(this, SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

QchWebPage::QchWebPage(QchWebPagePrivate &dd, QObject *parent) :
    QWebPage(parent),
    d_ptr(&dd)
{
    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        setNetworkAccessManager(engine->networkAccessManager());
    }

    mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(mainFrame(), SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    connect(mainFrame(), SIGNAL(iconChanged()), this, SIGNAL(iconChanged()));
    connect(mainFrame(), SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    connect(this, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
    connect(this, SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

QchWebPage::~QchWebPage() {}

QUrl QchWebPage::url() const {
    return mainFrame()->url();
}

void QchWebPage::setUrl(const QUrl &url) {
    mainFrame()->setUrl(url);
}

QUrl QchWebPage::baseUrl() const {
    return mainFrame()->baseUrl();
}

QUrl QchWebPage::requestedUrl() const {
    return mainFrame()->requestedUrl();
}

QString QchWebPage::icon() const {
    return mainFrame()->icon().name();
}

QString QchWebPage::title() const {
    return mainFrame()->title();
}

QString QchWebPage::toHtml() const {
    return mainFrame()->toHtml();
}

void QchWebPage::setHtml(const QString &html, const QUrl &baseUrl) {
    mainFrame()->setHtml(html, baseUrl);
}

QString QchWebPage::toPlainText() const {
    return mainFrame()->toPlainText();
}

void QchWebPage::setText(const QString &text) {
    mainFrame()->setContent(text.toUtf8(), "text/plain");
}

int QchWebPage::contentWidth() const {
    return mainFrame()->contentsSize().width();
}

int QchWebPage::contentHeight() const {
    return mainFrame()->contentsSize().height();
}

int QchWebPage::preferredWidth() const {
    return preferredContentsSize().width();
}

void QchWebPage::setPreferredWidth(int width) {
    if (width != preferredWidth()) {
        setPreferredContentsSize(QSize(width, preferredHeight()));
        emit preferredWidthChanged();
    }
}

int QchWebPage::preferredHeight() const {
    return preferredContentsSize().height();
}

void QchWebPage::setPreferredHeight(int height) {
    if (height != preferredHeight()) {
        setPreferredContentsSize(QSize(preferredWidth(), height));
        emit preferredHeightChanged();
    }
}

qreal QchWebPage::zoomFactor() const {
    return currentFrame()->zoomFactor();
}

void QchWebPage::setZoomFactor(qreal zoom) {
    if (zoom != zoomFactor()) {
        currentFrame()->setZoomFactor(zoom);
        emit zoomFactorChanged();
    }
}

int QchWebPage::progress() const {
    Q_D(const QchWebPage);

    return d->progress;
}

QchWebPage::Status QchWebPage::status() const {
    Q_D(const QchWebPage);

    return d->status;
}

QString QchWebPage::statusText() const {
    Q_D(const QchWebPage);

    return d->statusText;
}

bool QchWebPage::hasSelection() const {
    return !selectedText().isEmpty();
}

QString QchWebPage::userAgent() const {
    Q_D(const QchWebPage);

    return d->userAgent;
}

void QchWebPage::setUserAgent(const QString &agent) {
    if (agent != userAgent()) {
        Q_D(QchWebPage);
        d->userAgent = agent;
        emit userAgentChanged();
    }
}

QDeclarativeComponent* QchWebPage::newWindowComponent() const {
    Q_D(const QchWebPage);

    return d->windowComponent;
}

void QchWebPage::setNewWindowComponent(QDeclarativeComponent *component) {
    if (component != newWindowComponent()) {
        Q_D(QchWebPage);
        d->windowComponent = component;
        emit newWindowComponentChanged();
    }
}

QObject* QchWebPage::newWindowParent() const {
    Q_D(const QchWebPage);

    return d->windowParent;
}

void QchWebPage::setNewWindowParent(QObject *parent) {
    if (parent != newWindowParent()) {
        Q_D(QchWebPage);
        d->windowParent = parent;
        emit newWindowParentChanged();
    }
}

QVariant QchWebPage::hitTestContent(int x, int y) {
    QWebHitTestResult result = currentFrame()->hitTestContent(QPoint(x, y));
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

bool QchWebPage::findText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument);
}

bool QchWebPage::findAllText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument | QWebPage::HighlightAllOccurrences);
}

void QchWebPage::load(const QUrl &url) {
    mainFrame()->load(url);
}

void QchWebPage::reload() {
    triggerAction(QWebPage::Reload);
}

void QchWebPage::stop() {
    triggerAction(QWebPage::Stop);
}

void QchWebPage::back() {
    triggerAction(QWebPage::Back);
}

void QchWebPage::forward() {
    triggerAction(QWebPage::Forward);
}

void QchWebPage::copy() {
    triggerAction(QWebPage::Copy);
}

void QchWebPage::cut() {
    triggerAction(QWebPage::Cut);
}

void QchWebPage::paste() {
    triggerAction(QWebPage::Paste);
}

QWebPage* QchWebPage::createWindow(WebWindowType type) {
    Q_UNUSED(type);
    Q_D(QchWebPage);

    if (!d->windowComponent) {
        return 0;
    }

    QWebPage *page = 0;
    QDeclarativeContext *creationContext = d->windowComponent->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->windowComponent->create(context)) {
        page = qobject_cast<QWebPage*>(obj);

        if (!page) {
            page = obj->findChild<QWebPage*>();
        }

        if (page) {
            page->setParent(d->windowParent);
        }
        else {
            qmlInfo(this) << tr("No QchWebPage found in window component");
            delete obj;
            delete context;
        }
    }
    else {
        delete context;
    }

    return page;
}

QString QchWebPage::userAgentForUrl(const QUrl &url) const {
    return userAgent().isEmpty() ? QWebPage::userAgentForUrl(url) : userAgent();
}

#include "moc_qchwebpage.cpp"

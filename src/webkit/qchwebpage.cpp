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

#include "qchwebpage.h"
#include "qchwebhistory.h"
#include "qchwebsettings.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QNetworkReply>
#include <QApplication>

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
            webHistory = new QchWebHistory(q);
        }

        return webHistory;
    }

    QchWebSettings* settings() {
        Q_Q(QchWebPage);

        if (!webSettings) {
            webSettings = new QchWebSettings(q);
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

    void _q_onUnsupportedContent(QNetworkReply *reply) {
        Q_Q(QchWebPage);

        if (reply->rawHeader("Content-Disposition").startsWith("attachment")) {
            emit q->downloadRequested(reply->request());
        }
        else {
            status = QchWebPage::Error;
            statusText = QchWebPage::tr("Content not supported");
            emit q->statusChanged();
            emit q->statusTextChanged();
        }
        
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

/*!
    \class WebPage
    \brief Provides an object to view and edit web documents.

    \ingroup webkit

    WebPage holds a main frame responsible for web content, settings, the history of navigated links and actions. 
    This class can be used to provide functionality like WebView in an item-less environment.
    
    \sa WebView
*/
QchWebPage::QchWebPage(QObject *parent) :
    QWebPage(parent),
    d_ptr(new QchWebPagePrivate(this))
{
    if (const QDeclarativeEngine *engine = qmlEngine(this)) {
        setNetworkAccessManager(engine->networkAccessManager());
    }

    setPalette(QApplication::palette("QWebView"));
    setForwardUnsupportedContent(true);
    
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
    connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

QchWebPage::QchWebPage(QchWebPagePrivate &dd, QObject *parent) :
    QWebPage(parent),
    d_ptr(&dd)
{
    if (const QDeclarativeEngine *engine = qmlEngine(this)) {
        setNetworkAccessManager(engine->networkAccessManager());
    }

    setPalette(QApplication::palette("QWebView"));
    setForwardUnsupportedContent(true);
    
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
    connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
}

QchWebPage::~QchWebPage() {}

/*!
    \brief The source url of the web page.
*/
QUrl QchWebPage::url() const {
    return mainFrame()->url();
}

void QchWebPage::setUrl(const QUrl &url) {
    mainFrame()->setUrl(url);
}

/*!
    \brief The base url of the web page.
*/
QUrl QchWebPage::baseUrl() const {
    return mainFrame()->baseUrl();
}

/*!
    \brief The requested url used to load the page, before any redirects.
*/
QUrl QchWebPage::requestedUrl() const {
    return mainFrame()->requestedUrl();
}

/*!
    \brief The source of the web page icon.
*/
QString QchWebPage::icon() const {
    return mainFrame()->icon().name();
}

/*!
    \brief The title of the web page.
*/
QString QchWebPage::title() const {
    return mainFrame()->title();
}

/*!
    \property WebElement WebPage::documentElement
    \brief The document element of the web page's main frame
*/
QWebElement QchWebPage::documentElement() const {
    return mainFrame()->documentElement();
}

/*!
    \property QString WebPage::html
    \brief The HTML of the web page.
*/
QString QchWebPage::toHtml() const {
    return mainFrame()->toHtml();
}

void QchWebPage::setHtml(const QString &html, const QUrl &baseUrl) {
    mainFrame()->setHtml(html, baseUrl);
}

/*!
    \property QString WebPage::text
    \brief The HTML of the web page as plain text.
*/
QString QchWebPage::toPlainText() const {
    return mainFrame()->toPlainText();
}

void QchWebPage::setText(const QString &text) {
    mainFrame()->setContent(text.toUtf8(), "text/plain");
}

/*!
    \brief The width of the content of the web page.
*/
int QchWebPage::contentWidth() const {
    return mainFrame()->contentsSize().width();
}

/*!
    \brief The height of the content of the web page.
*/
int QchWebPage::contentHeight() const {
    return mainFrame()->contentsSize().height();
}

/*!
    \brief The preferred width of the web page.
*/
int QchWebPage::preferredWidth() const {
    return preferredContentsSize().width();
}

void QchWebPage::setPreferredWidth(int width) {
    if (width != preferredWidth()) {
        setPreferredContentsSize(QSize(width, preferredHeight()));
        emit preferredWidthChanged();
    }
}

/*!
    \brief The preferred height of the web page.
*/
int QchWebPage::preferredHeight() const {
    return preferredContentsSize().height();
}

void QchWebPage::setPreferredHeight(int height) {
    if (height != preferredHeight()) {
        setPreferredContentsSize(QSize(preferredWidth(), height));
        emit preferredHeightChanged();
    }
}

/*!
    \brief The zoom factor of the web page.
*/
qreal QchWebPage::zoomFactor() const {
    return currentFrame()->zoomFactor();
}

void QchWebPage::setZoomFactor(qreal zoom) {
    if (zoom != zoomFactor()) {
        currentFrame()->setZoomFactor(zoom);
        emit zoomFactorChanged();
    }
}

/*!
    \brief The loading progress of the web page.
*/
int QchWebPage::progress() const {
    Q_D(const QchWebPage);

    return d->progress;
}

/*!
    \brief The current status of the web page.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>WebPage.Null</td>
            <td>No web page has been loaded (default).</td>
        </tr>
        <tr>
            <td>WebPage.Loading</td>
            <td>The web page is being loaded.</td>
        </tr>
        <tr>
            <td>WebPage.Ready</td>
            <td>The web page has been loaded.</td>
        </tr>
        <tr>
            <td>WebPage.Error</td>
            <td>An error occured when loading the web page.</td>
        </tr>
    </table>
*/
QchWebPage::Status QchWebPage::status() const {
    Q_D(const QchWebPage);

    return d->status;
}

/*!
    \brief The status text of the web page.
*/
QString QchWebPage::statusText() const {
    Q_D(const QchWebPage);

    return d->statusText;
}

/*!
    \brief Whether any HTML is selected in the web page.
*/
bool QchWebPage::hasSelection() const {
    return !selectedText().isEmpty();
}

/*!
    \brief The user-agent string used when loading a web page.
*/
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

/*!
    \brief The component used when a new window is requested.
*/
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

/*!    
    Performs a hit test at postion \a x,\a y, and returns the result.
*/
QWebHitTestResult QchWebPage::hitTestContent(int x, int y) {
    return currentFrame()->hitTestContent(QPoint(x, y));
}

/*!    
    Searches for the next occurrance of \a text in the web page. Returns true if successful.
*/
bool QchWebPage::findText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument);
}

/*!    
    Searches for all occurrances of \a text in the web page. Returns true if successful.
*/
bool QchWebPage::findAllText(const QString &text) {
    return QWebPage::findText(text, QWebPage::FindWrapsAroundDocument | QWebPage::HighlightAllOccurrences);
}

/*!    
    Attempts to load the web page located at \a url.
    
    \sa url, baseUrl, requestedUrl
*/
void QchWebPage::load(const QUrl &url) {
    mainFrame()->load(url);
}

/*!    
    Reloads the current web page.
*/
void QchWebPage::reload() {
    triggerAction(QWebPage::Reload);
}

/*!    
    Aborts the loading of a web page.
*/
void QchWebPage::stop() {
    triggerAction(QWebPage::Stop);
}

/*!    
    Navigates to the previous item in the history, if possible.
    
    \sa WebHistory::backItem, WebHistory::canGoBack
*/
void QchWebPage::back() {
    triggerAction(QWebPage::Back);
}

/*!    
    Navigates to the next item in the history, if possible.
    
    \sa WebHistory::forwardItem, WebHistory::canGoForward
*/
void QchWebPage::forward() {
    triggerAction(QWebPage::Forward);
}

/*!    
    Copies the selected HTML to the clipboard.
    
    \sa hasSelection, selectedHtml
*/
void QchWebPage::copy() {
    triggerAction(QWebPage::Copy);
}

/*!    
    Copies the selected HTML to the clipboard and removes it from the web page.
    
    \sa hasSelection, selectedHtml, contentEditable
*/
void QchWebPage::cut() {
    triggerAction(QWebPage::Cut);
}

/*!    
    Inserts the the clipboard's contents into the web page.
    
    \sa contentEditable
*/
void QchWebPage::paste() {
    triggerAction(QWebPage::Paste);
}

void QchWebPage::triggerAction(QWebPage::WebAction action, bool checked) {
    QWebPage::triggerAction(action, checked);
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

/*!
    \fn void WebPage::downloadRequested(QVariantMap request)

    This signal is emitted when the user decides to download a link. The url of the link as well as additional 
    meta-information is contained in \a request.

    \sa unsupportedContent()
*/

/*!
    \fn void WebPage::unsupportedContent(QVariantMap content)

    This signal is emitted when WebKit cannot handle a link the user navigated to or a web server's response includes 
    a "Content-Disposition" header with the 'attachment' directive. If "Content-Disposition" is present in \a content, 
    the web server is indicating that the client should prompt the user to save the content regardless of content-type. 
    See RFC 2616 sections 19.5.1 for details about Content-Disposition.

    \note This signal is only emitted if the \link forwardUnsupportedContent\endlink property is set to true.

    \sa downloadRequested()
*/

#include "moc_qchwebpage.cpp"

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

#include "qchwebview.h"
#include "qchwebhistory.h"
#include "qchwebsettings.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeInfo>
#include <QNetworkReply>
#include <QApplication>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

class QchWebViewPrivate
{

public:
    QchWebViewPrivate(QchWebView *parent) :
        q_ptr(parent),
        webPage(0),
        webHistory(0),
        webSettings(0),
        windowComponent(0),
        windowParent(0),
        contextMenuPolicy(Qt::DefaultContextMenu),
        progress(0),
        status(QchWebView::Null)
    {
    }

    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (QchWebView *view = qobject_cast<QchWebView*>(list->object)) {
            obj->setParent(view);
        }
    }

    static void jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
        if (!obj) {
            return;
        }

        if (QchWebView *view = qobject_cast<QchWebView*>(list->object)) {
            view->d_func()->jsObjectList << obj;
            view->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }

    QDeclarativeListProperty<QObject> data() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, QchWebViewPrivate::data_append);
    }

    QDeclarativeListProperty<QObject> jsObjects() {
        return QDeclarativeListProperty<QObject>(q_func(), 0, QchWebViewPrivate::jsobjects_append);
    }

    QchWebPage* page() const {
        return webPage;
    }

    void setPage(QchWebPage *page) {
        if (page != webPage) {
            Q_Q(QchWebView);
            
            if (webPage) {
                q->disconnect(webPage, 0, q, 0);
            }
            
            webPage = page;
            status = QchWebView::Null;
            q->setPage(page);
            emit q->pageChanged();
            emit q->statusChanged();
            
            q->connect(webPage, SIGNAL(preferredWidthChanged()), q, SIGNAL(preferredWidthChanged()));
            q->connect(webPage, SIGNAL(preferredHeightChanged()), q, SIGNAL(preferredHeightChanged()));
            q->connect(webPage, SIGNAL(selectionChanged()), q, SIGNAL(selectedTextChanged()));
            q->connect(webPage, SIGNAL(userAgentChanged()), q, SIGNAL(userAgentChanged()));
            q->connect(webPage, SIGNAL(linkClicked(QUrl)), q, SIGNAL(linkClicked(QUrl)));
            q->connect(webPage, SIGNAL(downloadRequested(QNetworkRequest)),
                       q, SIGNAL(downloadRequested(QNetworkRequest)));
            q->connect(webPage, SIGNAL(unsupportedContent(QNetworkReply*)),
                       q, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
            q->connect(webPage->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
                       q, SLOT(_q_onJavaScriptWindowObjectCleared()));
        }
    }

    QchWebHistory* history() {
        if (!webHistory) {
            webHistory = new QchWebHistory(page());
        }

        return webHistory;
    }

    QchWebSettings* settings() {
        if (!webSettings) {
            webSettings = new QchWebSettings(page());
        }

        return webSettings;
    }

    void _q_onLoadStarted() {
        Q_Q(QchWebView);

        status = QchWebView::Loading;
        emit q->statusChanged();
    }

    void _q_onLoadFinished(bool ok) {
        Q_Q(QchWebView);

        status = ok ? QchWebView::Ready : QchWebView::Error;
        emit q->statusChanged();
    }

    void _q_onLoadProgress(int p) {
        Q_Q(QchWebView);

        progress = p;
        emit q->progressChanged();
    }

    void _q_onStatusBarMessage(const QString &message) {
        if (message != statusText) {
            statusText = message;
            Q_Q(QchWebView);
            emit q->statusTextChanged();
        }
    }

    void _q_onUnsupportedContent(QNetworkReply *reply) {
        Q_Q(QchWebView);

        if (reply->rawHeader("Content-Disposition").startsWith("attachment")) {
            emit q->downloadRequested(reply->request());
        }
        else {
            status = QchWebView::Error;
            statusText = QchWebView::tr("Content not supported");
            emit q->statusChanged();
            emit q->statusTextChanged();
        }
        
        reply->deleteLater();
    }

    void _q_onJavaScriptWindowObjectCleared() {
        Q_Q(QchWebView);

        foreach (QObject *obj, jsObjectList) {
            q->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }
        
    QchWebView *q_ptr;
        
    QchWebPage *webPage;

    QchWebHistory *webHistory;

    QchWebSettings *webSettings;

    QDeclarativeComponent *windowComponent;

    QDeclarativeItem *windowParent;
    
    Qt::ContextMenuPolicy contextMenuPolicy;

    int progress;

    QchWebView::Status status;

    QString statusText;

    QList<QObject*> jsObjectList;

    Q_DECLARE_PUBLIC(QchWebView)
};

/*!
    \class WebView
    \brief Provides an item that is used to view and edit web documents.

    \ingroup webkit

    WebView is the main component of the org.hildon.webkit web browsing module. It can be used in various applications 
    to display web content live from the internet.
    
    \include webview.qml
    
    \sa WebPage
*/
QchWebView::QchWebView(QGraphicsItem *parent) :
    QGraphicsWebView(parent),
    d_ptr(new QchWebViewPrivate(this))
{
    Q_D(QchWebView);

    d->webPage = new QchWebPage(this);
    setPage(d->webPage);
    setResizesToContents(true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setPalette(QApplication::palette("QWebView"));

    if (const QDeclarativeEngine *engine = qmlEngine(this)) {
        d->webPage->setNetworkAccessManager(engine->networkAccessManager());
    }
    
    connect(d->webPage, SIGNAL(preferredWidthChanged()), this, SIGNAL(preferredWidthChanged()));
    connect(d->webPage, SIGNAL(preferredHeightChanged()), this, SIGNAL(preferredHeightChanged()));
    connect(d->webPage, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    connect(d->webPage, SIGNAL(userAgentChanged()), this, SIGNAL(userAgentChanged()));
    connect(d->webPage, SIGNAL(downloadRequested(QNetworkRequest)),
            this, SIGNAL(downloadRequested(QNetworkRequest)));
    connect(d->webPage, SIGNAL(unsupportedContent(QNetworkReply*)),
            this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(d->webPage->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

QchWebView::QchWebView(QchWebViewPrivate &dd, QGraphicsItem *parent) :
    QGraphicsWebView(parent),
    d_ptr(&dd)
{
    Q_D(QchWebView);

    d->webPage = new QchWebPage(this);
    setPage(d->webPage);
    setResizesToContents(true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setPalette(QApplication::palette("QWebView"));

    if (const QDeclarativeEngine *engine = qmlEngine(this)) {
        d->webPage->setNetworkAccessManager(engine->networkAccessManager());
    }

    connect(d->webPage, SIGNAL(preferredWidthChanged()), this, SIGNAL(preferredWidthChanged()));
    connect(d->webPage, SIGNAL(preferredHeightChanged()), this, SIGNAL(preferredHeightChanged()));
    connect(d->webPage, SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    connect(d->webPage, SIGNAL(userAgentChanged()), this, SIGNAL(userAgentChanged()));
    connect(d->webPage, SIGNAL(downloadRequested(QNetworkRequest)),
            this, SIGNAL(downloadRequested(QNetworkRequest)));
    connect(d->webPage, SIGNAL(unsupportedContent(QNetworkReply*)),
            this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    connect(d->webPage->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

QchWebView::~QchWebView() {}

Qt::ContextMenuPolicy QchWebView::contextMenuPolicy() const {
    Q_D(const QchWebView);
    
    return d->contextMenuPolicy;
}

void QchWebView::setContextMenuPolicy(Qt::ContextMenuPolicy policy) {
    if (policy != contextMenuPolicy()) {
        Q_D(QchWebView);
        d->contextMenuPolicy = policy;
        emit contextMenuPolicyChanged();
    }
}

/*!
    \brief The preferred width of the web view.
*/
int QchWebView::preferredWidth() const {
    Q_D(const QchWebView);
    
    return d->webPage->preferredWidth();
}

void QchWebView::setPreferredWidth(int w) {
    Q_D(QchWebView);
    
    d->webPage->setPreferredWidth(w);
}

/*!
    \brief The preferred height of the web view.
*/
int QchWebView::preferredHeight() const {
    Q_D(const QchWebView);
    
    return d->webPage->preferredHeight();
}

void QchWebView::setPreferredHeight(int h) {
    Q_D(QchWebView);
    
    d->webPage->setPreferredHeight(h);
}

/*!
    \property WebElement WebView::documentElement
    \brief The document element of the web view's main frame
*/
QWebElement QchWebView::documentElement() const {
    return page()->mainFrame()->documentElement();
}

/*!
    \property string WebView::html
    \brief The HTML of the web view.
*/
QString QchWebView::toHtml() const {
    return page()->mainFrame()->toHtml();
}

/*!
    \property string WebView::text
    \brief The HTML of the web view as plain text.
*/
QString QchWebView::toPlainText() const {
    return page()->mainFrame()->toPlainText();
}

void QchWebView::setText(const QString &text) {
    page()->mainFrame()->setContent(text.toUtf8(), "text/plain");
}

/*!
    \brief Whether any text is selected in the web view.
*/
bool QchWebView::hasSelection() const {
    return !selectedText().isEmpty();
}

/*!
    \brief The selected text of the web view.
*/
QString QchWebView::selectedText() const {
    return page()->selectedText();
}

/*!
    \brief The policy used to determine how to handle activated links.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>WebPage.DontDelegateLinks</td>
            <td>No links are delegated (default).</td>
        </tr>
        <tr>
            <td>WebPage.DelegateExternalLinks</td>
            <td>When activating links that point to documents not stored on the local filesystem or an equivalent - 
            such as the Qt resource system - then linkClicked() is emitted.</td>
        </tr>
        <tr>
            <td>WebPage.DelegateAllLinks</td>
            <td>Whenever a link is activated the linkClicked() signal is emitted.</td>
        </tr>
    </table>
*/
QWebPage::LinkDelegationPolicy QchWebView::linkDelegationPolicy() const {
    return page()->linkDelegationPolicy();
}

void QchWebView::setLinkDelegationPolicy(QWebPage::LinkDelegationPolicy policy) {
    if (policy != linkDelegationPolicy()) {
        page()->setLinkDelegationPolicy(policy);
        emit linkDelegationPolicyChanged();
    }
}

/*!
    \brief The loading progress of the web view.
*/
int QchWebView::progress() const {
    Q_D(const QchWebView);

    return d->progress;
}

/*!
    \brief The current status of the web view.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>WebView.Null</td>
            <td>No web page has been loaded (default).</td>
        </tr>
        <tr>
            <td>WebView.Loading</td>
            <td>The web page is being loaded.</td>
        </tr>
        <tr>
            <td>WebView.Ready</td>
            <td>The web page has been loaded.</td>
        </tr>
        <tr>
            <td>WebView.Error</td>
            <td>An error occured when loading the web page.</td>
        </tr>
    </table>
*/
QchWebView::Status QchWebView::status() const {
    Q_D(const QchWebView);

    return d->status;
}

/*!
    \brief The status text of the web view.
*/
QString QchWebView::statusText() const {
    Q_D(const QchWebView);

    return d->statusText;
}

/*!
    \brief The user-agent string used when loading a web page.
*/
QString QchWebView::userAgent() const {
    Q_D(const QchWebView);

    return d->webPage->userAgent();
}

void QchWebView::setUserAgent(const QString &agent) {
    Q_D(QchWebView);

    d->webPage->setUserAgent(agent);
}

/*!
    \brief The component used when a new window is requested.
*/
QDeclarativeComponent* QchWebView::newWindowComponent() const {
    Q_D(const QchWebView);

    return d->windowComponent;
}

void QchWebView::setNewWindowComponent(QDeclarativeComponent *component) {
    if (component != newWindowComponent()) {
        Q_D(QchWebView);
        d->windowComponent = component;
        emit newWindowComponentChanged();
    }
}

QDeclarativeItem* QchWebView::newWindowParent() const {
    Q_D(const QchWebView);

    return d->windowParent;
}

void QchWebView::setNewWindowParent(QDeclarativeItem *parent) {
    if (parent != newWindowParent()) {
        Q_D(QchWebView);
        d->windowParent = parent;
        emit newWindowParentChanged();
    }
}

/*!    
    Performs a hit test at postion \a x,\a y, and returns the result.
*/
QWebHitTestResult QchWebView::hitTestContent(int x, int y) {
    return page()->currentFrame()->hitTestContent(QPoint(x, y));
}

/*!    
    Searches for the next occurrance of \a text in the web page. Returns true if successful.
*/
bool QchWebView::findText(const QString &text) {
    return QGraphicsWebView::findText(text, QWebPage::FindWrapsAroundDocument);
}

/*!    
    Searches for all occurrances of \a text in the web page. Returns true if successful.
*/
bool QchWebView::findAllText(const QString &text) {
    return QGraphicsWebView::findText(text, QWebPage::FindWrapsAroundDocument | QWebPage::HighlightAllOccurrences);
}

/*!    
    Copies the selected HTML to the clipboard.
    
    \sa WebPage::copy()
*/
void QchWebView::copy() {
    triggerPageAction(QWebPage::Copy);
}

/*!    
    Copies the selected HTML to the clipboard and removes it from the web page.
    
    \sa WebPage::cut()
*/
void QchWebView::cut() {
    triggerPageAction(QWebPage::Cut);
}

/*!    
    Inserts the the clipboard's contents into the web page.
    
    \sa WebPage::paste()
*/
void QchWebView::paste() {
    triggerPageAction(QWebPage::Paste);
}

void QchWebView::triggerAction(int action, bool checked) {
    triggerPageAction(QWebPage::WebAction(action), checked);
}

QGraphicsWebView* QchWebView::createWindow(QWebPage::WebWindowType type) {
    Q_UNUSED(type);
    Q_D(QchWebView);

    if (!d->windowComponent) {
        return 0;
    }

    QGraphicsWebView *view = 0;
    QDeclarativeContext *creationContext = d->windowComponent->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->windowComponent->create(context)) {
        view = qobject_cast<QGraphicsWebView*>(obj);

        if (!view) {
            view = obj->findChild<QGraphicsWebView*>();
        }

        if (view) {
            view->setParent(d->windowParent);
        }
        else {
            qmlInfo(this) << tr("No QchWebView found in window component");
            delete obj;
            delete context;
        }
    }
    else {
        delete context;
    }

    return view;
}

void QchWebView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    switch (contextMenuPolicy()) {
    case Qt::DefaultContextMenu:
        QGraphicsWebView::contextMenuEvent(event);
        return;
    case Qt::CustomContextMenu:
        emit customContextMenuRequested(event->pos().x(), event->pos().y());
        break;
    case Qt::ActionsContextMenu: {
        QMenu menu;
        
        foreach (QAction *action, actions()) {
            menu.addAction(action);
        }
        
        menu.exec(event->screenPos());
        break;
    }
    case Qt::NoContextMenu:
        event->ignore();
        return;
    default:
        break;
    }
    
    event->accept();
}

void QchWebView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_C:
        if (event->modifiers() & Qt::ControlModifier) {
            triggerPageAction(QWebPage::Copy);
            event->accept();
            return;
        }

        break;
    case Qt::Key_X:
        if (event->modifiers() & Qt::ControlModifier) {
            triggerPageAction(QWebPage::Cut);
            event->accept();
            return;
        }

        break;
    case Qt::Key_V:
        if (event->modifiers() & Qt::ControlModifier) {
            triggerPageAction(QWebPage::Paste);
            event->accept();
            return;
        }

        break;
    default:
        break;
    }

    QGraphicsWebView::keyPressEvent(event);
}

/*!
    \fn void WebView::downloadRequested(QVariantMap request)

    This signal is emitted when the user decides to download a link. The url of the link as well as additional 
    meta-information is contained in \a request.

    \sa unsupportedContent()
*/

/*!
    \fn void WebView::unsupportedContent(QVariantMap content)

    This signal is emitted when WebKit cannot handle a link the user navigated to or a web server's response includes 
    a "Content-Disposition" header with the 'attachment' directive. If "Content-Disposition" is present in \a content, 
    the web server is indicating that the client should prompt the user to save the content regardless of content-type. 
    See RFC 2616 sections 19.5.1 for details about Content-Disposition.

    \note This signal is only emitted if the \link forwardUnsupportedContent\endlink property is set to true.

    \sa downloadRequested()
*/

#include "moc_qchwebview.cpp"

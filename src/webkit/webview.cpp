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

#include "webview_p.h"
#include "webview_p_p.h"
#include "webhistory_p.h"
#include "websettings_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QWebFrame>
#include <QAbstractKineticScroller>
#include <QGraphicsOpacityEffect>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeComponent>
#include <QDeclarativeInfo>
#include <QTimer>
#include <QNetworkReply>

WebView::WebView(QWidget *parent) :
    QWebView(parent),
    d_ptr(new WebViewPrivate(this))
{
    Q_D(WebView);

    d->suppressor = new WebViewSelectionSuppressor(this);
    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->page()->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->page(), SIGNAL(scrollRequested(int,int,QRect)), this, SLOT(_q_onScrollRequested()));
    this->connect(this->page(), SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    this->connect(this->page(), SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked(QUrl)));
    this->connect(this->page(), SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    this->connect(this->page(), SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    this->connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    this->connect(this, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

WebView::WebView(WebViewPrivate &dd, QWidget *parent) :
    QWebView(parent),
    d_ptr(&dd)
{
    Q_D(WebView);

    d->suppressor = new WebViewSelectionSuppressor(this);
    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    if (QDeclarativeEngine *engine = qmlEngine(this)) {
        this->page()->setNetworkAccessManager(engine->networkAccessManager());
    }

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(this->page(), SIGNAL(scrollRequested(int,int,QRect)), this, SLOT(_q_onScrollRequested()));
    this->connect(this->page(), SIGNAL(selectionChanged()), this, SIGNAL(selectedTextChanged()));
    this->connect(this->page(), SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked(QUrl)));
    this->connect(this->page(), SIGNAL(downloadRequested(QNetworkRequest)), this, SLOT(_q_onDownloadRequested(QNetworkRequest)));
    this->connect(this->page(), SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(_q_onUnsupportedContent(QNetworkReply*)));
    this->connect(this->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(_q_onJavaScriptWindowObjectCleared()));
    this->connect(this, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    this->connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(urlChanged()));
    this->connect(this, SIGNAL(loadStarted()), this, SLOT(_q_onLoadStarted()));
    this->connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_q_onLoadFinished(bool)));
    this->connect(this, SIGNAL(loadProgress(int)), this, SLOT(_q_onLoadProgress(int)));
    this->connect(this, SIGNAL(statusBarMessage(QString)), this, SLOT(_q_onStatusBarMessage(QString)));
}

WebView::~WebView() {}

void WebView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void WebView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal WebView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void WebView::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine WebView::left() const {
    Q_D(const WebView);

    return d->left;
}

AnchorLine WebView::right() const {
    Q_D(const WebView);

    return d->right;
}

AnchorLine WebView::top() const {
    Q_D(const WebView);

    return d->top;
}

AnchorLine WebView::bottom() const {
    Q_D(const WebView);

    return d->bottom;
}

AnchorLine WebView::horizontalCenter() const {
    Q_D(const WebView);

    return d->horizontalCenter;
}

AnchorLine WebView::verticalCenter() const {
    Q_D(const WebView);

    return d->verticalCenter;
}

QString WebView::iconSource() const {
    return this->icon().name();
}

QString WebView::toHtml() const {
    return this->page()->mainFrame()->toHtml();
}

QString WebView::toPlainText() const {
    return this->page()->mainFrame()->toPlainText();
}

void WebView::setText(const QString &text) {
    this->page()->mainFrame()->setContent(text.toUtf8(), "text/plain");
}

bool WebView::interactive() const {
    Q_D(const WebView);

    return d->kineticScroller->isEnabled();
}

void WebView::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(WebView);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool WebView::textSelectionEnabled() const {
    Q_D(const WebView);

    return !d->suppressor->isEnabled();
}

void WebView::setTextSelectionEnabled(bool enabled) {
    Q_D(WebView);

    if (enabled == this->textSelectionEnabled()) {
        return;
    }

    if (enabled) {
        d->suppressor->disable();
    }
    else {
        d->suppressor->enable();
    }

    d->kineticScroller->setEnabled(!enabled);

    emit textSelectionEnabledChanged();
}

bool WebView::hasSelection() const {
    return !this->selectedText().isEmpty();
}

QWebPage::LinkDelegationPolicy WebView::linkDelegationPolicy() const {
    return this->page()->linkDelegationPolicy();
}

void WebView::setLinkDelegationPolicy(QWebPage::LinkDelegationPolicy policy) {
    if (policy != this->linkDelegationPolicy()) {
        this->page()->setLinkDelegationPolicy(policy);
        emit linkDelegationPolicyChanged();
    }
}

bool WebView::forwardUnsupportedContent() const {
    return this->page()->forwardUnsupportedContent();
}

void WebView::setForwardUnsupportedContent(bool forward) {
    if (forward != this->forwardUnsupportedContent()) {
        this->page()->setForwardUnsupportedContent(forward);
        emit forwardUnsupportedContentChanged();
    }
}

bool WebView::moving() const {
    Q_D(const WebView);

    if (d->scrollTimer->isActive()) {
        return true;
    }

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool WebView::atXBeginning() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().x() == 0;
    }

    return false;
}

bool WebView::atXEnd() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().x() == frame->contentsSize().width() - frame->geometry().width();
    }

    return false;
}

bool WebView::atYBeginning() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().y() == 0;
    }

    return false;
}

bool WebView::atYEnd() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().y() == frame->contentsSize().height() - frame->geometry().height();
    }

    return false;
}

int WebView::contentX() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().x();
    }

    return 0;
}

void WebView::setContentX(int x) {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        frame->setScrollPosition(QPoint(x, frame->scrollPosition().y()));
    }
}

int WebView::contentY() const {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        return frame->scrollPosition().y();
    }

    return 0;
}

void WebView::setContentY(int y) {
    if (QWebFrame *frame = this->page()->currentFrame()) {
        frame->setScrollPosition(QPoint(frame->scrollPosition().x(), y));
    }
}

qreal WebView::flickDeceleration() const {
    Q_D(const WebView);

    return d->kineticScroller->decelerationFactor();
}

void WebView::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(WebView);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal WebView::maximumFlickVelocity() const {
    Q_D(const WebView);

    return d->kineticScroller->maximumVelocity();
}

void WebView::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(WebView);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

int WebView::progress() const {
    Q_D(const WebView);

    return d->progress;
}

WebView::Status WebView::status() const {
    Q_D(const WebView);

    return d->status;
}

QString WebView::statusText() const {
    Q_D(const WebView);

    return d->statusText;
}

QDeclarativeComponent* WebView::newWindowComponent() const {
    Q_D(const WebView);

    return d->windowComponent;
}

void WebView::setNewWindowComponent(QDeclarativeComponent *component) {
    if (component != this->newWindowComponent()) {
        Q_D(WebView);
        d->windowComponent = component;
        emit newWindowComponentChanged();
    }
}

QWidget* WebView::newWindowParent() const {
    Q_D(const WebView);

    return d->windowParent;
}

void WebView::setNewWindowParent(QWidget *parent) {
    if (parent != this->newWindowParent()) {
        Q_D(WebView);
        d->windowParent = parent;
        emit newWindowParentChanged();
    }
}

QVariant WebView::hitTestContent(int x, int y) {
    QWebHitTestResult result = this->page()->currentFrame()->hitTestContent(QPoint(x, y));
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

bool WebView::findText(const QString &text) {
    return QWebView::findText(text, QWebPage::FindWrapsAroundDocument);
}

bool WebView::findAllText(const QString &text) {
    return QWebView::findText(text, QWebPage::FindWrapsAroundDocument | QWebPage::HighlightAllOccurrences);
}

void WebView::copy() {
    this->triggerPageAction(QWebPage::Copy);
}

void WebView::cut() {
    this->triggerPageAction(QWebPage::Cut);
}

void WebView::paste() {
    this->triggerPageAction(QWebPage::Paste);
}

QWebView* WebView::createWindow(QWebPage::WebWindowType type) {
    Q_UNUSED(type);
    Q_D(WebView);

    if (!d->windowComponent) {
        return 0;
    }

    QWebView *view = 0;
    QDeclarativeContext *creationContext = d->windowComponent->creationContext();
    QDeclarativeContext *context = new QDeclarativeContext(creationContext ? creationContext : qmlContext(this));

    if (QObject *obj = d->windowComponent->create(context)) {
        view = qobject_cast<QWebView*>(obj);

        if (!view) {
            view = obj->findChild<QWebView*>();
        }

        if (view) {
            view->setParent(d->windowParent);
        }
        else {
            qmlInfo(this) << tr("No WebView found in window component");
            delete obj;
            delete context;
        }
    }
    else {
        delete context;
    }

    return view;
}

void WebView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QWebView::changeEvent(event);
}

void WebView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QWebView::moveEvent(event);
}

void WebView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QWebView::resizeEvent(event);
}

void WebView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QWebView::showEvent(event);
}

void WebView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QWebView::hideEvent(event);
}

void WebView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QWebView::focusInEvent(event);
}

void WebView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QWebView::focusOutEvent(event);
}

void WebView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_C:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Copy);
            event->accept();
            return;
        }

        break;
    case Qt::Key_X:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Cut);
            event->accept();
            return;
        }

        break;
    case Qt::Key_V:
        if (event->modifiers() & Qt::ControlModifier) {
            this->triggerPageAction(QWebPage::Paste);
            event->accept();
            return;
        }

        break;
    default:
        break;
    }

    QWebView::keyPressEvent(event);
}

void WebView::classBegin() {}

void WebView::componentComplete() {
    Q_D(WebView);

    d->componentComplete();

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }

    foreach (QObject *obj, d->jsObjectList) {
        this->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
    }
}

void WebViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void WebViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void WebViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->actionList.append(obj);
        view->d_func()->dataList.append(obj);

        if (!view->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            view->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            view->addActions(group->actions());
        }
    }
}

void WebViewPrivate::jsobjects_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (WebView *view = qobject_cast<WebView*>(list->object)) {
        view->d_func()->jsObjectList.append(obj);
        view->d_func()->dataList.append(obj);

        if (view->d_func()->complete) {
            view->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
        }
    }
}

QDeclarativeListProperty<QObject> WebViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> WebViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, WebViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> WebViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::actions_append);
}

QDeclarativeListProperty<QObject> WebViewPrivate::jsObjects() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, WebViewPrivate::jsobjects_append);
}

WebHistory* WebViewPrivate::history() {
    Q_Q(WebView);

    if (!webHistory) {
        webHistory = new WebHistory(q->history(), q);
    }

    return webHistory;
}

WebSettings* WebViewPrivate::settings() {
    Q_Q(WebView);

    if (!webSettings) {
        webSettings = new WebSettings(q->settings(), q);
    }

    return webSettings;
}

void WebViewPrivate::_q_onLoadStarted() {
    Q_Q(WebView);

    status = WebView::Loading;
    emit q->statusChanged();
    emit q->urlChanged();
    emit q->titleChanged();
}

void WebViewPrivate::_q_onLoadFinished(bool ok) {
    Q_Q(WebView);

    status = ok ? WebView::Ready : WebView::Error;
    emit q->statusChanged();
    emit q->urlChanged();
    emit q->titleChanged();
}

void WebViewPrivate::_q_onLoadProgress(int p) {
    Q_Q(WebView);

    progress = p;
    emit q->progressChanged();
}

void WebViewPrivate::_q_onStatusBarMessage(const QString &message) {
    if (message != statusText) {
        statusText = message;
        Q_Q(WebView);
        emit q->statusTextChanged();
    }
}

void WebViewPrivate::_q_onDownloadRequested(const QNetworkRequest &request) {
    Q_Q(WebView);

    QVariantMap map;
    QVariantMap headers;
    map["url"] = request.url();

    foreach (QByteArray header, request.rawHeaderList()) {
        headers[header] = request.rawHeader(header);
    }

    map["headers"] = headers;
    emit q->downloadRequested(map);
}

void WebViewPrivate::_q_onUnsupportedContent(QNetworkReply *reply) {
    Q_Q(WebView);

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

void WebViewPrivate::_q_onJavaScriptWindowObjectCleared() {
    Q_Q(WebView);

    foreach (QObject *obj, jsObjectList) {
        q->page()->mainFrame()->addToJavaScriptWindowObject(obj->objectName(), obj);
    }
}

void WebViewPrivate::_q_onScrollRequested() {
    Q_Q(WebView);

    if (!scrollTimer->isActive()) {
        emit q->movingChanged();

        if (atXBeginning) {
            atXBeginning = false;
            emit q->atXBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atXEndChanged();
        }

        if (atYBeginning) {
            atYBeginning = false;
            emit q->atYBeginningChanged();
        }

        if (atXEnd) {
            atXEnd = false;
            emit q->atYEndChanged();
        }
    }

    emit q->contentXChanged();
    emit q->contentYChanged();

    scrollTimer->start();
}

void WebViewPrivate::_q_onScrollingStopped() {
    Q_Q(WebView);

    bool xb = q->atXBeginning();
    bool xe = q->atYEnd();
    bool yb = q->atYBeginning();
    bool ye = q->atYEnd();

    if (xb != atXBeginning) {
        atXBeginning = xb;
        emit q->atXBeginningChanged();
    }

    if (xe != atXEnd) {
        atXEnd = xe;
        emit q->atXEndChanged();
    }

    if (yb != atYBeginning) {
        atYBeginning = yb;
        emit q->atYBeginningChanged();
    }

    if (ye != atYEnd) {
        atYEnd = ye;
        emit q->atYEndChanged();
    }

    emit q->movingChanged();
}

#include "moc_webview_p.cpp"

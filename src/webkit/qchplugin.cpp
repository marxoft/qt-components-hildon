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

#include "qchplugin.h"
#include "qchnetworkrequest.h"
#include "qchscriptengineacquirer.h"
#include "qchwebelement.h"
#include "qchwebhistory.h"
#include "qchwebhistoryinterface.h"
#include "qchwebhittestresult.h"
#include "qchwebpage.h"
#include "qchwebsettings.h"
#include "qchwebview.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QScriptEngine>

void QchPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.webkit"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);
    
    QScriptEngine *se = QchScriptEngineAcquirer::getScriptEngine(engine);
    
    if (se) {
        QScriptValue request = se->newQObject(new QchNetworkRequest(se));
        se->setDefaultPrototype(qMetaTypeId<QNetworkRequest>(), request);
        se->setDefaultPrototype(qMetaTypeId<QNetworkRequest*>(), request);
        QScriptValue element = se->newQObject(new QchWebElement(se));
        se->setDefaultPrototype(qMetaTypeId<QWebElement>(), element);
        se->setDefaultPrototype(qMetaTypeId<QWebElement*>(), element);
        QScriptValue result = se->newQObject(new QchWebHitTestResult(se));
        se->setDefaultPrototype(qMetaTypeId<QWebHitTestResult>(), result);
        se->setDefaultPrototype(qMetaTypeId<QWebHitTestResult*>(), result);
    }
    
    if (engine->rootContext()->contextProperty("webHistory").isNull()) {
        engine->rootContext()->setContextProperty("webHistory", new QchWebHistoryInterface(engine));
        engine->rootContext()->setContextProperty("webSettings", new QchWebSettings(engine));
        
        qmlRegisterUncreatableType<QchWebHistory>(uri, 1, 0, "WebHistory", "");
        qmlRegisterUncreatableType<QchWebHistoryInterface>(uri, 1, 0, "WebHistoryInterface", "");
        qmlRegisterUncreatableType<QchWebSettings>(uri, 1, 0, "WebSettings", "");
    }
}

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.webkit"));

    qmlRegisterType<QchWebPage>(uri, 1, 0, "WebPage");
    qmlRegisterType<QchWebView>(uri, 1, 0, "WebView");
}

Q_EXPORT_PLUGIN2(qchwebkit, QchPlugin)

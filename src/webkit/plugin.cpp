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

#include "plugin_p.h"
#include "webpage_p.h"
#include "webview_p.h"
#include "webhistory_p.h"
#include "webhistoryinterface_p.h"
#include "websettings_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void Plugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.webkit"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);

    if (engine->rootContext()->contextProperty("webHistory").isNull()) {
        engine->rootContext()->setContextProperty("webHistory", new WebHistoryInterface(engine));
        engine->rootContext()->setContextProperty("webSettings", new WebSettings(engine));

        qmlRegisterUncreatableType<WebHistory>(uri, 1, 0, "WebHistory", "");
        qmlRegisterUncreatableType<WebHistoryInterface>(uri, 1, 0, "WebHistoryInterface", "");
        qmlRegisterUncreatableType<WebSettings>(uri, 1, 0, "WebSettings", "");
    }
}

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.webkit"));

    qmlRegisterType<WebPage>(uri, 1, 0, "WebPage");
    qmlRegisterType<WebView>(uri, 1, 0, "WebView");
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildonwebkit, Plugin)

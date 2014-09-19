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
#include "clipboard_p.h"
#include "directory_p.h"
#include "process_p.h"
#include "screensaver_p.h"
#include "screenshot_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void Plugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.utils"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);

    if (engine->rootContext()->contextProperty("clipboard").isNull()) {
        engine->rootContext()->setContextProperty("clipboard", new Clipboard(engine));

        qmlRegisterUncreatableType<Clipboard>(uri, 1, 0, "Clipboard", "");
    }
}

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.utils"));

    qmlRegisterType<Directory>(uri, 1, 0, "Directory");
    qmlRegisterType<Process>(uri, 1, 0, "Process");
    qmlRegisterType<ScreenSaver>(uri, 1, 0, "ScreenSaver");
    qmlRegisterType<ScreenShot>(uri, 1, 0, "ScreenShot");
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildonutils, Plugin)

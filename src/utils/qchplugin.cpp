/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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
#include "qchclipboard.h"
#include "qchdirectory.h"
#include "qchfile.h"
#include "qchprocess.h"
#include "qchscreensaver.h"
#include "qchscreenshot.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void QchPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.utils"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);

    if (engine->rootContext()->contextProperty("clipboard").isNull()) {
        engine->rootContext()->setContextProperty("clipboard", new QchClipboard(engine));
    }
}

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.utils"));

    qmlRegisterType<QchDirectory>(uri, 1, 0, "Directory");
    qmlRegisterType<QchFile>(uri, 1, 0, "File");
    qmlRegisterType<QchProcess>(uri, 1, 0, "Process");
    qmlRegisterType<QchScreenSaver>(uri, 1, 0, "ScreenSaver");
    qmlRegisterType<QchScreenShot>(uri, 1, 0, "ScreenShot");
}

Q_EXPORT_PLUGIN2(qchutils, QchPlugin)

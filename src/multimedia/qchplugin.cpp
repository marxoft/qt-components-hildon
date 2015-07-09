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
#include "metadatawatcher.h"
#include "qchaudioplayer.h"
#include "qchnowplayingmodel.h"
#include <QDeclarativeEngine>
#include <libmafw/mafw-log.h>

void QchPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.multimedia"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);
    
    // Disable mafw syslog logging
    mafw_log_init(NULL);
}

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.multimedia"));
    
    qmlRegisterUncreatableType<QchMediaStatus>(uri, 1, 0, "MediaStatus", "");
    qmlRegisterUncreatableType<QchMediaType>(uri, 1, 0, "MediaType", "");
    qmlRegisterUncreatableType<MetadataWatcher>(uri, 1, 0, "MetadataWatcher", "");

    qmlRegisterType<QchAudioPlayer>(uri, 1, 0, "Audio");
    qmlRegisterType<QchNowPlayingModel>(uri, 1, 0, "NowPlayingModel");
}

Q_EXPORT_PLUGIN2(hildonmultimedia, QchPlugin)

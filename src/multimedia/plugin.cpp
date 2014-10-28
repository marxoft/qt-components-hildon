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
#include "audioplayer_p.h"
#include "metadatawatcher_p.h"
#include "playbackmodel_p.h"
#include "videoplayer_p.h"
#include <QDeclarativeEngine>
#include <libmafw/mafw-log.h>

void Plugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.multimedia"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);
    
    // Disable mafw syslog logging
    mafw_log_init(NULL);
}

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.multimedia"));
    
    qmlRegisterUncreatableType<MediaStatus>(uri, 1, 0, "MediaStatus", "");
    qmlRegisterUncreatableType<MediaType>(uri, 1, 0, "MediaType", "");
    qmlRegisterUncreatableType<MetadataWatcher>(uri, 1, 0, "MetadataWatcher", "");

    qmlRegisterType<AudioPlayer>(uri, 1, 0, "Audio");
    qmlRegisterType<PlaybackModel>(uri, 1, 0, "NowPlayingModel");
    qmlRegisterType<VideoPlayer>(uri, 1, 0, "Video");
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildonmultimedia, Plugin)

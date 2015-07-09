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
 
#include "qchaudioplayer.h"
#include "metadatawatcher.h"
#include "missioncontrol.h"
#include "mafw/mafwregistryadapter.h"
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDeclarativeInfo>

class QchAudioPlayerPrivate
{

public:
    QchAudioPlayerPrivate(QchAudioPlayer *parent) :
        q_ptr(parent),
        mafwRegistry(0),
        mafwRenderer(0),
        mafwPlaylist(0),
        mafwTrackerSource(0),
        metadataWatcher(0),
        missionControl(0),
        autoLoad(true),
        bufferProgress(0.0),
        seekable(true),
        position(0),
        duration(0),
        status(QchMediaStatus::Stopped),
        muted(false),
        volume(0),
        muteVolume(0),
        tickInterval(1000),
        positionTimerId(-1),
        sourceLoaded(true),
        readyToPlay(false),
        playWhenReady(false),
        complete(false)
    {
    }
    
    void loadSource() {
        QString uriToPlay = source.startsWith("/") ? "file://" + source : source;
        QString objectId = mafwTrackerSource->createObjectId(uriToPlay);
        
        if (uriToPlay.startsWith("file://")) {
            QString mime(gnome_vfs_get_mime_type_for_name(uriToPlay.toUtf8()));
            objectId = objectId.remove(0, 18) // "urisource::file://"
                               .replace("/", "%2F")
                               .prepend("localtagfs::music/songs/");
        }
        
        mafwPlaylist->assignAudioPlaylist();
        mafwPlaylist->clear();
        mafwPlaylist->appendItem(objectId);
        sourceLoaded = true;
    }
    
    void startPositionTimer() {
        if (positionTimerId == -1) {
            Q_Q(QchAudioPlayer);
            positionTimerId = q->startTimer(tickInterval);
        }
        
        mafwRenderer->getPosition();
    }
    
    void stopPositionTimer() {
        if (positionTimerId != -1) {
            Q_Q(QchAudioPlayer);
            q->killTimer(positionTimerId);
            positionTimerId = -1;
        }
    }
    
    void _q_onStatusReady(MafwPlaylist*, uint index, MafwPlayState state, const char*, const QString &error) {
        Q_Q(QchAudioPlayer);
        
        q->disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                      q, SLOT(_q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

        q->connect(mafwRenderer, SIGNAL(stateChanged(int)), q, SLOT(_q_onStateChanged(int)));
        
        _q_onStateChanged(state);
        
        if (!error.isEmpty()) {
            qmlInfo(q) << error;
        }
    }
    
    void _q_onMetaDataChanged() {
        Q_Q(QchAudioPlayer);
        
        int dur = metadataWatcher->metadata().value(MAFW_METADATA_KEY_DURATION).toInt();
        bool seek = metadataWatcher->metadata().value(MAFW_METADATA_KEY_IS_SEEKABLE).toBool();
        QString uri = metadataWatcher->metadata().value(MAFW_METADATA_KEY_URI).toString();
        
        if (dur != duration) {
            duration = dur;
            emit q->durationChanged();
        }
        
        if (seek != seekable) {
            seekable = seek;
            emit q->seekableChanged();
        }
        
        if (uri != source) {
            source = uri;
            sourceLoaded = true;
            emit q->sourceChanged();
        }
    }
    
    void _q_onBufferProgressChanged(float progress) {
        Q_Q(QchAudioPlayer);
        
        bufferProgress = progress;
        emit q->bufferProgressChanged();
    }
    
    void _q_onPositionChanged(int pos) {
        Q_Q(QchAudioPlayer);
        
        position = pos;
        emit q->positionChanged();
    }
    
    void _q_onVolumeChanged(int vol) {
        Q_Q(QchAudioPlayer);
        
        volume = vol;
        emit q->volumeChanged();
    }
    
    void _q_onStateChanged(int state) {
        Q_Q(QchAudioPlayer);
        
        QchMediaStatus::Status oldStatus = status;
        
        switch (state) {
        case Transitioning:
            readyToPlay = false;
            status = QchMediaStatus::Loading;
            break;
        case Playing:
            readyToPlay = false;
            status = QchMediaStatus::Playing;
            
            if (tickInterval > 0) {
                startPositionTimer();
            }
            
            if (oldStatus == QchMediaStatus::Paused) {
                emit q->resumed();
            }
            else {
                emit q->started();
            }
            
            break;
        case Paused:
            readyToPlay = true;
            
            if (playWhenReady) {
                playWhenReady = false;
                q->play();
            }
            else {
                status = QchMediaStatus::Paused;
                mafwRenderer->getPosition();
                stopPositionTimer();
                emit q->paused();
            }
            
            break;
        case Stopped:
            readyToPlay = true;
            
            if (playWhenReady) {
                playWhenReady = false;
                q->play();
            }
            else {
                if ((duration > 0) && (position >= duration)) {
                    status = QchMediaStatus::EndOfMedia;
                }
                else {
                    status = QchMediaStatus::Stopped;
                }
                
                position = 0;
                stopPositionTimer();
                emit q->positionChanged();
                emit q->stopped();
            }
            
            break;
        default:
            readyToPlay = false;
            break;
        }
        
        emit q->statusChanged();
    }
    
    void _q_onPropertyChanged(const QDBusMessage &msg) {
        if (msg.arguments()[0].toString() == MAFW_PROPERTY_RENDERER_VOLUME) {
            Q_Q(QchAudioPlayer);
            volume = qdbus_cast<QVariant>(msg.arguments()[1]).toInt();
            emit q->volumeChanged();
        }
    }
    
    void _q_onError(const QDBusMessage &msg) {
        if (msg.arguments()[0] == "com.nokia.mafw.error.renderer") {
            status = QchMediaStatus::Error;
            errorString.clear();
            errorString.append(QchAudioPlayer::tr("Unable to play media"));
            errorString.append("\n");

            if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_MEDIA) {
                errorString.append(QchAudioPlayer::tr("Media not found"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_URI_NOT_AVAILABLE) {
                errorString.append(QchAudioPlayer::tr("URI not available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INVALID_URI) {
                errorString.append(QchAudioPlayer::tr("Invalid URI"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_MEDIA_NOT_FOUND) {
                errorString.append(QchAudioPlayer::tr("Unable to open media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_STREAM_DISCONNECTED) {
                errorString.append(QchAudioPlayer::tr("Playback stream no longer available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_TYPE_NOT_AVAILABLE) {
                errorString.append(QchAudioPlayer::tr("Could not determine MIME-type"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYBACK) {
                errorString.append(QchAudioPlayer::tr("General error occured, unable to continue playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNABLE_TO_PERFORM) {
                errorString.append(QchAudioPlayer::tr("General error occured"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_TYPE) {
                errorString.append(QchAudioPlayer::tr("Unsupported media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_RESOLUTION) {
                errorString.append(QchAudioPlayer::tr("Unsupported resolution"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_FPS) {
                errorString.append(QchAudioPlayer::tr("Unsupported framerate"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DRM) {
                errorString.append(QchAudioPlayer::tr("Media is protected by DRM"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DEVICE_UNAVAILABLE) {
                errorString.append(QchAudioPlayer::tr("System sound device is unavailable"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CORRUPTED_FILE) {
                errorString.append(QchAudioPlayer::tr("Media corrupted"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYLIST_PARSING) {
                errorString.append(QchAudioPlayer::tr("Error while parsing playlist"));
                errorString.append(QchAudioPlayer::tr("Playlist may be corrupt or empty"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CODEC_NOT_FOUND) {
                errorString.append(QchAudioPlayer::tr("Codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_VIDEO_CODEC_NOT_FOUND) {
                errorString.append(QchAudioPlayer::tr("Video codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_AUDIO_CODEC_NOT_FOUND) {
                errorString.append(QchAudioPlayer::tr("Audio codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_PLAYLIST) {
                errorString.append(QchAudioPlayer::tr("No playlist assigned"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INDEX_OUT_OF_BOUNDS) {
                errorString.append(QchAudioPlayer::tr("Media index is not in bound with playlist items"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PLAY) {
                errorString.append(QchAudioPlayer::tr("Unable to start playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_STOP) {
                errorString.append(QchAudioPlayer::tr("Unable to stop playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PAUSE) {
                errorString.append(QchAudioPlayer::tr("Unable to pause playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_SET_POSITION) {
                errorString.append(QchAudioPlayer::tr("Unable to seek position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_POSITION) {
                errorString.append(QchAudioPlayer::tr("Unable to retrieve current position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_STATUS) {
                errorString.append(QchAudioPlayer::tr("Unable to get current playback status"));
            }
                
            Q_Q(QchAudioPlayer);
            emit q->statusChanged();
            emit q->error(errorString);
        }
    }
    
    QchAudioPlayer *q_ptr;
    
    MafwRegistryAdapter *mafwRegistry;
    MafwRendererAdapter *mafwRenderer;
    MafwPlaylistAdapter *mafwPlaylist;
    MafwSourceAdapter *mafwTrackerSource;
    MetadataWatcher *metadataWatcher;
    MissionControl *missionControl;
    
    bool autoLoad;
    
    qreal bufferProgress;
    
    QString errorString;
    
    bool seekable;
    
    int position;
    int duration;
    
    QString source;
    
    QchMediaStatus::Status status;
    
    bool muted;
    
    int volume;
    int muteVolume;
    
    int tickInterval;
    
    int positionTimerId;
    
    bool sourceLoaded;
    
    bool readyToPlay;
    bool playWhenReady;
    
    bool complete;
    
    Q_DECLARE_PUBLIC(QchAudioPlayer)
};

QchAudioPlayer::QchAudioPlayer(QObject *parent) :
    QObject(parent),
    d_ptr(new QchAudioPlayerPrivate(this))
{
    Q_D(QchAudioPlayer);
    
    d->mafwRegistry = MafwRegistryAdapter::get();
    d->mafwRenderer = d->mafwRegistry->renderer();
    d->mafwPlaylist = d->mafwRegistry->playlist();
    d->mafwTrackerSource = d->mafwRegistry->source(MafwRegistryAdapter::Tracker);
    d->metadataWatcher = MetadataWatcher::acquire();
    d->missionControl = MissionControl::acquire();
    
    connect(d->metadataWatcher, SIGNAL(metadataChanged()), this, SLOT(_q_onMetaDataChanged()));
    connect(d->mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                  this, SLOT(_q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));
    connect(d->mafwRenderer, SIGNAL(signalGetPosition(int,QString)), this, SLOT(_q_onPositionChanged(int)));
    connect(d->mafwRenderer, SIGNAL(signalGetVolume(int)), this, SLOT(_q_onVolumeChanged(int)));
    connect(d->mafwRenderer, SIGNAL(bufferingInfo(float)), this, SLOT(_q_onBufferProgressChanged(float)));
            
    QDBusConnection::sessionBus().connect("com.nokia.mafw.renderer.Mafw-Gst-Renderer-Plugin.gstrenderer",
                                          "/com/nokia/mafw/renderer/gstrenderer",
                                          "com.nokia.mafw.extension",
                                          "property_changed",
                                          this, SLOT(_q_onPropertyChanged(const QDBusMessage &)));
                                          
    QDBusConnection::sessionBus().connect("",
                                          "/com/nokia/mafw/renderer/gstrenderer",
                                          "com.nokia.mafw.extension",
                                          "error",
                                          this, SLOT(_q_onError(const QDBusMessage &)));
}

QchAudioPlayer::~QchAudioPlayer() {
    Q_D(QchAudioPlayer);
    
    d->mafwRenderer->enablePlayback(false);
    d->mafwRenderer->stop();
}

bool QchAudioPlayer::autoLoad() const {
    Q_D(const QchAudioPlayer);
    
    return d->autoLoad;
}

void QchAudioPlayer::setAutoLoad(bool enable) {
    if (enable != autoLoad()) {
        Q_D(QchAudioPlayer);
        d->autoLoad = enable;
        emit autoLoadChanged();
    }
}

qreal QchAudioPlayer::bufferProgress() const {
    Q_D(const QchAudioPlayer);
    
    return d->bufferProgress;
}

QString QchAudioPlayer::errorString() const {
    Q_D(const QchAudioPlayer);
    
    return d->errorString;
}

MetadataWatcher* QchAudioPlayer::metaData() const {
    Q_D(const QchAudioPlayer);
    
    return d->metadataWatcher;
}

bool QchAudioPlayer::isMuted() const {
    Q_D(const QchAudioPlayer);
    
    return d->muted;
}

void QchAudioPlayer::setMuted(bool muted) {
    if (muted != isMuted()) {
        Q_D(QchAudioPlayer);
        d->muted = muted;
        emit mutedChanged();
        
        if (muted) {
            d->muteVolume = volume();
            setVolume(0);
        }
        else {
            setVolume(d->muteVolume);
        }
    }
}

bool QchAudioPlayer::isPaused() const {
    return status() == QchMediaStatus::Paused;
}

void QchAudioPlayer::setPaused(bool paused) {
    if (paused) {
        pause();
    }
    else if (isPaused()) {
        play();
    }
}

bool QchAudioPlayer::isPlaying() const {
    switch (status()) {
    case QchMediaStatus::Loading:
    case QchMediaStatus::Playing:
        return true;
    default:
        return false;
    }
}

void QchAudioPlayer::setPlaying(bool playing) {
    if (playing) {
        play();
    }
    else if (isPlaying()) {
        pause();
    }
}

bool QchAudioPlayer::isSeekable() const {
    Q_D(const QchAudioPlayer);
    
    return d->seekable;
}

int QchAudioPlayer::position() const {
    Q_D(const QchAudioPlayer);
    
    return d->position;
}

void QchAudioPlayer::setPosition(int pos) {
    if (pos != position()) {
        Q_D(QchAudioPlayer);
        d->mafwRenderer->setPosition(SeekAbsolute, pos);
        d->mafwRenderer->getPosition();
    }
}

int QchAudioPlayer::duration() const {
    Q_D(const QchAudioPlayer);
    
    return d->duration;
}

QString QchAudioPlayer::source() const {
    Q_D(const QchAudioPlayer);
    
    return d->source;
}

void QchAudioPlayer::setSource(const QString &uri) {
    if (uri != source()) {
        Q_D(QchAudioPlayer);
        d->source = uri;
        
        if (autoLoad()) {
            d->loadSource();
        }
        else {
            d->sourceLoaded = false;
        }
    }
}

QchMediaStatus::Status QchAudioPlayer::status() const {
    Q_D(const QchAudioPlayer);
    
    return d->status;
}

int QchAudioPlayer::volume() const {
    Q_D(const QchAudioPlayer);
    
    return d->volume;
}

void QchAudioPlayer::setVolume(int vol) {
    if (vol != volume()) {
        Q_D(QchAudioPlayer);
        d->volume = qBound(0, vol, 100);
        d->mafwRenderer->setVolume(d->volume);
        d->mafwRenderer->getVolume();
    }
}

int QchAudioPlayer::tickInterval() const {
    Q_D(const QchAudioPlayer);
    
    return d->tickInterval;
}

void QchAudioPlayer::setTickInterval(int interval) {
    if (interval != tickInterval()) {
        Q_D(QchAudioPlayer);
        d->tickInterval = qMax(0, interval);
        emit tickIntervalChanged();
        
        d->stopPositionTimer();
        
        if ((interval > 0) && (isPlaying())) {
            d->startPositionTimer();
        }
    }
}

void QchAudioPlayer::play() {
    Q_D(QchAudioPlayer);
    
    if (isPaused()) {
        d->mafwRenderer->resume();
    }
    else {
        if (!d->sourceLoaded) {
            d->loadSource();
        }
        
        if (d->readyToPlay) {
            d->mafwRenderer->play();
        }
        else {
            d->playWhenReady = true;
        }
    }
}

void QchAudioPlayer::pause() {
    if (isPlaying()) {
        Q_D(QchAudioPlayer);
        d->mafwRenderer->pause();
    }
}

void QchAudioPlayer::stop() {
    if ((isPlaying()) || (isPaused())) {
        Q_D(QchAudioPlayer);
        d->mafwRenderer->stop();
    }
}

void QchAudioPlayer::classBegin() {}

void QchAudioPlayer::componentComplete() {
    Q_D(QchAudioPlayer);
    
    d->complete = true;
    
    if (d->mafwRenderer->isRendererReady()) {
        d->mafwRenderer->getStatus();
        d->mafwRenderer->getVolume();
    }
    else {
        connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getStatus()));
        connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getVolume()));
    }
}

void QchAudioPlayer::timerEvent(QTimerEvent *) {
    Q_D(QchAudioPlayer);
    
    d->mafwRenderer->getPosition();
}

#include "moc_qchaudioplayer.cpp"

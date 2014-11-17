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
 
#include "videoplayer_p.h"
#include "item_p_p.h"
#include "metadatawatcher_p.h"
#include "missioncontrol_p.h"
#include "mafw/mafwregistryadapter.h"
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <QApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDeclarativeInfo>

class VideoPlayerPrivate : public ItemPrivate
{

public:
    VideoPlayerPrivate(VideoPlayer *parent) :
        ItemPrivate(parent),
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
        status(MediaStatus::Stopped),
        muted(false),
        volume(0),
        muteVolume(0),
        tickInterval(1000),
        positionTimerId(-1),
        sourceLoaded(true),
        readyToPlay(false),
        playWhenReady(false)
    {
    }
    
    void loadSource() {
        QString uriToPlay = source.startsWith("/") ? "file://" + source : source;
        QString objectId = mafwTrackerSource->createObjectId(uriToPlay);
        
        if (uriToPlay.startsWith("file://")) {
            QString mime(gnome_vfs_get_mime_type_for_name(uriToPlay.toUtf8()));
            objectId = objectId.remove(0, 18) // "urisource::file://"
                               .replace("/", "%2F")
                               .prepend(QString("localtagfs::%1/")
                               .arg(mime.startsWith("video") ? "videos" : "music/songs"));
        }
        
        mafwPlaylist->assignVideoPlaylist();
        mafwPlaylist->clear();
        mafwPlaylist->appendItem(objectId);
        sourceLoaded = true;
    }
    
    void startPositionTimer() {
        if (positionTimerId == -1) {
            Q_Q(VideoPlayer);
            positionTimerId = q->startTimer(tickInterval);
        }
        
        mafwRenderer->getPosition();
    }
    
    void stopPositionTimer() {
        if (positionTimerId != -1) {
            Q_Q(VideoPlayer);
            q->killTimer(positionTimerId);
            positionTimerId = -1;
        }
    }
    
    void _q_onStatusReady(MafwPlaylist*, uint index, MafwPlayState state, const char*, const QString &error) {
        Q_Q(VideoPlayer);
        
        q->disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                      q, SLOT(_q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

        q->connect(mafwRenderer, SIGNAL(stateChanged(int)), q, SLOT(_q_onStateChanged(int)));
        
        this->_q_onStateChanged(state);
        
        if (!error.isEmpty()) {
            qmlInfo(q) << error;
        }
    }
    
    void _q_onMetaDataChanged() {
        Q_Q(VideoPlayer);
        
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
        
        emit q->hasAudioChanged();
        emit q->hasVideoChanged();
    }
    
    void _q_onBufferProgressChanged(float progress) {
        Q_Q(VideoPlayer);
        
        bufferProgress = progress;
        emit q->bufferProgressChanged();
    }
    
    void _q_onPositionChanged(int pos) {
        Q_Q(VideoPlayer);
        
        position = pos;
        emit q->positionChanged();
    }
    
    void _q_onVolumeChanged(int vol) {
        Q_Q(VideoPlayer);
        
        volume = vol;
        emit q->volumeChanged();
    }
    
    void _q_onStateChanged(int state) {
        Q_Q(VideoPlayer);
        
        MediaStatus::Status oldStatus = status;
        
        switch (state) {
        case Transitioning:
            status = MediaStatus::Loading;
            break;
        case Playing:
            status = MediaStatus::Playing;
            
            if (tickInterval > 0) {
                this->startPositionTimer();
            }
            
            if (oldStatus == MediaStatus::Paused) {
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
                status = MediaStatus::Paused;
                mafwRenderer->getPosition();
                this->stopPositionTimer();
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
                    status = MediaStatus::EndOfMedia;
                }
                else {
                    status = MediaStatus::Stopped;
                }
                
                position = 0;
                this->stopPositionTimer();
                emit q->positionChanged();
                emit q->stopped();
            }
            
            break;
        default:
            break;
        }
        
        emit q->statusChanged();
    }
    
    void _q_onPropertyChanged(const QDBusMessage &msg) {
        if (msg.arguments()[0].toString() == MAFW_PROPERTY_RENDERER_VOLUME) {
            Q_Q(VideoPlayer);
            volume = qdbus_cast<QVariant>(msg.arguments()[1]).toInt();
            emit q->volumeChanged();
        }
    }
    
    void _q_onError(const QDBusMessage &msg) {
        if (msg.arguments()[0] == "com.nokia.mafw.error.renderer") {
            status = MediaStatus::Error;
            errorString.clear();
            errorString.append(VideoPlayer::tr("Unable to play media"));
            errorString.append("\n");

            if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_MEDIA) {
                errorString.append(VideoPlayer::tr("Media not found"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_URI_NOT_AVAILABLE) {
                errorString.append(VideoPlayer::tr("URI not available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INVALID_URI) {
                errorString.append(VideoPlayer::tr("Invalid URI"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_MEDIA_NOT_FOUND) {
                errorString.append(VideoPlayer::tr("Unable to open media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_STREAM_DISCONNECTED) {
                errorString.append(VideoPlayer::tr("Playback stream no longer available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_TYPE_NOT_AVAILABLE) {
                errorString.append(VideoPlayer::tr("Could not determine MIME-type"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYBACK) {
                errorString.append(VideoPlayer::tr("General error occured, unable to continue playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNABLE_TO_PERFORM) {
                errorString.append(VideoPlayer::tr("General error occured"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_TYPE) {
                errorString.append(VideoPlayer::tr("Unsupported media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_RESOLUTION) {
                errorString.append(VideoPlayer::tr("Unsupported resolution"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_FPS) {
                errorString.append(VideoPlayer::tr("Unsupported framerate"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DRM) {
                errorString.append(VideoPlayer::tr("Media is protected by DRM"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DEVICE_UNAVAILABLE) {
                errorString.append(VideoPlayer::tr("System sound device is unavailable"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CORRUPTED_FILE) {
                errorString.append(VideoPlayer::tr("Media corrupted"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYLIST_PARSING) {
                errorString.append(VideoPlayer::tr("Error while parsing playlist"));
                errorString.append(VideoPlayer::tr("Playlist may be corrupt or empty"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CODEC_NOT_FOUND) {
                errorString.append(VideoPlayer::tr("Codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_VIDEO_CODEC_NOT_FOUND) {
                errorString.append(VideoPlayer::tr("Video codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_AUDIO_CODEC_NOT_FOUND) {
                errorString.append(VideoPlayer::tr("Video codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_PLAYLIST) {
                errorString.append(VideoPlayer::tr("No playlist assigned"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INDEX_OUT_OF_BOUNDS) {
                errorString.append(VideoPlayer::tr("Media index is not in bound with playlist items"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PLAY) {
                errorString.append(VideoPlayer::tr("Unable to start playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_STOP) {
                errorString.append(VideoPlayer::tr("Unable to stop playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PAUSE) {
                errorString.append(VideoPlayer::tr("Unable to pause playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_SET_POSITION) {
                errorString.append(VideoPlayer::tr("Unable to seek position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_POSITION) {
                errorString.append(VideoPlayer::tr("Unable to retrieve current position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_STATUS) {
                errorString.append(VideoPlayer::tr("Unable to get current playback status"));
            }
                
            Q_Q(VideoPlayer);
            emit q->statusChanged();
            emit q->error(errorString);
        }
    }
    
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
    
    MediaStatus::Status status;
    
    bool muted;
    
    int volume;
    int muteVolume;
    
    int tickInterval;
    
    int positionTimerId;
    
    bool sourceLoaded;
    
    bool readyToPlay;
    bool playWhenReady;
    
    Q_DECLARE_PUBLIC(VideoPlayer)
};

VideoPlayer::VideoPlayer(QWidget *parent) :
    Item(*new VideoPlayerPrivate(this), parent)
{
    Q_D(VideoPlayer);
    
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    
    d->mafwRegistry = MafwRegistryAdapter::get();
    d->mafwRenderer = d->mafwRegistry->renderer();
    d->mafwPlaylist = d->mafwRegistry->playlist();
    d->mafwTrackerSource = d->mafwRegistry->source(MafwRegistryAdapter::Tracker);
    d->metadataWatcher = MetadataWatcher::acquire();
    d->missionControl = MissionControl::acquire();
    
    d->mafwRenderer->setErrorPolicy(MAFW_RENDERER_ERROR_POLICY_STOP);
    
    this->connect(d->metadataWatcher, SIGNAL(metadataChanged()), this, SLOT(_q_onMetaDataChanged()));
    this->connect(d->mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                  this, SLOT(_q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));
    this->connect(d->mafwRenderer, SIGNAL(signalGetPosition(int,QString)), this, SLOT(_q_onPositionChanged(int)));
    this->connect(d->mafwRenderer, SIGNAL(signalGetVolume(int)), this, SLOT(_q_onVolumeChanged(int)));
    this->connect(d->mafwRenderer, SIGNAL(bufferingInfo(float)), this, SLOT(_q_onBufferProgressChanged(float)));
            
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

VideoPlayer::~VideoPlayer() {
    Q_D(VideoPlayer);
    
    d->mafwRenderer->setErrorPolicy(MAFW_RENDERER_ERROR_POLICY_CONTINUE);
    d->mafwRenderer->enablePlayback(false);
    d->mafwRenderer->stop();
}

bool VideoPlayer::autoLoad() const {
    Q_D(const VideoPlayer);
    
    return d->autoLoad;
}

void VideoPlayer::setAutoLoad(bool enable) {
    if (enable != this->autoLoad()) {
        Q_D(VideoPlayer);
        d->autoLoad = enable;
        emit autoLoadChanged();
    }
}

qreal VideoPlayer::bufferProgress() const {
    Q_D(const VideoPlayer);
    
    return d->bufferProgress;
}

QString VideoPlayer::errorString() const {
    Q_D(const VideoPlayer);
    
    return d->errorString;
}

bool VideoPlayer::hasAudio() const {
    return !this->metaData()->audioCodec().isEmpty();
}

bool VideoPlayer::hasVideo() const {
    return !this->metaData()->videoCodec().isEmpty();
}

MetadataWatcher* VideoPlayer::metaData() const {
    Q_D(const VideoPlayer);
    
    return d->metadataWatcher;
}

bool VideoPlayer::isMuted() const {
    Q_D(const VideoPlayer);
    
    return d->muted;
}

void VideoPlayer::setMuted(bool muted) {
    if (muted != this->isMuted()) {
        Q_D(VideoPlayer);
        d->muted = muted;
        emit mutedChanged();
        
        if (muted) {
            d->muteVolume = this->volume();
            this->setVolume(0);
        }
        else {
            this->setVolume(d->muteVolume);
        }
    }
}

bool VideoPlayer::isPaused() const {
    return this->status() == MediaStatus::Paused;
}

void VideoPlayer::setPaused(bool paused) {
    if (paused) {
        this->pause();
    }
    else if (this->isPaused()) {
        this->play();
    }
}

bool VideoPlayer::isPlaying() const {
    switch (this->status()) {
    case MediaStatus::Loading:
    case MediaStatus::Playing:
        return true;
    default:
        return false;
    }
}

void VideoPlayer::setPlaying(bool playing) {
    if (playing) {
        this->play();
    }
    else if (this->isPlaying()) {
        this->pause();
    }
}

bool VideoPlayer::isSeekable() const {
    Q_D(const VideoPlayer);
    
    return d->seekable;
}

int VideoPlayer::position() const {
    Q_D(const VideoPlayer);
    
    return d->position;
}

void VideoPlayer::setPosition(int pos) {
    if (pos != this->position()) {
        Q_D(VideoPlayer);
        d->mafwRenderer->setPosition(SeekAbsolute, pos);
        d->mafwRenderer->getPosition();
    }
}

int VideoPlayer::duration() const {
    Q_D(const VideoPlayer);
    
    return d->duration;
}

QString VideoPlayer::source() const {
    Q_D(const VideoPlayer);
    
    return d->source;
}

void VideoPlayer::setSource(const QString &uri) {
    if (uri != this->source()) {
        Q_D(VideoPlayer);
        d->source = uri;
        
        if (this->autoLoad()) {
            d->loadSource();
        }
        else {
            d->sourceLoaded = false;
        }
    }
}

MediaStatus::Status VideoPlayer::status() const {
    Q_D(const VideoPlayer);
    
    return d->status;
}

int VideoPlayer::volume() const {
    Q_D(const VideoPlayer);
    
    return d->volume;
}

void VideoPlayer::setVolume(int vol) {
    if (vol != this->volume()) {
        Q_D(VideoPlayer);
        d->volume = qBound(0, vol, 100);
        d->mafwRenderer->setVolume(d->volume);
        d->mafwRenderer->getVolume();
    }
}

int VideoPlayer::tickInterval() const {
    Q_D(const VideoPlayer);
    
    return d->tickInterval;
}

void VideoPlayer::setTickInterval(int interval) {
    if (interval != this->tickInterval()) {
        Q_D(VideoPlayer);
        d->tickInterval = qMax(0, interval);
        emit tickIntervalChanged();
        
        d->stopPositionTimer();
        
        if ((interval > 0) && (this->isPlaying())) {
            d->startPositionTimer();
        }
    }
}

void VideoPlayer::play() {
    if (this->isPlaying()) {
        return;
    }
    
    Q_D(VideoPlayer);
    
    if (this->isPaused()) {
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

void VideoPlayer::pause() {
    if (!this->isPlaying()) {
        Q_D(VideoPlayer);
        d->mafwRenderer->pause();
    }
}

void VideoPlayer::stop() {
    if ((this->isPlaying()) || (this->isPaused())) {
        Q_D(VideoPlayer);
        d->mafwRenderer->stop();
    }
}

void VideoPlayer::timerEvent(QTimerEvent *) {
    Q_D(VideoPlayer);
    
    d->mafwRenderer->getPosition();
}

void VideoPlayer::componentComplete() {
    Q_D(VideoPlayer);
    
    Item::componentComplete();
    QApplication::syncX();
    d->mafwRenderer->setColorKey(QColor(3, 13, 3).rgb() & 0xffffff);
    d->mafwRenderer->setWindowXid(this->winId());
    
    if (d->mafwRenderer->isRendererReady()) {
        d->mafwRenderer->getStatus();
        d->mafwRenderer->getVolume();
    }
    else {
        this->connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getStatus()));
        this->connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getVolume()));
    }
}

#include "moc_videoplayer_p.cpp"

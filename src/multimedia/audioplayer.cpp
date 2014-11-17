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
 
#include "audioplayer_p.h"
#include "metadatawatcher_p.h"
#include "missioncontrol_p.h"
#include "mafw/mafwregistryadapter.h"
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDeclarativeInfo>

class AudioPlayerPrivate
{

public:
    AudioPlayerPrivate(AudioPlayer *parent) :
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
        status(MediaStatus::Stopped),
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
            Q_Q(AudioPlayer);
            positionTimerId = q->startTimer(tickInterval);
        }
        
        mafwRenderer->getPosition();
    }
    
    void stopPositionTimer() {
        if (positionTimerId != -1) {
            Q_Q(AudioPlayer);
            q->killTimer(positionTimerId);
            positionTimerId = -1;
        }
    }
    
    void _q_onStatusReady(MafwPlaylist*, uint index, MafwPlayState state, const char*, const QString &error) {
        Q_Q(AudioPlayer);
        
        q->disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                      q, SLOT(_q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

        q->connect(mafwRenderer, SIGNAL(stateChanged(int)), q, SLOT(_q_onStateChanged(int)));
        
        this->_q_onStateChanged(state);
        
        if (!error.isEmpty()) {
            qmlInfo(q) << error;
        }
    }
    
    void _q_onMetaDataChanged() {
        Q_Q(AudioPlayer);
        
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
        Q_Q(AudioPlayer);
        
        bufferProgress = progress;
        emit q->bufferProgressChanged();
    }
    
    void _q_onPositionChanged(int pos) {
        Q_Q(AudioPlayer);
        
        position = pos;
        emit q->positionChanged();
    }
    
    void _q_onVolumeChanged(int vol) {
        Q_Q(AudioPlayer);
        
        volume = vol;
        emit q->volumeChanged();
    }
    
    void _q_onStateChanged(int state) {
        Q_Q(AudioPlayer);
        
        MediaStatus::Status oldStatus = status;
        
        switch (state) {
        case Transitioning:
            readyToPlay = false;
            status = MediaStatus::Loading;
            break;
        case Playing:
            readyToPlay = false;
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
            readyToPlay = false;
            break;
        }
        
        emit q->statusChanged();
    }
    
    void _q_onPropertyChanged(const QDBusMessage &msg) {
        if (msg.arguments()[0].toString() == MAFW_PROPERTY_RENDERER_VOLUME) {
            Q_Q(AudioPlayer);
            volume = qdbus_cast<QVariant>(msg.arguments()[1]).toInt();
            emit q->volumeChanged();
        }
    }
    
    void _q_onError(const QDBusMessage &msg) {
        if (msg.arguments()[0] == "com.nokia.mafw.error.renderer") {
            status = MediaStatus::Error;
            errorString.clear();
            errorString.append(AudioPlayer::tr("Unable to play media"));
            errorString.append("\n");

            if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_MEDIA) {
                errorString.append(AudioPlayer::tr("Media not found"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_URI_NOT_AVAILABLE) {
                errorString.append(AudioPlayer::tr("URI not available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INVALID_URI) {
                errorString.append(AudioPlayer::tr("Invalid URI"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_MEDIA_NOT_FOUND) {
                errorString.append(AudioPlayer::tr("Unable to open media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_STREAM_DISCONNECTED) {
                errorString.append(AudioPlayer::tr("Playback stream no longer available"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_TYPE_NOT_AVAILABLE) {
                errorString.append(AudioPlayer::tr("Could not determine MIME-type"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYBACK) {
                errorString.append(AudioPlayer::tr("General error occured, unable to continue playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNABLE_TO_PERFORM) {
                errorString.append(AudioPlayer::tr("General error occured"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_TYPE) {
                errorString.append(AudioPlayer::tr("Unsupported media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_RESOLUTION) {
                errorString.append(AudioPlayer::tr("Unsupported resolution"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_UNSUPPORTED_FPS) {
                errorString.append(AudioPlayer::tr("Unsupported framerate"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DRM) {
                errorString.append(AudioPlayer::tr("Media is protected by DRM"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_DEVICE_UNAVAILABLE) {
                errorString.append(AudioPlayer::tr("System sound device is unavailable"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CORRUPTED_FILE) {
                errorString.append(AudioPlayer::tr("Media corrupted"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_PLAYLIST_PARSING) {
                errorString.append(AudioPlayer::tr("Error while parsing playlist"));
                errorString.append(AudioPlayer::tr("Playlist may be corrupt or empty"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CODEC_NOT_FOUND) {
                errorString.append(AudioPlayer::tr("Codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_VIDEO_CODEC_NOT_FOUND) {
                errorString.append(AudioPlayer::tr("Video codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_AUDIO_CODEC_NOT_FOUND) {
                errorString.append(AudioPlayer::tr("Audio codec not found:") + "\n");
                errorString.append(msg.arguments()[2].toString());
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_NO_PLAYLIST) {
                errorString.append(AudioPlayer::tr("No playlist assigned"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_INDEX_OUT_OF_BOUNDS) {
                errorString.append(AudioPlayer::tr("Media index is not in bound with playlist items"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PLAY) {
                errorString.append(AudioPlayer::tr("Unable to start playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_STOP) {
                errorString.append(AudioPlayer::tr("Unable to stop playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_PAUSE) {
                errorString.append(AudioPlayer::tr("Unable to pause playback"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_SET_POSITION) {
                errorString.append(AudioPlayer::tr("Unable to seek position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_POSITION) {
                errorString.append(AudioPlayer::tr("Unable to retrieve current position in media"));
            }
            else if (msg.arguments()[1] == MAFW_RENDERER_ERROR_CANNOT_GET_STATUS) {
                errorString.append(AudioPlayer::tr("Unable to get current playback status"));
            }
                
            Q_Q(AudioPlayer);
            emit q->statusChanged();
            emit q->error(errorString);
        }
    }
    
    AudioPlayer *q_ptr;
    
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
    
    bool complete;
    
    Q_DECLARE_PUBLIC(AudioPlayer)
};

AudioPlayer::AudioPlayer(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioPlayerPrivate(this))
{
    Q_D(AudioPlayer);
    
    d->mafwRegistry = MafwRegistryAdapter::get();
    d->mafwRenderer = d->mafwRegistry->renderer();
    d->mafwPlaylist = d->mafwRegistry->playlist();
    d->mafwTrackerSource = d->mafwRegistry->source(MafwRegistryAdapter::Tracker);
    d->metadataWatcher = MetadataWatcher::acquire();
    d->missionControl = MissionControl::acquire();
    
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

AudioPlayer::~AudioPlayer() {
    Q_D(AudioPlayer);
    
    d->mafwRenderer->enablePlayback(false);
    d->mafwRenderer->stop();
}

bool AudioPlayer::autoLoad() const {
    Q_D(const AudioPlayer);
    
    return d->autoLoad;
}

void AudioPlayer::setAutoLoad(bool enable) {
    if (enable != this->autoLoad()) {
        Q_D(AudioPlayer);
        d->autoLoad = enable;
        emit autoLoadChanged();
    }
}

qreal AudioPlayer::bufferProgress() const {
    Q_D(const AudioPlayer);
    
    return d->bufferProgress;
}

QString AudioPlayer::errorString() const {
    Q_D(const AudioPlayer);
    
    return d->errorString;
}

MetadataWatcher* AudioPlayer::metaData() const {
    Q_D(const AudioPlayer);
    
    return d->metadataWatcher;
}

bool AudioPlayer::isMuted() const {
    Q_D(const AudioPlayer);
    
    return d->muted;
}

void AudioPlayer::setMuted(bool muted) {
    if (muted != this->isMuted()) {
        Q_D(AudioPlayer);
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

bool AudioPlayer::isPaused() const {
    return this->status() == MediaStatus::Paused;
}

void AudioPlayer::setPaused(bool paused) {
    if (paused) {
        this->pause();
    }
    else if (this->isPaused()) {
        this->play();
    }
}

bool AudioPlayer::isPlaying() const {
    switch (this->status()) {
    case MediaStatus::Loading:
    case MediaStatus::Playing:
        return true;
    default:
        return false;
    }
}

void AudioPlayer::setPlaying(bool playing) {
    if (playing) {
        this->play();
    }
    else if (this->isPlaying()) {
        this->pause();
    }
}

bool AudioPlayer::isSeekable() const {
    Q_D(const AudioPlayer);
    
    return d->seekable;
}

int AudioPlayer::position() const {
    Q_D(const AudioPlayer);
    
    return d->position;
}

void AudioPlayer::setPosition(int pos) {
    if (pos != this->position()) {
        Q_D(AudioPlayer);
        d->mafwRenderer->setPosition(SeekAbsolute, pos);
        d->mafwRenderer->getPosition();
    }
}

int AudioPlayer::duration() const {
    Q_D(const AudioPlayer);
    
    return d->duration;
}

QString AudioPlayer::source() const {
    Q_D(const AudioPlayer);
    
    return d->source;
}

void AudioPlayer::setSource(const QString &uri) {
    if (uri != this->source()) {
        Q_D(AudioPlayer);
        d->source = uri;
        
        if (this->autoLoad()) {
            d->loadSource();
        }
        else {
            d->sourceLoaded = false;
        }
    }
}

MediaStatus::Status AudioPlayer::status() const {
    Q_D(const AudioPlayer);
    
    return d->status;
}

int AudioPlayer::volume() const {
    Q_D(const AudioPlayer);
    
    return d->volume;
}

void AudioPlayer::setVolume(int vol) {
    if (vol != this->volume()) {
        Q_D(AudioPlayer);
        d->volume = qBound(0, vol, 100);
        d->mafwRenderer->setVolume(d->volume);
        d->mafwRenderer->getVolume();
    }
}

int AudioPlayer::tickInterval() const {
    Q_D(const AudioPlayer);
    
    return d->tickInterval;
}

void AudioPlayer::setTickInterval(int interval) {
    if (interval != this->tickInterval()) {
        Q_D(AudioPlayer);
        d->tickInterval = qMax(0, interval);
        emit tickIntervalChanged();
        
        d->stopPositionTimer();
        
        if ((interval > 0) && (this->isPlaying())) {
            d->startPositionTimer();
        }
    }
}

void AudioPlayer::play() {
    Q_D(AudioPlayer);
    
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

void AudioPlayer::pause() {
    if (this->isPlaying()) {
        Q_D(AudioPlayer);
        d->mafwRenderer->pause();
    }
}

void AudioPlayer::stop() {
    if ((this->isPlaying()) || (this->isPaused())) {
        Q_D(AudioPlayer);
        d->mafwRenderer->stop();
    }
}

void AudioPlayer::classBegin() {}

void AudioPlayer::componentComplete() {
    Q_D(AudioPlayer);
    
    d->complete = true;
    
    if (d->mafwRenderer->isRendererReady()) {
        d->mafwRenderer->getStatus();
        d->mafwRenderer->getVolume();
    }
    else {
        this->connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getStatus()));
        this->connect(d->mafwRenderer, SIGNAL(rendererReady()), d->mafwRenderer, SLOT(getVolume()));
    }
}

void AudioPlayer::timerEvent(QTimerEvent *) {
    Q_D(AudioPlayer);
    
    d->mafwRenderer->getPosition();
}

#include "moc_audioplayer_p.cpp"

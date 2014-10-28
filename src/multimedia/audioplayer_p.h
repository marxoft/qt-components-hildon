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

#ifndef AUDIOPLAYER_P_H
#define AUDIOPLAYER_P_H

#include "mediastatus_p.h"
#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDBusMessage;
class MetadataWatcher;
class AudioPlayerPrivate;

class AudioPlayer : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(bool autoLoad READ autoLoad WRITE setAutoLoad NOTIFY autoLoadChanged)
    Q_PROPERTY(qreal bufferProgress READ bufferProgress NOTIFY bufferProgressChanged)
    Q_PROPERTY(int duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY error)
    Q_PROPERTY(MetadataWatcher* metaData READ metaData CONSTANT)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool paused READ isPaused WRITE setPaused NOTIFY statusChanged)
    Q_PROPERTY(bool playing READ isPlaying WRITE setPlaying NOTIFY statusChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool seekable READ isSeekable NOTIFY seekableChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(MediaStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int tickInterval READ tickInterval WRITE setTickInterval NOTIFY tickIntervalChanged)
    
    Q_ENUMS(MediaStatus::Status)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    explicit AudioPlayer(QObject *parent = 0);
    ~AudioPlayer();
    
    bool autoLoad() const;
    void setAutoLoad(bool enable);
    
    qreal bufferProgress() const;
    
    QString errorString() const;
    
    MetadataWatcher* metaData() const;
    
    bool isMuted() const;
    void setMuted(bool muted);
    
    bool isPaused() const;
    void setPaused(bool paused);
    
    bool isPlaying() const;
    void setPlaying(bool playing);
    
    bool isSeekable() const;
    
    int position() const;
    void setPosition(int pos);
    
    int duration() const;
    
    QString source() const;
    void setSource(const QString &uri);
    
    MediaStatus::Status status() const;
    
    int volume() const;
    void setVolume(int vol);
    
    int tickInterval() const;
    void setTickInterval(int interval);
    
public slots:
    void play();
    void pause();
    void stop();
    
signals:
    void autoLoadChanged();
    void bufferProgressChanged();
    void durationChanged();
    void error(const QString &errorString);
    void mutedChanged();
    void paused();
    void positionChanged();
    void resumed();
    void seekableChanged();
    void sourceChanged();
    void started();
    void statusChanged();
    void stopped();
    void tickIntervalChanged();
    void volumeChanged();
    
private:
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual void timerEvent(QTimerEvent *);
    
    QScopedPointer<AudioPlayerPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(AudioPlayer)
    Q_DISABLE_COPY(AudioPlayer)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusReady(MafwPlaylist*,uint,MafwPlayState,const char*,QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onMetaDataChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onBufferProgressChanged(float))
    Q_PRIVATE_SLOT(d_func(), void _q_onPositionChanged(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onVolumeChanged(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStateChanged(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onPropertyChanged(QDBusMessage))
    Q_PRIVATE_SLOT(d_func(), void _q_onError(QDBusMessage))
};

QML_DECLARE_TYPE(AudioPlayer)

#endif // AUDIOPLAYER_P_H

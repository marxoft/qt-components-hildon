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
 
#ifndef PLAYBACKMODEL_P_H
#define PLAYBACKMODEL_P_H

#include "mediatype_p.h"
#include "modelindex_p.h"
#include <QStandardItemModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class PlaybackModelPrivate;

class PlaybackModel : public QStandardItemModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(MediaType::Type mediaType READ mediaType WRITE setMediaType NOTIFY mediaTypeChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool repeat READ isRepeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(bool shuffle READ isShuffled WRITE setShuffled NOTIFY shuffledChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    enum Roles {
        AlbumArtistRole = Qt::UserRole + 1,
        AlbumTitleRole,
        ArtistRole,
        AudioBitRateRole,
        AudioCodecRole,
        CommentRole,
        ComposerRole,
        CopyrightRole,
        CoverArtUrlRole,
        DateRole,
        DescriptionRole,
        DurationRole,
        GenreRole,
        IdRole,
        KeywordsRole,
        LastPlayedRole,
        LastThumbnailUrlRole,
        LyricsRole,
        MimeTypeRole,
        PlayCountRole,
        ResolutionRole,
        ResumePositionRole,
        SizeRole,
        ThumbnailUrlRole,
        TitleRole,
        TrackNumberRole,
        UrlRole,
        VideoBitRateRole,
        VideoCodecRole,
        VideoFrameRateRole,
        YearRole
    };
    
    explicit PlaybackModel(QObject *parent = 0);
    ~PlaybackModel();
    
    MediaType::Type mediaType() const;
    void setMediaType(MediaType::Type type);
    
    int position() const;
    void setPosition(int pos);
    
    bool isRepeat() const;
    void setRepeat(bool repeat);
    
    bool isShuffled() const;
    void setShuffled(bool shuffle);
    
    Q_INVOKABLE void appendSource(const QString &uri);
    Q_INVOKABLE void appendItem(const QString &id);
    Q_INVOKABLE void insertSource(const QModelIndex &index, const QString &uri);
    Q_INVOKABLE void insertItem(const QModelIndex &index, const QString &id);
    Q_INVOKABLE void moveItem(const QModelIndex &from, const QModelIndex &to);
    Q_INVOKABLE void removeItem(const QModelIndex &index);
    
    Q_INVOKABLE QVariant modelIndex(int row, int column = 0, const QModelIndex &parent = QModelIndex());
    
    Q_INVOKABLE QVariant property(const QModelIndex &index, const QString &name);
    
public slots:
    void clearItems();
    void loadItems();
    
    void next();
    void previous();
    
signals:
    void countChanged();
    void mediaTypeChanged();
    void positionChanged();
    void ready();
    void repeatChanged();
    void shuffledChanged();
    
private:
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<PlaybackModelPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(PlaybackModel)
    Q_DISABLE_COPY(PlaybackModel)
    
    Q_PRIVATE_SLOT(d_func(), void _q_assignPlaylist())
    Q_PRIVATE_SLOT(d_func(), void _q_onPlaylistChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onPropertyChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onPositionChanged(int))
    Q_PRIVATE_SLOT(d_func(), void _q_onStatusChanged(MafwPlaylist*,uint,MafwPlayState,const char*,QString))
    Q_PRIVATE_SLOT(d_func(), void _q_onGConfValueChanged());
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsReady(QString,GHashTable*,guint))
    Q_PRIVATE_SLOT(d_func(), void _q_onItemsChanged(guint,guint,guint))
    Q_PRIVATE_SLOT(d_func(), void _q_onItemMoved(guint,guint))
};

QML_DECLARE_TYPE(PlaybackModel)

#endif // PLAYBACKMODEL_P_H

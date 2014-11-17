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
 
#include "playbackmodel_p.h"
#include "playlistquerymanager_p.h"
#include "mafw/mafwregistryadapter.h"
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <QDBusConnection>
#include <GConfItem>

class PlaybackModelPrivate
{

public:
    PlaybackModelPrivate(PlaybackModel *parent) :
        q_ptr(parent),
        mafwRegistry(0),
        mafwRenderer(0),
        mafwPlaylist(0),
        mafwTrackerSource(0),
        gconfItem(0),
        mediaType(MediaType::Audio),
        position(0),
        repeat(false),
        shuffle(false),
        playlistAssigned(false),
        complete(false)
    {
    }
   
    QString uriToId(QString uri) const {
        if (uri.startsWith("/")) {
            uri.prepend("file://");
        }
        
        QString objectId = mafwTrackerSource->createObjectId(uri);
        
        if (uri.startsWith("file://")) {
            QString mime(gnome_vfs_get_mime_type_for_name(uri.toUtf8()));
            objectId = objectId.remove(0, 18) // "urisource::file://"
                               .replace("/", "%2F")
                               .prepend(QString("localtagfs::%1/")
                               .arg(mime.startsWith("video") ? "videos" : "music/songs"));
        }
        
        return objectId;
    }
    
    void connectSignals() {
        Q_Q(PlaybackModel);
        
        QDBusConnection::sessionBus().connect("", "", "com.nokia.mafw.playlist", "property_changed",
                                              q, SLOT(_q_onPropertyChanged()));
                                              
        q->connect(mafwPlaylist, SIGNAL(contentsChanged(guint, guint, guint)), 
                   q, SLOT(_q_onItemsChanged(guint, guint, guint)), Qt::UniqueConnection);
                   
        q->connect(mafwPlaylist, SIGNAL(itemMoved(guint, guint)), 
                   q, SLOT(_q_onItemMoved(guint, guint)), Qt::UniqueConnection);
                   
        q->connect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                   q, SLOT(_q_onStatusChanged(MafwPlaylist*,uint,MafwPlayState,const char*,QString)), Qt::UniqueConnection);
                   
        q->connect(mafwRenderer, SIGNAL(mediaChanged(int,char*)), q, SLOT(_q_onPositionChanged(int)), Qt::UniqueConnection);
        
        q->connect(gconfItem, SIGNAL(valueChanged()), q, SLOT(_q_onGConfValueChanged()), Qt::UniqueConnection);
    }
    
    void disconnectSignals() {
        Q_Q(PlaybackModel);
        
        QDBusConnection::sessionBus().disconnect("", "", "com.nokia.mafw.playlist", "property_changed",
                                              q, SLOT(_q_onPropertyChanged()));
                                              
        q->disconnect(mafwPlaylist, SIGNAL(contentsChanged(guint, guint, guint)), 
                      q, SLOT(_q_onItemsChanged(guint, guint, guint)));
                      
        q->disconnect(mafwPlaylist, SIGNAL(itemMoved(guint, guint)), 
                      q, SLOT(_q_onItemMoved(guint, guint)));
                      
        q->disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
                      q, SLOT(_q_onStatusChanged(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));
                      
        q->disconnect(mafwRenderer, SIGNAL(mediaChanged(int,char*)), q, SLOT(_q_onPositionChanged(int)));
        
        q->disconnect(gconfItem, SIGNAL(valueChanged()), q, SLOT(_q_onGConfValueChanged()));
    }
    
    void _q_assignPlaylist() {
        if ((playlistAssigned) || (!mafwRenderer->isRendererReady())) {
            return;
        }
        
        switch (mediaType) {
        case MediaType::Radio:
            mafwPlaylist->assignRadioPlaylist();
            break;
        case MediaType::Video:
            mafwPlaylist->assignVideoPlaylist();
            break;
        default:
            mafwPlaylist->assignAudioPlaylist();
            break;
        }
        
        Q_Q(PlaybackModel);
        
        playlistAssigned = true;
        this->connectSignals();
        emit q->ready();
    }
    
    void _q_onPlaylistChanged() {
        switch (mediaType) {
        case MediaType::Radio:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpRadioPlaylist");
            break;
        case MediaType::Video:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpVideoPlaylist");
            break;
        default:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpAudioPlaylist");
            break;
        }
        
        if (!playlistAssigned) {
            this->disconnectSignals();
        }
    }
       
    void _q_onPropertyChanged() {
        Q_Q(PlaybackModel);
        
        repeat = mafwPlaylist->isRepeat();
        shuffle = mafwPlaylist->isShuffled();
        emit q->repeatChanged();
        emit q->shuffledChanged();
    }
    
    void _q_onPositionChanged(int index) {
        Q_Q(PlaybackModel);
        
        position = index;
        emit q->positionChanged();
    }
    
    void _q_onStatusChanged(MafwPlaylist*, uint index, MafwPlayState, const char*, QString) {
        this->_q_onPositionChanged(index);
    }
    
    void _q_onGConfValueChanged() {
        this->_q_onPositionChanged(gconfItem->value().toInt());
    }
    
    void _q_onItemsReady(QString objectId, GHashTable* metadata, guint index) {
        if (!metadata) {
            return;
        }
        
        Q_Q(PlaybackModel);
        
        QStandardItem *item = q->item(index);
        
        if (!item) {
            return;
        }
        
        QString album;
        QString artist;
        int audioBitRate;
        QString audioCodec;
        QString comment;
        QString composer;
        QString copyright;
        QString coverArtUrl;
        qint64 date;
        QString description;
        int duration;
        QString genre;
        QString keywords;
        qint64 lastPlayed;
        QString lastThumbnailUrl;
        QString lyrics;
        QString mimeType;
        QString organization;
        int playCount;
        int resX;
        int resY;
        int resumePosition;
        int size;
        QString thumbnailUrl;
        QString title;
        int trackNumber;
        QString url;
        int videoBitRate;
        QString videoCodec;
        int videoFrameRate;
        int year;
        GValue *v;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_ALBUM);
        album = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_ARTIST);
        artist = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_AUDIO_BITRATE);
        audioBitRate = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_AUDIO_CODEC);
        audioCodec = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_COMMENT);
        comment = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_COMPOSER);
        composer = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_COPYRIGHT);
        copyright = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_ALBUM_ART_URI);
        coverArtUrl = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_MODIFIED);
        date = v ? g_value_get_int64 (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_DESCRIPTION);
        description = v ? QString::fromUtf8(g_value_get_string(v)) : "";

        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_DURATION);
        duration = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_GENRE);
        genre = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_TAGS);
        keywords = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_LAST_PLAYED);
        lastPlayed = v ? g_value_get_int64 (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_PAUSED_THUMBNAIL_URI);
        lastThumbnailUrl = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_LYRICS);
        lyrics = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_MIME);
        mimeType = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_ORGANIZATION);
        organization = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_PLAY_COUNT);
        playCount = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_RES_X);
        resX = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_RES_Y);
        resY = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_PAUSED_POSITION);
        resumePosition = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_FILESIZE);
        size = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_THUMBNAIL_URI);
        thumbnailUrl = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_TITLE);
        title = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_TRACK);
        trackNumber = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_URI);
        url = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_VIDEO_BITRATE);
        videoBitRate = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_VIDEO_CODEC);
        videoCodec = v ? QString::fromUtf8(g_value_get_string(v)) : "";
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_VIDEO_FRAMERATE);
        videoFrameRate = v ? g_value_get_int (v) : 0;
        
        v = mafw_metadata_first(metadata, MAFW_METADATA_KEY_YEAR);
        year = v ? g_value_get_int (v) : 0;
        
        item->setText(title);
        item->setData(artist, PlaybackModel::AlbumArtistRole);
        item->setData(album, PlaybackModel::AlbumTitleRole);
        item->setData(artist, PlaybackModel::ArtistRole);
        item->setData(audioBitRate, PlaybackModel::AudioBitRateRole);
        item->setData(audioCodec, PlaybackModel::AudioCodecRole);
        item->setData(comment, PlaybackModel::CommentRole);
        item->setData(composer, PlaybackModel::ComposerRole);
        item->setData(copyright, PlaybackModel::CopyrightRole);
        item->setData(coverArtUrl, PlaybackModel::CoverArtUrlRole);
        item->setData(date, PlaybackModel::DateRole);
        item->setData(description, PlaybackModel::DescriptionRole);
        item->setData(duration, PlaybackModel::DurationRole);
        item->setData(genre, PlaybackModel::GenreRole);
        item->setData(keywords, PlaybackModel::KeywordsRole);
        item->setData(lastPlayed, PlaybackModel::LastPlayedRole);
        item->setData(lastThumbnailUrl, PlaybackModel::LastThumbnailUrlRole);
        item->setData(lyrics, PlaybackModel::LyricsRole);
        item->setData(mimeType, PlaybackModel::MimeTypeRole);
        item->setData(organization, PlaybackModel::OrganizationRole);
        item->setData(playCount, PlaybackModel::PlayCountRole);
        item->setData(QSize(resX, resY), PlaybackModel::ResolutionRole);
        item->setData(resumePosition, PlaybackModel::ResumePositionRole);
        item->setData(size, PlaybackModel::SizeRole);
        item->setData(thumbnailUrl, PlaybackModel::ThumbnailUrlRole);
        item->setData(title, PlaybackModel::TitleRole);
        item->setData(trackNumber, PlaybackModel::TrackNumberRole);
        item->setData(url, PlaybackModel::UrlRole);
        item->setData(videoBitRate, PlaybackModel::VideoBitRateRole);
        item->setData(videoCodec, PlaybackModel::VideoCodecRole);
        item->setData(videoFrameRate, PlaybackModel::VideoFrameRateRole);
        item->setData(year, PlaybackModel::YearRole);
    };
    
    void _q_onItemsChanged(guint from, guint nremove, guint nreplace) {
        Q_Q(PlaybackModel);

        bool synthetic = from == (uint) -1;

        if (synthetic) {
            q->clear();
            from = 0;
            nreplace = mafwPlaylist->getSize();
        }

        if (nremove > 0) {
            q->removeRows(from, nremove);
            emit q->countChanged();
            queryManager->itemsRemoved(from, nremove);
        }
        else if (nreplace > 0) {
            gchar** items = mafw_playlist_get_items(mafwPlaylist->mafw_playlist, from, from + nreplace - 1, NULL);
            
            for (int i = 0; items[i] != NULL; i++) {
                QStandardItem *item = new QStandardItem;
                item->setData(0, PlaybackModel::DurationRole);
                item->setData(QString::fromUtf8(items[i]), PlaybackModel::IdRole);
                q->insertRow(from + i, item);
            }
            
            emit q->countChanged();
            
            g_strfreev(items);

            if (!synthetic) {
                queryManager->itemsInserted(from, nreplace);
            }
            
            queryManager->getItems(from, from + nreplace - 1);
        }

        if (synthetic) {
            this->_q_onPositionChanged(gconfItem->value().toInt());
        }
        
        mafwRenderer->getStatus();
    }
    
    void _q_onItemMoved(guint from, guint to) {
        Q_Q(PlaybackModel);
        
        queryManager->itemsRemoved(from, 1);
        queryManager->itemsInserted(to, 1);

        if (QStandardItem *item = q->item(to)) {
            if (item->data(PlaybackModel::DurationRole) == 0) {
                queryManager->getItems(to, to);
            }
        }

        mafwRenderer->getStatus();
    }
    
    PlaybackModel *q_ptr;
    
    mutable MafwRegistryAdapter *mafwRegistry;
    mutable MafwRendererAdapter *mafwRenderer;
    mutable MafwPlaylistAdapter *mafwPlaylist;
    mutable MafwSourceAdapter *mafwTrackerSource;
    mutable PlaylistQueryManager *queryManager;
    
    GConfItem *gconfItem;
    
    MediaType::Type mediaType;
    
    int position;
    
    bool repeat;
    bool shuffle;
    
    bool playlistAssigned;
    
    bool complete;
    
    Q_DECLARE_PUBLIC(PlaybackModel)
};

PlaybackModel::PlaybackModel(QObject *parent) :
    QStandardItemModel(parent),
    d_ptr(new PlaybackModelPrivate(this))
{
    Q_D(PlaybackModel);
    
    d->mafwRegistry = MafwRegistryAdapter::get();
    d->mafwRenderer = d->mafwRegistry->renderer();
    d->mafwPlaylist = d->mafwRegistry->playlist();
    d->mafwTrackerSource = d->mafwRegistry->source(MafwRegistryAdapter::Tracker);
    d->queryManager = new PlaylistQueryManager(this, d->mafwPlaylist);
    d->gconfItem = new GConfItem("/apps/mediaplayer/last_playing_song", this);
    
    QHash<int, QByteArray> roles;
    roles[AlbumArtistRole] = "albumArtist";
    roles[AlbumTitleRole] = "albumTitle";
    roles[ArtistRole] = "artist";
    roles[AudioBitRateRole] = "audioBitRate";
    roles[AudioCodecRole] = "audioCodec";
    roles[CommentRole] = "comment";
    roles[ComposerRole] = "composer";
    roles[CopyrightRole] = "copyright";
    roles[CoverArtUrlRole] = "coverArtUrl";
    roles[DateRole] = "date";
    roles[DescriptionRole] = "description";
    roles[DurationRole] = "duration";
    roles[GenreRole] = "genre";
    roles[IdRole] = "id";
    roles[KeywordsRole] = "keywords";
    roles[LastPlayedRole] = "lastPlayed";
    roles[LastThumbnailUrlRole] = "lastThumbnailUrl";
    roles[LyricsRole] = "lyrics";
    roles[MimeTypeRole] = "mimeType";
    roles[OrganizationRole] = "organization";
    roles[PlayCountRole] = "playCount";
    roles[ResolutionRole] = "resolution";
    roles[ResumePositionRole] = "resumePosition";
    roles[SizeRole] = "size";
    roles[ThumbnailUrlRole] = "thumbnailUrl";
    roles[TitleRole] = "title";
    roles[TrackNumberRole] = "trackNumber";
    roles[UrlRole] = "url";
    roles[VideoBitRateRole] = "videoBitRate";
    roles[VideoCodecRole] = "videoCodec";
    roles[VideoFrameRateRole] = "videoFrameRate";
    roles[YearRole] = "year";
    this->setRoleNames(roles);
}

PlaybackModel::~PlaybackModel() {}

MediaType::Type PlaybackModel::mediaType() const {
    Q_D(const PlaybackModel);
    
    return d->mediaType;
}

void PlaybackModel::setMediaType(MediaType::Type type) {
    if (type != this->mediaType()) {
        Q_D(PlaybackModel);
        d->mediaType = type;
        emit mediaTypeChanged();
        
        if (d->complete) {
            this->clear();
            d->_q_assignPlaylist();
        }
    }
}

int PlaybackModel::position() const {
    Q_D(const PlaybackModel);
    
    return d->position;
}

void PlaybackModel::setPosition(int pos) {
    if (pos != this->position()) {
        Q_D(PlaybackModel);
        d->_q_assignPlaylist();
        d->mafwRenderer->gotoIndex(pos);
    }
}

bool PlaybackModel::isRepeat() const {
    Q_D(const PlaybackModel);
    
    return d->repeat;
}

void PlaybackModel::setRepeat(bool repeat) {
    if (repeat != this->isRepeat()) {
        Q_D(PlaybackModel);
        d->_q_assignPlaylist();
        d->mafwPlaylist->setRepeat(repeat);
    }
}

bool PlaybackModel::isShuffled() const {
    Q_D(const PlaybackModel);
    
    return d->shuffle;
}

void PlaybackModel::setShuffled(bool shuffled) {
    if (shuffled != this->isShuffled()) {
        Q_D(PlaybackModel);
        d->_q_assignPlaylist();
        d->mafwPlaylist->setShuffled(shuffled);
    }
}

void PlaybackModel::appendSource(const QString &uri) {
    Q_D(PlaybackModel);
    
    this->appendItem(d->uriToId(uri));
}

void PlaybackModel::appendItem(const QString &id) {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->appendItem(id);
}

void PlaybackModel::insertSource(const QModelIndex &index, const QString &uri) {
    Q_D(PlaybackModel);
    
    this->insertItem(index, d->uriToId(uri));
}

void PlaybackModel::insertItem(const QModelIndex &index, const QString &id) {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->insertItem(id, index.row());
}

void PlaybackModel::moveItem(const QModelIndex &from, const QModelIndex &to) {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->moveItem(from.row(), to.row());
}

void PlaybackModel::removeItem(const QModelIndex &index) {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->removeItem(index.row());
}

QVariant PlaybackModel::modelIndex(int row, int column, const QModelIndex &parent) {
    return QVariant::fromValue(this->index(row, column, parent));
}

QVariant PlaybackModel::property(const QModelIndex &index, const QString &name) {
    return this->data(index, this->roleNames().key(name.toUtf8()));
}

void PlaybackModel::clearItems() {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->clear();
    d->gconfItem->set(0);
}

void PlaybackModel::loadItems() {
    Q_D(PlaybackModel);
    
    this->clear();
    d->_q_assignPlaylist();
    d->_q_onItemsChanged(-1, 0, 0);
}

void PlaybackModel::next() {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwRenderer->next();
}

void PlaybackModel::previous() {
    Q_D(PlaybackModel);
    
    d->_q_assignPlaylist();
    d->mafwRenderer->previous();
}

void PlaybackModel::classBegin() {}

void PlaybackModel::componentComplete() {
    Q_D(PlaybackModel);
    
    d->complete = true;
    
    this->connect(d->queryManager, SIGNAL(onGetItems(QString, GHashTable*, guint)), 
                  this, SLOT(_q_onItemsReady(QString, GHashTable*, guint)));
                  
    this->connect(d->mafwPlaylist, SIGNAL(playlistChanged()), this, SLOT(_q_onPlaylistChanged()));
    
    if (d->mafwRenderer->isRendererReady()) {
        d->_q_assignPlaylist();
    }
    else {
        this->connect(d->mafwRenderer, SIGNAL(rendererReady()), this, SLOT(_q_assignPlaylist()));
    }
}

#include "moc_playbackmodel_p.cpp"

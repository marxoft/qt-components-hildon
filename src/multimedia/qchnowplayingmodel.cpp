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
 
#include "qchnowplayingmodel.h"
#include "playlistquerymanager.h"
#include "mafw/mafwregistryadapter.h"
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <QDBusConnection>
#include <GConfItem>

class QchNowPlayingModelPrivate
{

public:
    QchNowPlayingModelPrivate(QchNowPlayingModel *parent) :
        q_ptr(parent),
        mafwRegistry(0),
        mafwRenderer(0),
        mafwPlaylist(0),
        mafwTrackerSource(0),
        gconfItem(0),
        mediaType(QchMediaType::Audio),
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
        Q_Q(QchNowPlayingModel);
        
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
        Q_Q(QchNowPlayingModel);
        
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
        case QchMediaType::Radio:
            mafwPlaylist->assignRadioPlaylist();
            break;
        case QchMediaType::Video:
            mafwPlaylist->assignVideoPlaylist();
            break;
        default:
            mafwPlaylist->assignAudioPlaylist();
            break;
        }
        
        Q_Q(QchNowPlayingModel);
        
        playlistAssigned = true;
        connectSignals();
        emit q->ready();
    }
    
    void _q_onPlaylistChanged() {
        switch (mediaType) {
        case QchMediaType::Radio:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpRadioPlaylist");
            break;
        case QchMediaType::Video:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpVideoPlaylist");
            break;
        default:
            playlistAssigned = (mafwPlaylist->playlistName() == "FmpAudioPlaylist");
            break;
        }
        
        if (!playlistAssigned) {
            disconnectSignals();
        }
    }
       
    void _q_onPropertyChanged() {
        Q_Q(QchNowPlayingModel);
        
        repeat = mafwPlaylist->isRepeat();
        shuffle = mafwPlaylist->isShuffled();
        emit q->repeatChanged();
        emit q->shuffledChanged();
    }
    
    void _q_onPositionChanged(int index) {
        Q_Q(QchNowPlayingModel);
        
        position = index;
        emit q->positionChanged();
    }
    
    void _q_onStatusChanged(MafwPlaylist*, uint index, MafwPlayState, const char*, QString) {
        _q_onPositionChanged(index);
    }
    
    void _q_onGConfValueChanged() {
        _q_onPositionChanged(gconfItem->value().toInt());
    }
    
    void _q_onItemsReady(QString objectId, GHashTable* metadata, guint index) {
        if (!metadata) {
            return;
        }
        
        Q_Q(QchNowPlayingModel);
        
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
        item->setData(artist, QchNowPlayingModel::AlbumArtistRole);
        item->setData(album, QchNowPlayingModel::AlbumTitleRole);
        item->setData(artist, QchNowPlayingModel::ArtistRole);
        item->setData(audioBitRate, QchNowPlayingModel::AudioBitRateRole);
        item->setData(audioCodec, QchNowPlayingModel::AudioCodecRole);
        item->setData(comment, QchNowPlayingModel::CommentRole);
        item->setData(composer, QchNowPlayingModel::ComposerRole);
        item->setData(copyright, QchNowPlayingModel::CopyrightRole);
        item->setData(coverArtUrl, QchNowPlayingModel::CoverArtUrlRole);
        item->setData(date, QchNowPlayingModel::DateRole);
        item->setData(description, QchNowPlayingModel::DescriptionRole);
        item->setData(duration, QchNowPlayingModel::DurationRole);
        item->setData(genre, QchNowPlayingModel::GenreRole);
        item->setData(keywords, QchNowPlayingModel::KeywordsRole);
        item->setData(lastPlayed, QchNowPlayingModel::LastPlayedRole);
        item->setData(lastThumbnailUrl, QchNowPlayingModel::LastThumbnailUrlRole);
        item->setData(lyrics, QchNowPlayingModel::LyricsRole);
        item->setData(mimeType, QchNowPlayingModel::MimeTypeRole);
        item->setData(organization, QchNowPlayingModel::OrganizationRole);
        item->setData(playCount, QchNowPlayingModel::PlayCountRole);
        item->setData(QSize(resX, resY), QchNowPlayingModel::ResolutionRole);
        item->setData(resumePosition, QchNowPlayingModel::ResumePositionRole);
        item->setData(size, QchNowPlayingModel::SizeRole);
        item->setData(thumbnailUrl, QchNowPlayingModel::ThumbnailUrlRole);
        item->setData(title, QchNowPlayingModel::TitleRole);
        item->setData(trackNumber, QchNowPlayingModel::TrackNumberRole);
        item->setData(url, QchNowPlayingModel::UrlRole);
        item->setData(videoBitRate, QchNowPlayingModel::VideoBitRateRole);
        item->setData(videoCodec, QchNowPlayingModel::VideoCodecRole);
        item->setData(videoFrameRate, QchNowPlayingModel::VideoFrameRateRole);
        item->setData(year, QchNowPlayingModel::YearRole);
    };
    
    void _q_onItemsChanged(guint from, guint nremove, guint nreplace) {
        Q_Q(QchNowPlayingModel);

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
                item->setData(0, QchNowPlayingModel::DurationRole);
                item->setData(QString::fromUtf8(items[i]), QchNowPlayingModel::IdRole);
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
            _q_onPositionChanged(gconfItem->value().toInt());
        }
        
        mafwRenderer->getStatus();
    }
    
    void _q_onItemMoved(guint from, guint to) {
        Q_Q(QchNowPlayingModel);
        
        queryManager->itemsRemoved(from, 1);
        queryManager->itemsInserted(to, 1);

        if (QStandardItem *item = q->item(to)) {
            if (item->data(QchNowPlayingModel::DurationRole) == 0) {
                queryManager->getItems(to, to);
            }
        }

        mafwRenderer->getStatus();
    }
    
    QchNowPlayingModel *q_ptr;
    
    mutable MafwRegistryAdapter *mafwRegistry;
    mutable MafwRendererAdapter *mafwRenderer;
    mutable MafwPlaylistAdapter *mafwPlaylist;
    mutable MafwSourceAdapter *mafwTrackerSource;
    mutable PlaylistQueryManager *queryManager;
    
    GConfItem *gconfItem;
    
    QchMediaType::Type mediaType;
    
    int position;
    
    bool repeat;
    bool shuffle;
    
    bool playlistAssigned;
    
    bool complete;
    
    Q_DECLARE_PUBLIC(QchNowPlayingModel)
};

QchNowPlayingModel::QchNowPlayingModel(QObject *parent) :
    QStandardItemModel(parent),
    d_ptr(new QchNowPlayingModelPrivate(this))
{
    Q_D(QchNowPlayingModel);
    
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
    setRoleNames(roles);
}

QchNowPlayingModel::~QchNowPlayingModel() {}

QchMediaType::Type QchNowPlayingModel::mediaType() const {
    Q_D(const QchNowPlayingModel);
    
    return d->mediaType;
}

void QchNowPlayingModel::setMediaType(QchMediaType::Type type) {
    if (type != mediaType()) {
        Q_D(QchNowPlayingModel);
        d->mediaType = type;
        emit mediaTypeChanged();
        
        if (d->complete) {
            clear();
            d->_q_assignPlaylist();
        }
    }
}

int QchNowPlayingModel::position() const {
    Q_D(const QchNowPlayingModel);
    
    return d->position;
}

void QchNowPlayingModel::setPosition(int pos) {
    if (pos != position()) {
        Q_D(QchNowPlayingModel);
        d->_q_assignPlaylist();
        d->mafwRenderer->gotoIndex(pos);
    }
}

bool QchNowPlayingModel::isRepeat() const {
    Q_D(const QchNowPlayingModel);
    
    return d->repeat;
}

void QchNowPlayingModel::setRepeat(bool repeat) {
    if (repeat != isRepeat()) {
        Q_D(QchNowPlayingModel);
        d->_q_assignPlaylist();
        d->mafwPlaylist->setRepeat(repeat);
    }
}

bool QchNowPlayingModel::isShuffled() const {
    Q_D(const QchNowPlayingModel);
    
    return d->shuffle;
}

void QchNowPlayingModel::setShuffled(bool shuffled) {
    if (shuffled != isShuffled()) {
        Q_D(QchNowPlayingModel);
        d->_q_assignPlaylist();
        d->mafwPlaylist->setShuffled(shuffled);
    }
}

void QchNowPlayingModel::appendSource(const QString &uri) {
    Q_D(QchNowPlayingModel);
    
    appendItem(d->uriToId(uri));
}

void QchNowPlayingModel::appendItem(const QString &id) {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->appendItem(id);
}

void QchNowPlayingModel::insertSource(int row, const QString &uri) {
    Q_D(QchNowPlayingModel);
    
    insertItem(row, d->uriToId(uri));
}

void QchNowPlayingModel::insertItem(int row, const QString &id) {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->insertItem(id, row);
}

void QchNowPlayingModel::moveItem(int from, int to) {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->moveItem(from, to);
}

void QchNowPlayingModel::removeItem(int row) {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->removeItem(row);
}

QVariant QchNowPlayingModel::property(int row, const QString &name) {
    return data(index(row, 0), roleNames().key(name.toUtf8()));
}

void QchNowPlayingModel::clearItems() {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwPlaylist->clear();
    d->gconfItem->set(0);
}

void QchNowPlayingModel::loadItems() {
    Q_D(QchNowPlayingModel);
    
    clear();
    d->_q_assignPlaylist();
    d->_q_onItemsChanged(-1, 0, 0);
}

void QchNowPlayingModel::next() {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwRenderer->next();
}

void QchNowPlayingModel::previous() {
    Q_D(QchNowPlayingModel);
    
    d->_q_assignPlaylist();
    d->mafwRenderer->previous();
}

void QchNowPlayingModel::classBegin() {}

void QchNowPlayingModel::componentComplete() {
    Q_D(QchNowPlayingModel);
    
    d->complete = true;
    
    connect(d->queryManager, SIGNAL(onGetItems(QString, GHashTable*, guint)), 
                  this, SLOT(_q_onItemsReady(QString, GHashTable*, guint)));
                  
    connect(d->mafwPlaylist, SIGNAL(playlistChanged()), this, SLOT(_q_onPlaylistChanged()));
    
    if (d->mafwRenderer->isRendererReady()) {
        d->_q_assignPlaylist();
    }
    else {
        connect(d->mafwRenderer, SIGNAL(rendererReady()), this, SLOT(_q_assignPlaylist()));
    }
}

#include "moc_qchnowplayingmodel.cpp"

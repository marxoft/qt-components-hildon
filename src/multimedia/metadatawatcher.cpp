#include "metadatawatcher_p.h"
#include <QImage>
#include <QCryptographicHash>

MetadataWatcher* MetadataWatcher::instance = NULL;

MetadataWatcher* MetadataWatcher::acquire()
{
    return instance ? instance : instance = new MetadataWatcher();
}

MetadataWatcher::MetadataWatcher() :
    QObject(),
    mafwRegistry(MafwRegistryAdapter::get()),
    mafwRenderer(mafwRegistry->renderer()),
    mafwSource(new MafwSourceAdapter(NULL)),
    mafwTrackerSource(mafwRegistry->source(MafwRegistryAdapter::Tracker)),
    sourceMetadataPresent(false)
{
    // Initialization
    connect(mafwRenderer, SIGNAL(rendererReady()), mafwRenderer, SLOT(getStatus()));
    connect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
            this, SLOT(onStatusReceived(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

    // Metadata
    connect(mafwRenderer, SIGNAL(metadataChanged(QString,QVariant)),
            this, SLOT(onRendererMetadataChanged(QString,QVariant)));
    connect(mafwRenderer, SIGNAL(signalGetCurrentMetadata(GHashTable*,QString,QString)),
            this, SLOT(onRendererMetadataReceived(GHashTable*,QString,QString)));
    connect(mafwSource, SIGNAL(metadataResult(QString,GHashTable*,QString)),
            this, SLOT(onSourceMetadataReceived(QString,GHashTable*,QString)));
    // Currently this is solely for the purpose of updating the paused position,
    // but it might be a good idea to keep all metadata in sync.
    connect(mafwTrackerSource, SIGNAL(metadataChanged(QString)),
            this, SLOT(onSourceMetadataChanged(QString)));
}

QString MetadataWatcher::albumTitle() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_ALBUM).toString();
}

QString MetadataWatcher::artist() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_ARTIST).toString();
}

int MetadataWatcher::audioBitRate() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_AUDIO_BITRATE).toInt();
}

QString MetadataWatcher::audioCodec() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_AUDIO_CODEC).toString();
}

QString MetadataWatcher::comment() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_COMMENT).toString();
}

QString MetadataWatcher::composer() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_COMPOSER).toString();
}

QString MetadataWatcher::copyright() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_COPYRIGHT).toString();
}

QString MetadataWatcher::coverArtUrl() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_RENDERER_ART_URI).toString();
}

qint64 MetadataWatcher::date() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_MODIFIED).toLongLong();
}

QString MetadataWatcher::description() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_DESCRIPTION).toString();
}

QString MetadataWatcher::genre() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_GENRE).toString();
}

qint64 MetadataWatcher::lastPlayed() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_LAST_PLAYED).toLongLong();
}

QString MetadataWatcher::lastThumbnailUrl() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_PAUSED_THUMBNAIL_URI).toString();
}

QString MetadataWatcher::lyrics() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_LYRICS).toString();
}

QString MetadataWatcher::mimeType() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_MIME).toString();
}

int MetadataWatcher::playCount() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_PLAY_COUNT).toInt();
}

QSize MetadataWatcher::resolution() const
{
    return QSize(currentMetadata.value(MAFW_METADATA_KEY_RES_X).toInt(),
                 currentMetadata.value(MAFW_METADATA_KEY_RES_Y).toInt());
}

int MetadataWatcher::resumePosition() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_PAUSED_POSITION).toInt();
}

int MetadataWatcher::size() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_FILESIZE).toInt();
}

QString MetadataWatcher::thumbnailUrl() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_THUMBNAIL_URI).toString();
}

QString MetadataWatcher::title() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_TITLE).toString();
}

int MetadataWatcher::trackNumber() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_TRACK).toInt();
}

int MetadataWatcher::videoBitRate() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_VIDEO_BITRATE).toInt();
}

QString MetadataWatcher::videoCodec() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_VIDEO_CODEC).toString();
}

qreal MetadataWatcher::videoFrameRate() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_VIDEO_FRAMERATE).toDouble();
}

int MetadataWatcher::year() const
{
    return currentMetadata.value(MAFW_METADATA_KEY_YEAR).toInt();
}

MafwSourceAdapter* MetadataWatcher::currentSource() const
{
    return mafwSource;
}

QMap<QString,QVariant> MetadataWatcher::metadata() const
{
    return currentMetadata;
}

void MetadataWatcher::setMetadataFromRenderer(QString key, QVariant value)
{
#ifdef MAFW_WORKAROUNDS
    // The renderer misreports duration of some UPnP media, so in this case give
    // priority to the source. setMetadataFromSource() implements the remaining
    // part of this workaround.
    if (key == MAFW_METADATA_KEY_DURATION
    &&  currentObjectId.startsWith("_uuid_"))
    {
        if (sourceMetadataPresent) {
            QVariant &currentValue = currentMetadata[key];
            if (currentValue.isNull()) {
                currentValue = value;
                emit metadataChanged();
            }
        } else {
            QVariant &backupValue = backupMetadata[key];
            if (backupValue.isNull())
                backupValue = value;

            QVariant &currentValue = currentMetadata[key];
            if (currentValue != value) {
                currentValue = value;
                emit metadataChanged();
            }
        }
        return;
    }
#endif

    if (!sourceMetadataPresent)
        backupMetadata[key] = value;

    QVariant &currentValue = currentMetadata[key];
    if (currentValue != value) {
        currentValue = value;
        emit metadataChanged();
    }
}

void MetadataWatcher::setMetadataFromSource(QString key, QVariant value)
{
#ifdef MAFW_WORKAROUNDS
    // Source's part of the workaround described in setMetadataFromRenderer()
    if (key == MAFW_METADATA_KEY_DURATION
    &&  currentObjectId.startsWith("_uuid_"))
    {
        if (sourceMetadataPresent) {
            QVariant &currentValue = currentMetadata[key];
            if (currentValue != value) {
                currentValue = value;
                emit metadataChanged();
            }
        } else {
            backupMetadata[key] = value;
        }
        return;
    }
#endif

    if (sourceMetadataPresent) {
        // Consider source metadata less important than renderer metadata,
        // that is do not overwrite it.
        QVariant &currentValue = currentMetadata[key];
        if (currentValue.isNull()) {
            currentValue = value;
            emit metadataChanged();
        }
    } else {
        QVariant &backupValue = backupMetadata[key];
        if (backupValue.isNull())
            backupValue = value;
    }
}

void MetadataWatcher::onStatusReceived(MafwPlaylist *, uint index, MafwPlayState, const char *objectId, QString)
{
    disconnect(mafwRenderer, SIGNAL(signalGetStatus(MafwPlaylist*,uint,MafwPlayState,const char*,QString)),
               this, SLOT(onStatusReceived(MafwPlaylist*,uint,MafwPlayState,const char*,QString)));

    connect(mafwRenderer, SIGNAL(mediaChanged(int,char*)), this, SLOT(onMediaChanged(int,char*)));

    onMediaChanged(index, (char *) objectId);
}

void MetadataWatcher::onMediaChanged(int, char *objectId)
{
    currentObjectId = QString::fromUtf8(objectId);

    backupMetadata.clear();
    sourceMetadataPresent = false;
    
    if (currentObjectId.isEmpty()) {
        currentMetadata.clear();
        emit metadataChanged();
        return;
    }

    // Reset the URI as soon as possible to avoid album art misdetection
    if (currentMetadata.remove(MAFW_METADATA_KEY_URI))
        emit metadataChanged();

    mafwRenderer->getCurrentMetadata();

    mafwSource->bind(mafwRegistry->findSourceByUUID(currentObjectId.left(currentObjectId.indexOf("::"))));
    mafwSource->getMetadata(currentObjectId, MAFW_SOURCE_LIST(MAFW_METADATA_KEY_URI,
                                                              MAFW_METADATA_KEY_TITLE,
                                                              MAFW_METADATA_KEY_DURATION,
                                                              MAFW_METADATA_KEY_ARTIST,
                                                              MAFW_METADATA_KEY_ALBUM,
                                                              MAFW_METADATA_KEY_GENRE,
                                                              MAFW_METADATA_KEY_TRACK,
                                                              MAFW_METADATA_KEY_YEAR,
                                                              MAFW_METADATA_KEY_PLAY_COUNT,
                                                              MAFW_METADATA_KEY_LAST_PLAYED,
                                                              MAFW_METADATA_KEY_DESCRIPTION,
                                                              MAFW_METADATA_KEY_MODIFIED,
                                                              MAFW_METADATA_KEY_PAUSED_POSITION,
                                                              MAFW_METADATA_KEY_PAUSED_THUMBNAIL_URI,
                                                              MAFW_METADATA_KEY_IS_SEEKABLE,
                                                              MAFW_METADATA_KEY_RES_X,
                                                              MAFW_METADATA_KEY_RES_Y,
                                                              MAFW_METADATA_KEY_COMMENT,
                                                              MAFW_METADATA_KEY_TAGS,
                                                              MAFW_METADATA_KEY_LYRICS,
                                                              MAFW_METADATA_KEY_COMPOSER,
                                                              MAFW_METADATA_KEY_FILESIZE,
                                                              MAFW_METADATA_KEY_COPYRIGHT,
                                                              MAFW_METADATA_KEY_AUDIO_BITRATE,
                                                              MAFW_METADATA_KEY_AUDIO_CODEC,
                                                              MAFW_METADATA_KEY_ALBUM_ART_URI,
                                                              MAFW_METADATA_KEY_VIDEO_BITRATE,
                                                              MAFW_METADATA_KEY_VIDEO_CODEC,
                                                              MAFW_METADATA_KEY_VIDEO_FRAMERATE
                                                              ));
}

void MetadataWatcher::onSourceMetadataReceived(QString objectId, GHashTable *metadata, QString)
{
    if (objectId != currentObjectId) return;

    GList *keys = g_hash_table_get_keys(metadata);

    for (GList *key = keys; key; key = key->next) {
        QString keyName((const char *) key->data);

        // Paused position might require some processing to prevent confusion in
        // the video window.
        if (keyName == MAFW_METADATA_KEY_PAUSED_POSITION) {
            int pausedPosition = g_value_get_int(mafw_metadata_first(metadata, MAFW_METADATA_KEY_PAUSED_POSITION));
            if (pausedPosition < 0)
                pausedPosition = 0;

            if (sourceMetadataPresent) {
                QVariant &currentValue = currentMetadata[keyName];
                if (currentValue != pausedPosition) {
                    currentValue = pausedPosition;
                    emit metadataChanged();
                }
            } else {
                backupMetadata[keyName] = pausedPosition;
            }
        }
        // Only one piece of cover art can be shown at a given time, so both
        // source- and renderer-provided images can be stored under the same
        // key to make the life of receiving classes easier.
        else if (keyName == MAFW_METADATA_KEY_ALBUM_ART_URI) {
            keyName = MAFW_METADATA_KEY_RENDERER_ART_URI;

            // Renderer-art comes as a simple path, not a URI, contrary
            // to album-art, thus a conversion is necessary.
            const char* uri = g_value_get_string(mafw_metadata_first(metadata, MAFW_METADATA_KEY_ALBUM_ART_URI));
            char* filename;
            if (uri && (filename = g_filename_from_uri(uri, NULL, NULL)))
                setMetadataFromSource(keyName, QString::fromUtf8(filename));
        }
        else {
            QVariant value = toQVariant(mafw_metadata_first(metadata, (const char *) key->data));
            setMetadataFromSource(keyName, value);

            // The title will double as station name for the radion window
            if (keyName == MAFW_METADATA_KEY_TITLE)
                setMetadataFromSource(MAFW_METADATA_KEY_ORGANIZATION, value);
        }

    }

    g_list_free(keys);

    if (!sourceMetadataPresent) {
        // The video window should always receive a position to resume from to
        // work properly.
        if (backupMetadata.value(MAFW_METADATA_KEY_PAUSED_POSITION).isNull())
            backupMetadata[MAFW_METADATA_KEY_PAUSED_POSITION] = 0;

        currentMetadata = backupMetadata;
        backupMetadata.clear();

        sourceMetadataPresent = true;

        emit metadataChanged();
    }
}

void MetadataWatcher::onSourceMetadataChanged(QString objectId)
{
    if (objectId != currentObjectId) return;

    mafwSource->getMetadata(currentObjectId, MAFW_SOURCE_LIST(MAFW_METADATA_KEY_PAUSED_POSITION));
}

void MetadataWatcher::onRendererMetadataReceived(GHashTable *metadata, QString objectId, QString)
{
    if (objectId != currentObjectId) return;

    // Make sure that video codec is always emitted before audio codec so that
    // media type detection does not fail.
    if (g_hash_table_lookup(metadata, MAFW_METADATA_KEY_VIDEO_CODEC))
        setMetadataFromRenderer(MAFW_METADATA_KEY_VIDEO_CODEC, g_value_get_string(mafw_metadata_first(metadata, MAFW_METADATA_KEY_VIDEO_CODEC)));

    GList *keys = g_hash_table_get_keys(metadata);

    // Accept all metadata
    for (GList *key = keys; key; key = key->next)
        setMetadataFromRenderer((const char *) key->data, toQVariant(mafw_metadata_first(metadata, (const char *) key->data)));

    g_list_free(keys);
}

void MetadataWatcher::onRendererMetadataChanged(QString metadata, QVariant value)
{
    if (metadata == MAFW_METADATA_KEY_AUDIO_CODEC) {
        // If video codec info is available, then audio codec info should not
        // arrive before it for media type detection to work. Make an additional
        // metadata request instead of handling it immediately, in case the
        // renderer has the desired information, but has not emitted it yet.
        mafwRenderer->getCurrentMetadata();
    } else {
        setMetadataFromRenderer(metadata, value);

        // Update video thumbnail
        if (metadata == MAFW_METADATA_KEY_PAUSED_THUMBNAIL_URI && currentObjectId.startsWith("localtagfs::videos")) {
            QString thumbFile = value.toString();
            if (thumbFile.contains("mafw-gst-renderer-")) {
                QImage thumbnail(thumbFile);
                if (thumbnail.width() > thumbnail.height()) {
                    // Horizontal, fill height
                    thumbnail = thumbnail.scaledToHeight(124, Qt::SmoothTransformation);
                    thumbnail = thumbnail.copy((thumbnail.width()-124)/2, 0, 124, 124);
                } else {
                    // Vertical, fill width
                    thumbnail = thumbnail.scaledToWidth(124, Qt::SmoothTransformation);
                    thumbnail = thumbnail.copy(0, (thumbnail.height()-124)/2, 124, 124);
                }

                thumbFile = "/home/user/.fmp_pause_thumbnail/"
                        + QCryptographicHash::hash(currentObjectId.toUtf8(), QCryptographicHash::Md5).toHex()
                        + ".jpeg";

                thumbnail.save(thumbFile, "JPEG");

                GHashTable* metadata = mafw_metadata_new();
                mafw_metadata_add_str(metadata, MAFW_METADATA_KEY_PAUSED_THUMBNAIL_URI, qstrdup(thumbFile.toUtf8()));
                mafwTrackerSource->setMetadata(currentObjectId, metadata);
                mafw_metadata_release(metadata);
            }

            // It is not necessary to inform VideosWindow directly about the change,
            // because it should receive the notification from MAFW, although that
            // can take a little bit longer.
        }
    }
}

QVariant MetadataWatcher::toQVariant(GValue *v)
{
    switch (G_VALUE_TYPE(v)) {
        case G_TYPE_INT:
            return g_value_get_int(v);
        case G_TYPE_INT64:
            return g_value_get_int64(v);
        case G_TYPE_STRING:
            return QString::fromUtf8(g_value_get_string(v));
        case G_TYPE_BOOLEAN:
            return g_value_get_boolean(v);
        default:
            return QVariant();
    }
}

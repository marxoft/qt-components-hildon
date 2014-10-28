#ifndef METADATAWATCHER_P_H
#define METADATAWATCHER_P_H

#include <QObject>
#include <QSize>

#include "mafw/mafwregistryadapter.h"

class MetadataWatcher: public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString albumArtist READ artist NOTIFY metadataChanged)
    Q_PROPERTY(QString albumTitle READ albumTitle NOTIFY metadataChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY metadataChanged)
    Q_PROPERTY(int audioBitRate READ audioBitRate NOTIFY metadataChanged)
    Q_PROPERTY(QString audioCodec READ audioCodec NOTIFY metadataChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY metadataChanged)
    Q_PROPERTY(QString composer READ composer NOTIFY metadataChanged)
    Q_PROPERTY(QString copyright READ copyright NOTIFY metadataChanged)
    Q_PROPERTY(QString coverArtUrl READ coverArtUrl NOTIFY metadataChanged)
    Q_PROPERTY(qint64 date READ date NOTIFY metadataChanged)
    Q_PROPERTY(QString description READ description NOTIFY metadataChanged)
    Q_PROPERTY(QString genre READ genre NOTIFY metadataChanged)
    Q_PROPERTY(QStringList keywords READ keywords NOTIFY metadataChanged)
    Q_PROPERTY(qint64 lastPlayed READ lastPlayed NOTIFY metadataChanged)
    Q_PROPERTY(QString lastThumbnailUrl READ lastThumbnailUrl NOTIFY metadataChanged)
    Q_PROPERTY(QString lyrics READ lyrics NOTIFY metadataChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY metadataChanged)
    Q_PROPERTY(int playCount READ playCount NOTIFY metadataChanged)
    Q_PROPERTY(QSize resolution READ resolution NOTIFY metadataChanged)
    Q_PROPERTY(int resumePosition READ resumePosition NOTIFY metadataChanged)
    Q_PROPERTY(int size READ size NOTIFY metadataChanged)
    Q_PROPERTY(QString thumbnailUrl READ thumbnailUrl NOTIFY metadataChanged)
    Q_PROPERTY(QString title READ title NOTIFY metadataChanged)
    Q_PROPERTY(int trackNumber READ trackNumber NOTIFY metadataChanged)
    Q_PROPERTY(int videoBitRate READ videoBitRate NOTIFY metadataChanged)
    Q_PROPERTY(QString videoCodec READ videoCodec NOTIFY metadataChanged)
    Q_PROPERTY(qreal videoFrameRate READ videoFrameRate NOTIFY metadataChanged)
    Q_PROPERTY(int year READ year NOTIFY metadataChanged)

public:
    static MetadataWatcher* acquire();
    
    QString albumTitle() const;
    QString artist() const;
    int audioBitRate() const;
    QString audioCodec() const;
    QString comment() const;
    QString composer() const;
    QString copyright() const;
    QString coverArtUrl() const;
    qint64 date() const;
    QString description() const;
    QString genre() const;
    QStringList keywords() const;
    qint64 lastPlayed() const;
    QString lastThumbnailUrl() const;
    QString lyrics() const;
    QString mimeType() const;
    int playCount() const;
    QSize resolution() const;
    int resumePosition() const;
    int size() const;
    QString thumbnailUrl() const;
    QString title() const;
    int trackNumber() const;
    int videoBitRate() const;
    QString videoCodec() const;
    qreal videoFrameRate() const;
    int year() const;
    
    MafwSourceAdapter* currentSource() const;
    QMap<QString,QVariant> metadata() const;

signals:
    void metadataChanged();

private:
    static MetadataWatcher *instance;
    
    MafwRegistryAdapter *mafwRegistry;
    MafwRendererAdapter *mafwRenderer;
    MafwSourceAdapter *mafwSource;
    MafwSourceAdapter *mafwTrackerSource;

    QMap<QString,QVariant> currentMetadata;
    QMap<QString,QVariant> backupMetadata;
    QString currentObjectId;

    bool sourceMetadataPresent;
    
    MetadataWatcher();

    void setMetadataFromSource(QString key, QVariant value);
    void setMetadataFromRenderer(QString key, QVariant value);

    static QVariant toQVariant(GValue *v);

private slots:
    void onStatusReceived(MafwPlaylist *, uint index, MafwPlayState, const char *objectId, QString);

    void onMediaChanged(int, char *objectId);
    void onSourceMetadataReceived(QString objectId, GHashTable *metadata, QString);
    void onSourceMetadataChanged(QString objectId);
    void onRendererMetadataReceived(GHashTable *metadata, QString objectId, QString);
    void onRendererMetadataChanged(QString metadata, QVariant value);
};

#endif // METADATAWATCHER_P_H

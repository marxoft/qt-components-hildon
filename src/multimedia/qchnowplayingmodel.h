/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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
 
#ifndef QCHPLAYBACKMODEL_H
#define QCHPLAYBACKMODEL_H

#include "qchmediatype.h"
#include <QStandardItemModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchNowPlayingModelPrivate;

class QchNowPlayingModel : public QStandardItemModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(QchMediaType::Type mediaType READ mediaType WRITE setMediaType NOTIFY mediaTypeChanged)
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
        OrganizationRole,
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
    
    explicit QchNowPlayingModel(QObject *parent = 0);
    ~QchNowPlayingModel();
    
    QchMediaType::Type mediaType() const;
    void setMediaType(QchMediaType::Type type);
    
    int position() const;
    void setPosition(int pos);
    
    bool isRepeat() const;
    void setRepeat(bool repeat);
    
    bool isShuffled() const;
    void setShuffled(bool shuffle);
    
    Q_INVOKABLE void appendSource(const QString &uri);
    Q_INVOKABLE void appendItem(const QString &id);
    Q_INVOKABLE void insertSource(int row, const QString &uri);
    Q_INVOKABLE void insertItem(int row, const QString &id);
    Q_INVOKABLE void moveItem(int from, int to);
    Q_INVOKABLE void removeItem(int row);
        
    Q_INVOKABLE QVariant property(int row, const QString &name);
    
public Q_SLOTS:
    void clearItems();
    void loadItems();
    
    void next();
    void previous();
    
Q_SIGNALS:
    void countChanged();
    void mediaTypeChanged();
    void positionChanged();
    void ready();
    void repeatChanged();
    void shuffledChanged();
    
private:
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<QchNowPlayingModelPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchNowPlayingModel)
    Q_DISABLE_COPY(QchNowPlayingModel)
    
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

QML_DECLARE_TYPE(QchNowPlayingModel)

#endif // QCHPLAYBACKMODEL_H

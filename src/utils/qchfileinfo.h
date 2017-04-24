/*!
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHFILEINFO_H
#define QCHFILEINFO_H

#include <QObject>
#include <QDateTime>
#include <QFileInfo>
#include <QScriptable>
#include <qdeclarative.h>

class QchFileInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath NOTIFY fileChanged)
    Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY fileChanged)
    Q_PROPERTY(QString baseName READ baseName NOTIFY fileChanged)
    Q_PROPERTY(QString completeBaseName READ completeBaseName NOTIFY fileChanged)
    Q_PROPERTY(bool caching READ caching WRITE setCaching NOTIFY cachingChanged)
    Q_PROPERTY(QString canonicalFilePath READ canonicalFilePath NOTIFY fileChanged)
    Q_PROPERTY(QString canonicalPath READ canonicalPath NOTIFY fileChanged)
    Q_PROPERTY(QDateTime created READ created NOTIFY fileChanged)
    Q_PROPERTY(QDateTime lastModified READ lastModified NOTIFY fileChanged)
    Q_PROPERTY(QDateTime lastRead READ lastRead NOTIFY fileChanged)
    Q_PROPERTY(bool exists READ exists NOTIFY fileChanged)
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY fileChanged)
    Q_PROPERTY(QString group READ group NOTIFY fileChanged)
    Q_PROPERTY(uint groupId READ groupId NOTIFY fileChanged)
    Q_PROPERTY(bool absolute READ isAbsolute NOTIFY fileChanged)
    Q_PROPERTY(bool isDir READ isDir NOTIFY fileChanged)
    Q_PROPERTY(bool executable READ isExecutable NOTIFY fileChanged)
    Q_PROPERTY(bool isFile READ isFile NOTIFY fileChanged)
    Q_PROPERTY(bool hidden READ isHidden NOTIFY fileChanged)
    Q_PROPERTY(bool readable READ isReadable NOTIFY fileChanged)
    Q_PROPERTY(bool relative READ isRelative NOTIFY fileChanged)
    Q_PROPERTY(bool root READ isRoot NOTIFY fileChanged)
    Q_PROPERTY(bool isSymLink READ isSymLink NOTIFY fileChanged)
    Q_PROPERTY(bool writable READ isWritable NOTIFY fileChanged)
    Q_PROPERTY(QString owner READ owner NOTIFY fileChanged)
    Q_PROPERTY(uint ownerId READ ownerId NOTIFY fileChanged)
    Q_PROPERTY(QString path READ path NOTIFY fileChanged)
    Q_PROPERTY(qint64 size READ size NOTIFY fileChanged)
    Q_PROPERTY(QString suffix READ suffix NOTIFY fileChanged)
    Q_PROPERTY(QString completeSuffix READ completeSuffix NOTIFY fileChanged)
    Q_PROPERTY(QString symLinkTarget READ symLinkTarget NOTIFY fileChanged)

public:
    explicit QchFileInfo(QObject *parent = 0);

    QString absoluteFilePath() const;
    QString absolutePath() const;

    QString baseName() const;
    QString completeBaseName() const;

    bool caching() const;
    void setCaching(bool enabled);

    QString canonicalFilePath() const;
    QString canonicalPath() const;

    QDateTime created() const;
    QDateTime lastModified() const;
    QDateTime lastRead() const;

    bool exists() const;

    QString file() const;
    void setFile(const QString &name);

    QString fileName() const;
    QString filePath() const;

    QString group() const;
    uint groupId() const;

    bool isAbsolute() const;
    bool isDir() const;
    bool isExecutable() const;
    bool isFile() const;
    bool isHidden() const;
    bool isReadable() const;
    bool isRelative() const;
    bool isRoot() const;
    bool isSymLink() const;
    bool isWritable() const;

    QString owner() const;
    uint ownerId() const;

    QString path() const;

    qint64 size() const;

    QString suffix() const;
    QString completeSuffix() const;

    QString symLinkTarget() const;

    Q_INVOKABLE void makeAbsolute();
    Q_INVOKABLE void refresh();

Q_SIGNALS:
    void cachingChanged();
    void fileChanged();

private:
    QString m_file;
    QFileInfo m_info;

    Q_DISABLE_COPY(QchFileInfo)
};

class QchScriptableFileInfo : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath)
    Q_PROPERTY(QString absolutePath READ absolutePath)
    Q_PROPERTY(QString baseName READ baseName)
    Q_PROPERTY(QString completeBaseName READ completeBaseName)
    Q_PROPERTY(bool caching READ caching WRITE setCaching)
    Q_PROPERTY(QString canonicalFilePath READ canonicalFilePath)
    Q_PROPERTY(QString canonicalPath READ canonicalPath)
    Q_PROPERTY(QDateTime created READ created)
    Q_PROPERTY(QDateTime lastModified READ lastModified)
    Q_PROPERTY(QDateTime lastRead READ lastRead)
    Q_PROPERTY(bool exists READ exists)
    Q_PROPERTY(QString file READ file WRITE setFile)
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(QString filePath READ filePath)
    Q_PROPERTY(QString group READ group)
    Q_PROPERTY(uint groupId READ groupId)
    Q_PROPERTY(bool absolute READ isAbsolute)
    Q_PROPERTY(bool isDir READ isDir)
    Q_PROPERTY(bool executable READ isExecutable)
    Q_PROPERTY(bool isFile READ isFile)
    Q_PROPERTY(bool hidden READ isHidden)
    Q_PROPERTY(bool readable READ isReadable)
    Q_PROPERTY(bool relative READ isRelative)
    Q_PROPERTY(bool root READ isRoot)
    Q_PROPERTY(bool isSymLink READ isSymLink)
    Q_PROPERTY(bool writable READ isWritable)
    Q_PROPERTY(QString owner READ owner)
    Q_PROPERTY(uint ownerId READ ownerId)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(qint64 size READ size)
    Q_PROPERTY(QString suffix READ suffix)
    Q_PROPERTY(QString completeSuffix READ completeSuffix)
    Q_PROPERTY(QString symLinkTarget READ symLinkTarget)

public:
    explicit QchScriptableFileInfo(QObject *parent = 0);

    QString absoluteFilePath() const;
    QString absolutePath() const;

    QString baseName() const;
    QString completeBaseName() const;

    bool caching() const;
    void setCaching(bool enabled);

    QString canonicalFilePath() const;
    QString canonicalPath() const;

    QDateTime created() const;
    QDateTime lastModified() const;
    QDateTime lastRead() const;

    bool exists() const;

    QString file() const;
    void setFile(const QString &name);

    QString fileName() const;
    QString filePath() const;

    QString group() const;
    uint groupId() const;

    bool isAbsolute() const;
    bool isDir() const;
    bool isExecutable() const;
    bool isFile() const;
    bool isHidden() const;
    bool isReadable() const;
    bool isRelative() const;
    bool isRoot() const;
    bool isSymLink() const;
    bool isWritable() const;

    QString owner() const;
    uint ownerId() const;

    QString path() const;

    qint64 size() const;

    QString suffix() const;
    QString completeSuffix() const;

    QString symLinkTarget() const;

    Q_INVOKABLE void makeAbsolute();
    Q_INVOKABLE void refresh();

private:
    Q_DISABLE_COPY(QchScriptableFileInfo)
};

QML_DECLARE_TYPE(QchFileInfo)
Q_DECLARE_METATYPE(QFileInfo)
Q_DECLARE_METATYPE(QFileInfo*)
Q_DECLARE_METATYPE(QFileInfoList)

#endif // QCHFILEINFO_H


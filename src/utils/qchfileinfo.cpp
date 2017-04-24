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

#include "qchfileinfo.h"
#include <QScriptEngine>

/*!
 * \class FileInfo
 * \brief Provides file information.
 * \ingroup utils
 *
 * FileInfo provides information about a file's name and path in the file system,
 * it's access rights and whether it is a directory or symbolic link, etc.
 *
 * \sa Directory
 */
QchFileInfo::QchFileInfo(QObject *parent) :
    QObject(parent)
{
}

/*!
 * The file's absolute path including the file name.
 *
 * \sa filePath, canonicalFilePath, relative
 */
QString QchFileInfo::absoluteFilePath() const {
    return m_info.absoluteFilePath();
}

/*!
 * The file's absolute path.
 *
 * \sa absoluteFilePath, path, canonicalPath, fileName, relative
 */
QString QchFileInfo::absolutePath() const {
    return m_info.absolutePath();
}

/*!
 * The base name of the file without the path.
 *
 * \sa fileName, suffix, completeSuffix, completeBaseName
 */
QString QchFileInfo::baseName() const {
    return m_info.baseName();
}

/*!
 * The complete base name of the file without the path.
 *
 * \sa fileName, suffix, completeSuffix, baseName
 */
QString QchFileInfo::completeBaseName() const {
    return m_info.completeBaseName();
}

/*!
 * Whether caching is enabled.
 *
 * The default value is \c true.
 */
bool QchFileInfo::caching() const {
    return m_info.caching();
}

void QchFileInfo::setCaching(bool enabled) {
    if (enabled != caching()) {
        m_info.setCaching(enabled);
        emit cachingChanged();
    }
}

/*!
 * The canonical path including the file name.
 *
 * \sa filePath, absoluteFilePath
 */
QString QchFileInfo::canonicalFilePath() const {
    return m_info.canonicalFilePath();
}

/*!
 * The canonical path without the file name.
 *
 * \sa path, absolutePath
 */
QString QchFileInfo::canonicalPath() const {
    return m_info.canonicalPath();
}

/*!
 * The date and time when the file was created.
 *
 * \sa lastModified, lastRead
 */
QDateTime QchFileInfo::created() const {
    return m_info.created();
}

/*!
 * The date and time when the file was last modified.
 *
 * \sa created, lastRead
 */
QDateTime QchFileInfo::lastModified() const {
    return m_info.lastModified();
}

/*!
 * The date and time when the file was last read.
 *
 * \sa created, lastModified
 */
QDateTime QchFileInfo::lastRead() const {
    return m_info.lastRead();
}

/*!
 * Whether the file exists.
 */
bool QchFileInfo::exists() const {
    return m_info.exists();
}

/*!
 * The path used to retrieve the file information.
 */
QString QchFileInfo::file() const {
    return m_file;
}

void QchFileInfo::setFile(const QString &name) {
    if (name != file()) {
        m_file = name;
        m_info.setFile(name);
        emit fileChanged();
    }
}

/*!
 * The name of the file, excluding the path.
 *
 * \sa relative, filePath, baseName, suffix
 */
QString QchFileInfo::fileName() const {
    return m_info.fileName();
}

/*!
 * The name of the file, including the path.
 *
 * \sa absoluteFilePath, canonicalFilePath, relative
 */
QString QchFileInfo::filePath() const {
    return m_info.filePath();
}

/*!
 * The group of the file.
 *
 * \sa groupId, owner, ownerId
 */
QString QchFileInfo::group() const {
    return m_info.group();
}

/*!
 * The id of the group the file belongs to.
 *
 * \sa group, owner, ownerId
 */
uint QchFileInfo::groupId() const {
    return m_info.groupId();
}

/*!
 * Whether the file path is absolute.
 *
 * \sa relative
 */
bool QchFileInfo::isAbsolute() const {
    return m_info.isAbsolute();
}

/*!
 * Whether the object points to a directory.
 *
 * \sa isFile, isSymLink
 */
bool QchFileInfo::isDir() const {
    return m_info.isDir();
}

/*!
 * Whether the file is executable.
 *
 * \sa readable, writable
 */
bool QchFileInfo::isExecutable() const {
    return m_info.isExecutable();
}

/*!
 * Whether the object points to a file.
 *
 * \sa isDir, isSymLink
 */
bool QchFileInfo::isFile() const {
    return m_info.isFile();
}

/*!
 * Whether the file is hidden.
 *
 */
bool QchFileInfo::isHidden() const {
    return m_info.isHidden();
}

/*!
 * Whether the file is readable.
 *
 * \sa writable, executable
 */
bool QchFileInfo::isReadable() const {
    return m_info.isReadable();
}

/*!
 * Whether the file path is relative.
 *
 * \sa absolute
 */
bool QchFileInfo::isRelative() const {
    return m_info.isRelative();
}

/*!
 * Whether the object points to the root directory.
 */
bool QchFileInfo::isRoot() const {
    return m_info.isRoot();
}

/*!
 * Whether the object points to a symbolic link.
 * \sa isFile, isDir, symLinkTarget
 */
bool QchFileInfo::isSymLink() const {
    return m_info.isSymLink();
}

/*!
 * Whether the file is writable.
 *
 * \sa readable, executable
 */
bool QchFileInfo::isWritable() const {
    return m_info.isWritable();
}

/*!
 * The owner of the file.
 *
 * \sa ownerId, group, groupId
 */
QString QchFileInfo::owner() const {
    return m_info.owner();
}

/*!
 * The id of the owner of the file.
 *
 * \sa owner, group, groupId
 */
uint QchFileInfo::ownerId() const {
    return m_info.ownerId();
}

/*!
 * The path of the file.
 *
 * \sa filePath, absolutePath, canonicalPath, fileName, relative
 */
QString QchFileInfo::path() const {
    return m_info.path();
}

/*!
 * The size of the file in bytes.
 *
 * \sa exists
 */
qint64 QchFileInfo::size() const {
    return m_info.size();
}

/*!
 * The suffix of the file.
 *
 * \sa fileName, completeSuffix, baseName, completeBaseName
 */
QString QchFileInfo::suffix() const {
    return m_info.suffix();
}

/*!
 * The complete suffix of the file.
 *
 * \sa fileName, suffix, baseName, completeBaseName
 */
QString QchFileInfo::completeSuffix() const {
    return m_info.completeSuffix();
}

/*!
 * The absolute path to the file or directory a symlink points to.
 *
 * \sa exists, isSymLink, idDir, isFile
 */
QString QchFileInfo::symLinkTarget() const {
    return m_info.symLinkTarget();
}

/*!
 * Converts the file's path to an absolute path if it is not already in that form.
 *
 * \sa filePath, relative
 */
void QchFileInfo::makeAbsolute() {
    if (!isAbsolute()) {
        m_info.makeAbsolute();
        emit fileChanged();
    }
}

/*!
 * Refreshes the information about the file.
 */
void QchFileInfo::refresh() {
    m_info.refresh();
    emit fileChanged();
}

QchScriptableFileInfo::QchScriptableFileInfo(QObject *parent) :
    QObject(parent)
{
}

QString QchScriptableFileInfo::absoluteFilePath() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->absoluteFilePath();
    }
}

QString QchScriptableFileInfo::absolutePath() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->absolutePath();
    }
}

QString QchScriptableFileInfo::baseName() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->baseName();
    }
}

QString QchScriptableFileInfo::completeBaseName() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->completeBaseName();
    }
}

bool QchScriptableFileInfo::caching() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->caching();
    }
}

void QchScriptableFileInfo::setCaching(bool enabled) {
    if (QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        info->setCaching(enabled);
    }
}

QString QchScriptableFileInfo::canonicalFilePath() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->canonicalFilePath();
    }
}

QString QchScriptableFileInfo::canonicalPath() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->canonicalPath();
    }
}

QDateTime QchScriptableFileInfo::created() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->created();
    }
}

QDateTime QchScriptableFileInfo::lastModified() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->lastModified();
    }
}

QDateTime QchScriptableFileInfo::lastRead() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->lastRead();
    }
}

bool QchScriptableFileInfo::exists() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->exists();
    }
}

QString QchScriptableFileInfo::file() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->absoluteFilePath();
    }
}

void QchScriptableFileInfo::setFile(const QString &name) {
    if (QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        info->setFile(name);
    }
}

QString QchScriptableFileInfo::fileName() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->fileName();
    }
}

QString QchScriptableFileInfo::filePath() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->filePath();
    }
}

QString QchScriptableFileInfo::group() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->group();
    }
}

uint QchScriptableFileInfo::groupId() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->groupId();
    }
}

bool QchScriptableFileInfo::isAbsolute() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isAbsolute();
    }
}

bool QchScriptableFileInfo::isDir() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isDir();
    }
}

bool QchScriptableFileInfo::isExecutable() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isExecutable();
    }
}

bool QchScriptableFileInfo::isFile() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isFile();
    }
}

bool QchScriptableFileInfo::isHidden() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isHidden();
    }
}

bool QchScriptableFileInfo::isReadable() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isReadable();
    }
}

bool QchScriptableFileInfo::isRelative() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isRelative();
    }
}

bool QchScriptableFileInfo::isRoot() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isRoot();
    }
}

bool QchScriptableFileInfo::isSymLink() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isSymLink();
    }
}

bool QchScriptableFileInfo::isWritable() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->isWritable();
    }
}

QString QchScriptableFileInfo::owner() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->owner();
    }
}

uint QchScriptableFileInfo::ownerId() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->ownerId();
    }
}

QString QchScriptableFileInfo::path() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->path();
    }
}

qint64 QchScriptableFileInfo::size() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->size();
    }
}

QString QchScriptableFileInfo::suffix() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->suffix();
    }
}

QString QchScriptableFileInfo::completeSuffix() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->completeSuffix();
    }
}

QString QchScriptableFileInfo::symLinkTarget() const {
    if (const QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        return info->symLinkTarget();
    }
}

void QchScriptableFileInfo::makeAbsolute() {
    if (QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        info->makeAbsolute();
    }
}

void QchScriptableFileInfo::refresh() {
    if (QFileInfo *info = qscriptvalue_cast<QFileInfo*>(thisObject())) {
        info->refresh();
    }
}


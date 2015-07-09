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

#include "qchdirectory.h"

QchDirectory::QchDirectory(QObject *parent) :
    QObject(parent)
{
}

QString QchDirectory::path() const {
    return m_dir.path();
}

void QchDirectory::setPath(const QString &path) {
    if (path != this->path()) {
        m_dir.setPath(path);
        emit pathChanged();
    }
}

QString QchDirectory::absolutePath() const {
    return m_dir.absolutePath();
}

QString QchDirectory::canonicalPath() const {
    return m_dir.canonicalPath();
}

uint QchDirectory::count() const {
    return m_dir.count();
}

QString QchDirectory::dirName() const {
    return m_dir.dirName();
}

bool QchDirectory::exists() const {
    return m_dir.exists();
}

QchDirectory::Filters QchDirectory::filter() const {
    return QchDirectory::Filters(int (m_dir.filter()));
}

void QchDirectory::setFilter(Filters filter) {
    m_dir.setFilter(QDir::Filters(int (filter)));
    emit filterChanged();
}

void QchDirectory::resetFilter() {
    if (m_dir.filter() != QDir::NoFilter) {
        m_dir.setFilter(QDir::NoFilter);
        emit filterChanged();
    }
}

bool QchDirectory::isAbsolute() const {
    return m_dir.isAbsolute();
}

bool QchDirectory::isReadable() const {
    return m_dir.isReadable();
}

bool QchDirectory::isRelative() const {
    return m_dir.isRelative();
}

bool QchDirectory::isRoot() const {
    return m_dir.isRoot();
}

QStringList QchDirectory::nameFilters() const {
    return m_dir.nameFilters();
}

void QchDirectory::setNameFilters(const QStringList &nameFilters) {
    m_dir.setNameFilters(nameFilters);
    emit nameFiltersChanged();
}

QchDirectory::SortFlags QchDirectory::sorting() const {
    return QchDirectory::SortFlags(int (m_dir.sorting()));
}

void QchDirectory::setSorting(SortFlags sorting) {
    m_dir.setSorting(QDir::SortFlags(int (sorting)));
    emit sortingChanged();
}

void QchDirectory::resetSorting() {
    if (m_dir.sorting() != QDir::NoSort) {
        m_dir.setSorting(QDir::NoSort);
        emit sortingChanged();
    }
}

bool QchDirectory::fileExists(const QString &fileName) const {
    return m_dir.exists(fileName);
}

QString QchDirectory::absoluteFilePath(const QString &fileName) const {
    return m_dir.absoluteFilePath(fileName);
}

QString QchDirectory::filePath(const QString &fileName) const {
    return m_dir.filePath(fileName);
}

QString QchDirectory::relativeFilePath(const QString &fileName) const {
    return m_dir.relativeFilePath(fileName);
}

bool QchDirectory::cd(const QString &dirName) {
    return m_dir.cd(dirName);
}

bool QchDirectory::cdUp() {
    return m_dir.cdUp();
}

QStringList QchDirectory::entryList() const {
    return m_dir.entryList(m_dir.nameFilters(), m_dir.filter(), m_dir.sorting());
}

bool QchDirectory::makeAbsolute() {
    return m_dir.makeAbsolute();
}

bool QchDirectory::mkdir(const QString &dirName) const {
    return m_dir.mkdir(dirName);
}

bool QchDirectory::mkpath(const QString &dirPath) const {
    return m_dir.mkpath(dirPath);
}

bool QchDirectory::remove(const QString &fileName) {
    return m_dir.remove(fileName);
}

bool QchDirectory::rename(const QString &oldName, const QString &newName) {
    return m_dir.rename(oldName, newName);
}

bool QchDirectory::rmdir(const QString &dirName) const {
    return m_dir.rmdir(dirName);
}

bool QchDirectory::rmpath(const QString &dirPath) const {
    return m_dir.rmpath(dirPath);
}

void QchDirectory::refresh() {
    m_dir.refresh();
    emit pathChanged();
}

QString QchDirectory::cleanPath(const QString &path) {
    return QDir::cleanPath(path);
}

QString QchDirectory::currentPath() {
    return QDir::currentPath();
}

void QchDirectory::setCurrentPath(const QString &path) {
    if (path != currentPath()) {
        if (QDir::setCurrent(path)) {
            emit currentPathChanged();
        }
    }
}

QString QchDirectory::homePath() {
    return QDir::homePath();
}

QString QchDirectory::rootPath() {
    return QDir::rootPath();
}

QString QchDirectory::tempPath() {
    return QDir::tempPath();
}

QString QchDirectory::fromNativeSeparators(const QString &pathName) {
    return QDir::fromNativeSeparators(pathName);
}

QString QchDirectory::toNativeSeparators(const QString &pathName) {
    return QDir::toNativeSeparators(pathName);
}

bool QchDirectory::match(const QString &filter, const QString &fileName) {
    return QDir::match(filter, fileName);
}

bool QchDirectory::match(const QStringList &filters, const QString &fileName) {
    return QDir::match(filters, fileName);
}

QStringList QchDirectory::searchPaths(const QString &prefix) {
    return QDir::searchPaths(prefix);
}

void QchDirectory::addSearchPath(const QString &prefix, const QString &path) {
    QDir::addSearchPath(prefix, path);
}

void QchDirectory::setSearchPaths(const QString &prefix, const QStringList &searchPaths) {
    QDir::setSearchPaths(prefix, searchPaths);
}

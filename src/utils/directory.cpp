#include "directory_p.h"

Directory::Directory(QObject *parent) :
    QObject(parent)
{
}

Directory::~Directory() {}

QString Directory::path() const {
    return m_dir.path();
}

void Directory::setPath(const QString &path) {
    if (path != this->path()) {
        m_dir.setPath(path);
        emit pathChanged();
    }
}

QString Directory::absolutePath() const {
    return m_dir.absolutePath();
}

QString Directory::canonicalPath() const {
    return m_dir.canonicalPath();
}

uint Directory::count() const {
    return m_dir.count();
}

QString Directory::dirName() const {
    return m_dir.dirName();
}

bool Directory::exists() const {
    return m_dir.exists();
}

Directory::Filters Directory::filter() const {
    return Directory::Filters(int (m_dir.filter()));
}

void Directory::setFilter(Filters filter) {
    m_dir.setFilter(QDir::Filters(int (filter)));
    emit filterChanged();
}

void Directory::resetFilter() {
    if (m_dir.filter() != QDir::NoFilter) {
        m_dir.setFilter(QDir::NoFilter);
        emit filterChanged();
    }
}

bool Directory::isAbsolute() const {
    return m_dir.isAbsolute();
}

bool Directory::isReadable() const {
    return m_dir.isReadable();
}

bool Directory::isRelative() const {
    return m_dir.isRelative();
}

bool Directory::isRoot() const {
    return m_dir.isRoot();
}

QStringList Directory::nameFilters() const {
    return m_dir.nameFilters();
}

void Directory::setNameFilters(const QStringList &nameFilters) {
    m_dir.setNameFilters(nameFilters);
    emit nameFiltersChanged();
}

Directory::SortFlags Directory::sorting() const {
    return Directory::SortFlags(int (m_dir.sorting()));
}

void Directory::setSorting(SortFlags sorting) {
    m_dir.setSorting(QDir::SortFlags(int (sorting)));
    emit sortingChanged();
}

void Directory::resetSorting() {
    if (m_dir.sorting() != QDir::NoSort) {
        m_dir.setSorting(QDir::NoSort);
        emit sortingChanged();
    }
}

bool Directory::fileExists(const QString &fileName) const {
    return m_dir.exists(fileName);
}

QString Directory::absoluteFilePath(const QString &fileName) const {
    return m_dir.absoluteFilePath(fileName);
}

QString Directory::filePath(const QString &fileName) const {
    return m_dir.filePath(fileName);
}

QString Directory::relativeFilePath(const QString &fileName) const {
    return m_dir.relativeFilePath(fileName);
}

bool Directory::cd(const QString &dirName) {
    return m_dir.cd(dirName);
}

bool Directory::cdUp() {
    return m_dir.cdUp();
}

QStringList Directory::entryList() const {
    return m_dir.entryList(m_dir.nameFilters(), m_dir.filter(), m_dir.sorting());
}

bool Directory::makeAbsolute() {
    return m_dir.makeAbsolute();
}

bool Directory::mkdir(const QString &dirName) const {
    return m_dir.mkdir(dirName);
}

bool Directory::mkpath(const QString &dirPath) const {
    return m_dir.mkpath(dirPath);
}

bool Directory::remove(const QString &fileName) {
    return m_dir.remove(fileName);
}

bool Directory::rename(const QString &oldName, const QString &newName) {
    return m_dir.rename(oldName, newName);
}

bool Directory::rmdir(const QString &dirName) const {
    return m_dir.rmdir(dirName);
}

bool Directory::rmpath(const QString &dirPath) const {
    return m_dir.rmpath(dirPath);
}

void Directory::refresh() {
    m_dir.refresh();
    emit pathChanged();
}

QString Directory::cleanPath(const QString &path) {
    return QDir::cleanPath(path);
}

QString Directory::currentPath() {
    return QDir::currentPath();
}

void Directory::setCurrentPath(const QString &path) {
    if (path != this->currentPath()) {
        if (QDir::setCurrent(path)) {
            emit currentPathChanged();
        }
    }
}

QString Directory::homePath() {
    return QDir::homePath();
}

QString Directory::rootPath() {
    return QDir::rootPath();
}

QString Directory::tempPath() {
    return QDir::tempPath();
}

QString Directory::fromNativeSeparators(const QString &pathName) {
    return QDir::fromNativeSeparators(pathName);
}

QString Directory::toNativeSeparators(const QString &pathName) {
    return QDir::toNativeSeparators(pathName);
}

bool Directory::match(const QString &filter, const QString &fileName) {
    return QDir::match(filter, fileName);
}

bool Directory::match(const QStringList &filters, const QString &fileName) {
    return QDir::match(filters, fileName);
}

QStringList Directory::searchPaths(const QString &prefix) {
    return QDir::searchPaths(prefix);
}

void Directory::addSearchPath(const QString &prefix, const QString &path) {
    QDir::addSearchPath(prefix, path);
}

void Directory::setSearchPaths(const QString &prefix, const QStringList &searchPaths) {
    QDir::setSearchPaths(prefix, searchPaths);
}

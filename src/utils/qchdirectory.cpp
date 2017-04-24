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

#include "qchdirectory.h"

/*!
    \class Directory
    \brief Provides access to directory structures and their contents.
    
    \ingroup utils
    
    A Directory is used to manipulate path names, access information regarding paths and files, and manipulate 
    the underlying file system. It can also be used to access Qt's resource system.

    A Directory can point to a file using either a relative or an absolute path. Absolute paths begin with the 
    directory separator.
    
    Relative file names begin with a directory name or a file name and specify a path relative to the current directory.
    
    \include directory.qml
*/
QchDirectory::QchDirectory(QObject *parent) :
    QObject(parent)
{
    m_dir.setFilter(QDir::AllEntries);
}

/*!
    \brief The path of the directory.
*/
QString QchDirectory::path() const {
    return m_dir.path();
}

void QchDirectory::setPath(const QString &path) {
    if (path != this->path()) {
        m_dir.setPath(path);
        emit pathChanged();
    }
}

/*!
    \brief The absolute path of the directory.
*/
QString QchDirectory::absolutePath() const {
    return m_dir.absolutePath();
}

/*!
    \brief The canonical path of the directory.
*/
QString QchDirectory::canonicalPath() const {
    return m_dir.canonicalPath();
}

/*!
    \brief The number of results in the directory.
*/
uint QchDirectory::count() const {
    return m_dir.count();
}

/*!
    \brief The name of the directory.
*/
QString QchDirectory::dirName() const {
    return m_dir.dirName();
}

/*!
    \brief Whether the directory exists.
*/
bool QchDirectory::exists() const {
    return m_dir.exists();
}

/*!
    \brief The filter used by entryList().
    
    The value of this property is a bitwise OR combination of the following:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Directory.Dirs</td>
            <td>List directories that match the filters.</td>
        </tr>
        <tr>
            <td>Directory.AllDirs</td>
            <td>List all directories; i.e. don't apply the filters to directory names.</td>
        </tr>
        <tr>
            <td>Directory.Files</td>
            <td>List files.</td>
        </tr>
        <tr>
            <td>Directory.NoSymLinks</td>
            <td>Do not list symbolic links.</td>
        </tr>
        <tr>
            <td>Directory.NoDotAndDotDot</td>
            <td>Do not list the special entries "." and "..".</td>
        </tr>
        <tr>
            <td>Directory.NoDot</td>
            <td>Do not list the special entry ".".</td>
        </tr>
        <tr>
            <td>Directory.NoDotDot</td>
            <td>Do not list the special entry "..".</td>
        </tr>
        <tr>
            <td>Directory.AllEntries</td>
            <td>List directories, files, drives and symlinks (this does not list broken symlinks unless you specify 
            System).</td>
        </tr>
        <tr>
            <td>Directory.Readable</td>
            <td>List files for which the application has read access.</td>
        </tr>
        <tr>
            <td>Directory.Writable</td>
            <td>List files for which the application has write access.</td>
        </tr>
        <tr>
            <td>Directory.Executable</td>
            <td>List files for which the application has execute access.</td>
        </tr>
        <tr>
            <td>Directory.Hidden</td>
            <td>List hidden files.</td>
        </tr>
        <tr>
            <td>Directory.System</td>
            <td>List system files.</td>
        </tr>
        <tr>
            <td>Directory.CaseSensitive</td>
            <td>The filter should be case sensitive.</td>
        </tr>
    </table>
*/
QchDirectory::Filters QchDirectory::filter() const {
    return QchDirectory::Filters(int (m_dir.filter()));
}

void QchDirectory::setFilter(Filters filter) {
    m_dir.setFilter(QDir::Filters(int (filter)));
    emit filterChanged();
}

void QchDirectory::resetFilter() {
    m_dir.setFilter(QDir::AllEntries);
    emit filterChanged();
}

/*!
    \property bool Directory::absolute
    \brief Whether the directory's path is absolute.
*/
bool QchDirectory::isAbsolute() const {
    return m_dir.isAbsolute();
}

/*!
    \property bool Directory::readable
    \brief Whether the directory is readable.
*/
bool QchDirectory::isReadable() const {
    return m_dir.isReadable();
}

bool QchDirectory::isRelative() const {
    return m_dir.isRelative();
}

/*!
    \property bool Directory::root
    \brief Whether the directory's path is the root path.
*/
bool QchDirectory::isRoot() const {
    return m_dir.isRoot();
}

/*!
    \property stringlist Directory::nameFilters
    \brief The name filters used by entryList().
    
    The name filters are a list of wildcards, e.g:
    
    /code
    nameFilters: [ "*.jpg", "*.jpeg", "*.png", "*.svg" ]
    /endcode
*/
QStringList QchDirectory::nameFilters() const {
    return m_dir.nameFilters();
}

void QchDirectory::setNameFilters(const QStringList &nameFilters) {
    m_dir.setNameFilters(nameFilters);
    emit nameFiltersChanged();
}

/*!
    \property flags Directory::sorting
    \brief The sorting used by entryList().
    
    The value of this property is a bitwise OR combination of the following:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Directory.Name</td>
            <td>Sort by name.</td>
        </tr>
        <tr>
            <td>Directory.Time</td>
            <td>Sort by modification time.</td>
        </tr>
        <tr>
            <td>Directory.Size</td>
            <td>Sort by file size.</td>
        </tr>
        <tr>
            <td>Directory.Type</td>
            <td>Sort by file extension.</td>
        </tr>
        <tr>
            <td>Directory.NoDotAndDotDot</td>
            <td>Do not list the special entries "." and "..".</td>
        </tr>
        <tr>
            <td>Directory.Unsorted</td>
            <td>Do not sort.</td>
        </tr>
        <tr>
            <td>Directory.NoSort</td>
            <td>Not sorted by default.</td>
        </tr>
        <tr>
            <td>Directory.DirsFirst</td>
            <td>Put directories first, then the files.</td>
        </tr>
        <tr>
            <td>Directory.DirsLast</td>
            <td>Put files first, then the directories.</td>
        </tr>
        <tr>
            <td>Directory.Reversed</td>
            <td>Reverse the sort order.</td>
        </tr>
        <tr>
            <td>Directory.IgnoreCase</td>
            <td>Sort case-insensitively.</td>
        </tr>
        <tr>
            <td>Directory.LocalAware</td>
            <td>Sort items appropriately using the current locale settings.</td>
        </tr>
    </table>
*/
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

/*!
    Returns true if the file called \a fileName exists; otherwise returns false.

    Unless \a fileName contains an absolute file path, the file name is assumed to be relative to the directory itself, 
    so this function is typically used to check for the presence of files within a directory.
*/
bool QchDirectory::fileExists(const QString &fileName) const {
    return m_dir.exists(fileName);
}

/*!
    Returns the absolute path name of a file in the directory. Does \e not check if the file actually exists in the 
    directory. Redundant multiple separators or "." and ".." directories in \a fileName are not removed 
    (see cleanPath()).

    \sa relativeFilePath(), filePath(), canonicalPath()
*/
QString QchDirectory::absoluteFilePath(const QString &fileName) const {
    return m_dir.absoluteFilePath(fileName);
}

/*!
    Returns the path name of a file in the directory. Does \e not check if the file actually exists in the directory. 
    If the Directory is relative the returned path name will also be relative. Redundant multiple separators or "." 
    and ".." directories in \a fileName are not removed (see cleanPath()).

    \sa dirName, absoluteFilePath(), relative, canonicalPath()
*/
QString QchDirectory::filePath(const QString &fileName) const {
    return m_dir.filePath(fileName);
}

/*!
    Returns the path to \a fileName relative to the directory.

    \sa absoluteFilePath(), filePath(), canonicalPath()
*/
QString QchDirectory::relativeFilePath(const QString &fileName) const {
    return m_dir.relativeFilePath(fileName);
}

/*!
    Changes the Directory's directory to \a dirName.

    Returns true if the new directory exists and is readable; otherwise returns false. Note that the logical cd() 
    operation is not performed if the new directory does not exist.

    Calling cd("..") is equivalent to calling cdUp().

    \sa cdUp(), readable, exists, path
*/
bool QchDirectory::cd(const QString &dirName) {
    return m_dir.cd(dirName);
}

/*!
    Changes directory by moving one directory up from the Directory's current directory.

    Returns true if the new directory exists and is readable; otherwise returns false. Note that the logical cdUp() 
    operation is not performed if the new directory does not exist.

    \sa cd(), readable, exists, path
*/
bool QchDirectory::cdUp() {
    return m_dir.cdUp();
}

/*!
    Returns a list of the names of all the files and directories in the directory, ordered according to 
    \link filter\endlink and \link nameFilters\endlink, and sorted according to \link sorting\endlink.
        
    Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

    \sa nameFilters, sorting, filter
*/
QStringList QchDirectory::entryList() const {
    return m_dir.entryList(m_dir.nameFilters(), m_dir.filter(), m_dir.sorting());    
}

static void staticRecursiveEntryList(QDir &dir, QStringList &names, bool includeDirectories) {
    foreach (const QFileInfo &info, dir.entryInfoList(dir.nameFilters(), dir.filter(), dir.sorting())) {
        const QString path = info.absoluteFilePath();
        
        if (info.isDir()) {
            if (includeDirectories) {
                names << path;
            }
            
            dir.setPath(path);
            staticRecursiveEntryList(dir, names, includeDirectories);
        }
        else {
            names << path;
        }
    }
}

/*!
    Returns a list of the absolute paths of all the files and directories in the directory and its subdirectories,
    ordered according to \link filter\endlink and \link nameFilters\endlink, and sorted according to
    \link sorting\endlink.
        
    Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

    \sa nameFilters, sorting, filter
*/
QStringList QchDirectory::recursiveEntryList() const {
    QStringList names;
    QDir dir(m_dir);
    dir.setFilter(dir.filter() | QDir::Dirs | QDir::NoDotAndDotDot);
    staticRecursiveEntryList(dir, names, m_dir.filter().testFlag(QDir::Dirs));
    return names;
}

/*!
    Returns a list of FileInfo of all the files and directories in the directory, ordered according to 
    \link filter\endlink and \link nameFilters\endlink, and sorted according to \link sorting\endlink.
        
    Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

    \sa nameFilters, sorting, filter
*/
QFileInfoList QchDirectory::entryInfoList() const {
    return m_dir.entryInfoList(m_dir.nameFilters(), m_dir.filter(), m_dir.sorting());
}

static void staticRecursiveEntryInfoList(QDir &dir, QFileInfoList &infos, bool includeDirectories) {
    foreach (const QFileInfo &info, dir.entryInfoList(dir.nameFilters(), dir.filter(), dir.sorting())) {
        if (info.isDir()) {
            if (includeDirectories) {
                infos << info;
            }
            
            dir.setPath(info.absoluteFilePath());
            staticRecursiveEntryInfoList(dir, infos, includeDirectories);
        }
        else {
            infos << info;
        }
    }
}

/*!
    Returns a list of FileInfo of all the files and directories in the directory and its subdirectories,
    ordered according to \link filter\endlink and \link nameFilters\endlink, and sorted according to
    \link sorting\endlink.
        
    Returns an empty list if the directory is unreadable, does not exist, or if nothing matches the specification.

    \sa nameFilters, sorting, filter
*/
QFileInfoList QchDirectory::recursiveEntryInfoList() const {
    QFileInfoList infos;
    QDir dir(m_dir);
    dir.setFilter(dir.filter() | QDir::Dirs | QDir::NoDotAndDotDot);
    staticRecursiveEntryInfoList(dir, infos, m_dir.filter().testFlag(QDir::Dirs));
    return infos;
}
/*!
    Converts the directory path to an absolute path. If it is already absolute nothing happens. Returns true if the 
    conversion succeeded; otherwise returns false.

    \sa absolute, relative, cleanPath()
*/
bool QchDirectory::makeAbsolute() {
    return m_dir.makeAbsolute();
}

/*!
    Creates a sub-directory called \a dirName.

    Returns true on success; otherwise returns false.

    If the directory already exists when this function is called, it will return false.

    \sa rmdir()
*/
bool QchDirectory::mkdir(const QString &dirName) const {
    return m_dir.mkdir(dirName);
}

/*!
    Creates the directory path \a dirPath.

    The function will create all parent directories necessary to create the directory.

    Returns true if successful; otherwise returns false.

    If the path already exists when this function is called, it will return true.

    \sa rmpath()
*/
bool QchDirectory::mkpath(const QString &dirPath) const {
    return m_dir.mkpath(dirPath);
}

/*!
    Removes the file, \a fileName.

    Returns true if the file is removed successfully; otherwise returns false.
*/
bool QchDirectory::remove(const QString &fileName) {
    return m_dir.remove(fileName);
}

static bool staticRemoveRecursively(QDir &dir) {
    bool ok = false;
    
    foreach (const QFileInfo &info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden
                                                      | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
        if (info.isDir()) {
            dir.setPath(info.absoluteFilePath());
            ok = staticRemoveRecursively(dir);
        }
        else {
            ok = QFile::remove(info.absoluteFilePath());
        }
        
        if (!ok) {
            return ok;
        }
    }
    
    ok = dir.rmdir(dir.path());
    return ok;
}

/*!
    Removes the directory, including all its contents.
    
    Returns \c true if successful, otherwise \c false.
*/
bool QchDirectory::removeRecursively() {
#if QT_VERSION >= 0x050000
    return m_dir.removeRecursively();
#else
    QDir dir(m_dir);
    return staticRemoveRecursively(dir);
#endif
}

/*!
    Renames a file or directory from \a oldName to \a newName, and returns true if successful; otherwise returns false.

    On most file systems, rename() fails only if \a oldName does not exist, if \a newName and \a oldName are not on the 
    same partition or if a file with the new name already exists. However, there are also other reasons why rename() can
    fail. For example, on at least one file system rename() fails if \a newName points to an open file.
*/
bool QchDirectory::rename(const QString &oldName, const QString &newName) {
    return m_dir.rename(oldName, newName);
}

/*!
    Removes the directory specified by \a dirName.

    The directory must be empty for rmdir() to succeed.

    Returns true if successful; otherwise returns false.

    \sa mkdir()
*/
bool QchDirectory::rmdir(const QString &dirName) const {
    return m_dir.rmdir(dirName);
}

/*!
    Removes the directory path \a dirPath.

    The function will remove all parent directories in \a dirPath, provided that they are empty. This is the opposite of
    mkpath(dirPath).

    Returns true if successful; otherwise returns false.

    \sa mkpath()
*/
bool QchDirectory::rmpath(const QString &dirPath) const {
    return m_dir.rmpath(dirPath);
}

/*!
    Refreshes the directory information.
*/
void QchDirectory::refresh() {
    m_dir.refresh();
    emit pathChanged();
}

/*!
    Removes all multiple directory separators "/" and resolves any "."s or ".."s found in the path, \a path.

    Symbolic links are kept. This function does not return the canonical path, but rather the simplest version of the 
    input. For example, "./local" becomes "local", "local/../bin" becomes "bin" and "/local/usr/../bin" becomes 
    "/local/bin".

    \sa absolutePath(), canonicalPath()
*/
QString QchDirectory::cleanPath(const QString &path) {
    return QDir::cleanPath(path);
}

/*!
    \brief The current path of the directory.
*/
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

/*!
    \brief The home path of the system.
*/
QString QchDirectory::homePath() {
    return QDir::homePath();
}

/*!
    \brief The root path of the system.
*/
QString QchDirectory::rootPath() {
    return QDir::rootPath();
}

/*!
    \brief The temp path of the system.
*/
QString QchDirectory::tempPath() {
    return QDir::tempPath();
}

QString QchDirectory::fromNativeSeparators(const QString &pathName) {
    return QDir::fromNativeSeparators(pathName);
}

QString QchDirectory::toNativeSeparators(const QString &pathName) {
    return QDir::toNativeSeparators(pathName);
}


/*!
    Returns true if the \a fileName matches the wildcard (glob) pattern \a filter; otherwise returns false. The \a 
    filter may contain multiple patterns separated by spaces or semicolons. The matching is case insensitive.

    \sa entryList()
*/
bool QchDirectory::match(const QString &filter, const QString &fileName) {
    return QDir::match(filter, fileName);
}

/*!
    \overload

    Returns true if the \a fileName matches any of the wildcard (glob) patterns in the list of \a filters; otherwise 
    returns false. The matching is case insensitive.

    \sa entryList()
*/
bool QchDirectory::match(const QStringList &filters, const QString &fileName) {
    return QDir::match(filters, fileName);
}

/*!
    Returns the search paths for \a prefix.

    \sa setSearchPaths(), addSearchPath()
*/
QStringList QchDirectory::searchPaths(const QString &prefix) {
    return QDir::searchPaths(prefix);
}

/*!
    Adds \a path to the search path for \a prefix.

    \sa setSearchPaths()
*/
void QchDirectory::addSearchPath(const QString &prefix, const QString &path) {
    QDir::addSearchPath(prefix, path);
}

/*!
    Sets or replaces Qt's search paths for file names with the prefix \a prefix to \a searchPaths.

    To specify a prefix for a file name, prepend the prefix followed by a single colon (e.g., "images:undo.png", 
    "xmldocs:books.xml"). \a prefix can only contain letters or numbers (e.g., it cannot contain a colon, nor a slash).

    Qt uses this search path to locate files with a known prefix. The search path entries are tested in order, starting 
    with the first entry.

    Search paths may contain paths to Qt Resource System.
*/
void QchDirectory::setSearchPaths(const QString &prefix, const QStringList &searchPaths) {
    QDir::setSearchPaths(prefix, searchPaths);
}

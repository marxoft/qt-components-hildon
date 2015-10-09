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

#include "qchfile.h"

/*!
    \class File
    \brief Provides an interface for reading from and writing to files.
    
    \ingroup utils
    
    File provides a subset of the C++ QFile API.
    
    \include file.qml
    
    \sa Directory
*/
QchFile::QchFile(QObject *parent) :
    QObject(parent)
{
}

/*
    \brief Whether the end of the file has been reached.
*/
bool QchFile::atEnd() const {
    return m_file.atEnd();
}

/*!
    \brief A description of the last error that occurred.
*/
QString QchFile::errorString() const {
    return m_file.errorString();
}

/*!
    \brief Whether the file specified by fileName exists.
*/
bool QchFile::exists() const {
    return m_file.exists();
}

/*!
    \brief The file name.
*/
QString QchFile::fileName() const {
    return m_file.fileName();
}

void QchFile::setFileName(const QString &name) {
    if (name != m_file.fileName()) {
        m_file.setFileName(name);
        emit existsChanged();
        emit fileNameChanged();
        emit permissionsChanged();
        emit sizeChanged();
    }
}

/*!
    \brief Whether the file is open.
    
    The default value is \c false.
    
    \sa close(), open()
*/
bool QchFile::isOpen() const {
    return m_file.isOpen();
}

/*!
    \brief The mode used to open the file.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>File.NotOpen</td>
            <td>The file is not open (default).</td>
        </tr>
        <tr>
            <td>File.ReadOnly</td>
            <td>The file is open for reading.</td>
        </tr>
        <tr>
            <td>File.WriteOnly</td>
            <td>The file is open for writing</td>
        </tr>
        <tr>
            <td>File.ReadWrite</td>
            <td>The file is open for reading and writing.</td>
        </tr>
        <tr>
            <td>File.Append</td>
            <td>The file is opened in append mode, so that all data is written to the end of the file.</td>
        </tr>
        <tr>
            <td>File.Truncate</td>
            <td>If possible, the file is truncated before it is opened.</td>
        </tr>
        <tr>
            <td>File.Text</td>
            <td>The end-of-line terminators are translated to '\\n'.</td>
        </tr>
        <tr>
            <td>File.Unbuffered</td>
            <td>Any buffer is bypassed.</td>
        </tr>
    </table>
    
    \sa isOpen, open()
*/  
QchFile::OpenMode QchFile::openMode() const {
    return QchFile::OpenMode(int (m_file.openMode()));
}

/*!
    \brief The complete OR-ed together combination of File.Permission for the file.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>File.ReadOwner</td>
            <td>The file is readable by the owner of the file.</td>
        </tr>
        <tr>
            <td>File.WriteOwner</td>
            <td>The file is writable by the owner of the file.</td>
        </tr>
        <tr>
            <td>File.ExeOwner</td>
            <td>The file is executable by the owner of the file.</td>
        </tr>
        <tr>
            <td>File.ReadUser</td>
            <td>The file is readable by the user.</td>
        </tr>
        <tr>
            <td>File.WriteUser</td>
            <td>The file is writable by the user.</td>
        </tr>
        <tr>
            <td>File.ExeUser</td>
            <td>The file is executable by the user.</td>
        </tr>
        <tr>
            <td>File.ReadGroup</td>
            <td>The file is readable by the group.</td>
        </tr>
        <tr>
            <td>File.WriteGroup</td>
            <td>The file is writable by the group.</td>
        </tr>
        <tr>
            <td>File.ExeGroup</td>
            <td>The file is executable by the group.</td>
        </tr>
        <tr>
            <td>File.ReadOther</td>
            <td>The file is readable by anyone.</td>
        </tr>
        <tr>
            <td>File.WriteOther</td>
            <td>The file is writable by anyone.</td>
        </tr>
        <tr>
            <td>File.ExeOther</td>
            <td>The file is executable by anyone.</td>
        </tr>
    </table>
*/
QchFile::Permissions QchFile::permissions() const {
    return QchFile::Permissions(int (m_file.permissions()));
}

void QchFile::setPermissions(QchFile::Permissions p) {
    m_file.setPermissions(QFile::Permissions(int (p)));
    emit permissionsChanged();
}

/*!
    \brief The current position in bytes.
*/
qint64 QchFile::pos() const {
    return m_file.pos();
}

/*!
    \brief The size of the file in bytes.
*/
qint64 QchFile::size() const {
    return m_file.size();
}

/*!
    \brief Closes the file.
    
    \sa isOpen, openMode, open()
*/
void QchFile::close() {
    if (m_file.isOpen()) {
        m_file.close();
        emit isOpenChanged();
    }
}

/*!
    \brief Opens the file using \a mode.
    
    \sa isOpen, openMode
*/
bool QchFile::open(int mode) {
    if (!m_file.open(QFile::OpenMode(mode))) {
        emit error();
        return false;
    }
    
    emit isOpenChanged();
    emit openModeChanged();
    return true;
}

/*!
    \brief Reads \a maxSize bytes from the file and returns the data.
    
    \sa readAll(), readLine()
*/
QByteArray QchFile::read(qint64 maxSize) {
    QByteArray ba = m_file.read(maxSize);
    
    if (ba.isEmpty()) {
        emit error();
    }
    else {
        emit posChanged();
    }
    
    return ba;
}

/*!
    \brief Reads all bytes from the file and returns the data.
    
    \sa read(), readLine()
*/
QByteArray QchFile::readAll() {
    QByteArray ba = m_file.readAll();
    
    if (ba.isEmpty()) {
        emit error();
    }
    else {
        emit posChanged();
    }
    
    return ba;
}

/*!
    \brief Reads \a maxSize bytes from the current line of the file and returns the data.
    
    \sa read(), readAll()
*/
QByteArray QchFile::readLine(qint64 maxSize) {
    QByteArray ba = m_file.readLine(maxSize);
    
    if (ba.isEmpty()) {
        emit error();
    }
    else {
        emit posChanged();
    }
    
    return ba;
}

/*!
    \brief Removes the file from the file system.
    
    Returns \c true if successful.
*/
bool QchFile::remove() {
    if (!m_file.remove()) {
        emit error();
        return false;
    }
    
    return true;
}

/*!
    \brief Renames the file to \a newName.
    
    Returns \c true if successful.
    
    \sa fileName
*/
bool QchFile::rename(const QString &newName) {
    if (!m_file.rename(newName)) {
        emit error();
        return false;
    }
    
    return true;
}

bool QchFile::resize(qint64 newSize) {
    if (!m_file.resize(newSize)) {
        emit error();
        return false;
    }
    
    emit posChanged();
    emit sizeChanged();
    return true;
}

bool QchFile::seek(qint64 pos) {
    if (!m_file.seek(pos)) {
        emit error();
        return false;
    }
    
    emit posChanged();
    return true;
}

/*!
    \brief Writes \a byteArray to the file and returns the number of bytes written.
*/
qint64 QchFile::write(const QByteArray &byteArray) {
    qint64 bytes = m_file.write(byteArray);
    
    if (bytes > 0) {
        emit posChanged();
    }
    else {
        emit error();
    }
    
    return bytes;
}

/*!
    \fn File::error()
    \brief Emitted when an error occurs.
    
    \sa errorString
*/

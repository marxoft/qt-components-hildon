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

#ifndef QCHFILE_H
#define QCHFILE_H

#include <QFile>
#include <qdeclarative.h>

class QchFile : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(bool atEnd READ atEnd NOTIFY posChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY error)
    Q_PROPERTY(bool exists READ exists NOTIFY existsChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(OpenMode openMode READ openMode NOTIFY openModeChanged)
    Q_PROPERTY(Permissions permissions READ permissions WRITE setPermissions NOTIFY permissionsChanged)
    Q_PROPERTY(qint64 pos READ pos WRITE seek NOTIFY posChanged)
    Q_PROPERTY(qint64 size READ size WRITE resize NOTIFY sizeChanged)
    
    Q_ENUMS(OpenModeFlag Permission)
    
public:
    enum OpenModeFlag {
        NotOpen = QFile::NotOpen,
        ReadOnly = QFile::ReadOnly,
        WriteOnly = QFile::WriteOnly,
        ReadWrite = QFile::ReadWrite,
        Append = QFile::Append,
        Truncate = QFile::Truncate,
        Text = QFile::Text,
        Unbuffered = QFile::Unbuffered
    };
    
    enum Permission {
        ReadOwner = QFile::ReadOwner,
        WriteOwner = QFile::WriteOwner,
        ExeOwner = QFile::ExeOwner,
        ReadUser = QFile::ReadUser,
        WriteUser = QFile::WriteUser,
        ExeUser = QFile::ExeUser,
        ReadGroup = QFile::ReadGroup,
        WriteGroup = QFile::WriteGroup,
        ExeGroup = QFile::ExeGroup,
        ReadOther = QFile::ReadOther,
        WriteOther = QFile::WriteOther,
        ExeOther = QFile::ExeOther
    };
    
    Q_DECLARE_FLAGS(OpenMode, OpenModeFlag)
    Q_DECLARE_FLAGS(Permissions, Permission)
    
    explicit QchFile(QObject *parent = 0);
        
    bool atEnd() const;
    
    QString errorString() const;
    
    bool exists() const;
    
    QString fileName() const;
    void setFileName(const QString &name);
    
    bool isOpen() const;
    
    OpenMode openMode() const;
    
    Permissions permissions() const;
    void setPermissions(Permissions p);
    
    qint64 pos() const;
    
    qint64 size() const;

public Q_SLOTS:
    void close();
    bool open(int mode);
    
    QByteArray read(qint64 maxSize);
    QByteArray readAll();
    QByteArray readLine(qint64 maxSize = 0);
    
    bool remove();
    bool rename(const QString &newName);
    
    bool resize(qint64 newSize);
    bool seek(qint64 pos);
    
    qint64 write(const QByteArray &byteArray);

Q_SIGNALS:
    void error();
    void existsChanged();
    void fileNameChanged();
    void isOpenChanged();
    void openModeChanged();
    void permissionsChanged();
    void posChanged();
    void sizeChanged();

private:
    QFile m_file;
    
    Q_DISABLE_COPY(QchFile)
};

QML_DECLARE_TYPE(QchFile)

Q_DECLARE_OPERATORS_FOR_FLAGS(QchFile::OpenMode)
Q_DECLARE_OPERATORS_FOR_FLAGS(QchFile::Permissions)
    
#endif // QCHFILE_H

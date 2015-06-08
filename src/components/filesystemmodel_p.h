/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FILESYSTEMMODEL_P_H
#define FILESYSTEMMODEL_P_H

#include "modelindex_p.h"
#include <QSortFilterProxyModel>
#include <qdeclarative.h>

class FileSystemModelPrivate;

class FileSystemModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QString filterPath READ filterPath WRITE setFilterPath NOTIFY filterPathChanged)
    Q_PROPERTY(bool showDirs READ showDirs WRITE setShowDirs NOTIFY dirFilterChanged)
    Q_PROPERTY(bool showFiles READ showFiles WRITE setShowFiles NOTIFY dirFilterChanged)
    Q_PROPERTY(bool showHidden READ showHidden WRITE setShowHidden NOTIFY dirFilterChanged)
    Q_PROPERTY(bool showDotAndDotDot READ showDotAndDotDot WRITE setShowDotAndDotDot NOTIFY dirFilterChanged)
    Q_PROPERTY(bool showSymlinks READ showSymlinks WRITE setShowSymlinks NOTIFY dirFilterChanged)
    Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks NOTIFY resolveSymlinksChanged)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly NOTIFY readOnlyChanged)
    Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables NOTIFY nameFilterDisablesChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    Q_PROPERTY(QStringList loadedDirectories READ loadedDirectories NOTIFY directoryLoaded)

    Q_ENUMS(Roles)

public:
    enum Roles {
        FileIconRole = Qt::DecorationRole,
        FilePathRole = Qt::UserRole + 1,
        FileNameRole = Qt::UserRole + 2,
        FilePermissionsRole = Qt::UserRole + 3,
        IsDirRole = Qt::UserRole + 4,
        SizeRole = Qt::UserRole + 5,
        TypeRole = Qt::UserRole + 6,
        LastModifiedRole = Qt::UserRole + 7
    };

    explicit FileSystemModel(QObject *parent = 0);
    ~FileSystemModel();

    QString rootPath() const;
    void setRootPath(const QString &path);

    QString filterPath() const;
    void setFilterPath(const QString &path);

    bool showDirs() const;
    void setShowDirs(bool show);

    bool showFiles() const;
    void setShowFiles(bool show);

    bool showHidden() const;
    void setShowHidden(bool show);

    bool showDotAndDotDot() const;
    void setShowDotAndDotDot(bool show);

    bool showSymlinks() const;
    void setShowSymlinks(bool show);

    bool resolveSymlinks() const;
    void setResolveSymlinks(bool resolve);

    bool isReadOnly() const;
    void setReadOnly(bool ro);

    bool nameFilterDisables() const;
    void setNameFilterDisables(bool disables);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &filters);

    QStringList loadedDirectories() const;

    Q_INVOKABLE bool directoryIsLoaded(const QString &directory) const;

    Q_INVOKABLE int count(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = FileNameRole) const;

    Q_INVOKABLE QVariant modelIndex(const QString &path, int column = 0) const;

    Q_INVOKABLE QString filePath(const QModelIndex &index) const;
    Q_INVOKABLE bool isDir(const QModelIndex &index) const;
    Q_INVOKABLE qint64 size(const QModelIndex &index) const;
    Q_INVOKABLE QString type(const QModelIndex &index) const;
    Q_INVOKABLE QDateTime lastModified(const QModelIndex &index) const;

    Q_INVOKABLE QVariant mkdir(const QModelIndex &parent, const QString &name);
    Q_INVOKABLE bool rmdir(const QModelIndex &index) const;
    Q_INVOKABLE QString fileName(const QModelIndex &index) const;
    Q_INVOKABLE QString fileIcon(const QModelIndex &index) const;
    Q_INVOKABLE bool remove(const QModelIndex &index) const;

signals:
    void rootPathChanged();
    void filterPathChanged();
    void directoryLoaded(const QString &directory);
    void resolveSymlinksChanged();
    void readOnlyChanged();
    void nameFilterDisablesChanged();
    void nameFiltersChanged();
    void dirFilterChanged();

protected:
    FileSystemModel(FileSystemModelPrivate &dd, QObject *parent = 0);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    QScopedPointer<FileSystemModelPrivate> d_ptr;

    Q_DECLARE_PRIVATE(FileSystemModel)

    Q_PRIVATE_SLOT(d_func(), void _q_onDirectoryLoaded(QString))

private:
    Q_DISABLE_COPY(FileSystemModel)
};

QML_DECLARE_TYPE(FileSystemModel)

#endif // FILESYSTEMMODEL_P_H

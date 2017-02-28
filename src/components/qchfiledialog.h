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

#ifndef QCHFILEDIALOG_H
#define QCHFILEDIALOG_H

#include "qchdialogstatus.h"
#include <qdeclarative.h>

class QchFileDialogPrivate;

class QchFileDialog : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString filePath READ filePath NOTIFY accepted)
    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    Q_PROPERTY(bool selectFolder READ selectFolder WRITE setSelectFolder NOTIFY selectFolderChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)

public:
    explicit QchFileDialog(QObject *parent = 0);
    ~QchFileDialog();
    
    QString filePath() const;
    
    QString folder() const;
    void setFolder(const QString &f);
    
    QStringList nameFilters() const;
    void setNameFilters(const QStringList &f);
    
    bool selectFolder() const;
    void setSelectFolder(bool s);
    
    QchDialogStatus::Status status() const;

public Q_SLOTS:
    void open();

Q_SIGNALS:
    void accepted();
    void folderChanged();
    void nameFiltersChanged();
    void rejected();
    void selectFolderChanged();
    void statusChanged();

protected:
    QScopedPointer<QchFileDialogPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchFileDialog)

private:
    Q_DISABLE_COPY(QchFileDialog)
};

QML_DECLARE_TYPE(QchFileDialog)

#endif // QCHFILEDIALOG_H

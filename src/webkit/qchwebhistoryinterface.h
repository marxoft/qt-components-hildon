/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QCHWEBHISTORYINTERFACE_H
#define QCHWEBHISTORYINTERFACE_H

#include <QWebHistoryInterface>
#include <qdeclarative.h>
#include <QStringList>

class QchWebHistoryInterface : public QWebHistoryInterface
{
    Q_OBJECT

    Q_PROPERTY(QStringList urls READ urls NOTIFY urlsChanged)
    Q_PROPERTY(int count READ count NOTIFY urlsChanged)
    Q_PROPERTY(QString storageFileName READ storageFileName WRITE setStorageFileName NOTIFY storageFileNameChanged)

public:
    explicit QchWebHistoryInterface(QObject *parent = 0);
    
    void addHistoryEntry(const QString &url);

    bool historyContains(const QString &url) const;

    QStringList urls() const;

    int count() const;

    QString storageFileName() const;
    void setStorageFileName(const QString &fileName);

public Q_SLOTS:
    bool save();
    bool load();
    void clear();

Q_SIGNALS:
    void urlsChanged();
    void storageFileNameChanged();

private:
    QStringList m_urls;

    QString m_fileName;
};

QML_DECLARE_TYPE(QchWebHistoryInterface)

#endif // QCHWEBHISTORYINTERFACE_H

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

#ifndef WEBHISTORYINTERFACE_P_H
#define WEBHISTORYINTERFACE_P_H

#include <QWebHistoryInterface>
#include <qdeclarative.h>
#include <QStringList>

class WebHistoryInterface : public QWebHistoryInterface
{
    Q_OBJECT

    Q_PROPERTY(QStringList urls READ urls NOTIFY urlsChanged)
    Q_PROPERTY(int count READ count NOTIFY urlsChanged)
    Q_PROPERTY(QString storageFileName READ storageFileName WRITE setStorageFileName NOTIFY storageFileNameChanged)

public:
    explicit WebHistoryInterface(QObject *parent = 0);
    ~WebHistoryInterface();

    void addHistoryEntry(const QString &url);

    bool historyContains(const QString &url) const;

    QStringList urls() const;

    int count() const;

    QString storageFileName() const;
    void setStorageFileName(const QString &fileName);

public slots:
    bool save();
    bool load();
    void clear();

signals:
    void urlsChanged();
    void storageFileNameChanged();

private:
    QStringList m_urls;

    QString m_fileName;
};

QML_DECLARE_TYPE(WebHistoryInterface)

#endif // WEBHISTORYINTERFACE_P_H

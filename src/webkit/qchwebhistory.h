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

#ifndef QCHWEBHISTORY_H
#define QCHWEBHISTORY_H

#include <QObject>
#include <QWebHistoryItem>
#include <qdeclarative.h>

class QWebPage;

class QchWebHistoryItem : public QObject, public QWebHistoryItem
{
    Q_OBJECT
    
    Q_PROPERTY(QIcon icon READ icon CONSTANT)
    Q_PROPERTY(bool valid READ isValid CONSTANT)
    Q_PROPERTY(QDateTime lastVisited READ lastVisited CONSTANT)
    Q_PROPERTY(QUrl originalUrl READ originalUrl CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QVariant userData READ webUserData WRITE setWebUserData)

public:
    explicit QchWebHistoryItem(const QWebHistoryItem &other, QObject *parent = 0);
    
    QVariant webUserData() const;
    void setWebUserData(const QVariant &data);

private:
    Q_DISABLE_COPY(QchWebHistoryItem)
};

class QchWebHistory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList backItems READ backItems CONSTANT)
    Q_PROPERTY(QVariantList forwardItems READ forwardItems CONSTANT)
    Q_PROPERTY(QVariantList items READ items CONSTANT)
    Q_PROPERTY(QchWebHistoryItem* backItem READ backItem NOTIFY currentIndexChanged)
    Q_PROPERTY(QchWebHistoryItem* forwardItem READ forwardItem NOTIFY currentIndexChanged)
    Q_PROPERTY(QchWebHistoryItem* currentItem READ currentItem NOTIFY currentIndexChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(int maximumItemCount READ maximumItemCount WRITE setMaximumItemCount NOTIFY maximumItemCountChanged)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY currentIndexChanged)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY currentIndexChanged)
    Q_PROPERTY(QString storageFileName READ storageFileName WRITE setStorageFileName NOTIFY storageFileNameChanged)

public:
    explicit QchWebHistory(QWebPage *parent);
    
    QVariantList backItems() const;
    QVariantList forwardItems() const;
    QVariantList items() const;

    QchWebHistoryItem* backItem() const;
    QchWebHistoryItem* forwardItem() const;
    QchWebHistoryItem* currentItem() const;

    Q_INVOKABLE QchWebHistoryItem* itemAt(int index) const;

    int currentIndex() const;
    void setCurrentIndex(int index);

    int maximumItemCount() const;
    void setMaximumItemCount(int count);

    int count() const;

    bool canGoBack() const;
    bool canGoForward() const;

    QString storageFileName() const;
    void setStorageFileName(const QString &fileName);

public Q_SLOTS:
    bool save();
    bool load();
    void clear();

Q_SIGNALS:
    void currentIndexChanged();
    void maximumItemCountChanged();
    void storageFileNameChanged();

private:
    QString m_fileName;

    Q_DISABLE_COPY(QchWebHistory)
};

QML_DECLARE_TYPE(QchWebHistoryItem)
QML_DECLARE_TYPE(QchWebHistory)

#endif // QCHWEBHISTORY_H

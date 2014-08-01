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

#ifndef WEBHISTORY_P_H
#define WEBHISTORY_P_H

#include <QObject>
#include <qdeclarative.h>

class QWebHistory;

class WebHistory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList backItems READ backItems CONSTANT)
    Q_PROPERTY(QVariantList forwardItems READ forwardItems CONSTANT)
    Q_PROPERTY(QVariantList items READ items CONSTANT)
    Q_PROPERTY(QVariant backItem READ backItem NOTIFY currentIndexChanged)
    Q_PROPERTY(QVariant forwardItem READ forwardItem NOTIFY currentIndexChanged)
    Q_PROPERTY(QVariant currentItem READ currentItem NOTIFY currentIndexChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(int maximumItemCount READ maximumItemCount WRITE setMaximumItemCount NOTIFY maximumItemCountChanged)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY currentIndexChanged)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY currentIndexChanged)
    Q_PROPERTY(QString storageFileName READ storageFileName WRITE setStorageFileName NOTIFY storageFileNameChanged)

public:
    explicit WebHistory(QWebHistory *history, QObject *parent = 0);
    ~WebHistory();

    QVariantList backItems() const;
    QVariantList forwardItems() const;
    QVariantList items() const;

    QVariant backItem() const;
    QVariant forwardItem() const;
    QVariant currentItem() const;

    Q_INVOKABLE QVariant itemAt(int index) const;

    int currentIndex() const;
    void setCurrentIndex(int index);

    int maximumItemCount() const;
    void setMaximumItemCount(int count);

    int count() const;

    bool canGoBack() const;
    bool canGoForward() const;

    QString storageFileName() const;
    void setStorageFileName(const QString &fileName);

public slots:
    bool save();
    bool load();
    void clear();

signals:
    void currentIndexChanged();
    void maximumItemCountChanged();
    void storageFileNameChanged();

private:
    QWebHistory *m_history;

    QString m_fileName;

    Q_DISABLE_COPY(WebHistory)
};

QML_DECLARE_TYPE(WebHistory)

#endif // WEBHISTORY_P_H

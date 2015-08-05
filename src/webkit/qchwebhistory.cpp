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

#include "qchwebhistory.h"
#include <QWebHistory>
#include <QFile>
#include <QDataStream>
#include <QDeclarativeInfo>

QchWebHistory::QchWebHistory(QWebHistory *history, QObject *parent) :
    QObject(parent),
    m_history(history)
{
}

static QVariant itemToVariant(const QWebHistoryItem &item) {
    QVariantMap map;
    map["icon"] = item.icon().name();
    map["valid"] = item.isValid();
    map["lastVisited"] = item.lastVisited();
    map["originalUrl"] = item.originalUrl();
    map["title"] = item.title();
    map["url"] = item.url();
    map["userData"] = item.userData();

    return map;
}

QVariantList QchWebHistory::backItems() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->backItems(m_history->count())) {
        list << itemToVariant(item);
    }

    return list;
}

QVariantList QchWebHistory::forwardItems() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->forwardItems(m_history->count())) {
        list << itemToVariant(item);
    }

    return list;
}

QVariantList QchWebHistory::items() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->items()) {
        list << itemToVariant(item);
    }

    return list;
}

QVariant QchWebHistory::backItem() const {
    return itemToVariant(m_history->backItem());
}

QVariant QchWebHistory::forwardItem() const {
    return itemToVariant(m_history->forwardItem());
}

QVariant QchWebHistory::currentItem() const {
    return itemToVariant(m_history->currentItem());
}

QVariant QchWebHistory::itemAt(int index) const {
    return itemToVariant(m_history->itemAt(index));
}

int QchWebHistory::currentIndex() const {
    return m_history->currentItemIndex();
}

void QchWebHistory::setCurrentIndex(int index) {
    if (index != currentIndex()) {
        m_history->goToItem(m_history->itemAt(index));
        emit currentIndexChanged();
    }
}

int QchWebHistory::maximumItemCount() const {
    return m_history->maximumItemCount();
}

void QchWebHistory::setMaximumItemCount(int count) {
    if (count != maximumItemCount()) {
        m_history->setMaximumItemCount(count);
        emit maximumItemCountChanged();
    }
}

int QchWebHistory::count() const {
    return m_history->count();
}

bool QchWebHistory::canGoBack() const {
    return m_history->canGoBack();
}

bool QchWebHistory::canGoForward() const {
    return m_history->canGoForward();
}

QString QchWebHistory::storageFileName() const {
    return m_fileName;
}

void QchWebHistory::setStorageFileName(const QString &fileName) {
    if (fileName != storageFileName()) {
        m_fileName = fileName;
        emit storageFileNameChanged();
    }
}

bool QchWebHistory::save() {
    QFile file(storageFileName());

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << *m_history;
        file.close();
        return true;
    }

    qmlInfo(this) << tr("Cannot save web history to %1: %2").arg(file.fileName()).arg(file.errorString());
}

bool QchWebHistory::load() {
    clear();
    QFile file(storageFileName());

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> *m_history;
        file.close();
        return true;
    }

    qmlInfo(this) << tr("Cannot load web history from %1: %2").arg(file.fileName()).arg(file.errorString());
}

void QchWebHistory::clear() {
    m_history->clear();
}

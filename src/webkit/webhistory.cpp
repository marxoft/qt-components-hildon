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

#include "webhistory_p.h"
#include <QWebHistory>
#include <QFile>
#include <QDataStream>
#include <QDeclarativeInfo>

WebHistory::WebHistory(QWebHistory *history, QObject *parent) :
    QObject(parent),
    m_history(history)
{
}

WebHistory::~WebHistory() {}

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

QVariantList WebHistory::backItems() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->backItems(m_history->count())) {
        list << itemToVariant(item);
    }

    return list;
}

QVariantList WebHistory::forwardItems() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->forwardItems(m_history->count())) {
        list << itemToVariant(item);
    }

    return list;
}

QVariantList WebHistory::items() const {
    QVariantList list;

    foreach (QWebHistoryItem item, m_history->items()) {
        list << itemToVariant(item);
    }

    return list;
}

QVariant WebHistory::backItem() const {
    return itemToVariant(m_history->backItem());
}

QVariant WebHistory::forwardItem() const {
    return itemToVariant(m_history->forwardItem());
}

QVariant WebHistory::currentItem() const {
    return itemToVariant(m_history->currentItem());
}

QVariant WebHistory::itemAt(int index) const {
    return itemToVariant(m_history->itemAt(index));
}

int WebHistory::currentIndex() const {
    return m_history->currentItemIndex();
}

void WebHistory::setCurrentIndex(int index) {
    if (index != this->currentIndex()) {
        m_history->goToItem(m_history->itemAt(index));
        emit currentIndexChanged();
    }
}

int WebHistory::maximumItemCount() const {
    return m_history->maximumItemCount();
}

void WebHistory::setMaximumItemCount(int count) {
    if (count != this->maximumItemCount()) {
        m_history->setMaximumItemCount(count);
        emit maximumItemCountChanged();
    }
}

int WebHistory::count() const {
    return m_history->count();
}

bool WebHistory::canGoBack() const {
    return m_history->canGoBack();
}

bool WebHistory::canGoForward() const {
    return m_history->canGoForward();
}

QString WebHistory::storageFileName() const {
    return m_fileName;
}

void WebHistory::setStorageFileName(const QString &fileName) {
    if (fileName != this->storageFileName()) {
        m_fileName = fileName;
        emit storageFileNameChanged();
    }
}

bool WebHistory::save() {
    QFile file(this->storageFileName());

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << *m_history;
        file.close();
        return true;
    }

    qmlInfo(this) << tr("Cannot save web history to %1: %2").arg(file.fileName()).arg(file.errorString());
}

bool WebHistory::load() {
    this->clear();
    QFile file(this->storageFileName());

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> *m_history;
        file.close();
        return true;
    }

    qmlInfo(this) << tr("Cannot load web history from %1: %2").arg(file.fileName()).arg(file.errorString());
}

void WebHistory::clear() {
    m_history->clear();
}

#include "moc_webhistory_p.cpp"

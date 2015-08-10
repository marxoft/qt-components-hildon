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
#include <QWebPage>
#include <QWebHistory>
#include <QFile>
#include <QDataStream>
#include <QDeclarativeInfo>

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

static QWebHistory* qWebHistory(const QchWebHistory *qwh) {
    if (QWebPage *page = qobject_cast<QWebPage*>(qwh->parent())) {
        if (QWebHistory *history = page->history()) {
            return history;
        }
    }
    
    return 0;
}

QchWebHistory::QchWebHistory(QWebPage *parent) :
    QObject(parent)
{
}

QVariantList QchWebHistory::backItems() const {
    QVariantList list;
    
    if (QWebHistory *history = qWebHistory(this)) {
        foreach (QWebHistoryItem item, history->backItems(history->count())) {
            list << itemToVariant(item);
        }
    }

    return list;
}

QVariantList QchWebHistory::forwardItems() const {
    QVariantList list;

    if (QWebHistory *history = qWebHistory(this)) {
        foreach (QWebHistoryItem item, history->forwardItems(history->count())) {
            list << itemToVariant(item);
        }
    }

    return list;
}

QVariantList QchWebHistory::items() const {
    QVariantList list;

    if (QWebHistory *history = qWebHistory(this)) {
        foreach (QWebHistoryItem item, history->items()) {
            list << itemToVariant(item);
        }
    }

    return list;
}

QVariant QchWebHistory::backItem() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return itemToVariant(history->backItem());
    }
    
    return QVariant();
}

QVariant QchWebHistory::forwardItem() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return itemToVariant(history->forwardItem());
    }
    
    return QVariant();
}

QVariant QchWebHistory::currentItem() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return itemToVariant(history->currentItem());
    }
    
    return QVariant();
}

QVariant QchWebHistory::itemAt(int index) const {
    if (QWebHistory *history = qWebHistory(this)) {
        return itemToVariant(history->itemAt(index));
    }
    
    return QVariant();
}

int QchWebHistory::currentIndex() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return history->currentItemIndex();
    }
    
    return -1;
}

void QchWebHistory::setCurrentIndex(int index) {
    if (index != currentIndex()) {
        if (QWebHistory *history = qWebHistory(this)) {
            history->goToItem(history->itemAt(index));
            emit currentIndexChanged();
        }
    }
}

int QchWebHistory::maximumItemCount() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return history->maximumItemCount();
    }
    
    return -1;
}

void QchWebHistory::setMaximumItemCount(int count) {
    if (count != maximumItemCount()) {
        if (QWebHistory *history = qWebHistory(this)) {
            history->setMaximumItemCount(count);
            emit maximumItemCountChanged();
        }
    }
}

int QchWebHistory::count() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return history->count();
    }
    
    return -1;
}

bool QchWebHistory::canGoBack() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return history->canGoBack();
    }
    
    return false;
}

bool QchWebHistory::canGoForward() const {
    if (QWebHistory *history = qWebHistory(this)) {
        return history->canGoForward();
    }
    
    return false;
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
    if (QWebHistory *history = qWebHistory(this)) {
        QFile file(storageFileName());

        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out << *history;
            file.close();
            return true;
        }
        
        qmlInfo(this) << tr("Cannot save web history to %1: %2").arg(file.fileName()).arg(file.errorString());
    }
}

bool QchWebHistory::load() {
    clear();
    
    if (QWebHistory *history = qWebHistory(this)) {
        QFile file(storageFileName());
        
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            in >> *history;
            file.close();
            return true;
        }
        
        qmlInfo(this) << tr("Cannot load web history from %1: %2").arg(file.fileName()).arg(file.errorString());
    }    
}

void QchWebHistory::clear() {
    if (QWebHistory *history = qWebHistory(this)) {
        history->clear();
    }
}

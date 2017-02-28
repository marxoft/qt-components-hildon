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

#include "qchwebhistory.h"
#include <QWebPage>
#include <QWebHistory>
#include <QFile>
#include <QDataStream>
#include <QDeclarativeEngine>
#include <QDeclarativeInfo>

QchWebHistoryItem::QchWebHistoryItem(const QWebHistoryItem &other, QObject *parent) :
    QObject(parent),
    QWebHistoryItem(other)
{
}

QVariant QchWebHistoryItem::webUserData() const {
    return QWebHistoryItem::userData();
}

void QchWebHistoryItem::setWebUserData(const QVariant &data) {
    QWebHistoryItem::setUserData(data);
}

static QWebHistory* qWebHistory(const QchWebHistory *qwh) {
    if (const QWebPage *page = qobject_cast<QWebPage*>(qwh->parent())) {
        if (QWebHistory *history = page->history()) {
            return history;
        }
    }
    
    return 0;
}

/*!
    \class WebHistory
    \brief Provides access to the web history of a WebPage or WebView.
    
    \ingroup webkit
    
    \note This component cannot be created in QML.
    
    \sa WebPage, WebView
*/
QchWebHistory::QchWebHistory(QWebPage *parent) :
    QObject(parent)
{
}

/*!
    \brief The list of back items in the history.
*/
QVariantList QchWebHistory::backItems() const {
    QVariantList list;
    
    if (const QWebHistory *history = qWebHistory(this)) {
        foreach (const QWebHistoryItem &item, history->backItems(history->count())) {
            QchWebHistoryItem *hi = new QchWebHistoryItem(item);
            QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
            list << QVariant::fromValue(hi);
        }
    }

    return list;
}

/*!
    \brief The list of forward items in the history.
*/
QVariantList QchWebHistory::forwardItems() const {
    QVariantList list;

    if (const QWebHistory *history = qWebHistory(this)) {
        foreach (const QWebHistoryItem &item, history->forwardItems(history->count())) {
            QchWebHistoryItem *hi = new QchWebHistoryItem(item);
            QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
            list << QVariant::fromValue(hi);
        }
    }

    return list;
}

/*!
    \brief The list of items in the history.
*/
QVariantList QchWebHistory::items() const {
    QVariantList list;

    if (const QWebHistory *history = qWebHistory(this)) {
        foreach (const QWebHistoryItem &item, history->items()) {
            QchWebHistoryItem *hi = new QchWebHistoryItem(item);
            QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
            list << QVariant::fromValue(hi);
        }
    }

    return list;
}

/*!
    \brief The most previous item in the history.
*/
QchWebHistoryItem* QchWebHistory::backItem() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        QchWebHistoryItem *hi = new QchWebHistoryItem(history->backItem());
        QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
        return hi;
    }
    
    return 0;
}

/*!
    \brief The next item in the history.
*/
QchWebHistoryItem* QchWebHistory::forwardItem() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        QchWebHistoryItem *hi = new QchWebHistoryItem(history->forwardItem());
        QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
        return hi;
    }
    
    return 0;
}

/*!
    \brief The current item in the history.
*/
QchWebHistoryItem* QchWebHistory::currentItem() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        QchWebHistoryItem *hi = new QchWebHistoryItem(history->currentItem());
        QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
        return hi;
    }
    
    return 0;
}

/*!    
    Returns the history item at \a index.
*/
QchWebHistoryItem* QchWebHistory::itemAt(int index) const {
    if (const QWebHistory *history = qWebHistory(this)) {
        QchWebHistoryItem *hi = new QchWebHistoryItem(history->itemAt(index));
        QDeclarativeEngine::setObjectOwnership(hi, QDeclarativeEngine::JavaScriptOwnership);
        return hi;
    }
    
    return 0;
}

/*!
    \brief The index of the current item in the history.
*/
int QchWebHistory::currentIndex() const {
    if (const QWebHistory *history = qWebHistory(this)) {
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

/*!
    \brief The maximum number of items in the history.
*/
int QchWebHistory::maximumItemCount() const {
    if (const QWebHistory *history = qWebHistory(this)) {
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

/*!
    \brief The current number of items in the history.
*/
int QchWebHistory::count() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        return history->count();
    }
    
    return -1;
}

/*!
    \brief Whether there is a back item available.
*/
bool QchWebHistory::canGoBack() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        return history->canGoBack();
    }
    
    return false;
}

/*!
    \brief Whether there is a forward item available.
*/

bool QchWebHistory::canGoForward() const {
    if (const QWebHistory *history = qWebHistory(this)) {
        return history->canGoForward();
    }
    
    return false;
}

/*!
    \brief The file name used to (re)store the history.
*/
QString QchWebHistory::storageFileName() const {
    return m_fileName;
}

void QchWebHistory::setStorageFileName(const QString &fileName) {
    if (fileName != storageFileName()) {
        m_fileName = fileName;
        emit storageFileNameChanged();
    }
}

/*!    
    Returns true if the history can be saved to \link storageFileName\endlink.
*/
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

/*!    
    Returns true if the history can be loaded from \link storageFileName\endlink.
*/
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

/*!    
    Clears all items from the history.
*/
void QchWebHistory::clear() {
    if (QWebHistory *history = qWebHistory(this)) {
        history->clear();
    }
}

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

#include "qchwebhistoryinterface.h"
#include <QFile>
#include <QTextStream>
#include <QDeclarativeInfo>

QchWebHistoryInterface::QchWebHistoryInterface(QObject *parent) :
    QWebHistoryInterface(parent)
{
    QWebHistoryInterface::setDefaultInterface(this);
}

void QchWebHistoryInterface::addHistoryEntry(const QString &url) {
    m_urls.removeOne(url);
    m_urls.prepend(url);
    emit urlsChanged();
}

bool QchWebHistoryInterface::historyContains(const QString &url) const {
    return m_urls.contains(url);
}

QStringList QchWebHistoryInterface::urls() const {
    return m_urls;
}

int QchWebHistoryInterface::count() const {
    return m_urls.size();
}

QString QchWebHistoryInterface::storageFileName() const {
    return m_fileName;
}

void QchWebHistoryInterface::setStorageFileName(const QString &fileName) {
    if (fileName != this->storageFileName()) {
        m_fileName = fileName;
        emit storageFileNameChanged();
    }
}

bool QchWebHistoryInterface::save() {
    QFile file(this->storageFileName());

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);

        for (int i = 0; i < m_urls.size(); i++) {
            out << m_urls.at(i) << "\n";
        }

        file.close();
        return true;
    }

    qmlInfo(this) << tr("Cannot save web history to %1: %2").arg(file.fileName()).arg(file.errorString());
}

bool QchWebHistoryInterface::load() {
    this->clear();
    QFile file(this->storageFileName());

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString line;

        while (!in.atEnd()) {
            line = in.readLine();

            if (!line.isNull()) {
                m_urls << line;
            }
        }

        file.close();
        emit urlsChanged();
        return true;
    }

    qmlInfo(this) << tr("Cannot load web history from %1: %2").arg(file.fileName()).arg(file.errorString());
}

void QchWebHistoryInterface::clear() {
    m_urls.clear();
    emit urlsChanged();
}

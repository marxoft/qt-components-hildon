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

#include "qmlgconfitem_p.h"
#include <GConfItem>
#include <QStringList>

QmlGConfItem::QmlGConfItem(QObject *parent) :
    QObject(parent),
    m_item(0)
{
}

QmlGConfItem::~QmlGConfItem() {}

QString QmlGConfItem::key() const {
    return m_item ? m_item->key() : QString();
}

void QmlGConfItem::setKey(const QString &key) {
    if (key != this->key()) {
        if (m_item) {
            delete m_item;
            m_item = 0;
        }
        
        if (!key.isEmpty()) {
            m_item = new GConfItem(key, this);
            
            if (m_initialValue.isValid()) {
                this->setValue(m_initialValue);
            }
            
            this->connect(m_item, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
            this->connect(m_item, SIGNAL(subtreeChanged(QString,QVariant)), this, SIGNAL(subtreeChanged(QString,QVariant)));
            emit keyChanged();
            emit valueChanged();
        }
    }
}

QVariant QmlGConfItem::value() const {
    return m_item ? m_item->value() : m_initialValue;
}

void QmlGConfItem::setValue(const QVariant &value) {
    if (value != this->value()) {
        if (m_item) {
            m_item->set(value);
            m_initialValue.clear();
        }
        else {
            m_initialValue = value;
        }
    }
}

void QmlGConfItem::resetValue() {
    this->setValue(QVariant::Invalid);
}

QStringList QmlGConfItem::childDirectories() const {
    return m_item ? m_item->listDirs() : QStringList();
}

QStringList QmlGConfItem::childEntries() const {
    return m_item ? m_item->listEntries() : QStringList();
}

void QmlGConfItem::classBegin() {}

void QmlGConfItem::componentComplete() {
    if ((m_item) && (m_initialValue.isValid())) {
        this->setValue(m_initialValue);
    }
}

#include "moc_qmlgconfitem_p.cpp"

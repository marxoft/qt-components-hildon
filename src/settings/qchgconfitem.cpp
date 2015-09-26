/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchgconfitem.h"
#include <GConfItem>

/*!
    \class GConfItem
    \brief Enables access to GConf keys in QML.
    
    \include gconf.qml
    
    \ingroup settings
*/
QchGConfItem::QchGConfItem(QObject *parent) :
    QObject(parent),
    m_item(0)
{
}

/*!
    \brief The GConf key.
*/
QString QchGConfItem::key() const {
    return m_item ? m_item->key() : QString();
}

void QchGConfItem::setKey(const QString &key) {
    if (key != this->key()) {
        if (m_item) {
            delete m_item;
            m_item = 0;
        }
        
        if (!key.isEmpty()) {
            m_item = new GConfItem(key, this);
            
            if (m_initialValue.isValid()) {
                setValue(m_initialValue);
            }
            
            connect(m_item, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
            connect(m_item, SIGNAL(subtreeChanged(QString,QVariant)), this, SIGNAL(subtreeChanged(QString,QVariant)));
            emit keyChanged();
            emit valueChanged();
        }
    }
}

/*!
    \brief The value associated with the \link key\endlink.
*/
QVariant QchGConfItem::value() const {
    return m_item ? m_item->value() : m_initialValue;
}

void QchGConfItem::setValue(const QVariant &value) {
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

void QchGConfItem::resetValue() {
    setValue(QVariant::Invalid);
}

/*!
    \brief The directories under the \link key\endlink.
*/
QStringList QchGConfItem::childDirectories() const {
    return m_item ? m_item->listDirs() : QStringList();
}

/*!
    \brief The entries under the \link key\endlink.
*/
QStringList QchGConfItem::childEntries() const {
    return m_item ? m_item->listEntries() : QStringList();
}

/*!
    \fn void GConfItem::subtreeChanged(QString key, QVariant value)
    
    This signal is emitted when an entry under the \link key\endlink changes. The changed \a key is passed along with 
    its new \a value.
*/

void QchGConfItem::classBegin() {}

void QchGConfItem::componentComplete() {
    if ((m_item) && (m_initialValue.isValid())) {
        setValue(m_initialValue);
    }
}

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

#include "listelement_p.h"
#include <QMetaProperty>

ListElement::ListElement(QObject *parent) :
    QDeclarativePropertyMap(parent)
{
}

ListElement::~ListElement() {}

void ListElement::classBegin() {}

void ListElement::componentComplete() {
    const QMetaObject *mo = this->metaObject();
    QVariantMap map;
    
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); i++) {
        QMetaProperty property = mo->property(i);
        map[property.name()] = property.read(this);
    }
    
    QMapIterator<QString, QVariant> iterator(map);
    
    while (iterator.hasNext()) {
        iterator.next();
        this->insert(iterator.key(), iterator.value());
    }
}


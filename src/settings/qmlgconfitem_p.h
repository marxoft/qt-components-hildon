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

#ifndef QMLGCONFITEM_P_H
#define QMLGCONFITEM_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class GConfItem;

class QmlGConfItem : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged FINAL)
    Q_PROPERTY(QVariant value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(QStringList childDirectories READ childDirectories NOTIFY keyChanged FINAL)
    Q_PROPERTY(QStringList childEntries READ childEntries NOTIFY keyChanged FINAL)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    explicit QmlGConfItem(QObject *parent = 0);
    ~QmlGConfItem();
    
    QString key() const;
    void setKey(const QString &key);
    
    QVariant value() const;
    void setValue(const QVariant &value);
    void resetValue();
    
    QStringList childDirectories() const;
    QStringList childEntries() const;
    
signals:
    void keyChanged();
    void valueChanged();
    void subtreeChanged(const QString &key, const QVariant &value);
    
protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    GConfItem *m_item;
    
    QVariant m_initialValue;
};

QML_DECLARE_TYPE(QmlGConfItem)

#endif // QMLGCONFITEM_P_H

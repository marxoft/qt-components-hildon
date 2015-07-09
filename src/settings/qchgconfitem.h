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

#ifndef QCHGCONFITEM_H
#define QCHGCONFITEM_H

#include <QObject>
#include <QStringList>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class GConfItem;

class QchGConfItem : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged FINAL)
    Q_PROPERTY(QVariant value READ value WRITE setValue RESET resetValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(QStringList childDirectories READ childDirectories NOTIFY keyChanged FINAL)
    Q_PROPERTY(QStringList childEntries READ childEntries NOTIFY keyChanged FINAL)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
public:
    explicit QchGConfItem(QObject *parent = 0);
    
    QString key() const;
    void setKey(const QString &key);
    
    QVariant value() const;
    void setValue(const QVariant &value);
    void resetValue();
    
    QStringList childDirectories() const;
    QStringList childEntries() const;
    
Q_SIGNALS:
    void keyChanged();
    void valueChanged();
    void subtreeChanged(const QString &key, const QVariant &value);
    
protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    GConfItem *m_item;
    
    QVariant m_initialValue;
};

QML_DECLARE_TYPE(QchGConfItem)

#endif // QCHGCONFITEM_H

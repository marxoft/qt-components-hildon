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

#ifndef QCHEXCLUSIVEGROUP_H
#define QCHEXCLUSIVEGROUP_H

#include <QObject>
#include <qdeclarative.h>

class QchExclusiveGroupPrivate;

class QchExclusiveGroup : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QObject* current READ current NOTIFY currentChanged)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    
    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchExclusiveGroup(QObject *parent = 0);
    ~QchExclusiveGroup();
    
    QObject* current() const;
    void setCurrent(QObject *obj);
    
    QDeclarativeListProperty<QObject> data();

public Q_SLOTS:
    void addCheckable(QObject *obj);
    void removeCheckable(QObject *obj);

Q_SIGNALS:
    void currentChanged();
    
protected:    
    QScopedPointer<QchExclusiveGroupPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchExclusiveGroup)
    
    Q_PRIVATE_SLOT(d_func(), void _q_updateCurrent())

private:
    Q_DISABLE_COPY(QchExclusiveGroup)
};

QML_DECLARE_TYPE(QchExclusiveGroup)

#endif // QCHEXCLUSIVEGROUP_H

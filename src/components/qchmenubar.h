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

#ifndef QCHMENUBAR_H
#define QCHMENUBAR_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchMenuItem;
class QchMenuBarPrivate;

class QchMenuBar : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(bool filtersExclusive READ filtersExclusive WRITE setFiltersExclusive NOTIFY filtersExclusiveChanged)
    Q_PROPERTY(QDeclarativeListProperty<QObject> filters READ filters)
    Q_PROPERTY(QDeclarativeListProperty<QObject> items READ items)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
    Q_CLASSINFO("DefaultProperty", "items")
    
public:
    explicit QchMenuBar(QObject *parent = 0);
    ~QchMenuBar();
    
    bool filtersExclusive() const;
    void setFiltersExclusive(bool exclusive);
    
    QDeclarativeListProperty<QObject> filters();
    QDeclarativeListProperty<QObject> items();

public Q_SLOTS:
    QchMenuItem *addFilter(const QString &text);
    QchMenuItem *insertFilter(int before, const QString &text);
    
    QchMenuItem* addItem(const QString &text);
    QchMenuItem* insertItem(int before, const QString &text);
    void removeItem(QObject *item);

Q_SIGNALS:
    void filtersExclusiveChanged();
    
protected:    
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<QchMenuBarPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchMenuBar)

private:
    Q_DISABLE_COPY(QchMenuBar)
};

QML_DECLARE_TYPE(QchMenuBar)
    
#endif // QCHMENUBAR_H

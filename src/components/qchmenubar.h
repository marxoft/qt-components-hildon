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

#ifndef QCHMENUBAR_H
#define QCHMENUBAR_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchMenuBarPrivate;

class QchMenuBar : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    
    Q_INTERFACES(QDeclarativeParserStatus)
    
    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchMenuBar(QObject *parent = 0);
    ~QchMenuBar();
    
    QDeclarativeListProperty<QObject> data();
    
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

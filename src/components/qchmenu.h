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

#ifndef QCHMENU_H
#define QCHMENU_H

#include <QMenu>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchMenuPrivate;

class QchMenu : public QMenu, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    
    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchMenu(QWidget *parent = 0);
    ~QchMenu();
    
    QDeclarativeListProperty<QObject> data();

public Q_SLOTS:
    void popup();
    
protected:
    virtual void classBegin();
    virtual void componentComplete();
    
    QScopedPointer<QchMenuPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchMenu)

private:
    Q_DISABLE_COPY(QchMenu)
};

QML_DECLARE_TYPE(QchMenu)
    
#endif // QCHMENU_H

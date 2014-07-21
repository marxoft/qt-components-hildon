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

#ifndef VALUESELECTOR_P_H
#define VALUESELECTOR_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class ValueSelectorPrivate;

class ValueSelector : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PRIVATE_PROPERTY(ValueSelector::d_func(), QDeclarativeListProperty<QObject> data READ data)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ValueSelector(QObject *parent = 0);
    ~ValueSelector();

protected:
    ValueSelector(ValueSelectorPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<ValueSelectorPrivate> d_ptr;

    Q_DECLARE_PRIVATE(ValueSelector)

private:
    friend class ValueButton;

    Q_DISABLE_COPY(ValueSelector)
};

QML_DECLARE_TYPE(ValueSelector)

#endif // VALUESELECTOR_P_H

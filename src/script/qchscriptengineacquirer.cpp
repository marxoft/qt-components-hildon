/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchscriptengineacquirer.h"
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>

class QchComponent : public QDeclarativeComponent
{
    
public:
    explicit QchComponent(QDeclarativeEngine *engine, QObject *parent = 0) :
        QDeclarativeComponent(engine, parent)
    {
        setData("import QtQuick 1.0\nQtObject {}\n", QUrl());
    }

private:
    friend class QchScriptEngineAcquirer;
    
    Q_DISABLE_COPY(QchComponent)
};

QScriptEngine* QchScriptEngineAcquirer::getScriptEngine(QDeclarativeEngine *engine) {
    QchComponent component(engine, engine);
    return component.createObject(&component).engine();
}

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

#ifndef QCHITEMACTION_H
#define QCHITEMACTION_H

#include <QWidgetAction>

class QDeclarativeComponent;
class QchItemActionPrivate;

class QchItemAction : public QWidgetAction
{
    Q_OBJECT
            
public:
    explicit QchItemAction(QObject *parent = 0);
    ~QchItemAction();
    
    QDeclarativeComponent* component() const;
    void setComponent(QDeclarativeComponent *c);

protected:
    virtual QWidget* createWidget(QWidget *parent);
    
    QScopedPointer<QchItemActionPrivate> d_ptr;
    
    Q_DECLARE_PRIVATE(QchItemAction)
    
private:
    Q_DISABLE_COPY(QchItemAction)
};

#endif // QCHITEMACTION_H

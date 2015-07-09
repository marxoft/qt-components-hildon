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

#ifndef QCHCLOSEEVENT_H
#define QCHCLOSEEVENT_H

#include <QObject>
#include <qdeclarative.h>

class QchCloseEvent : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)

public:
    QchCloseEvent() :
        m_accepted(true)
    {
    }
    
    inline bool isAccepted() { return m_accepted; }
    void setAccepted(bool accepted) { m_accepted = accepted; }

private:
    bool m_accepted;
};

QML_DECLARE_TYPE(QchCloseEvent)

#endif // QCHCLOSEEVENT_H

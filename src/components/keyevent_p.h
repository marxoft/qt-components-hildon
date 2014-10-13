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

#ifndef KEYEVENT_P_H
#define KEYEVENT_P_H

#include <QObject>
#include <QKeyEvent>
#include <qdeclarative.h>

class KeyEvent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
    Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat CONSTANT)
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int key READ key CONSTANT)
    Q_PROPERTY(int modifiers READ modifiers CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)

public:
    explicit KeyEvent(const QKeyEvent &event, QObject *parent = 0);
    ~KeyEvent();

    bool isAccepted() const;
    void setAccepted(bool accept);

    bool isAutoRepeat() const;

    int count() const;

    int key() const;

    int modifiers() const;

    QString text() const;

private:
    QKeyEvent m_event;

    Q_DISABLE_COPY(KeyEvent)
};

QML_DECLARE_TYPE(KeyEvent)

#endif // KEYEVENT_P_H

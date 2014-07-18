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


#ifndef LISTITEMMOUSEAREA_P_H
#define LISTITEMMOUSEAREA_P_H

#include "listitemcontent_p.h"

class QMouseEvent;
class ListItemMouseAreaPrivate;

class ListItemMouseArea : public ListItemContent
{
    Q_OBJECT

    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mouseYChanged)
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(bool preventStealing READ preventStealing WRITE setPreventStealing NOTIFY preventStealingChanged)

public:
    explicit ListItemMouseArea(QObject *parent = 0);

    bool containsMouse() const;

    int mouseX() const;
    int mouseY() const;

    bool isPressed() const;

    bool preventStealing() const;
    void setPreventStealing(bool prevent);

    bool editorEvent(QEvent *event, const QRect &rect);

signals:
    void canceled();
    void clicked();
    void containsMouseChanged();
    void doubleClicked();
    void entered();
    void exited();
    void mouseXChanged();
    void mouseYChanged();
    void positionChanged();
    void pressAndHold();
    void pressed();
    void pressedChanged();
    void preventStealingChanged();
    void released();

protected:
    ListItemMouseArea(ListItemMouseAreaPrivate &dd, QObject *parent = 0);

    virtual bool mousePressEvent(QMouseEvent *event);
    virtual bool mouseReleaseEvent(QMouseEvent *event);
    virtual bool mouseMoveEvent(QMouseEvent *event);
    virtual bool mouseDoubleClickEvent(QMouseEvent *event);

    void timerEvent(QTimerEvent *event);

    Q_DECLARE_PRIVATE(ListItemMouseArea)

private:
    Q_DISABLE_COPY(ListItemMouseArea)
};

QML_DECLARE_TYPE(ListItemMouseArea)

#endif // LISTITEMMOUSEAREA_P_H

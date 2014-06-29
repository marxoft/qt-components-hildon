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

#ifndef MOUSEAREA_P_H
#define MOUSEAREA_P_H

#include "item_p.h"

class MouseDrag : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QWidget* target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(DragAxis axis READ axis WRITE setAxis NOTIFY axisChanged)
    Q_PROPERTY(int minimumX READ minimumX WRITE setMinimumX NOTIFY minimumXChanged)
    Q_PROPERTY(int maximumX READ maximumX WRITE setMaximumX NOTIFY maximumXChanged)
    Q_PROPERTY(int minimumY READ minimumY WRITE setMinimumY NOTIFY minimumYChanged)
    Q_PROPERTY(int maximumY READ maximumY WRITE setMaximumY NOTIFY maximumYChanged)
    Q_PROPERTY(bool filterChildren READ filterChildren WRITE setFilterChildren NOTIFY filterChildrenChanged)

    Q_ENUMS(DragAxis)

public:
    enum DragAxis {
        XAxis = 0,
        YAxis,
        XandYAxis
    };

    explicit MouseDrag(QObject *parent = 0);
    ~MouseDrag();

    QWidget* target() const;
    void setTarget(QWidget *target);
    void resetTarget();

    bool active() const;

    DragAxis axis() const;
    void setAxis(DragAxis axis);

    int minimumX() const;
    void setMinimumX(int x);

    int maximumX() const;
    void setMaximumX(int x);

    int minimumY() const;
    void setMinimumY(int y);

    int maximumY() const;
    void setMaximumY(int y);

    bool filterChildren() const;
    void setFilterChildren(bool filter);

signals:
    void targetChanged();
    void activeChanged();
    void axisChanged();
    void minimumXChanged();
    void maximumXChanged();
    void minimumYChanged();
    void maximumYChanged();
    void filterChildrenChanged();

private:
    void setActive(bool active);

    QWidget *m_target;

    bool m_active;

    DragAxis m_axis;

    int m_minX;
    int m_maxX;
    int m_minY;
    int m_maxY;

    bool m_filter;

    friend class MouseArea;

    Q_DISABLE_COPY(MouseDrag)
};

class MouseAreaPrivate;

class MouseArea : public Item
{
    Q_OBJECT

    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mouseYChanged)
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(bool preventStealing READ preventStealing WRITE setPreventStealing NOTIFY preventStealingChanged)
    Q_PRIVATE_PROPERTY(MouseArea::d_func(), MouseDrag* drag READ drag CONSTANT FINAL)

public:
    explicit MouseArea(QWidget *parent = 0);
    ~MouseArea();

    bool containsMouse() const;

    int mouseX() const;
    int mouseY() const;

    bool isPressed() const;

    bool preventStealing() const;
    void setPreventStealing(bool prevent);

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
    MouseArea(MouseAreaPrivate &dd, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void timerEvent(QTimerEvent *event);

    Q_DISABLE_COPY(MouseArea)
    Q_DECLARE_PRIVATE(MouseArea)
};

QML_DECLARE_TYPE(MouseDrag)
QML_DECLARE_TYPE(MouseArea)

#endif // MOUSEAREA_P_H

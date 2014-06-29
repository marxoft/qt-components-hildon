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

#ifndef RECTANGLE_P_H
#define RECTANGLE_P_H

#include "item_p.h"
#include <QPen>

class Rectangle;
class RectanglePrivate;

class Border : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth NOTIFY widthChanged)

public:
    explicit Border(QObject *parent = 0);
    ~Border();

    QColor color() const;
    void setColor(const QColor &color);

    int width() const;
    void setWidth(int width);
    void resetWidth();

    QPen pen() const;

signals:
    void colorChanged();
    void widthChanged();

private:
    QPen m_pen;

    Q_DISABLE_COPY(Border)
};

class GradientStop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit GradientStop(QObject *parent = 0);
    ~GradientStop();

    QColor color() const;
    void setColor(const QColor &color);

    qreal position() const;
    void setPosition(qreal pos);

    QGradientStop stop() const;

signals:
    void colorChanged();
    void positionChanged();

private:
    QGradientStop m_stop;

    Q_DISABLE_COPY(GradientStop)
};

class Gradient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDeclarativeListProperty<GradientStop> stops READ qmlStops)

    Q_CLASSINFO("DefaultProperty", "stops")

public:
    explicit Gradient(QObject *parent = 0);
    ~Gradient();

    QGradientStops stops() const;
    QDeclarativeListProperty<GradientStop> qmlStops();

    static void stops_append(QDeclarativeListProperty<GradientStop> *list, GradientStop *stop);

signals:
    void stopsChanged();

private:
    QList<GradientStop*> m_stops;

    Q_DISABLE_COPY(Gradient)
};

class Rectangle : public Item
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PRIVATE_PROPERTY(Rectangle::d_func(), Border* border READ border CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(Rectangle::d_func(), Gradient* gradient READ gradient WRITE setGradient RESET resetGradient)

public:
    explicit Rectangle(QWidget *parent = 0);
    ~Rectangle();

    QColor color() const;
    void setColor(const QColor &color);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal radius() const;
    void setRadius(qreal radius);

    bool smooth() const;
    void setSmooth(bool smooth);

signals:
    void colorChanged();
    void opacityChanged();
    void radiusChanged();
    void smoothChanged();

private:
    Rectangle(RectanglePrivate &dd, QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

    Q_DISABLE_COPY(Rectangle)
    Q_DECLARE_PRIVATE(Rectangle)
};

QML_DECLARE_TYPE(Border)
QML_DECLARE_TYPE(Gradient)
QML_DECLARE_TYPE(GradientStop)
QML_DECLARE_TYPE(Rectangle)

#endif // RECTANGLE_P_H

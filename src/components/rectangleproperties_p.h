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

#ifndef RECTANGLEPROPERTIES_P_H
#define RECTANGLEPROPERTIES_P_H

#include <QObject>
#include <QColor>
#include <QPen>
#include <QDeclarativeListProperty>
#include <qdeclarative.h>

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

QML_DECLARE_TYPE(Border)
QML_DECLARE_TYPE(Gradient)
QML_DECLARE_TYPE(GradientStop)

#endif // RECTANGLEPROPERTIES_P_H

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

#include "rectangle_p.h"
#include "rectangle_p_p.h"
#include <QPainter>
#include <QPaintEvent>

Border::Border(QObject *parent) :
    QObject(parent),
    m_pen(Qt::black)
{
}

Border::~Border() {}

QColor Border::color() const {
    return m_pen.color();
}

void Border::setColor(const QColor &color) {
    if (color != this->color()) {
        m_pen.setColor(color);
        emit colorChanged();
    }
}

int Border::width() const {
    return m_pen.width();
}

void Border::setWidth(int width) {
    if (width != this->width()) {
        m_pen.setWidth(width);
        emit widthChanged();
    }
}

void Border::resetWidth() {
    this->setWidth(0);
}

QPen Border::pen() const {
    return m_pen;
}

GradientStop::GradientStop(QObject *parent) :
    QObject(parent)
{
}

GradientStop::~GradientStop() {}

QColor GradientStop::color() const {
    return m_stop.second;
}

void GradientStop::setColor(const QColor &color) {
    if (color != this->color()) {
        m_stop.second = color;
        emit colorChanged();
    }
}

qreal GradientStop::position() const {
    return m_stop.first;
}

void GradientStop::setPosition(qreal pos) {
    if (pos != this->position()) {
        m_stop.first = pos;
        emit positionChanged();
    }
}

QGradientStop GradientStop::stop() const {
    return m_stop;
}

Gradient::Gradient(QObject *parent) :
    QObject(parent)
{
}

Gradient::~Gradient() {}

QGradientStops Gradient::stops() const {
    QGradientStops s(m_stops.size());

    for (int i = 0; i < m_stops.size(); i++) {
        s.append(m_stops.at(i)->stop());
    }

    return s;
}

QDeclarativeListProperty<GradientStop> Gradient::qmlStops() {
    return QDeclarativeListProperty<GradientStop>(this, 0, Gradient::stops_append);
}

void Gradient::stops_append(QDeclarativeListProperty<GradientStop> *list, GradientStop *stop) {
    if (!stop) {
        return;
    }

    if (Gradient *gradient = qobject_cast<Gradient*>(list->object)) {
        gradient->m_stops.append(stop);
        emit gradient->stopsChanged();
        gradient->connect(stop, SIGNAL(colorChanged()), gradient, SIGNAL(stopsChanged()));
        gradient->connect(stop, SIGNAL(positionChanged()), gradient, SIGNAL(stopsChanged()));
    }
}

Rectangle::Rectangle(QWidget *parent) :
    Item(*new RectanglePrivate(this), parent)
{
}

Rectangle::Rectangle(RectanglePrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
}

Rectangle::~Rectangle() {}

QColor Rectangle::color() const {
    Q_D(const Rectangle);

    return d->color;
}

void Rectangle::setColor(const QColor &color) {
    if (color != this->color()) {
        Q_D(Rectangle);
        d->color = color;
        emit colorChanged();

        if (d->complete) {
            this->update();
        }
    }
}

qreal Rectangle::radius() const {
    Q_D(const Rectangle);

    return d->radius;
}

void Rectangle::setRadius(qreal radius) {
    if (radius != this->radius()) {
        Q_D(Rectangle);
        d->radius = radius;
        emit radiusChanged();

        if (d->complete) {
            this->update();
        }
    }
}

bool Rectangle::smooth() const {
    Q_D(const Rectangle);

    return d->smooth;
}

void Rectangle::setSmooth(bool smooth) {
    if (smooth != this->smooth()) {
        Q_D(Rectangle);
        d->smooth = smooth;
        emit smoothChanged();

        if (d->complete) {
            this->update();
        }
    }
}

void Rectangle::paintEvent(QPaintEvent *event) {
    Q_D(Rectangle);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, this->smooth());

    if (d->rectBorder) {
        painter.setPen(d->rectBorder->pen());
    }
    else {
        painter.setPen(Qt::transparent);
    }

    if ((d->rectGradient) && (!d->rectGradient->stops().isEmpty())) {
        QLinearGradient gradient(0, 0, 0, d->rectGradient->stops().last().first * this->height());
        gradient.setStops(d->rectGradient->stops());
        painter.setBrush(gradient);
    }
    else {
        painter.setBrush(this->color());
    }

    painter.drawRoundedRect(this->rect(), this->radius(), this->radius());

    event->accept();
}

RectanglePrivate::RectanglePrivate(Rectangle *parent) :
    ItemPrivate(parent),
    rectBorder(0),
    rectGradient(0),
    color(Qt::white),
    radius(0.0),
    smooth(false)
{
}

Border* RectanglePrivate::border() {
    if (!rectBorder) {
        Q_Q(Rectangle);
        rectBorder = new Border(q);
        q->connect(rectBorder, SIGNAL(colorChanged()), q, SLOT(update()));
        q->connect(rectBorder, SIGNAL(widthChanged()), q, SLOT(update()));
    }

    return rectBorder;
}

Gradient* RectanglePrivate::gradient() {
    return rectGradient;
}

void RectanglePrivate::setGradient(Gradient *gradient) {
    if (gradient == rectGradient) {
        return;
    }

    Q_Q(Rectangle);

    Gradient *oldGradient = rectGradient;
    rectGradient = gradient;
    q->connect(gradient, SIGNAL(stopsChanged()), q, SLOT(update()));

    if (oldGradient) {
        delete oldGradient;
    }
}

void RectanglePrivate::resetGradient() {
    this->setGradient(0);
}

#include "moc_rectangle_p.cpp"

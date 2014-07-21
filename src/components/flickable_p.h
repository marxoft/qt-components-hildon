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

#ifndef FLICKABLE_P_H
#define FLICKABLE_P_H

#include "anchors_p.h"
#include <QScrollArea>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class FlickablePrivate;

class Flickable : public QScrollArea, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PROPERTY(bool interactive READ interactive WRITE setInteractive NOTIFY interactiveChanged)
    Q_PROPERTY(bool moving READ moving NOTIFY movingChanged)
    Q_PROPERTY(bool atXBeginning READ atXBeginning NOTIFY contentXChanged)
    Q_PROPERTY(bool atXEnd READ atXEnd NOTIFY contentXChanged)
    Q_PROPERTY(bool atYBeginning READ atYBeginning NOTIFY contentYChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd NOTIFY contentYChanged)
    Q_PROPERTY(int contentX READ contentX WRITE setContentX NOTIFY contentXChanged)
    Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    Q_PROPERTY(qreal flickDeceleration READ flickDeceleration WRITE setFlickDeceleration NOTIFY flickDecelerationChanged)
    Q_PROPERTY(qreal maximumFlickVelocity READ maximumFlickVelocity WRITE setMaximumFlickVelocity NOTIFY maximumFlickVelocityChanged)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(Flickable::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit Flickable(QWidget *parent = 0);
    ~Flickable();

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

    bool interactive() const;
    void setInteractive(bool interactive);

    bool moving() const;

    bool atXBeginning() const;
    bool atXEnd() const;

    bool atYBeginning() const;
    bool atYEnd() const;

    int contentX() const;
    void setContentX(int x);

    int contentY() const;
    void setContentY(int y);

    qreal flickDeceleration() const;
    void setFlickDeceleration(qreal deceleration);

    qreal maximumFlickVelocity() const;
    void setMaximumFlickVelocity(qreal maximum);

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();
    void interactiveChanged();
    void movingChanged();
    void contentXChanged();
    void contentYChanged();
    void flickDecelerationChanged();
    void maximumFlickVelocityChanged();

protected:
    Flickable(FlickablePrivate &dd, QWidget *parent = 0);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<FlickablePrivate> d_ptr;

    Q_DECLARE_PRIVATE(Flickable)

private:
    Q_DISABLE_COPY(Flickable)
};

QML_DECLARE_TYPE(Flickable)

#endif // FLICKABLE_P_H

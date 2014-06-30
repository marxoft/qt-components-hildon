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

#ifndef LISTVIEW_P_H
#define LISTVIEW_P_H

#include "anchors_p.h"
#include <QListView>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeComponent;
class ListViewPrivate;

class ListView : public QListView, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PRIVATE_PROPERTY(ListView::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PROPERTY(bool interactive READ interactive WRITE setInteractive NOTIFY interactiveChanged)
    Q_PROPERTY(bool moving READ moving)
    Q_PROPERTY(bool atXBeginning READ atXBeginning NOTIFY contentXChanged)
    Q_PROPERTY(bool atXEnd READ atXEnd NOTIFY contentXChanged)
    Q_PROPERTY(bool atYBeginning READ atYBeginning NOTIFY contentYChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd NOTIFY contentYChanged)
    Q_PROPERTY(int contentX READ contentX WRITE setContentX NOTIFY contentXChanged)
    Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(ListView::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QVariant model READ model WRITE setModel)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QVariant rootIndex READ rootIndex WRITE setRootIndex)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QVariant currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PRIVATE_PROPERTY(ListView::d_func(), QDeclarativeComponent* delegate READ delegate WRITE setDelegate RESET resetDelegate)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit ListView(QWidget *parent = 0);
    ~ListView();

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

public slots:
    void positionViewAtBeginning();
    void positionViewAtEnd();
    void positionViewAtIndex(const QModelIndex &index, ScrollHint mode);
    void positionViewAtIndex(int index, ScrollHint mode);

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void interactiveChanged();
    void movingChanged();
    void contentXChanged();
    void contentYChanged();
    void flickDecelerationChanged();
    void maximumFlickVelocityChanged();

protected slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

protected:
    ListView(ListViewPrivate &dd, QWidget *parent = 0);

    void changeEvent(QEvent *event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

    void classBegin();
    void componentComplete();

    QScopedPointer<ListViewPrivate> d_ptr;

    Q_DISABLE_COPY(ListView)
    Q_DECLARE_PRIVATE(ListView)
};

QML_DECLARE_TYPE(ListView)
Q_DECLARE_METATYPE(QModelIndex)

#endif // LISTVIEW_P_H

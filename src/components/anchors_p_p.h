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

#ifndef ANCHORS_P_P_H
#define ANCHORS_P_P_H

#include "anchors_p.h"

inline bool operator==(const AnchorLine& a, const AnchorLine& b) {
    return (a.item == b.item) && (a.line == b.line);
}

inline bool operator!=(const AnchorLine& a, const AnchorLine& b) {
    return (a.item != b.item) || (a.line != b.line);
}

class AnchorsPrivate
{

public:
    AnchorsPrivate(QObject *i, Anchors *parent) :
        q_ptr(parent),
        leftMargin(0),
        rightMargin(0),
        topMargin(0),
        bottomMargin(0),
        margins(0),
        horizontalCenterOffset(0),
        verticalCenterOffset(0),
        itemComplete(false),
        updatingMe(false),
        inDestructor(false),
        leftMarginExplicit(false),
        rightMarginExplicit(false),
        topMarginExplicit(false),
        bottomMarginExplicit(false),
        updatingHorizontalAnchor(0),
        updatingVerticalAnchor(0),
        updatingCenterIn(0),
        updatingFill(0),
        item(i),
        centerIn(0),
        fill(0)
    {
    }

    virtual ~AnchorsPrivate() {}

    void clearItem(QObject *i);

    int calculateDependency(QObject *i);
    void addDepend(QObject *i);
    void remDepend(QObject *i);
    bool isItemComplete() const;

    void setItemX(int x);
    void setItemY(int y);
    void setItemPos(const QPoint &pos);
    void setItemWidth(int width);
    void setItemHeight(int height);
    void setItemSize(const QSize &size);

    void onItemCompleted();
    void update();

    bool checkHValid() const;
    bool checkVValid() const;
    bool checkHAnchorValid(AnchorLine anchor) const;
    bool checkVAnchorValid(AnchorLine anchor) const;
    bool calcStretch(const AnchorLine &edge1, const AnchorLine &edge2, int offset1, int offset2, AnchorLine::Line line, int &stretch);

    void _q_updateHorizontalAnchors();
    void _q_updateVerticalAnchors();
    void centerInChanged();
    void fillChanged();

    Anchors *q_ptr;

    AnchorLine left;
    AnchorLine right;
    AnchorLine top;
    AnchorLine bottom;
    AnchorLine horizontalCenter;
    AnchorLine verticalCenter;

    int leftMargin;
    int rightMargin;
    int topMargin;
    int bottomMargin;
    int margins;
    int horizontalCenterOffset;
    int verticalCenterOffset;

    bool itemComplete;
    bool updatingMe;
    bool inDestructor;
    bool leftMarginExplicit;
    bool rightMarginExplicit;
    bool topMarginExplicit;
    bool bottomMarginExplicit;
    uint updatingHorizontalAnchor;
    uint updatingVerticalAnchor;
    uint updatingCenterIn;
    uint updatingFill;

    Anchors::AnchorFlags usedAnchors;

    QObject *item;
    QObject *centerIn;
    QObject *fill;

    Q_DECLARE_PUBLIC(Anchors)
};

QML_DECLARE_TYPE(AnchorLine)

#endif // ANCHORS_P_P_H

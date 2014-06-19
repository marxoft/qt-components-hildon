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
#include <QWidget>

inline bool operator==(const AnchorLine& a, const AnchorLine& b) {
    return (a.widget == b.widget) && (a.line == b.line);
}

inline bool operator!=(const AnchorLine& a, const AnchorLine& b) {
    return (a.widget != b.widget) || (a.line != b.line);
}

class AnchorsPrivate
{

public:
    AnchorsPrivate(QWidget *w, Anchors *parent) :
        q_ptr(parent),
        leftMargin(0),
        rightMargin(0),
        topMargin(0),
        bottomMargin(0),
        margins(0),
        horizontalCenterOffset(0),
        verticalCenterOffset(0),
        widgetComplete(false),
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
        widget(w),
        centerIn(0),
        fill(0)
    {
    }

    virtual ~AnchorsPrivate() {}

    void clearWidget(QWidget *w);

    int calculateDependency(QWidget *w);
    void addDepend(QWidget *w);
    void remDepend(QWidget *w);
    bool isWidgetComplete() const;

    void setWidgetX(int x);
    void setWidgetY(int y);
    void setWidgetPos(const QPoint &pos);
    void setWidgetWidth(int width);
    void setWidgetHeight(int height);
    void setWidgetSize(const QSize &size);

    void onWidgetCompleted();
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

    bool widgetComplete;
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

    QWidget *widget;
    QWidget *centerIn;
    QWidget *fill;

    Q_DECLARE_PUBLIC(Anchors)
};

QML_DECLARE_TYPE(AnchorLine)

#endif // ANCHORS_P_P_H

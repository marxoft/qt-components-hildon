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

#ifndef ANCHORS_P_H
#define ANCHORS_P_H

#include "anchorline_p.h"
#include <QObject>
#include <qdeclarative.h>

class AnchorsPrivate;

class Anchors : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AnchorLine left READ left WRITE setLeft RESET resetLeft NOTIFY leftChanged)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin RESET resetLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(AnchorLine right READ right WRITE setRight RESET resetRight NOTIFY rightChanged)
    Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin RESET resetRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(AnchorLine top READ top WRITE setTop RESET resetTop NOTIFY topChanged)
    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin RESET resetTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(AnchorLine bottom READ bottom WRITE setBottom RESET resetBottom NOTIFY bottomChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin WRITE setBottomMargin RESET resetBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(int margins READ margins WRITE setMargins NOTIFY marginsChanged)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter WRITE setHorizontalCenter RESET resetHorizontalCenter NOTIFY horizontalCenterChanged)
    Q_PROPERTY(int horizontalCenterOffset READ horizontalCenterOffset WRITE setHorizontalCenterOffset NOTIFY horizontalCenterOffsetChanged)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter WRITE setVerticalCenter RESET resetVerticalCenter NOTIFY verticalCenterChanged)
    Q_PROPERTY(int verticalCenterOffset READ verticalCenterOffset WRITE setVerticalCenterOffset NOTIFY verticalCenterOffsetChanged)
    Q_PROPERTY(QObject* centerIn READ centerIn WRITE setCenterIn RESET resetCenterIn NOTIFY centerInChanged)
    Q_PROPERTY(QObject* fill READ fill WRITE setFill RESET resetFill NOTIFY fillChanged)

public:
    enum Anchor {
        LeftAnchor = 0x01,
        RightAnchor = 0x02,
        TopAnchor = 0x04,
        BottomAnchor = 0x08,
        HCenterAnchor = 0x10,
        VCenterAnchor = 0x20,
        Horizontal_Mask = LeftAnchor | RightAnchor | HCenterAnchor,
        Vertical_Mask = TopAnchor | BottomAnchor | VCenterAnchor
    };

    Q_DECLARE_FLAGS(AnchorFlags, Anchor)

    explicit Anchors(QObject *item = 0, QObject *parent = 0);
    ~Anchors();

    AnchorLine left() const;
    void setLeft(const AnchorLine &edge);
    void resetLeft();

    int leftMargin() const;
    void setLeftMargin(int offset);
    void resetLeftMargin();

    AnchorLine right() const;
    void setRight(const AnchorLine &edge);
    void resetRight();

    int rightMargin() const;
    void setRightMargin(int offset);
    void resetRightMargin();

    AnchorLine top() const;
    void setTop(const AnchorLine &edge);
    void resetTop();

    int topMargin() const;
    void setTopMargin(int offset);
    void resetTopMargin();

    AnchorLine bottom() const;
    void setBottom(const AnchorLine &edge);
    void resetBottom();

    int bottomMargin() const;
    void setBottomMargin(int offset);
    void resetBottomMargin();

    int margins() const;
    void setMargins(int offset);

    AnchorLine horizontalCenter() const;
    void setHorizontalCenter(const AnchorLine &edge);
    void resetHorizontalCenter();

    int horizontalCenterOffset() const;
    void setHorizontalCenterOffset(int offset);

    AnchorLine verticalCenter() const;
    void setVerticalCenter(const AnchorLine &edge);
    void resetVerticalCenter();

    int verticalCenterOffset() const;
    void setVerticalCenterOffset(int offset);

    QObject* centerIn() const;
    void setCenterIn(QObject *c);
    void resetCenterIn();

    QObject* fill() const;
    void setFill(QObject *f);
    void resetFill();

    AnchorFlags usedAnchors() const;

signals:
    void leftChanged();
    void leftMarginChanged();
    void rightChanged();
    void rightMarginChanged();
    void topChanged();
    void topMarginChanged();
    void bottomChanged();
    void bottomMarginChanged();
    void marginsChanged();
    void horizontalCenterChanged();
    void horizontalCenterOffsetChanged();
    void verticalCenterChanged();
    void verticalCenterOffsetChanged();
    void centerInChanged();
    void fillChanged();

private:
    Anchors(AnchorsPrivate &dd, QObject *parent = 0);

    QScopedPointer<AnchorsPrivate> d_ptr;

    friend class ItemPrivate;
    friend class ListItemPrivate;
    friend class ListItemContentPrivate;

    Q_DISABLE_COPY(Anchors)
    Q_DECLARE_PRIVATE(Anchors)

    Q_PRIVATE_SLOT(d_func(), void centerInChanged())
    Q_PRIVATE_SLOT(d_func(), void fillChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_updateHorizontalAnchors())
    Q_PRIVATE_SLOT(d_func(), void _q_updateVerticalAnchors())
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Anchors::AnchorFlags)

QML_DECLARE_TYPE(Anchors)

#endif // ANCHORS_P_H

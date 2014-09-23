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

#include "listitemprogressbar_p.h"
#include "listitemcontent_p_p.h"
#include <QPainter>
#include <QApplication>

ListItemProgressBar::ListItemProgressBar(QObject *parent) :
    ListItemContent(parent),
    QStyleOptionProgressBarV2()
{
}

int ListItemProgressBar::getMinimum() const {
    return minimum;
}

void ListItemProgressBar::setMinimum(int min) {
    if (min != this->getMinimum()) {
        minimum = min;
        emit minimumChanged();
    }
}

int ListItemProgressBar::getMaximum() const {
    return maximum;
}

void ListItemProgressBar::setMaximum(int max) {
    if (max != this->getMaximum()) {
        maximum = max;
        emit maximumChanged();
    }
}

int ListItemProgressBar::getProgress() const {
    return progress;
}

void ListItemProgressBar::setProgress(int p) {
    if (p != this->getProgress()) {
        progress = p;
        emit progressChanged();
    }
}

QString ListItemProgressBar::getText() const {
    return text;
}

void ListItemProgressBar::setText(const QString &t) {
    if (t != this->getText()) {
        text = t;
        emit textChanged();
    }
}

Qt::Alignment ListItemProgressBar::getTextAlignment() const {
    return textAlignment;
}

void ListItemProgressBar::setTextAlignment(Qt::Alignment align) {
    if (align != this->getTextAlignment()) {
        textAlignment = align;
        emit textAlignmentChanged();
    }
}

bool ListItemProgressBar::getTextVisible() const {
    return textVisible;
}

void ListItemProgressBar::setTextVisible(bool visible) {
    if (visible != this->getTextVisible()) {
        textVisible = visible;
        emit textVisibleChanged();
    }
}

Qt::Orientation ListItemProgressBar::getOrientation() const {
    return orientation;
}

void ListItemProgressBar::setOrientation(Qt::Orientation orient) {
    if (orient != this->getOrientation()) {
        orientation = orient;
        emit orientationChanged();
    }
}

bool ListItemProgressBar::getInvertedAppearance() const {
    return invertedAppearance;
}

void ListItemProgressBar::setInvertedAppearance(bool inverted) {
    if (inverted != this->getInvertedAppearance()) {
        invertedAppearance = inverted;
        emit invertedAppearanceChanged();
    }
}

ListItemProgressBar::Direction ListItemProgressBar::getTextDirection() const {
    return bottomToTop ? BottomToTop : TopToBottom;
}

void ListItemProgressBar::setTextDirection(Direction dir) {
    if (dir != this->getTextDirection()) {
        switch (dir) {
        case BottomToTop:
            bottomToTop = true;
            break;
        default:
            bottomToTop = false;
            break;
        }

        emit textDirectionChanged();
    }
}

void ListItemProgressBar::paint(QPainter *painter, const QRect &r) {
    Q_D(const ListItemContent);

    painter->save();
    painter->setOpacity(painter->opacity() * this->opacity());
    painter->setRenderHint(QPainter::Antialiasing, this->smooth());
    QStyleOptionProgressBarV2::rect = QRect(r.left() + this->x(),
                 r.top() + this->y(),
                 this->width(),
                 this->height());
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, this, painter);
    painter->restore();

    foreach (ListItemContent *content, d->contentList) {
        if (content->isVisible()) {
            content->paint(painter,
                           QRect(r.left() + this->x(),
                                 r.top() + this->y(),
                                 this->width(),
                                 this->height()));
        }
    }
}

#include "moc_listitemprogressbar_p.cpp"

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

#include "platformstyle_p.h"
#include <QMaemo5Style>

PlatformStyle::PlatformStyle(QObject *parent) :
    QObject(parent)
{
}

PlatformStyle::~PlatformStyle() {}

QColor PlatformStyle::defaultTextColor() {
    return QMaemo5Style::standardColor("DefaultTextColor");
}

QColor PlatformStyle::secondaryTextColor() {
    return QMaemo5Style::standardColor("SecondaryTextColor");
}

QColor PlatformStyle::activeTextColor() {
    return QMaemo5Style::standardColor("ActiveTextColor");
}

QColor PlatformStyle::disabledTextColor() {
    return QMaemo5Style::standardColor("DisabledTextColor");
}

QColor PlatformStyle::paintedTextColor() {
    return QMaemo5Style::standardColor("PaintedTextColor");
}

QColor PlatformStyle::reversedTextColor() {
    return QMaemo5Style::standardColor("ReversedTextColor");
}

QColor PlatformStyle::reversedSecondaryTextColor() {
    return QMaemo5Style::standardColor("ReversedSecondaryTextColor");
}

QColor PlatformStyle::reversedActiveTextColor() {
    return QMaemo5Style::standardColor("ReversedActiveTextColor");
}

QColor PlatformStyle::reversedDisabledTextColor() {
    return QMaemo5Style::standardColor("ReversedDisabledTextColor");
}

QColor PlatformStyle::reversedPaintedTextColor() {
    return QMaemo5Style::standardColor("ReversedPaintedTextColor");
}

QColor PlatformStyle::defaultBackgroundColor() {
    return QMaemo5Style::standardColor("DefaultBackgroundColor");
}

QColor PlatformStyle::darkerBackgroundColor() {
    return QMaemo5Style::standardColor("DarkerBackgroundColor");
}

QColor PlatformStyle::reversedBackgroundColor() {
    return QMaemo5Style::standardColor("ReversedBackgroundColor");
}

QColor PlatformStyle::selectionColor() {
    return QMaemo5Style::standardColor("SelectionColor");
}

QColor PlatformStyle::reversedSelectionColor() {
    return QMaemo5Style::standardColor("ReversedSelectionColor");
}

QColor PlatformStyle::contentBackgroundColor() {
    return QMaemo5Style::standardColor("ContentBackgroundColor");
}

QColor PlatformStyle::contentFrameColor() {
    return QMaemo5Style::standardColor("ContentFrameColor");
}

QColor PlatformStyle::contentSelectionColor() {
    return QMaemo5Style::standardColor("ContentSelectionColor");
}

QColor PlatformStyle::titleTextColor() {
    return QMaemo5Style::standardColor("TitleTextColor");
}

QColor PlatformStyle::buttonTextColor() {
    return QMaemo5Style::standardColor("ButtonTextColor");
}

QColor PlatformStyle::buttonTextPressedColor() {
    return QMaemo5Style::standardColor("ButtonTextPressedColor");
}

QColor PlatformStyle::buttonTextDisabledColor() {
    return QMaemo5Style::standardColor("ButtonTextDisabledColor");
}

QColor PlatformStyle::accentColor1() {
    return QMaemo5Style::standardColor("AccentColor1");
}

QColor PlatformStyle::accentColor2() {
    return QMaemo5Style::standardColor("AccentColor2");
}

QColor PlatformStyle::accentColor3() {
    return QMaemo5Style::standardColor("AccentColor3");
}

QColor PlatformStyle::attentionColor() {
    return QMaemo5Style::standardColor("AttentionColor");
}

QColor PlatformStyle::notificationBackgroundColor() {
    return QMaemo5Style::standardColor("NotificationBackgroundColor");
}

QColor PlatformStyle::notificationTextColor() {
    return QMaemo5Style::standardColor("NotificationTextColor");
}

QColor PlatformStyle::notificationSecondaryTextColor() {
    return QMaemo5Style::standardColor("NotificationSecondaryTextColor");
}

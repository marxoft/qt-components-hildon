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

#include "qchstyle.h"
#include <QMaemo5Style>

QchStyle::QchStyle(QObject *parent) :
    QObject(parent)
{
}

int QchStyle::paddingSmall() {
    return 4;
}

int QchStyle::paddingMedium() {
    return 8;
}

int QchStyle::paddingLarge() {
    return 16;
}

int QchStyle::fontSizeSmall() {
    return 13;
}

int QchStyle::fontSizeMedium() {
    return 18;
}

int QchStyle::fontSizeLarge() {
    return 24;
}

int QchStyle::iconSizeSmall() {
    return 24;
}

int QchStyle::iconSizeLarge() {
    return 48;
}

QColor QchStyle::defaultTextColor() {
    return QMaemo5Style::standardColor("DefaultTextColor");
}

QColor QchStyle::secondaryTextColor() {
    return QMaemo5Style::standardColor("SecondaryTextColor");
}

QColor QchStyle::activeTextColor() {
    return QMaemo5Style::standardColor("ActiveTextColor");
}

QColor QchStyle::disabledTextColor() {
    return QMaemo5Style::standardColor("DisabledTextColor");
}

QColor QchStyle::paintedTextColor() {
    return QMaemo5Style::standardColor("PaintedTextColor");
}

QColor QchStyle::reversedTextColor() {
    return QMaemo5Style::standardColor("ReversedTextColor");
}

QColor QchStyle::reversedSecondaryTextColor() {
    return QMaemo5Style::standardColor("ReversedSecondaryTextColor");
}

QColor QchStyle::reversedActiveTextColor() {
    return QMaemo5Style::standardColor("ReversedActiveTextColor");
}

QColor QchStyle::reversedDisabledTextColor() {
    return QMaemo5Style::standardColor("ReversedDisabledTextColor");
}

QColor QchStyle::reversedPaintedTextColor() {
    return QMaemo5Style::standardColor("ReversedPaintedTextColor");
}

QColor QchStyle::defaultBackgroundColor() {
    return QMaemo5Style::standardColor("DefaultBackgroundColor");
}

QColor QchStyle::darkerBackgroundColor() {
    return QMaemo5Style::standardColor("DarkerBackgroundColor");
}

QColor QchStyle::reversedBackgroundColor() {
    return QMaemo5Style::standardColor("ReversedBackgroundColor");
}

QColor QchStyle::selectionColor() {
    return QMaemo5Style::standardColor("SelectionColor");
}

QColor QchStyle::reversedSelectionColor() {
    return QMaemo5Style::standardColor("ReversedSelectionColor");
}

QColor QchStyle::contentBackgroundColor() {
    return QMaemo5Style::standardColor("ContentBackgroundColor");
}

QColor QchStyle::contentFrameColor() {
    return QMaemo5Style::standardColor("ContentFrameColor");
}

QColor QchStyle::contentSelectionColor() {
    return QMaemo5Style::standardColor("ContentSelectionColor");
}

QColor QchStyle::titleTextColor() {
    return QMaemo5Style::standardColor("TitleTextColor");
}

QColor QchStyle::buttonTextColor() {
    return QMaemo5Style::standardColor("ButtonTextColor");
}

QColor QchStyle::buttonTextPressedColor() {
    return QMaemo5Style::standardColor("ButtonTextPressedColor");
}

QColor QchStyle::buttonTextDisabledColor() {
    return QMaemo5Style::standardColor("ButtonTextDisabledColor");
}

QColor QchStyle::accentColor1() {
    return QMaemo5Style::standardColor("AccentColor1");
}

QColor QchStyle::accentColor2() {
    return QMaemo5Style::standardColor("AccentColor2");
}

QColor QchStyle::accentColor3() {
    return QMaemo5Style::standardColor("AccentColor3");
}

QColor QchStyle::attentionColor() {
    return QMaemo5Style::standardColor("AttentionColor");
}

QColor QchStyle::notificationBackgroundColor() {
    return QMaemo5Style::standardColor("NotificationBackgroundColor");
}

QColor QchStyle::notificationTextColor() {
    return QMaemo5Style::standardColor("NotificationTextColor");
}

QColor QchStyle::notificationSecondaryTextColor() {
    return QMaemo5Style::standardColor("NotificationSecondaryTextColor");
}

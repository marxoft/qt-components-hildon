/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchstyle.h"
#include "qchtheme.h"
#include <QMaemo5Style>

/*!
    \class Style
    \brief Provides access to style constants.
    
    \ingroup components
    
    \note Style is a context property and cannot be created in QML.
*/
QchStyle::QchStyle(QObject *parent) :
    QObject(parent),
    m_theme(new QchTheme(this))
{
    connect(m_theme, SIGNAL(changed()), this, SIGNAL(changed()));
}

/*!
    \brief Small padding constant.
*/
int QchStyle::paddingSmall() {
    return 4;
}

/*!
    \brief Medium padding constant.
*/
int QchStyle::paddingMedium() {
    return 8;
}

/*!
    \brief Large padding constant.
*/
int QchStyle::paddingLarge() {
    return 16;
}

/*!
    \brief Small font point size constant.
*/
int QchStyle::fontSizeSmall() {
    return 13;
}

/*!
    \brief Medium font point size constant.
*/
int QchStyle::fontSizeMedium() {
    return 18;
}

/*!
    \brief Large font point size constant.
*/
int QchStyle::fontSizeLarge() {
    return 26;
}

/*!
    \brief XLarge font point size constant.
*/
int QchStyle::fontSizeXLarge() {
    return 31;
}

/*!
    \brief XXLarge font point size constant.
*/
int QchStyle::fontSizeXXLarge() {
    return 52;
}

/*!
    \brief XXXLarge font point size constant.
*/
int QchStyle::fontSizeXXXLarge() {
    return 74;
}

/*!
    \brief Small icon size constant.
*/
int QchStyle::iconSizeSmall() {
    return 24;
}

/*!
    \brief Large icon size constant.
*/
int QchStyle::iconSizeLarge() {
    return 48;
}

/*!
    \brief Enabled opacity constant.
*/
qreal QchStyle::enabledOpacity() {
    return 1.0;
}

/*!
    \brief Disabled opacity constant.
*/
qreal QchStyle::disabledOpacity() {
    return 0.3;
}

/*!
    \brief Default text color constant.
*/
QColor QchStyle::defaultTextColor() {
    return QMaemo5Style::standardColor("DefaultTextColor");
}

/*!
    \brief Secondary text color constant.
*/
QColor QchStyle::secondaryTextColor() {
    return QMaemo5Style::standardColor("SecondaryTextColor");
}

/*!
    \brief Active text color constant.
*/
QColor QchStyle::activeTextColor() {
    return QMaemo5Style::standardColor("ActiveTextColor");
}

/*!
    \brief Disabled text color constant.
*/
QColor QchStyle::disabledTextColor() {
    return QMaemo5Style::standardColor("DisabledTextColor");
}

/*!
    \brief Painted text color constant.
*/
QColor QchStyle::paintedTextColor() {
    return QMaemo5Style::standardColor("PaintedTextColor");
}

/*!
    \brief Reversed text color constant.
*/
QColor QchStyle::reversedTextColor() {
    return QMaemo5Style::standardColor("ReversedTextColor");
}

/*!
    \brief Reversed secondary text color constant.
*/
QColor QchStyle::reversedSecondaryTextColor() {
    return QMaemo5Style::standardColor("ReversedSecondaryTextColor");
}

/*!
    \brief Reversed active text color constant.
*/
QColor QchStyle::reversedActiveTextColor() {
    return QMaemo5Style::standardColor("ReversedActiveTextColor");
}

/*!
    \brief Reversed disabled text color constant.
*/
QColor QchStyle::reversedDisabledTextColor() {
    return QMaemo5Style::standardColor("ReversedDisabledTextColor");
}

/*!
    \brief Reversed painted text color constant.
*/
QColor QchStyle::reversedPaintedTextColor() {
    return QMaemo5Style::standardColor("ReversedPaintedTextColor");
}

/*!
    \brief Default background color constant.
*/
QColor QchStyle::defaultBackgroundColor() {
    return QMaemo5Style::standardColor("DefaultBackgroundColor");
}

/*!
    \brief Darker background color constant.
*/
QColor QchStyle::darkerBackgroundColor() {
    return QMaemo5Style::standardColor("DarkerBackgroundColor");
}

/*!
    \brief Reversed background color constant.
*/
QColor QchStyle::reversedBackgroundColor() {
    return QMaemo5Style::standardColor("ReversedBackgroundColor");
}

/*!
    \brief Selection color constant.
*/
QColor QchStyle::selectionColor() {
    return QMaemo5Style::standardColor("SelectionColor");
}

/*!
    \brief Reversed selection color constant.
*/
QColor QchStyle::reversedSelectionColor() {
    return QMaemo5Style::standardColor("ReversedSelectionColor");
}

/*!
    \brief Content background color constant.
*/
QColor QchStyle::contentBackgroundColor() {
    return QMaemo5Style::standardColor("ContentBackgroundColor");
}

/*!
    \brief Content frame color constant.
*/
QColor QchStyle::contentFrameColor() {
    return QMaemo5Style::standardColor("ContentFrameColor");
}

/*!
    \brief Content selection color constant.
*/
QColor QchStyle::contentSelectionColor() {
    return QMaemo5Style::standardColor("ContentSelectionColor");
}

/*!
    \brief Title text color constant.
*/
QColor QchStyle::titleTextColor() {
    return QMaemo5Style::standardColor("TitleTextColor");
}

/*!
    \brief Button text color constant.
*/
QColor QchStyle::buttonTextColor() {
    return QMaemo5Style::standardColor("ButtonTextColor");
}

/*!
    \brief Pressed button text color constant.
*/
QColor QchStyle::buttonTextPressedColor() {
    return QMaemo5Style::standardColor("ButtonTextPressedColor");
}

/*!
    \brief Disabled button text color constant.
*/
QColor QchStyle::buttonTextDisabledColor() {
    return QMaemo5Style::standardColor("ButtonTextDisabledColor");
}

/*!
    \brief Accent color 1 constant.
*/
QColor QchStyle::accentColor1() {
    return QMaemo5Style::standardColor("AccentColor1");
}

/*!
    \brief Accent color 2 constant.
*/
QColor QchStyle::accentColor2() {
    return QMaemo5Style::standardColor("AccentColor2");
}

/*!
    \brief Accent color 3 constant.
*/
QColor QchStyle::accentColor3() {
    return QMaemo5Style::standardColor("AccentColor3");
}

/*!
    \brief Attention color constant.
*/
QColor QchStyle::attentionColor() {
    return QMaemo5Style::standardColor("AttentionColor");
}

/*!
    \brief Notification background color constant.
*/
QColor QchStyle::notificationBackgroundColor() {
    return QMaemo5Style::standardColor("NotificationBackgroundColor");
}

/*!
    \brief Notification text color constant.
*/
QColor QchStyle::notificationTextColor() {
    return QMaemo5Style::standardColor("NotificationTextColor");
}

/*!
    \brief Notification secondary text color constant.
*/
QColor QchStyle::notificationSecondaryTextColor() {
    return QMaemo5Style::standardColor("NotificationSecondaryTextColor");
}

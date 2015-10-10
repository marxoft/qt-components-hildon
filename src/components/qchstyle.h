/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHSTYLE_H
#define QCHSTYLE_H

#include <QObject>
#include <QColor>

class QchStyle : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int paddingSmall READ paddingSmall CONSTANT)
    Q_PROPERTY(int paddingMedium READ paddingMedium CONSTANT)
    Q_PROPERTY(int paddingLarge READ paddingLarge CONSTANT)
    Q_PROPERTY(int fontSizeSmall READ fontSizeSmall CONSTANT)
    Q_PROPERTY(int fontSizeMedium READ fontSizeMedium CONSTANT)
    Q_PROPERTY(int fontSizeLarge READ fontSizeLarge CONSTANT)
    Q_PROPERTY(int fontSizeXLarge READ fontSizeXLarge CONSTANT)
    Q_PROPERTY(int fontSizeXXLarge READ fontSizeXXLarge CONSTANT)
    Q_PROPERTY(int fontSizeXXXLarge READ fontSizeXXXLarge CONSTANT)
    Q_PROPERTY(int iconSizeSmall READ iconSizeSmall CONSTANT)
    Q_PROPERTY(int iconSizeLarge READ iconSizeLarge CONSTANT)
    Q_PROPERTY(qreal enabledOpacity READ enabledOpacity CONSTANT)
    Q_PROPERTY(qreal disabledOpacity READ disabledOpacity CONSTANT)
    Q_PROPERTY(QColor defaultTextColor READ defaultTextColor CONSTANT)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor CONSTANT)
    Q_PROPERTY(QColor activeTextColor READ activeTextColor CONSTANT)
    Q_PROPERTY(QColor disabledTextColor READ disabledTextColor CONSTANT)
    Q_PROPERTY(QColor paintedTextColor READ paintedTextColor CONSTANT)
    Q_PROPERTY(QColor reversedTextColor READ reversedTextColor CONSTANT)
    Q_PROPERTY(QColor reversedSecondaryTextColor READ reversedSecondaryTextColor CONSTANT)
    Q_PROPERTY(QColor reversedActiveTextColor READ reversedActiveTextColor CONSTANT)
    Q_PROPERTY(QColor reversedDisabledTextColor READ reversedDisabledTextColor CONSTANT)
    Q_PROPERTY(QColor reversedPaintedTextColor READ reversedPaintedTextColor CONSTANT)
    Q_PROPERTY(QColor defaultBackgroundColor READ defaultBackgroundColor CONSTANT)
    Q_PROPERTY(QColor darkerBackgroundColor READ darkerBackgroundColor CONSTANT)
    Q_PROPERTY(QColor reversedBackgroundColor READ reversedBackgroundColor CONSTANT)
    Q_PROPERTY(QColor selectionColor READ selectionColor CONSTANT)
    Q_PROPERTY(QColor reversedSelectionColor READ reversedSelectionColor CONSTANT)
    Q_PROPERTY(QColor contentBackgroundColor READ contentBackgroundColor CONSTANT)
    Q_PROPERTY(QColor contentFrameColor READ contentFrameColor CONSTANT)
    Q_PROPERTY(QColor contentSelectionColor READ contentSelectionColor CONSTANT)
    Q_PROPERTY(QColor titleTextColor READ titleTextColor CONSTANT)
    Q_PROPERTY(QColor buttonTextColor READ buttonTextColor CONSTANT)
    Q_PROPERTY(QColor buttonTextPressedColor READ buttonTextPressedColor CONSTANT)
    Q_PROPERTY(QColor buttonTextDisabledColor READ buttonTextDisabledColor CONSTANT)
    Q_PROPERTY(QColor accentColor1 READ accentColor1 CONSTANT)
    Q_PROPERTY(QColor accentColor2 READ accentColor2 CONSTANT)
    Q_PROPERTY(QColor accentColor3 READ accentColor3 CONSTANT)
    Q_PROPERTY(QColor attentionColor READ attentionColor CONSTANT)
    Q_PROPERTY(QColor notificationBackgroundColor READ notificationBackgroundColor CONSTANT)
    Q_PROPERTY(QColor notificationTextColor READ notificationTextColor CONSTANT)
    Q_PROPERTY(QColor notificationSecondaryTextColor READ notificationSecondaryTextColor CONSTANT)

public:
    explicit QchStyle(QObject *parent = 0);

    static int paddingSmall();
    static int paddingMedium();
    static int paddingLarge();

    static int fontSizeSmall();
    static int fontSizeMedium();
    static int fontSizeLarge();
    static int fontSizeXLarge();
    static int fontSizeXXLarge();
    static int fontSizeXXXLarge();
    
    static int iconSizeSmall();
    static int iconSizeLarge();
    
    static qreal enabledOpacity();
    static qreal disabledOpacity();

    static QColor defaultTextColor();
    static QColor secondaryTextColor();
    static QColor activeTextColor();
    static QColor disabledTextColor();
    static QColor paintedTextColor();
    static QColor reversedTextColor();
    static QColor reversedSecondaryTextColor();
    static QColor reversedActiveTextColor();
    static QColor reversedDisabledTextColor();
    static QColor reversedPaintedTextColor();
    static QColor defaultBackgroundColor();
    static QColor darkerBackgroundColor();
    static QColor reversedBackgroundColor();
    static QColor selectionColor();
    static QColor reversedSelectionColor();
    static QColor contentBackgroundColor();
    static QColor contentFrameColor();
    static QColor contentSelectionColor();
    static QColor titleTextColor();
    static QColor buttonTextColor();
    static QColor buttonTextPressedColor();
    static QColor buttonTextDisabledColor();
    static QColor accentColor1();
    static QColor accentColor2();
    static QColor accentColor3();
    static QColor attentionColor();
    static QColor notificationBackgroundColor();
    static QColor notificationTextColor();
    static QColor notificationSecondaryTextColor();
};

#endif // QCHSTYLE_H

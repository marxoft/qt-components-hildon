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

#ifndef QCHSTYLE_H
#define QCHSTYLE_H

#include <QObject>
#include <QColor>
#include <qdeclarative.h>

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
    Q_PROPERTY(QString fontFamily READ fontFamily NOTIFY changed)
    Q_PROPERTY(QColor defaultTextColor READ defaultTextColor NOTIFY changed)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor NOTIFY changed)
    Q_PROPERTY(QColor activeTextColor READ activeTextColor NOTIFY changed)
    Q_PROPERTY(QColor disabledTextColor READ disabledTextColor NOTIFY changed)
    Q_PROPERTY(QColor paintedTextColor READ paintedTextColor NOTIFY changed)
    Q_PROPERTY(QColor reversedTextColor READ reversedTextColor NOTIFY changed)
    Q_PROPERTY(QColor reversedSecondaryTextColor READ reversedSecondaryTextColor NOTIFY changed)
    Q_PROPERTY(QColor reversedActiveTextColor READ reversedActiveTextColor NOTIFY changed)
    Q_PROPERTY(QColor reversedDisabledTextColor READ reversedDisabledTextColor NOTIFY changed)
    Q_PROPERTY(QColor reversedPaintedTextColor READ reversedPaintedTextColor NOTIFY changed)
    Q_PROPERTY(QColor defaultBackgroundColor READ defaultBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor darkerBackgroundColor READ darkerBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor reversedBackgroundColor READ reversedBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor selectionColor READ selectionColor NOTIFY changed)
    Q_PROPERTY(QColor reversedSelectionColor READ reversedSelectionColor NOTIFY changed)
    Q_PROPERTY(QColor contentBackgroundColor READ contentBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor contentFrameColor READ contentFrameColor NOTIFY changed)
    Q_PROPERTY(QColor contentSelectionColor READ contentSelectionColor NOTIFY changed)
    Q_PROPERTY(QColor titleTextColor READ titleTextColor NOTIFY changed)
    Q_PROPERTY(QColor buttonTextColor READ buttonTextColor NOTIFY changed)
    Q_PROPERTY(QColor buttonTextPressedColor READ buttonTextPressedColor NOTIFY changed)
    Q_PROPERTY(QColor buttonTextDisabledColor READ buttonTextDisabledColor NOTIFY changed)
    Q_PROPERTY(QColor accentColor1 READ accentColor1 NOTIFY changed)
    Q_PROPERTY(QColor accentColor2 READ accentColor2 NOTIFY changed)
    Q_PROPERTY(QColor accentColor3 READ accentColor3 NOTIFY changed)
    Q_PROPERTY(QColor attentionColor READ attentionColor NOTIFY changed)
    Q_PROPERTY(QColor notificationBackgroundColor READ notificationBackgroundColor NOTIFY changed)
    Q_PROPERTY(QColor notificationTextColor READ notificationTextColor NOTIFY changed)
    Q_PROPERTY(QColor notificationSecondaryTextColor READ notificationSecondaryTextColor NOTIFY changed)

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
    
    static QString fontFamily();

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

Q_SIGNALS:
    void changed();

private:
    Q_DISABLE_COPY(QchStyle)
};

QML_DECLARE_TYPE(QchStyle)

#endif // QCHSTYLE_H

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

#include "qchfontmetrics.h"

/*!
    \class FontMetrics
    \brief Provides metrics for a given font.
    
    \ingroup components
    
    FontMetrics calculates the size of characters and strings for a given font.

    It provides a subset of the C++ QFontMetrics API, with the added ability to change the font that is used for
    calculations via the font property.
    
    \sa TextMetrics
*/
QchFontMetrics::QchFontMetrics(QObject *parent) :
    QObject(parent),
    m_fontMetrics(QFontMetrics(m_font))
{
}

/*!
    \brief The ascent of the font.
    
    \sa descent, height
*/
int QchFontMetrics::ascent() const {
    return m_fontMetrics.ascent();
}

/*!
    \brief The average width of glyphs in the font.
*/
int QchFontMetrics::averageCharacterWidth() const {
    return m_fontMetrics.averageCharWidth();
}

/*!
    \brief The descent of the font.
    
    \sa ascent, height
*/
int QchFontMetrics::descent() const {
    return m_fontMetrics.descent();
}

/*!
    \brief The font used for the metrics calculations.
*/
QFont QchFontMetrics::font() const {
    return m_font;
}

void QchFontMetrics::setFont(const QFont &f) {
    if (f != font()) {
        m_font = f;
        m_fontMetrics = QFontMetrics(f);
        emit changed();
    }
}

/*!
    \brief The height of the font.
*/
int QchFontMetrics::height() const {
    return m_fontMetrics.height();
}

/*!
    \brief The leading of the font.
*/
int QchFontMetrics::leading() const {
    return m_fontMetrics.leading();
}

/*!
    \brief The distance from one base line to the next.
*/
int QchFontMetrics::lineSpacing() const {
    return m_fontMetrics.lineSpacing();
}

/*!
    \brief The width of the underline and strikeout lines, adjusted for the point size of the font.
*/
int QchFontMetrics::lineWidth() const {
    return m_fontMetrics.lineWidth();
}

/*!
    \brief The width of the widest character in the font.
*/
int QchFontMetrics::maximumCharacterWidth() const {
    return m_fontMetrics.maxWidth();
}

/*!
    \brief The minimum left bearing of the font.
*/
int QchFontMetrics::minimumLeftBearing() const {
    return m_fontMetrics.minLeftBearing();
}

/*!
    \brief The minimum right bearing of the font.
*/
int QchFontMetrics::minimumRightBearing() const {
    return m_fontMetrics.minRightBearing();
}

/*!
    \brief The distance from the base line to where an overline should be drawn.
    
    \sa strikeOutPosition, underlinePosition
*/
int QchFontMetrics::overlinePosition() const {
    return m_fontMetrics.overlinePos();
}

/*!
    \brief The distance from the base line to where the strikeout line should be drawn.
    
    \sa overlinePosition, underlinePosition
*/
int QchFontMetrics::strikeOutPosition() const {
    return m_fontMetrics.strikeOutPos();
}

/*!
    \brief The distance from the base line to where an underscore should be drawn.
    
    \sa overlinePosition, strikeOutPosition
*/
int QchFontMetrics::underlinePosition() const {
    return m_fontMetrics.underlinePos();
}

/*!
    \brief The 'x' height of the font.
*/
int QchFontMetrics::xHeight() const {
    return m_fontMetrics.xHeight();
}

/*!
    \brief Returns the advance in pixels of the characters in \a text.
    
    This is the distance from the position of the string to where the next string should be drawn.
    
    \sa TextMetrics::advanceWidth
*/
int QchFontMetrics::advanceWidth(const QString &text) {
    return m_fontMetrics.width(text);
}

/*!
    \brief Returns the bounding rectangle of the characters in the string specified by \a text.
    
    \sa TextMetrics::boundingRect
*/
QRect QchFontMetrics::boundingRect(const QString &text) {
    return m_fontMetrics.boundingRect(text);
}

/*!
    \brief Returns a tight bounding rectangle around the characters in the string specified by \a text.
    
    \sa TextMetrics::tightBoundingRect
*/
QRect QchFontMetrics::tightBoundingRect(const QString &text) {
    return m_fontMetrics.tightBoundingRect(text);
}

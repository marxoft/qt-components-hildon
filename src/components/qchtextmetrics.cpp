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

#include "qchtextmetrics.h"
#include <limits.h>

/*!
    \class TextMetrics
    \brief Calculates various properties of a given string of text for a particular font.
    
    \ingroup components
    
    TextMetrics provides a declarative API for the functions in FontMetrics which take arguments.
    
    \sa FontMetrics
*/
QchTextMetrics::QchTextMetrics(QObject *parent) :
    QObject(parent),
    m_fontMetrics(QFontMetrics(m_font)),
    m_elide(Qt::ElideNone),
    m_elideWidth(std::numeric_limits<int>::max())
{
}

/*!
    \brief The advance in pixels of the characters in text.
    
    This is the distance from the position of the string to where the next string should be drawn.
    
    \sa FontMetrics::width
*/
int QchTextMetrics::advanceWidth() const {
    return m_fontMetrics.width(text());
}

/*!
    \brief The bounding rectangle of the characters in the string specified by text.
    
    \sa FontMetrics::boundingRect(), tightBoundingRect
*/
QRect QchTextMetrics::boundingRect() const {
    return m_fontMetrics.boundingRect(text());
}

/*!
    \brief Determines the position in which the string is elided.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Name</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Qt.ElideNone</td>
            <td>No eliding (default).</td>
        </tr>
        <tr>
            <td>Qt.ElideLeft</td>
            <td>For example: "...World".</td>
        </tr>
        <tr>
            <td>Qt.ElideMiddle</td>
            <td>For example: "He...ld".</td>
        </tr>
        <tr>
            <td>Qt.ElideRight</td>
            <td>For example: "Hello...".</td>
        </tr>
    </table>
    
    \sa elidedText, elideWidth
*/
Qt::TextElideMode QchTextMetrics::elide() const {
    return m_elide;
}

void QchTextMetrics::setElide(Qt::TextElideMode m) {
    if (m != elide()) {
        m_elide = m;
        emit changed();
    }
}

/*!
    \brief The text elided (if neccessary) according to the specified elide and elideWidth.
    
    \sa elide, elideWidth, text, width
*/
QString QchTextMetrics::elidedText() const {
    return width() > elideWidth() ? m_fontMetrics.elidedText(text(), elide(), elideWidth())
                                  : text();
}

/*!
    \brief The largest width the text can have (in pixels) before eliding will occur.
    
    \sa elide, elidedText
*/
int QchTextMetrics::elideWidth() const {
    return m_elideWidth;
}

void QchTextMetrics::setElideWidth(int w) {
    if (w != elideWidth()) {
        m_elideWidth = w;
        emit changed();
    }
}

/*!
    \brief The font used for the metrics calculations.
*/
QFont QchTextMetrics::font() const {
    return m_font;
}

void QchTextMetrics::setFont(const QFont &f) {
    if (f != font()) {
        m_font = f;
        m_fontMetrics = QFontMetrics(f);
        emit changed();
    }
}

/*!
    \brief The height of the bounding rectangle of the characters in the string specified by text.
    
    It is equivalent to:
    
    \code
    textMetrics.boundingRect.height
    \endcode
    
    \sa boundingRect
*/
int QchTextMetrics::height() const {
    return boundingRect().height();
}

/*!
    \brief The text used for the metrics calculations.
*/
QString QchTextMetrics::text() const {
    return m_text;
}

void QchTextMetrics::setText(const QString &t) {
    if (t != text()) {
        m_text = t;
        emit changed();
    }
}

/*!
    \brief The tight bounding rectangle around the characters in the string specified by text.
    
    \sa FontMetrics::tightBoundingRect(), boundingRect
*/
QRect QchTextMetrics::tightBoundingRect() const {
    return m_fontMetrics.tightBoundingRect(text());
}

/*!
    \brief The width of the bounding rectangle of the characters in the string specified by text.
    
    It is equivalent to:
    
    \code
    textMetrics.boundingRect.width
    \endcode
    
    \sa boundingRect
*/
int QchTextMetrics::width() const {
    return boundingRect().width();
}

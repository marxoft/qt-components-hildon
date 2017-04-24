/*!
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchtextcharformat.h"

/*!
 * \class TextCharFormat
 * \ingroup components
 * \brief Provides formatting information for characters in a text document.
 *
 * \sa SyntaxHighlighter, SyntaxHighlightRule
 */
QchTextCharFormat::QchTextCharFormat(QObject *parent) :
    QObject(parent)
{
}

QchTextCharFormat::QchTextCharFormat(const QTextCharFormat &otherFormat, QObject *parent) :
    QObject(parent),
    format(otherFormat)
{
}

/*!
 * Whether the text is formatted as an anchor.
 *
 * The default value is \c false.
 */
bool QchTextCharFormat::isAnchor() const {
    return format.isAnchor();
}

void QchTextCharFormat::setAnchor(bool anchor) {
    if (anchor != format.isAnchor()) {
        format.setAnchor(anchor);
        emit anchorChanged();
        emit changed();
    }
}

/*!
 * The text format's hypertext link, or an empty string if none has been set.
 *
 * \sa anchor, anchorNames
 */
QString QchTextCharFormat::anchorHref() const {
    return format.anchorHref();
}

void QchTextCharFormat::setAnchorHref(const QString &href) {
    if (href != format.anchorHref()) {
        format.setAnchorHref(href);
        emit anchorHrefChanged();
        emit changed();
    }
}

/*!
 * The anchor names associated with this text format.
 *
 * \sa anchor, anchorHref
 */
QStringList QchTextCharFormat::anchorNames() const {
    return format.anchorNames();
}

void QchTextCharFormat::setAnchorNames(const QStringList &names) {
    format.setAnchorNames(names);
    emit anchorNamesChanged();
    emit changed();
}

/*!
 * The text format's background color.
 *
 * \sa color
 */
QColor QchTextCharFormat::backgroundColor() const {
    return format.background().color();
}

void QchTextCharFormat::setBackgroundColor(const QColor &color) {
    if (color != format.background().color()) {
        format.setBackground(color);
        emit backgroundColorChanged();
        emit changed();
    }
}

void QchTextCharFormat::resetBackgroundColor() {
    setBackgroundColor(QColor());
}

/*!
 * The text format's foreground color.
 *
 * \sa backgroundColor
 */
QColor QchTextCharFormat::color() const {
    return format.foreground().color();
}

void QchTextCharFormat::setColor(const QColor &color) {
    if (color != format.foreground().color()) {
        format.setForeground(color);
        emit colorChanged();
        emit changed();
    }
}

/*!
 * The text format's font.
 */
QFont QchTextCharFormat::font() const {
    return format.font();
}

void QchTextCharFormat::setFont(const QFont &font) {
    if (font != format.font()) {
        format.setFont(font);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font capitalization.
 *
 * \sa font
 */
int QchTextCharFormat::fontCapitalization() const {
    return format.fontCapitalization();
}

void QchTextCharFormat::setFontCapitalization(int capitalization) {
    if (capitalization != format.fontCapitalization()) {
        format.setFontCapitalization(QFont::Capitalization(capitalization));
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font family.
 *
 * \sa font
 */
QString QchTextCharFormat::fontFamily() const {
    return format.fontFamily();
}

void QchTextCharFormat::setFontFamily(const QString &family) {
    if (family != format.fontFamily()) {
        format.setFontFamily(family);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font is fixed pitch.
 *
 * \sa font
 */
bool QchTextCharFormat::fontFixedPitch() const {
    return format.fontFixedPitch();
}

void QchTextCharFormat::setFontFixedPitch(bool fixed) {
    if (fixed != format.fontFixedPitch()) {
        format.setFontFixedPitch(fixed);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font is italic.
 *
 * \sa font
 */
bool QchTextCharFormat::fontItalic() const {
    return format.fontItalic();
}

void QchTextCharFormat::setFontItalic(bool italic) {
    if (italic != format.fontItalic()) {
        format.setFontItalic(italic);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font kerning is enabled.
 *
 * \sa font
 */
bool QchTextCharFormat::fontKerning() const {
    return format.fontKerning();
}

void QchTextCharFormat::setFontKerning(bool kerning) {
    if (kerning != format.fontKerning()) {
        format.setFontKerning(kerning);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The current letter spacing percentage of the text format's font.
 *
 * \sa font
 */
qreal QchTextCharFormat::fontLetterSpacing() const {
    return format.fontLetterSpacing();
}

void QchTextCharFormat::setFontLetterSpacing(qreal spacing) {
    if (spacing != format.fontLetterSpacing()) {
        format.setFontLetterSpacing(spacing);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font is overlined.
 *
 * \sa font
 */
bool QchTextCharFormat::fontOverline() const {
    return format.fontOverline();
}

void QchTextCharFormat::setFontOverline(bool overline) {
    if (overline != format.fontOverline()) {
        format.setFontOverline(overline);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The font size used to display text in this format.
 *
 * \sa font
 */
qreal QchTextCharFormat::fontPointSize() const {
    return format.fontPointSize();
}

void QchTextCharFormat::setFontPointSize(qreal size) {
    if (size != format.fontPointSize()) {
        format.setFontPointSize(size);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font is struck out.
 *
 * \sa font
 */
bool QchTextCharFormat::fontStrikeOut() const {
    return format.fontStrikeOut();
}

void QchTextCharFormat::setFontStrikeOut(bool strikeOut) {
    if (strikeOut != format.fontStrikeOut()) {
        format.setFontStrikeOut(strikeOut);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font style hint.
 *
 * \sa font
 */
int QchTextCharFormat::fontStyleHint() const {
    return format.fontStyleHint();
}

void QchTextCharFormat::setFontStyleHint(int hint) {
    if (hint != format.fontStyleHint()) {
        format.setFontStyleHint(QFont::StyleHint(hint));
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font style strategy.
 *
 * \sa font
 */
int QchTextCharFormat::fontStyleStrategy() const {
    return format.fontStyleStrategy();
}

void QchTextCharFormat::setFontStyleStrategy(int strategy) {
    if (strategy != format.fontStyleStrategy()) {
        format.setFontStyleStrategy(QFont::StyleStrategy(strategy));
        emit fontChanged();
        emit changed();
    }
}

/*!
 * Whether the text format's font is underlined.
 *
 * \sa font
 */
bool QchTextCharFormat::fontUnderline() const {
    return format.fontUnderline();
}

void QchTextCharFormat::setFontUnderline(bool underline) {
    if (underline != format.fontUnderline()) {
        format.setFontUnderline(underline);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font weight.
 *
 * \sa font
 */
int QchTextCharFormat::fontWeight() const {
    return format.fontWeight();
}

void QchTextCharFormat::setFontWeight(int weight) {
    if (weight != format.fontWeight()) {
        format.setFontWeight(weight);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's font word spacing.
 *
 * \sa font
 */
qreal QchTextCharFormat::fontWordSpacing() const {
    return format.fontWordSpacing();
}

void QchTextCharFormat::setFontWordSpacing(qreal spacing) {
    if (spacing != format.fontWordSpacing()) {
        format.setFontWordSpacing(spacing);
        emit fontChanged();
        emit changed();
    }
}

/*!
 * The text format's outline color.
 *
 * \sa outlineStyle
 */
QColor QchTextCharFormat::textOutlineColor() const {
    return format.textOutline().color();
}

void QchTextCharFormat::setTextOutlineColor(const QColor &color) {
    if (color != format.textOutline().color()) {
        format.setTextOutline(color);
        emit textOutlineColorChanged();
        emit changed();
    }
}

void QchTextCharFormat::resetTextOutlineColor() {
    setTextOutlineColor(QColor());
}

/*!
 * The text format's outline style.
 *
 * \sa outlineColor
 */
int QchTextCharFormat::textOutlineStyle() const {
    return format.textOutline().style();
}

void QchTextCharFormat::setTextOutlineStyle(int style) {
    if (style != format.textOutline().style()) {
        QPen pen = format.textOutline();
        pen.setStyle(Qt::PenStyle(style));
        format.setTextOutline(pen);
        emit textOutlineStyleChanged();
        emit changed();
    }
}

/*!
 * The text format's underlineColor
 *
 * \sa underlineStyle
 */
QColor QchTextCharFormat::underlineColor() const {
    return format.underlineColor();
}

void QchTextCharFormat::setUnderlineColor(const QColor &color) {
    if (color != format.underlineColor()) {
        format.setUnderlineColor(color);
        emit underlineColorChanged();
        emit changed();
    }
}

void QchTextCharFormat::resetUnderlineColor() {
    setUnderlineColor(QColor());
}

/*!
 * The text format's underline style.
 *
 * \sa underlineColor
 */
int QchTextCharFormat::underlineStyle() const {
    return format.underlineStyle();
}

void QchTextCharFormat::setUnderlineStyle(int style) {
    if (style != format.underlineStyle()) {
        format.setUnderlineStyle(QTextCharFormat::UnderlineStyle(style));
        emit underlineStyleChanged();
        emit changed();
    }
}

/*!
 * The text format's vertical alignment.
 */
int QchTextCharFormat::verticalAlignment() const {
    return format.verticalAlignment();
}

void QchTextCharFormat::setVerticalAlignment(int alignment) {
    if (alignment != format.verticalAlignment()) {
        format.setVerticalAlignment(QTextCharFormat::VerticalAlignment(alignment));
        emit verticalAlignmentChanged();
        emit changed();
    }
}


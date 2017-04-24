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

#ifndef QCHTEXTCHARFORMAT_H
#define QCHTEXTCHARFORMAT_H

#include <QObject>
#include <QTextCharFormat>
#include <qdeclarative.h>

class QchTextCharFormat : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool anchor READ isAnchor WRITE setAnchor NOTIFY anchorChanged)
    Q_PROPERTY(QString anchorHref READ anchorHref WRITE setAnchorHref NOTIFY anchorHrefChanged)
    Q_PROPERTY(QStringList anchorNames READ anchorNames WRITE setAnchorNames NOTIFY anchorNamesChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor
               RESET resetBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor NOTIFY colorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont RESET resetFont NOTIFY fontChanged)
    Q_PROPERTY(int fontCapitalization READ fontCapitalization WRITE setFontCapitalization NOTIFY fontChanged)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontChanged)
    Q_PROPERTY(bool fontFixedPitch READ fontFixedPitch WRITE setFontFixedPitch NOTIFY fontChanged)
    Q_PROPERTY(bool fontItalic READ fontItalic WRITE setFontItalic NOTIFY fontChanged)
    Q_PROPERTY(bool fontKerning READ fontKerning WRITE setFontKerning NOTIFY fontChanged)
    Q_PROPERTY(qreal fontLetterSpacing READ fontLetterSpacing WRITE setFontLetterSpacing NOTIFY fontChanged)
    Q_PROPERTY(bool fontOverline READ fontOverline WRITE setFontOverline NOTIFY fontOverlineChanged)
    Q_PROPERTY(qreal fontPointSize READ fontPointSize WRITE setFontPointSize NOTIFY fontChanged)
    Q_PROPERTY(bool fontStrikeOut READ fontStrikeOut WRITE setFontStrikeOut NOTIFY fontChanged)
    Q_PROPERTY(int fontStyleHint READ fontStyleHint WRITE setFontStyleHint NOTIFY fontChanged)
    Q_PROPERTY(int fontStyleStrategy READ fontStyleStrategy WRITE setFontStyleStrategy NOTIFY fontChanged)
    Q_PROPERTY(bool fontUnderline READ fontUnderline WRITE setFontUnderline NOTIFY fontChanged)
    Q_PROPERTY(int fontWeight READ fontWeight WRITE setFontWeight NOTIFY fontChanged)
    Q_PROPERTY(qreal fontWordSpacing READ fontWordSpacing WRITE setFontWordSpacing NOTIFY fontChanged)
    Q_PROPERTY(QColor textOutlineColor READ textOutlineColor WRITE setTextOutlineColor RESET resetTextOutlineColor
               NOTIFY textOutlineColorChanged)
    Q_PROPERTY(int textOutlineStyle READ textOutlineStyle WRITE setTextOutlineStyle NOTIFY textOutlineStyleChanged)
    Q_PROPERTY(QColor underlineColor READ underlineColor WRITE setUnderlineColor RESET resetUnderlineColor
               NOTIFY underlineColorChanged)
    Q_PROPERTY(int underlineStyle READ underlineStyle WRITE setUnderlineStyle NOTIFY underlineStyleChanged)
    Q_PROPERTY(int verticalAlignment READ verticalAlignment WRITE setVerticalAlignment
               NOTIFY verticalAlignmentChanged)

    Q_ENUMS(LineStyle VerticalAlignment)

public:
    enum LineStyle {
        NoOutline = 0,
        SingleLine,
        DashLine,
        DotLine,
        DashDotLine,
        DashDotDotLine
    };

    enum VerticalAlignment {
        AlignNormal = 0,
        AlignSuperScript,
        AlignSubScript,
        AlignMiddle,
        AlignTop,
        AlignBottom
    };

    explicit QchTextCharFormat(QObject *parent = 0);
    explicit QchTextCharFormat(const QTextCharFormat &otherFormat, QObject *parent = 0);

    bool isAnchor() const;
    void setAnchor(bool anchor);

    QString anchorHref() const;
    void setAnchorHref(const QString &href);

    QStringList anchorNames() const;
    void setAnchorNames(const QStringList &names);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    void resetBackgroundColor();

    QColor color() const;
    void setColor(const QColor &color);
    void resetColor();

    QFont font() const;
    void setFont(const QFont &font);
    void resetFont();

    int fontCapitalization() const;
    void setFontCapitalization(int capitalization);

    QString fontFamily() const;
    void setFontFamily(const QString &family);

    bool fontFixedPitch() const;
    void setFontFixedPitch(bool fixed);

    bool fontItalic() const;
    void setFontItalic(bool italic);

    bool fontKerning() const;
    void setFontKerning(bool kerning);

    qreal fontLetterSpacing() const;
    void setFontLetterSpacing(qreal spacing);

    bool fontOverline() const;
    void setFontOverline(bool overline);

    qreal fontPointSize() const;
    void setFontPointSize(qreal size);

    bool fontStrikeOut() const;
    void setFontStrikeOut(bool strikeOut);

    int fontStyleHint() const;
    void setFontStyleHint(int hint);

    int fontStyleStrategy() const;
    void setFontStyleStrategy(int strategy);

    bool fontUnderline() const;
    void setFontUnderline(bool underline);

    int fontWeight() const;
    void setFontWeight(int weight);

    qreal fontWordSpacing() const;
    void setFontWordSpacing(qreal spacing);

    QColor textOutlineColor() const;
    void setTextOutlineColor(const QColor &color);
    void resetTextOutlineColor();

    int textOutlineStyle() const;
    void setTextOutlineStyle(int style);

    QColor underlineColor() const;
    void setUnderlineColor(const QColor &color);
    void resetUnderlineColor();

    int underlineStyle() const;
    void setUnderlineStyle(int style);

    int verticalAlignment() const;
    void setVerticalAlignment(int alignment);

    QTextCharFormat format;

Q_SIGNALS:
    void changed();
    void anchorChanged();
    void anchorHrefChanged();
    void anchorNamesChanged();
    void backgroundColorChanged();
    void colorChanged();
    void fontChanged();
    void textOutlineColorChanged();
    void textOutlineStyleChanged();
    void underlineColorChanged();
    void underlineStyleChanged();
    void verticalAlignmentChanged();

private:
    Q_DISABLE_COPY(QchTextCharFormat)
};

QML_DECLARE_TYPE(QchTextCharFormat)

#endif // QCHTEXTCHARFORMAT_H


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

#ifndef TEXTEDIT_P_H
#define TEXTEDIT_P_H

#include "item_p.h"
#include <QTextEdit>

class TextEditPrivate;

class TextEdit : public Item
{
    Q_OBJECT

    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(QTextEdit::AutoFormatting autoFormatting READ autoFormatting WRITE setAutoFormatting)
    Q_PROPERTY(bool tabChangesFocus READ tabChangesFocus WRITE setTabChangesFocus)
    Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle)
    Q_PROPERTY(bool undoRedoEnabled READ isUndoRedoEnabled WRITE setUndoRedoEnabled)
    Q_PROPERTY(QTextEdit::LineWrapMode lineWrapMode READ lineWrapMode WRITE setLineWrapMode)
    Q_PROPERTY(int lineWrapColumnOrWidth READ lineWrapColumnOrWidth WRITE setLineWrapColumnOrWidth)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    Q_PROPERTY(QString html READ html WRITE setHtml NOTIFY textChanged USER true)
    Q_PROPERTY(QString text READ text WRITE setText DESIGNABLE false)
    Q_PROPERTY(bool overwriteMode READ overwriteMode WRITE setOverwriteMode)
    Q_PROPERTY(int tabStopWidth READ tabStopWidth WRITE setTabStopWidth)
    Q_PROPERTY(bool acceptRichText READ acceptRichText WRITE setAcceptRichText)
    Q_PROPERTY(int cursorWidth READ cursorWidth WRITE setCursorWidth)
    Q_PROPERTY(Qt::TextInteractionFlags textInteractionFlags READ textInteractionFlags WRITE setTextInteractionFlags)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor textBackgroundColor READ textBackgroundColor WRITE setTextBackgroundColor)

public:
    explicit TextEdit(QWidget *parent = 0);
    ~TextEdit();

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    QTextEdit::AutoFormatting autoFormatting() const;
    void setAutoFormatting(QTextEdit::AutoFormatting formatting);

    bool tabChangesFocus() const;
    void setTabChangesFocus(bool changes);

    QString documentTitle() const;
    void setDocumentTitle(const QString &title);

    bool isUndoRedoEnabled() const;
    void setUndoRedoEnabled(bool enabled);

    QTextEdit::LineWrapMode lineWrapMode() const;
    void setLineWrapMode(QTextEdit::LineWrapMode mode);

    int lineWrapColumnOrWidth() const;
    void setLineWrapColumnOrWidth(int width);

    bool isReadOnly() const;
    void setReadOnly(bool readOnly);

    QString html() const;
    void setHtml(const QString &html);

    QString text() const;
    void setText(const QString &text);

    bool overwriteMode() const;
    void setOverwriteMode(bool overwrite);

    int tabStopWidth() const;
    void setTabStopWidth(int width);

    bool acceptRichText() const;
    void setAcceptRichText(bool accept);

    int cursorWidth() const;
    void setCursorWidth(int width);

    Qt::TextInteractionFlags textInteractionFlags() const;
    void setTextInteractionFlags(Qt::TextInteractionFlags flags);

    QColor textColor() const;
    void setTextColor(const QColor &color);

    QColor textBackgroundColor() const;
    void setTextBackgroundColor(const QColor &color);

public slots:
    void clear();
    void copy();
    void cut();
    void paste();
    void redo();
    void selectAll();

signals:
    void textChanged();
    void undoAvailable(bool b);
    void redoAvailable(bool b);
    void currentCharFormatChanged(const QTextCharFormat &format);
    void copyAvailable(bool b);
    void selectionChanged();
    void cursorPositionChanged();

protected:
    TextEdit(TextEditPrivate &dd, QWidget *parent = 0);

    Q_DECLARE_PRIVATE(TextEdit)

private:
    Q_DISABLE_COPY(TextEdit)
};

QML_DECLARE_TYPE(TextEdit)

#endif // TEXTEDIT_P_H

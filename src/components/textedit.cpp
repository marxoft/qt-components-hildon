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

#include "textedit_p.h"
#include "textedit_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QScrollArea>
#include <QVBoxLayout>

TextEdit::TextEdit(QWidget *parent) :
    Item(*new TextEditPrivate(this), parent)
{
    Q_D(TextEdit);

    d->edit = new QTextEdit(this);
    new TextEditAutoResizer(d->edit);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    QScrollArea *scrollArea = new QScrollArea(this);

    scrollArea->setWidget(d->edit);
    scrollArea->setWidgetResizable(true);
    vbox->addWidget(scrollArea);

    this->connect(d->edit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->edit, SIGNAL(undoAvailable(bool)), this, SIGNAL(undoAvailable(bool)));
    this->connect(d->edit, SIGNAL(redoAvailable(bool)), this, SIGNAL(redoAvailable(bool)));
    this->connect(d->edit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SIGNAL(currentCharFormatChanged(QTextCharFormat)));
    this->connect(d->edit, SIGNAL(copyAvailable(bool)), this, SIGNAL(copyAvailable(bool)));
    this->connect(d->edit, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->edit, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
}

TextEdit::TextEdit(TextEditPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(TextEdit);

    if (!d->edit) {
        d->edit = new QTextEdit(this);
    }

    new TextEditAutoResizer(d->edit);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    QScrollArea *scrollArea = new QScrollArea(this);

    scrollArea->setWidget(d->edit);
    scrollArea->setWidgetResizable(true);
    vbox->addWidget(scrollArea);

    this->connect(d->edit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->edit, SIGNAL(undoAvailable(bool)), this, SIGNAL(undoAvailable(bool)));
    this->connect(d->edit, SIGNAL(redoAvailable(bool)), this, SIGNAL(redoAvailable(bool)));
    this->connect(d->edit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this, SIGNAL(currentCharFormatChanged(QTextCharFormat)));
    this->connect(d->edit, SIGNAL(copyAvailable(bool)), this, SIGNAL(copyAvailable(bool)));
    this->connect(d->edit, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->edit, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
}

TextEdit::~TextEdit() {}

Qt::Alignment TextEdit::alignment() const {
    Q_D(const TextEdit);

    return d->edit->alignment();
}

void TextEdit::setAlignment(Qt::Alignment align) {
    Q_D(TextEdit);

    d->edit->setAlignment(align);
}

QTextEdit::AutoFormatting TextEdit::autoFormatting() const {
    Q_D(const TextEdit);

    return d->edit->autoFormatting();
}

void TextEdit::setAutoFormatting(QTextEdit::AutoFormatting formatting) {
    Q_D(TextEdit);

    return d->edit->setAutoFormatting(formatting);
}

bool TextEdit::tabChangesFocus() const {
    Q_D(const TextEdit);

    return d->edit->tabChangesFocus();
}

void TextEdit::setTabChangesFocus(bool changes) {
    Q_D(TextEdit);

    d->edit->setTabChangesFocus(changes);
}

QString TextEdit::documentTitle() const {
    Q_D(const TextEdit);

    return d->edit->documentTitle();
}

void TextEdit::setDocumentTitle(const QString &title) {
    Q_D(TextEdit);

    d->edit->setDocumentTitle(title);
}

bool TextEdit::isUndoRedoEnabled() const {
    Q_D(const TextEdit);

    return d->edit->isUndoRedoEnabled();
}

void TextEdit::setUndoRedoEnabled(bool enabled) {
    Q_D(TextEdit);

    d->edit->setUndoRedoEnabled(enabled);
}

QTextEdit::LineWrapMode TextEdit::lineWrapMode() const {
    Q_D(const TextEdit);

    return d->edit->lineWrapMode();
}

void TextEdit::setLineWrapMode(QTextEdit::LineWrapMode mode) {
    Q_D(TextEdit);

    d->edit->setLineWrapMode(mode);
}

int TextEdit::lineWrapColumnOrWidth() const {
    Q_D(const TextEdit);

    return d->edit->lineWrapColumnOrWidth();
}

void TextEdit::setLineWrapColumnOrWidth(int width) {
    Q_D(TextEdit);

    d->edit->setLineWrapColumnOrWidth(width);
}

bool TextEdit::isReadOnly() const {
    Q_D(const TextEdit);

    return d->edit->isReadOnly();
}

void TextEdit::setReadOnly(bool readOnly) {
    Q_D(TextEdit);

    d->edit->setReadOnly(readOnly);
}

QString TextEdit::html() const {
    Q_D(const TextEdit);

    return d->edit->toHtml();
}

void TextEdit::setHtml(const QString &html) {
    Q_D(TextEdit);

    d->edit->setHtml(html);
}

QString TextEdit::text() const {
    Q_D(const TextEdit);

    return d->edit->toPlainText();
}

void TextEdit::setText(const QString &text) {
    Q_D(TextEdit);

    d->edit->setText(text);
}

bool TextEdit::overwriteMode() const {
    Q_D(const TextEdit);

    return d->edit->overwriteMode();
}

void TextEdit::setOverwriteMode(bool overwrite) {
    Q_D(TextEdit);

    d->edit->setOverwriteMode(overwrite);
}

int TextEdit::tabStopWidth() const {
    Q_D(const TextEdit);

    return d->edit->tabStopWidth();
}

void TextEdit::setTabStopWidth(int width) {
    Q_D(TextEdit);

    d->edit->setTabStopWidth(width);
}

bool TextEdit::acceptRichText() const {
    Q_D(const TextEdit);

    return d->edit->acceptRichText();
}

void TextEdit::setAcceptRichText(bool accept) {
    Q_D(TextEdit);

    d->edit->setAcceptRichText(accept);
}

int TextEdit::cursorWidth() const {
    Q_D(const TextEdit);

    return d->edit->cursorWidth();
}

void TextEdit::setCursorWidth(int width) {
    Q_D(TextEdit);

    d->edit->setCursorWidth(width);
}

Qt::TextInteractionFlags TextEdit::textInteractionFlags() const {
    Q_D(const TextEdit);

    return d->edit->textInteractionFlags();
}

void TextEdit::setTextInteractionFlags(Qt::TextInteractionFlags flags) {
    Q_D(TextEdit);

    d->edit->setTextInteractionFlags(flags);
}

QColor TextEdit::textColor() const {
    Q_D(const TextEdit);

    return d->edit->textColor();
}

void TextEdit::setTextColor(const QColor &color) {
    Q_D(TextEdit);

    d->edit->setTextColor(color);
}

QColor TextEdit::textBackgroundColor() const {
    Q_D(const TextEdit);

    return d->edit->textBackgroundColor();
}

void TextEdit::setTextBackgroundColor(const QColor &color) {
    Q_D(TextEdit);

    return d->edit->setTextBackgroundColor(color);
}

void TextEdit::clear() {
    Q_D(TextEdit);

    d->edit->clear();
}

void TextEdit::copy() {
    Q_D(TextEdit);

    d->edit->copy();
}

void TextEdit::cut() {
    Q_D(TextEdit);

    d->edit->cut();
}

void TextEdit::paste() {
    Q_D(TextEdit);

    d->edit->paste();
}

void TextEdit::redo() {
    Q_D(TextEdit);

    d->edit->redo();
}

void TextEdit::selectAll() {
    Q_D(TextEdit);

    d->edit->selectAll();
}

#include "moc_textedit_p.cpp"

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
#include "texteditautoresizer_p.h"
#include "item_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QTimer>

class TextEditPrivate : public ItemPrivate
{

public:
    TextEditPrivate(TextEdit *parent) :
        ItemPrivate(parent),
        edit(0),
        scrollArea(0),
        kineticScroller(0),
        scrollTimer(0),
        undoAvailable(false),
        redoAvailable(false),
        copyAvailable(false)
    {
    }

    void _q_onUndoAvailable(bool available) {
        if (available != undoAvailable) {
            Q_Q(TextEdit);
            undoAvailable = available;
            emit q->undoAvailableChanged();
        }
    }

    void _q_onRedoAvailable(bool available) {
        if (available != redoAvailable) {
            Q_Q(TextEdit);
            redoAvailable = available;
            emit q->redoAvailableChanged();
        }
    }

    void _q_onCopyAvailable(bool available) {
        if (available != copyAvailable) {
            Q_Q(TextEdit);
            copyAvailable = available;
            emit q->copyAvailableChanged();
        }
    }

    void _q_onHorizontalScrollPositionChanged() {
        Q_Q(TextEdit);

        if (!scrollTimer->isActive()) {
            emit q->movingChanged();

            if (atXBeginning) {
                atXBeginning = false;
                emit q->atXBeginningChanged();
            }

            if (atXEnd) {
                atXEnd = false;
                emit q->atXEndChanged();
            }
        }

        emit q->contentXChanged();

        scrollTimer->start();
    }

    void _q_onVerticalScrollPositionChanged() {
        Q_Q(TextEdit);

        if (!scrollTimer->isActive()) {
            emit q->movingChanged();

            if (atYBeginning) {
                atYBeginning = false;
                emit q->atYBeginningChanged();
            }

            if (atXEnd) {
                atXEnd = false;
                emit q->atYEndChanged();
            }
        }

        emit q->contentYChanged();

        scrollTimer->start();
    }

    void _q_onScrollingStopped() {
        Q_Q(TextEdit);

        bool xb = q->atXBeginning();
        bool xe = q->atYEnd();
        bool yb = q->atYBeginning();
        bool ye = q->atYEnd();

        if (xb != atXBeginning) {
            atXBeginning = xb;
            emit q->atXBeginningChanged();
        }

        if (xe != atXEnd) {
            atXEnd = xe;
            emit q->atXEndChanged();
        }

        if (yb != atYBeginning) {
            atYBeginning = yb;
            emit q->atYBeginningChanged();
        }

        if (ye != atYEnd) {
            atYEnd = ye;
            emit q->atYEndChanged();
        }

        emit q->movingChanged();
    }

    QTextEdit *edit;

    QScrollArea *scrollArea;

    QAbstractKineticScroller *kineticScroller;

    QTimer *scrollTimer;

    bool undoAvailable;
    bool redoAvailable;
    bool copyAvailable;

    bool atXBeginning;
    bool atXEnd;
    bool atYBeginning;
    bool atYEnd;

    Q_DECLARE_PUBLIC(TextEdit)
};

TextEdit::TextEdit(QWidget *parent) :
    Item(*new TextEditPrivate(this), parent)
{
    Q_D(TextEdit);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    d->edit = new QTextEdit(this);
    new TextEditAutoResizer(d->edit);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    d->scrollArea = new QScrollArea(this);
    d->kineticScroller = d->scrollArea->property("kineticScroller").value<QAbstractKineticScroller*>();
    d->scrollArea->setWidget(d->edit);
    d->scrollArea->setWidgetResizable(true);
    vbox->addWidget(d->scrollArea);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(d->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
    this->connect(d->edit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->edit, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->edit, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
    this->connect(d->edit, SIGNAL(undoAvailable(bool)), this, SLOT(_q_onUndoAvailable(bool)));
    this->connect(d->edit, SIGNAL(redoAvailable(bool)), this, SLOT(_q_onRedoAvailable(bool)));
    this->connect(d->edit, SIGNAL(copyAvailable(bool)), this, SLOT(_q_onCopyAvailable(bool)));
}

TextEdit::TextEdit(TextEditPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(TextEdit);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    d->edit = new QTextEdit(this);
    new TextEditAutoResizer(d->edit);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    d->scrollArea = new QScrollArea(this);
    d->kineticScroller = d->scrollArea->property("kineticScroller").value<QAbstractKineticScroller*>();
    d->scrollArea->setWidget(d->edit);
    d->scrollArea->setWidgetResizable(true);
    vbox->addWidget(d->scrollArea);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(d->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
    this->connect(d->edit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->edit, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->edit, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
    this->connect(d->edit, SIGNAL(undoAvailable(bool)), this, SLOT(_q_onUndoAvailable(bool)));
    this->connect(d->edit, SIGNAL(redoAvailable(bool)), this, SLOT(_q_onRedoAvailable(bool)));
    this->connect(d->edit, SIGNAL(copyAvailable(bool)), this, SLOT(_q_onCopyAvailable(bool)));
}

TextEdit::~TextEdit() {}

Qt::Alignment TextEdit::alignment() const {
    Q_D(const TextEdit);

    return d->edit->alignment();
}

void TextEdit::setAlignment(Qt::Alignment align) {
    if (align != this->alignment()) {
        Q_D(TextEdit);
        d->edit->setAlignment(align);
        emit alignmentChanged();
    }
}

QTextEdit::AutoFormatting TextEdit::autoFormatting() const {
    Q_D(const TextEdit);

    return d->edit->autoFormatting();
}

void TextEdit::setAutoFormatting(QTextEdit::AutoFormatting formatting) {
    if (formatting != this->autoFormatting()) {
        Q_D(TextEdit);
        d->edit->setAutoFormatting(formatting);
        emit autoFormattingChanged();
    }
}

bool TextEdit::tabChangesFocus() const {
    Q_D(const TextEdit);

    return d->edit->tabChangesFocus();
}

void TextEdit::setTabChangesFocus(bool changes) {
    if (changes != this->tabChangesFocus()) {
        Q_D(TextEdit);
        d->edit->setTabChangesFocus(changes);
        emit tabChangesFocusChanged();
    }
}

QString TextEdit::documentTitle() const {
    Q_D(const TextEdit);

    return d->edit->documentTitle();
}

void TextEdit::setDocumentTitle(const QString &title) {
    if (title != this->documentTitle()) {
        Q_D(TextEdit);
        d->edit->setDocumentTitle(title);
        emit documentTitleChanged();
    }
}

bool TextEdit::isUndoRedoEnabled() const {
    Q_D(const TextEdit);

    return d->edit->isUndoRedoEnabled();
}

void TextEdit::setUndoRedoEnabled(bool enabled) {
    if (enabled != this->isUndoRedoEnabled()) {
        Q_D(TextEdit);
        d->edit->setUndoRedoEnabled(enabled);
        emit undoRedoEnabledChanged();
    }
}

QTextEdit::LineWrapMode TextEdit::lineWrapMode() const {
    Q_D(const TextEdit);

    return d->edit->lineWrapMode();
}

void TextEdit::setLineWrapMode(QTextEdit::LineWrapMode mode) {
    if (mode != this->lineWrapMode()) {
        Q_D(TextEdit);
        d->edit->setLineWrapMode(mode);
        emit lineWrapModeChanged();
    }
}

int TextEdit::lineWrapColumnOrWidth() const {
    Q_D(const TextEdit);

    return d->edit->lineWrapColumnOrWidth();
}

void TextEdit::setLineWrapColumnOrWidth(int width) {
    if (width != this->lineWrapColumnOrWidth()) {
        Q_D(TextEdit);
        d->edit->setLineWrapColumnOrWidth(width);
        emit lineWrapColumnOrWidthChanged();
    }
}

TextEdit::WrapMode TextEdit::wordWrapMode() const {
    Q_D(const TextEdit);

    return WrapMode(d->edit->wordWrapMode());
}

void TextEdit::setWordWrapMode(WrapMode mode) {
    if (mode != this->wordWrapMode()) {
        Q_D(TextEdit);
        d->edit->setWordWrapMode(QTextOption::WrapMode(mode));
        emit wordWrapModeChanged();
    }
}

bool TextEdit::isReadOnly() const {
    Q_D(const TextEdit);

    return d->edit->isReadOnly();
}

void TextEdit::setReadOnly(bool readOnly) {
    if (readOnly != this->isReadOnly()) {
        Q_D(TextEdit);
        d->edit->setReadOnly(readOnly);
    }
}

QString TextEdit::html() const {
    Q_D(const TextEdit);

    return d->edit->toHtml();
}

void TextEdit::setHtml(const QString &html) {
    Q_D(TextEdit);

    d->edit->setHtml(html);
    emit textChanged();
}

QString TextEdit::text() const {
    Q_D(const TextEdit);

    return d->edit->toPlainText();
}

void TextEdit::setText(const QString &text) {
    Q_D(TextEdit);

    d->edit->setPlainText(text);
    emit textChanged();
}

bool TextEdit::overwriteMode() const {
    Q_D(const TextEdit);

    return d->edit->overwriteMode();
}

void TextEdit::setOverwriteMode(bool overwrite) {
    if (overwrite != this->overwriteMode()) {
        Q_D(TextEdit);
        d->edit->setOverwriteMode(overwrite);
        emit overwriteModeChanged();
    }
}

int TextEdit::tabStopWidth() const {
    Q_D(const TextEdit);

    return d->edit->tabStopWidth();
}

void TextEdit::setTabStopWidth(int width) {
    if (width != this->tabStopWidth()) {
        Q_D(TextEdit);
        d->edit->setTabStopWidth(width);
        emit tabStopWidthChanged();
    }
}

bool TextEdit::acceptRichText() const {
    Q_D(const TextEdit);

    return d->edit->acceptRichText();
}

void TextEdit::setAcceptRichText(bool accept) {
    if (accept != this->acceptRichText()) {
        Q_D(TextEdit);
        d->edit->setAcceptRichText(accept);
        emit acceptRichTextChanged();
    }
}

int TextEdit::cursorWidth() const {
    Q_D(const TextEdit);

    return d->edit->cursorWidth();
}

void TextEdit::setCursorWidth(int width) {
    if (width != this->cursorWidth()) {
        Q_D(TextEdit);
        d->edit->setCursorWidth(width);
        emit cursorWidthChanged();
    }
}

Qt::TextInteractionFlags TextEdit::textInteractionFlags() const {
    Q_D(const TextEdit);

    return d->edit->textInteractionFlags();
}

void TextEdit::setTextInteractionFlags(Qt::TextInteractionFlags flags) {
    Q_D(TextEdit);

    d->edit->setTextInteractionFlags(flags);
    emit textInteractionFlagsChanged();
}

QColor TextEdit::textColor() const {
    Q_D(const TextEdit);

    return d->edit->textColor();
}

void TextEdit::setTextColor(const QColor &color) {
    if (color != this->textColor()) {
        Q_D(TextEdit);
        d->edit->setTextColor(color);
        emit textColorChanged();
    }
}

QColor TextEdit::textBackgroundColor() const {
    Q_D(const TextEdit);

    return d->edit->textBackgroundColor();
}

void TextEdit::setTextBackgroundColor(const QColor &color) {
    if (color != this->textBackgroundColor()) {
        Q_D(TextEdit);
        d->edit->setTextBackgroundColor(color);
        emit textBackgroundColorChanged();
    }
}

bool TextEdit::isUndoAvailable() const {
    Q_D(const TextEdit);

    return d->undoAvailable;
}

bool TextEdit::isRedoAvailable() const {
    Q_D(const TextEdit);

    return d->redoAvailable;
}

bool TextEdit::isCopyAvailable() const {
    Q_D(const TextEdit);

    return d->copyAvailable;
}

bool TextEdit::interactive() const {
    Q_D(const TextEdit);

    return d->kineticScroller->isEnabled();
}

void TextEdit::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(TextEdit);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool TextEdit::moving() const {
    Q_D(const TextEdit);

    if (d->scrollTimer->isActive()) {
        return true;
    }

    switch (d->kineticScroller->state()) {
    case QAbstractKineticScroller::Pushing:
    case QAbstractKineticScroller::AutoScrolling:
        return true;
    default:
        return false;
    }
}

bool TextEdit::atXBeginning() const {
    Q_D(const TextEdit);

    return d->scrollArea->horizontalScrollBar()->value() == d->scrollArea->horizontalScrollBar()->minimum();
}

bool TextEdit::atXEnd() const {
    Q_D(const TextEdit);

    return d->scrollArea->horizontalScrollBar()->value() == d->scrollArea->horizontalScrollBar()->maximum();
}

bool TextEdit::atYBeginning() const {
    Q_D(const TextEdit);

    return d->scrollArea->verticalScrollBar()->value() == d->scrollArea->verticalScrollBar()->minimum();
}

bool TextEdit::atYEnd() const {
    Q_D(const TextEdit);

    return d->scrollArea->verticalScrollBar()->value() == d->scrollArea->verticalScrollBar()->maximum();
}

int TextEdit::contentX() const {
    Q_D(const TextEdit);

    return d->scrollArea->horizontalScrollBar()->value();
}

void TextEdit::setContentX(int x) {
    Q_D(TextEdit);

    d->scrollArea->horizontalScrollBar()->setValue(x);
}

int TextEdit::contentY() const {
    Q_D(const TextEdit);

    return d->scrollArea->horizontalScrollBar()->value();
}

void TextEdit::setContentY(int y) {
    Q_D(TextEdit);

    d->scrollArea->verticalScrollBar()->setValue(y);
}

qreal TextEdit::flickDeceleration() const {
    Q_D(const TextEdit);

    return d->kineticScroller->decelerationFactor();
}

void TextEdit::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(TextEdit);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal TextEdit::maximumFlickVelocity() const {
    Q_D(const TextEdit);

    return d->kineticScroller->maximumVelocity();
}

void TextEdit::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(TextEdit);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
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

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

#include "textbrowser_p.h"
#include "texteditautoresizer_p.h"
#include "item_p_p.h"
#include <QActionGroup>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QTimer>

class TextBrowserPrivate : public ItemPrivate
{

public:
    TextBrowserPrivate(TextBrowser *parent) :
        ItemPrivate(parent),
        browser(0),
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
            Q_Q(TextBrowser);
            undoAvailable = available;
            emit q->undoAvailableChanged();
        }
    }

    void _q_onRedoAvailable(bool available) {
        if (available != redoAvailable) {
            Q_Q(TextBrowser);
            redoAvailable = available;
            emit q->redoAvailableChanged();
        }
    }

    void _q_onCopyAvailable(bool available) {
        if (available != copyAvailable) {
            Q_Q(TextBrowser);
            copyAvailable = available;
            emit q->copyAvailableChanged();
        }
    }

    void _q_onHorizontalScrollPositionChanged() {
        Q_Q(TextBrowser);

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
        Q_Q(TextBrowser);

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
        Q_Q(TextBrowser);

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

    QTextBrowser *browser;

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

    Q_DECLARE_PUBLIC(TextBrowser)
};

TextBrowser::TextBrowser(QWidget *parent) :
    Item(*new TextBrowserPrivate(this), parent)
{
    Q_D(TextBrowser);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    d->browser = new QTextBrowser(this);
    new TextEditAutoResizer(d->browser);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    d->scrollArea = new QScrollArea(this);
    d->kineticScroller = d->scrollArea->property("kineticScroller").value<QAbstractKineticScroller*>();
    d->scrollArea->setWidget(d->browser);
    d->scrollArea->setWidgetResizable(true);
    vbox->addWidget(d->scrollArea);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(d->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
    this->connect(d->browser, SIGNAL(sourceChanged(QUrl)), this, SIGNAL(sourceChanged()));
    this->connect(d->browser, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->browser, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->browser, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
    this->connect(d->browser, SIGNAL(historyChanged()), this, SIGNAL(historyChanged()));
    this->connect(d->browser, SIGNAL(anchorClicked(QUrl)), this, SIGNAL(anchorClicked(QUrl)));
    this->connect(d->browser, SIGNAL(highlighted(QUrl)), this, SIGNAL(highlighted(QUrl)));
    this->connect(d->browser, SIGNAL(undoAvailable(bool)), this, SLOT(_q_onUndoAvailable(bool)));
    this->connect(d->browser, SIGNAL(redoAvailable(bool)), this, SLOT(_q_onRedoAvailable(bool)));
    this->connect(d->browser, SIGNAL(copyAvailable(bool)), this, SLOT(_q_onCopyAvailable(bool)));
}

TextBrowser::TextBrowser(TextBrowserPrivate &dd, QWidget *parent) :
    Item(dd, parent)
{
    Q_D(TextBrowser);

    d->scrollTimer = new QTimer(this);
    d->scrollTimer->setInterval(500);
    d->scrollTimer->setSingleShot(true);

    d->browser = new QTextBrowser(this);
    new TextEditAutoResizer(d->browser);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    d->scrollArea = new QScrollArea(this);
    d->kineticScroller = d->scrollArea->property("kineticScroller").value<QAbstractKineticScroller*>();
    d->scrollArea->setWidget(d->browser);
    d->scrollArea->setWidgetResizable(true);
    vbox->addWidget(d->scrollArea);

    this->connect(d->scrollTimer, SIGNAL(timeout()), this, SLOT(_q_onScrollingStopped()));
    this->connect(d->scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onHorizontalScrollPositionChanged()));
    this->connect(d->scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(_q_onVerticalScrollPositionChanged()));
    this->connect(d->browser, SIGNAL(sourceChanged(QUrl)), this, SIGNAL(sourceChanged()));
    this->connect(d->browser, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    this->connect(d->browser, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    this->connect(d->browser, SIGNAL(cursorPositionChanged()), this, SIGNAL(cursorPositionChanged()));
    this->connect(d->browser, SIGNAL(historyChanged()), this, SIGNAL(historyChanged()));
    this->connect(d->browser, SIGNAL(anchorClicked(QUrl)), this, SIGNAL(anchorClicked(QUrl)));
    this->connect(d->browser, SIGNAL(highlighted(QUrl)), this, SIGNAL(highlighted(QUrl)));
    this->connect(d->browser, SIGNAL(undoAvailable(bool)), this, SLOT(_q_onUndoAvailable(bool)));
    this->connect(d->browser, SIGNAL(redoAvailable(bool)), this, SLOT(_q_onRedoAvailable(bool)));
    this->connect(d->browser, SIGNAL(copyAvailable(bool)), this, SLOT(_q_onCopyAvailable(bool)));
}

TextBrowser::~TextBrowser() {}

Qt::Alignment TextBrowser::alignment() const {
    Q_D(const TextBrowser);

    return d->browser->alignment();
}

void TextBrowser::setAlignment(Qt::Alignment align) {
    if (align != this->alignment()) {
        Q_D(TextBrowser);
        d->browser->setAlignment(align);
        emit alignmentChanged();
    }
}

QTextBrowser::AutoFormatting TextBrowser::autoFormatting() const {
    Q_D(const TextBrowser);

    return d->browser->autoFormatting();
}

void TextBrowser::setAutoFormatting(QTextBrowser::AutoFormatting formatting) {
    if (formatting != this->autoFormatting()) {
        Q_D(TextBrowser);
        d->browser->setAutoFormatting(formatting);
        emit autoFormattingChanged();
    }
}

bool TextBrowser::tabChangesFocus() const {
    Q_D(const TextBrowser);

    return d->browser->tabChangesFocus();
}

void TextBrowser::setTabChangesFocus(bool changes) {
    if (changes != this->tabChangesFocus()) {
        Q_D(TextBrowser);
        d->browser->setTabChangesFocus(changes);
        emit tabChangesFocusChanged();
    }
}

QString TextBrowser::documentTitle() const {
    Q_D(const TextBrowser);

    return d->browser->documentTitle();
}

void TextBrowser::setDocumentTitle(const QString &title) {
    if (title != this->documentTitle()) {
        Q_D(TextBrowser);
        d->browser->setDocumentTitle(title);
        emit documentTitleChanged();
    }
}

bool TextBrowser::isUndoRedoEnabled() const {
    Q_D(const TextBrowser);

    return d->browser->isUndoRedoEnabled();
}

void TextBrowser::setUndoRedoEnabled(bool enabled) {
    if (enabled != this->isUndoRedoEnabled()) {
        Q_D(TextBrowser);
        d->browser->setUndoRedoEnabled(enabled);
        emit undoRedoEnabledChanged();
    }
}

QTextBrowser::LineWrapMode TextBrowser::lineWrapMode() const {
    Q_D(const TextBrowser);

    return d->browser->lineWrapMode();
}

void TextBrowser::setLineWrapMode(QTextBrowser::LineWrapMode mode) {
    if (mode != this->lineWrapMode()) {
        Q_D(TextBrowser);
        d->browser->setLineWrapMode(mode);
        emit lineWrapModeChanged();
    }
}

int TextBrowser::lineWrapColumnOrWidth() const {
    Q_D(const TextBrowser);

    return d->browser->lineWrapColumnOrWidth();
}

void TextBrowser::setLineWrapColumnOrWidth(int width) {
    if (width != this->lineWrapColumnOrWidth()) {
        Q_D(TextBrowser);
        d->browser->setLineWrapColumnOrWidth(width);
        emit lineWrapColumnOrWidthChanged();
    }
}

TextBrowser::WrapMode TextBrowser::wordWrapMode() const {
    Q_D(const TextBrowser);

    return WrapMode(d->browser->wordWrapMode());
}

void TextBrowser::setWordWrapMode(WrapMode mode) {
    if (mode != this->wordWrapMode()) {
        Q_D(TextBrowser);
        d->browser->setWordWrapMode(QTextOption::WrapMode(mode));
        emit wordWrapModeChanged();
    }
}

bool TextBrowser::isReadOnly() const {
    Q_D(const TextBrowser);

    return d->browser->isReadOnly();
}

void TextBrowser::setReadOnly(bool readOnly) {
    if (readOnly != this->isReadOnly()) {
        Q_D(TextBrowser);
        d->browser->setReadOnly(readOnly);
    }
}

QUrl TextBrowser::source() const {
    Q_D(const TextBrowser);
    
    return d->browser->source();
}

void TextBrowser::setSource(const QUrl &source) {
    Q_D(TextBrowser);
    
    d->browser->setSource(source);
}

QString TextBrowser::html() const {
    Q_D(const TextBrowser);

    return d->browser->toHtml();
}

void TextBrowser::setHtml(const QString &html) {
    Q_D(TextBrowser);

    d->browser->setHtml(html);
    emit textChanged();
}

QString TextBrowser::text() const {
    Q_D(const TextBrowser);

    return d->browser->toPlainText();
}

void TextBrowser::setText(const QString &text) {
    Q_D(TextBrowser);

    d->browser->setPlainText(text);
    emit textChanged();
}

QStringList TextBrowser::searchPaths() const {
    Q_D(const TextBrowser);
    
    return d->browser->searchPaths();
}

void TextBrowser::setSearchPaths(const QStringList &paths) {
    Q_D(TextBrowser);
    
    d->browser->setSearchPaths(paths);
    emit searchPathsChanged();
}

bool TextBrowser::overwriteMode() const {
    Q_D(const TextBrowser);

    return d->browser->overwriteMode();
}

void TextBrowser::setOverwriteMode(bool overwrite) {
    if (overwrite != this->overwriteMode()) {
        Q_D(TextBrowser);
        d->browser->setOverwriteMode(overwrite);
        emit overwriteModeChanged();
    }
}

int TextBrowser::tabStopWidth() const {
    Q_D(const TextBrowser);

    return d->browser->tabStopWidth();
}

void TextBrowser::setTabStopWidth(int width) {
    if (width != this->tabStopWidth()) {
        Q_D(TextBrowser);
        d->browser->setTabStopWidth(width);
        emit tabStopWidthChanged();
    }
}

bool TextBrowser::acceptRichText() const {
    Q_D(const TextBrowser);

    return d->browser->acceptRichText();
}

void TextBrowser::setAcceptRichText(bool accept) {
    if (accept != this->acceptRichText()) {
        Q_D(TextBrowser);
        d->browser->setAcceptRichText(accept);
        emit acceptRichTextChanged();
    }
}

int TextBrowser::cursorWidth() const {
    Q_D(const TextBrowser);

    return d->browser->cursorWidth();
}

void TextBrowser::setCursorWidth(int width) {
    if (width != this->cursorWidth()) {
        Q_D(TextBrowser);
        d->browser->setCursorWidth(width);
        emit cursorWidthChanged();
    }
}

Qt::TextInteractionFlags TextBrowser::textInteractionFlags() const {
    Q_D(const TextBrowser);

    return d->browser->textInteractionFlags();
}

void TextBrowser::setTextInteractionFlags(Qt::TextInteractionFlags flags) {
    Q_D(TextBrowser);

    d->browser->setTextInteractionFlags(flags);
    emit textInteractionFlagsChanged();
}

QColor TextBrowser::textColor() const {
    Q_D(const TextBrowser);

    return d->browser->textColor();
}

void TextBrowser::setTextColor(const QColor &color) {
    if (color != this->textColor()) {
        Q_D(TextBrowser);
        d->browser->setTextColor(color);
        emit textColorChanged();
    }
}

QColor TextBrowser::textBackgroundColor() const {
    Q_D(const TextBrowser);

    return d->browser->textBackgroundColor();
}

void TextBrowser::setTextBackgroundColor(const QColor &color) {
    if (color != this->textBackgroundColor()) {
        Q_D(TextBrowser);
        d->browser->setTextBackgroundColor(color);
        emit textBackgroundColorChanged();
    }
}

bool TextBrowser::isUndoAvailable() const {
    Q_D(const TextBrowser);

    return d->undoAvailable;
}

bool TextBrowser::isRedoAvailable() const {
    Q_D(const TextBrowser);

    return d->redoAvailable;
}

bool TextBrowser::isCopyAvailable() const {
    Q_D(const TextBrowser);

    return d->copyAvailable;
}

bool TextBrowser::isBackwardAvailable() const {
    Q_D(const TextBrowser);
    
    return d->browser->isBackwardAvailable();
}

bool TextBrowser::isForwardAvailable() const {
    Q_D(const TextBrowser);
    
    return d->browser->isForwardAvailable();
}

int TextBrowser::backwardHistoryCount() const {
    Q_D(const TextBrowser);
    
    return d->browser->backwardHistoryCount();
}

int TextBrowser::forwardHistoryCount() const {
    Q_D(const TextBrowser);
    
    return d->browser->forwardHistoryCount();
}

bool TextBrowser::interactive() const {
    Q_D(const TextBrowser);

    return d->kineticScroller->isEnabled();
}

void TextBrowser::setInteractive(bool interactive) {
    if (interactive != this->interactive()) {
        Q_D(TextBrowser);
        d->kineticScroller->setEnabled(interactive);
        emit interactiveChanged();
    }
}

bool TextBrowser::moving() const {
    Q_D(const TextBrowser);

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

bool TextBrowser::atXBeginning() const {
    Q_D(const TextBrowser);

    return d->scrollArea->horizontalScrollBar()->value() == d->scrollArea->horizontalScrollBar()->minimum();
}

bool TextBrowser::atXEnd() const {
    Q_D(const TextBrowser);

    return d->scrollArea->horizontalScrollBar()->value() == d->scrollArea->horizontalScrollBar()->maximum();
}

bool TextBrowser::atYBeginning() const {
    Q_D(const TextBrowser);

    return d->scrollArea->verticalScrollBar()->value() == d->scrollArea->verticalScrollBar()->minimum();
}

bool TextBrowser::atYEnd() const {
    Q_D(const TextBrowser);

    return d->scrollArea->verticalScrollBar()->value() == d->scrollArea->verticalScrollBar()->maximum();
}

int TextBrowser::contentX() const {
    Q_D(const TextBrowser);

    return d->scrollArea->horizontalScrollBar()->value();
}

void TextBrowser::setContentX(int x) {
    Q_D(TextBrowser);

    d->scrollArea->horizontalScrollBar()->setValue(x);
}

int TextBrowser::contentY() const {
    Q_D(const TextBrowser);

    return d->scrollArea->horizontalScrollBar()->value();
}

void TextBrowser::setContentY(int y) {
    Q_D(TextBrowser);

    d->scrollArea->verticalScrollBar()->setValue(y);
}

qreal TextBrowser::flickDeceleration() const {
    Q_D(const TextBrowser);

    return d->kineticScroller->decelerationFactor();
}

void TextBrowser::setFlickDeceleration(qreal deceleration) {
    if (deceleration != this->flickDeceleration()) {
        Q_D(TextBrowser);
        d->kineticScroller->setDecelerationFactor(deceleration);
        emit flickDecelerationChanged();
    }
}

qreal TextBrowser::maximumFlickVelocity() const {
    Q_D(const TextBrowser);

    return d->kineticScroller->maximumVelocity();
}

void TextBrowser::setMaximumFlickVelocity(qreal maximum) {
    if (maximum != this->maximumFlickVelocity()) {
        Q_D(TextBrowser);
        d->kineticScroller->setMaximumVelocity(maximum);
        emit maximumFlickVelocityChanged();
    }
}

QString TextBrowser::historyTitle(int i) const {
    Q_D(const TextBrowser);
    
    return d->browser->historyTitle(i);
}

QUrl TextBrowser::historyUrl(int i) const {
    Q_D(const TextBrowser);
    
    return d->browser->historyUrl(i);
}

void TextBrowser::clear() {
    Q_D(TextBrowser);

    d->browser->clear();
}

void TextBrowser::copy() {
    Q_D(TextBrowser);

    d->browser->copy();
}

void TextBrowser::cut() {
    Q_D(TextBrowser);

    d->browser->cut();
}

void TextBrowser::paste() {
    Q_D(TextBrowser);

    d->browser->paste();
}

void TextBrowser::redo() {
    Q_D(TextBrowser);

    d->browser->redo();
}

void TextBrowser::selectAll() {
    Q_D(TextBrowser);

    d->browser->selectAll();
}

void TextBrowser::backward() {
    Q_D(TextBrowser);
    
    d->browser->backward();
}

void TextBrowser::forward() {
    Q_D(TextBrowser);
    
    d->browser->forward();
}

void TextBrowser::home() {
    Q_D(TextBrowser);
    
    d->browser->home();
}

void TextBrowser::reload() {
    Q_D(TextBrowser);
    
    d->browser->reload();
}

void TextBrowser::clearHistory() {
    Q_D(TextBrowser);
    
    d->browser->clearHistory();
}

#include "moc_textbrowser_p.cpp"

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

#include "qchtextdocument.h"
#include <QTextBlock>
#include <QTextCursor>
#include <QTextLayout>

class QchTextDocumentPrivate
{

public:
    QchTextDocumentPrivate(QchTextDocument *parent) :
        q_ptr(parent),
        target(0),
        textDocument(0),
        complete(false)
    {
    }

    void updateTextDocument() {
        if (!complete) {
            return;
        }

        Q_Q(QchTextDocument);

        if (textDocument) {
            q->disconnect(textDocument, SIGNAL(blockCountChanged(int)), q, SIGNAL(lineCountChanged()));
            q->disconnect(textDocument, SIGNAL(modificationChanged(bool)), q, SIGNAL(modifiedChanged()));
            q->disconnect(textDocument, SIGNAL(redoAvailable(bool)), q, SIGNAL(canRedoChanged()));
            q->disconnect(textDocument, SIGNAL(undoAvailable(bool)), q, SIGNAL(canUndoChanged()));
            q->disconnect(textDocument, SIGNAL(destroyed(QObject*)), q, SLOT(_q_onTextDocumentDestroyed()));
        }

        if (target) {
            textDocument = target->findChild<QTextDocument*>();

            if (textDocument) {
                q->connect(textDocument, SIGNAL(blockCountChanged(int)), q, SIGNAL(lineCountChanged()));
                q->connect(textDocument, SIGNAL(modificationChanged(bool)), q, SIGNAL(modifiedChanged()));
                q->connect(textDocument, SIGNAL(redoAvailable(bool)), q, SIGNAL(canRedoChanged()));
                q->connect(textDocument, SIGNAL(undoAvailable(bool)), q, SIGNAL(canUndoChanged()));
                q->connect(textDocument, SIGNAL(destroyed(QObject*)), q, SLOT(_q_onTextDocumentDestroyed()));
            }
        }
        else {
            textDocument = 0;
        }

        emit q->textDocumentChanged();
        emit q->canRedoChanged();
        emit q->canUndoChanged();
        emit q->lineCountChanged();
        emit q->modifiedChanged();
    }

    void _q_onTargetDestroyed() {
        Q_Q(QchTextDocument);
        target = 0;
        emit q->targetChanged();
    }

    void _q_onTextDocumentDestroyed() {
        Q_Q(QchTextDocument);
        textDocument = 0;
        emit q->textDocumentChanged();
        emit q->canRedoChanged();
        emit q->canUndoChanged();
        emit q->lineCountChanged();
        emit q->modifiedChanged();
    }

    QchTextDocument *q_ptr;
    QObject *target;
    QTextDocument *textDocument;

    bool complete;

    Q_DECLARE_PUBLIC(QchTextDocument)
};

QchTextDocument::QchTextDocument(QObject *parent) :
    QObject(parent),
    d_ptr(new QchTextDocumentPrivate(this))
{
}

QchTextDocument::~QchTextDocument() {}

QObject* QchTextDocument::target() const {
    Q_D(const QchTextDocument);
    return d->target;
}

void QchTextDocument::setTarget(QObject *obj) {
    if (obj != target()) {
        Q_D(QchTextDocument);

        if (d->target) {
            disconnect(d->target, SIGNAL(destroyed(QObject*)), this, SLOT(_q_onTargetDestroyed()));
        }

        d->target = obj;

        if (d->target) {
            connect(d->target, SIGNAL(destroyed(QObject*)), this, SLOT(_q_onTargetDestroyed()));
        }

        emit targetChanged();
        d->updateTextDocument();
    }
}

void QchTextDocument::resetTarget() {
    setTarget(0);
}

QTextDocument* QchTextDocument::textDocument() const {
    Q_D(const QchTextDocument);
    return d->textDocument;
}

bool QchTextDocument::canRedo() const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->isRedoAvailable() : false;
}

bool QchTextDocument::canUndo() const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->isUndoAvailable() : false;
}

int QchTextDocument::lineCount() const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->blockCount() : 0;
}

bool QchTextDocument::isModified() const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->isModified() : false;
}

void QchTextDocument::setModified(bool modified) {
    Q_D(QchTextDocument);

    if (d->textDocument) {
        d->textDocument->setModified(modified);
    }
}

int QchTextDocument::lineHeight(int lineNumber) const {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return 0;
    }

    const QTextLayout *layout = d->textDocument->findBlockByNumber(lineNumber).layout();
    return layout ? int(layout->boundingRect().height()) : 0;
}

int QchTextDocument::lineNumber(int position) const {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return 0;
    }

    QTextCursor cursor(d->textDocument);
    cursor.setPosition(position);
    return cursor.blockNumber();
}

int QchTextDocument::columnNumber(int position) const {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return 0;
    }

    QTextCursor cursor(d->textDocument);
    cursor.setPosition(position);
    return cursor.positionInBlock();
}

int QchTextDocument::position(int lineNumber, int columnNumber) const {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return 0;
    }

    QTextCursor cursor(d->textDocument);
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineNumber);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, columnNumber);
    return cursor.position();
}

void QchTextDocument::redo() {
    Q_D(QchTextDocument);

    if (d->textDocument) {
        d->textDocument->redo();
    }
}

void QchTextDocument::undo() {
    Q_D(QchTextDocument);

    if (d->textDocument) {
        d->textDocument->undo();
    }
}

void QchTextDocument::append(const QString &text) {
    Q_D(const QchTextDocument);
    
    if (!d->textDocument) {
        return;
    }

    QTextCursor cursor(d->textDocument);
    cursor.setPosition(d->textDocument->characterCount());
    cursor.insertText(text);
}

void QchTextDocument::insert(int position, const QString &text) {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return;
    }

    QTextCursor cursor(d->textDocument);
    cursor.setPosition(position);
    cursor.insertText(text);
}

QString QchTextDocument::remove(int start, int end) {
    Q_D(const QchTextDocument);

    if (!d->textDocument) {
        return QString();
    }

    QTextCursor cursor(d->textDocument);
    cursor.setPosition(start);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    const QString text = cursor.selectedText();
    cursor.deleteChar();
    return text;
}

QString QchTextDocument::text(int start, int end) const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->toPlainText().mid(start, end - start) : QString();
}

QString QchTextDocument::formattedText(int start, int end) const {
    Q_D(const QchTextDocument);
    return d->textDocument ? d->textDocument->toHtml().mid(start, end - start) : QString();
}

void QchTextDocument::classBegin() {}

void QchTextDocument::componentComplete() {
    Q_D(QchTextDocument);
    d->complete = true;

    if (d->target) {
        d->updateTextDocument();
    }
}

#include "moc_qchtextdocument.cpp"


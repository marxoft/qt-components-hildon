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

#ifndef QCHTEXTDOCUMENT_H
#define QCHTEXTDOCUMENT_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <QTextDocument>
#include <qdeclarative.h>

class QTextDocument;
class QchTextDocumentPrivate;

class QchTextDocument : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QObject* target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged)
    Q_PROPERTY(QTextDocument* textDocument READ textDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY canRedoChanged)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged)
    Q_PROPERTY(int lineCount READ lineCount NOTIFY lineCountChanged)
    Q_PROPERTY(bool modified READ isModified WRITE setModified NOTIFY modifiedChanged)

    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit QchTextDocument(QObject *parent = 0);
    ~QchTextDocument();

    QObject* target() const;
    void setTarget(QObject *obj);
    void resetTarget();

    QTextDocument* textDocument() const;

    bool canRedo() const;
    bool canUndo() const;

    int lineCount() const;

    bool isModified() const;
    void setModified(bool modified = true);

public Q_SLOTS:
    int lineHeight(int lineNumber) const;

    int lineNumber(int position) const;
    int columnNumber(int position) const;
    int position(int lineNumber, int columnNumber) const;
    
    void redo();
    void undo();

    void append(const QString &text);
    void insert(int position, const QString &text);
    QString remove(int start, int end);

    QString text(int start, int end) const;
    QString formattedText(int start, int end) const;

Q_SIGNALS:
    void targetChanged();
    void textDocumentChanged();
    void canRedoChanged();
    void canUndoChanged();
    void lineCountChanged();
    void modifiedChanged();

private:
    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<QchTextDocumentPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_onTargetDestroyed())
    Q_PRIVATE_SLOT(d_func(), void _q_onTextDocumentDestroyed())

    Q_DECLARE_PRIVATE(QchTextDocument)
    Q_DISABLE_COPY(QchTextDocument)
};

QML_DECLARE_TYPE(QchTextDocument)
QML_DECLARE_TYPE(QTextDocument)

#endif // QCHTEXTDOCUMENT_H


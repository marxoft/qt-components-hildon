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

#ifndef TEXTBROWSER_P_H
#define TEXTBROWSER_P_H

#include "item_p.h"
#include <QTextBrowser>

class TextBrowserPrivate;

class TextBrowser : public Item
{
    Q_OBJECT

    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(QTextBrowser::AutoFormatting autoFormatting READ autoFormatting WRITE setAutoFormatting NOTIFY autoFormattingChanged)
    Q_PROPERTY(bool tabChangesFocus READ tabChangesFocus WRITE setTabChangesFocus NOTIFY tabChangesFocusChanged)
    Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle NOTIFY documentTitleChanged)
    Q_PROPERTY(bool undoRedoEnabled READ isUndoRedoEnabled WRITE setUndoRedoEnabled NOTIFY undoRedoEnabledChanged)
    Q_PROPERTY(QTextBrowser::LineWrapMode lineWrapMode READ lineWrapMode WRITE setLineWrapMode NOTIFY lineWrapModeChanged)
    Q_PROPERTY(int lineWrapColumnOrWidth READ lineWrapColumnOrWidth WRITE setLineWrapColumnOrWidth NOTIFY lineWrapColumnOrWidthChanged)
    Q_PROPERTY(WrapMode wordWrapMode READ wordWrapMode WRITE setWordWrapMode NOTIFY wordWrapModeChanged)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly NOTIFY readOnlyChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString html READ html WRITE setHtml NOTIFY textChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QStringList searchPaths READ searchPaths WRITE setSearchPaths NOTIFY searchPathsChanged)
    Q_PROPERTY(bool overwriteMode READ overwriteMode WRITE setOverwriteMode NOTIFY overwriteModeChanged)
    Q_PROPERTY(int tabStopWidth READ tabStopWidth WRITE setTabStopWidth NOTIFY tabStopWidthChanged)
    Q_PROPERTY(bool acceptRichText READ acceptRichText WRITE setAcceptRichText NOTIFY acceptRichTextChanged)
    Q_PROPERTY(int cursorWidth READ cursorWidth WRITE setCursorWidth NOTIFY cursorWidthChanged)
    Q_PROPERTY(Qt::TextInteractionFlags textInteractionFlags READ textInteractionFlags WRITE setTextInteractionFlags NOTIFY textInteractionFlagsChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor textBackgroundColor READ textBackgroundColor WRITE setTextBackgroundColor NOTIFY textBackgroundColorChanged)
    Q_PROPERTY(bool undoAvailable READ isUndoAvailable NOTIFY undoAvailableChanged)
    Q_PROPERTY(bool redoAvailable READ isRedoAvailable NOTIFY redoAvailableChanged)
    Q_PROPERTY(bool copyAvailable READ isCopyAvailable NOTIFY copyAvailableChanged)
    Q_PROPERTY(bool backwardAvailable READ isBackwardAvailable NOTIFY historyChanged)
    Q_PROPERTY(bool forwardAvailable READ isForwardAvailable NOTIFY historyChanged)
    Q_PROPERTY(int backwardHistoryCount READ backwardHistoryCount NOTIFY historyChanged)
    Q_PROPERTY(int forwardHistoryCount READ forwardHistoryCount NOTIFY historyChanged)
    Q_PROPERTY(bool openLinks READ openLinks WRITE setOpenLinks NOTIFY openLinksChanged)
    Q_PROPERTY(bool openExternalLinks READ openExternalLinks WRITE setOpenExternalLinks NOTIFY openExternalLinksChanged)
    Q_PROPERTY(bool interactive READ interactive WRITE setInteractive NOTIFY interactiveChanged)
    Q_PROPERTY(bool moving READ moving NOTIFY movingChanged)
    Q_PROPERTY(bool atXBeginning READ atXBeginning NOTIFY atXBeginningChanged)
    Q_PROPERTY(bool atXEnd READ atXEnd NOTIFY atXEndChanged)
    Q_PROPERTY(bool atYBeginning READ atYBeginning NOTIFY atYBeginningChanged)
    Q_PROPERTY(bool atYEnd READ atYEnd NOTIFY atYEndChanged)
    Q_PROPERTY(int contentX READ contentX WRITE setContentX NOTIFY contentXChanged)
    Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
    Q_PROPERTY(qreal flickDeceleration READ flickDeceleration WRITE setFlickDeceleration NOTIFY flickDecelerationChanged)
    Q_PROPERTY(qreal maximumFlickVelocity READ maximumFlickVelocity WRITE setMaximumFlickVelocity NOTIFY maximumFlickVelocityChanged)

    Q_ENUMS(QTextBrowser::AutoFormatting QTextBrowser::LineWrapMode WrapMode)

public:
    enum WrapMode {
        NoWrap = 0,
        WordWrap,
        ManualWrap,
        WrapAnywhere,
        WrapAtWordBoundaryOrAnywhere
    };

    explicit TextBrowser(QWidget *parent = 0);
    ~TextBrowser();

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment align);

    QTextBrowser::AutoFormatting autoFormatting() const;
    void setAutoFormatting(QTextBrowser::AutoFormatting formatting);

    bool tabChangesFocus() const;
    void setTabChangesFocus(bool changes);

    QString documentTitle() const;
    void setDocumentTitle(const QString &title);

    bool isUndoRedoEnabled() const;
    void setUndoRedoEnabled(bool enabled);

    QTextBrowser::LineWrapMode lineWrapMode() const;
    void setLineWrapMode(QTextBrowser::LineWrapMode mode);

    int lineWrapColumnOrWidth() const;
    void setLineWrapColumnOrWidth(int width);

    WrapMode wordWrapMode() const;
    void setWordWrapMode(WrapMode mode);

    bool isReadOnly() const;
    void setReadOnly(bool readOnly);
    
    QUrl source() const;
    void setSource(const QUrl &source);

    QString html() const;
    void setHtml(const QString &html);

    QString text() const;
    void setText(const QString &text);
    
    QStringList searchPaths() const;
    void setSearchPaths(const QStringList &paths);

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

    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    bool isCopyAvailable() const;
    
    bool isBackwardAvailable() const;
    bool isForwardAvailable() const;
    
    int backwardHistoryCount() const;
    int forwardHistoryCount() const;
    
    bool openLinks() const;
    void setOpenLinks(bool open);
    
    bool openExternalLinks() const;
    void setOpenExternalLinks(bool open);

    bool interactive() const;
    void setInteractive(bool interactive);

    bool moving() const;

    bool atXBeginning() const;
    bool atXEnd() const;

    bool atYBeginning() const;
    bool atYEnd() const;

    int contentX() const;
    void setContentX(int x);

    int contentY() const;
    void setContentY(int y);

    qreal flickDeceleration() const;
    void setFlickDeceleration(qreal deceleration);

    qreal maximumFlickVelocity() const;
    void setMaximumFlickVelocity(qreal maximum);
    
    Q_INVOKABLE QString historyTitle(int i) const;
    Q_INVOKABLE QUrl historyUrl(int i) const;

public slots:
    void clear();
    void copy();
    void cut();
    void paste();
    void redo();
    void selectAll();
    
    void backward();
    void forward();
    void home();
    void reload();
    void clearHistory();

signals:
    void alignmentChanged();
    void autoFormattingChanged();
    void tabChangesFocusChanged();
    void documentTitleChanged();
    void undoRedoEnabledChanged();
    void lineWrapModeChanged();
    void lineWrapColumnOrWidthChanged();
    void wordWrapModeChanged();
    void readOnlyChanged();
    void sourceChanged();
    void textChanged();
    void searchPathsChanged();
    void overwriteModeChanged();
    void tabStopWidthChanged();
    void acceptRichTextChanged();
    void cursorWidthChanged();
    void textInteractionFlagsChanged();
    void textColorChanged();
    void textBackgroundColorChanged();
    void selectionChanged();
    void cursorPositionChanged();
    void undoAvailableChanged();
    void redoAvailableChanged();
    void copyAvailableChanged();
    void historyChanged();
    void openLinksChanged();
    void openExternalLinksChanged();
    void interactiveChanged();
    void movingChanged();
    void atXBeginningChanged();
    void atXEndChanged();
    void atYBeginningChanged();
    void atYEndChanged();
    void contentXChanged();
    void contentYChanged();
    void flickDecelerationChanged();
    void maximumFlickVelocityChanged();
    void anchorClicked(const QUrl &link);
    void highlighted(const QUrl &link);

protected:
    TextBrowser(TextBrowserPrivate &dd, QWidget *parent = 0);

    Q_DECLARE_PRIVATE(TextBrowser)

    Q_PRIVATE_SLOT(d_func(), void _q_onUndoAvailable(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onRedoAvailable(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onCopyAvailable(bool))
    Q_PRIVATE_SLOT(d_func(), void _q_onHorizontalScrollPositionChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onVerticalScrollPositionChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onScrollingStopped())

private:
    Q_DISABLE_COPY(TextBrowser)
};

QML_DECLARE_TYPE(TextBrowser)

#endif // TEXTBROWSER_P_H

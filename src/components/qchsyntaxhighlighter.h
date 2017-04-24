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

#ifndef QCHSYNTAXHIGHLIGHTER_H
#define QCHSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QDeclarativeListProperty>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QchTextCharFormat;
class QchSyntaxHighlightRulePrivate;

class QchSyntaxHighlightRule : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QchTextCharFormat* format READ format WRITE setFormat RESET resetFormat NOTIFY formatChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority RESET resetPriority NOTIFY priorityChanged)
    Q_PROPERTY(QRegExp regExp READ regExp WRITE setRegExp RESET resetRegExp NOTIFY regExpChanged)
    Q_PROPERTY(int regExpIndex READ regExpIndex WRITE setRegExpIndex NOTIFY regExpIndexChanged)
    Q_PROPERTY(QRegExp startRegExp READ regExp WRITE setRegExp RESET resetRegExp NOTIFY regExpChanged)
    Q_PROPERTY(int startRegExpIndex READ regExpIndex WRITE setRegExpIndex NOTIFY regExpIndexChanged)
    Q_PROPERTY(QRegExp endRegExp READ endRegExp WRITE setEndRegExp RESET resetEndRegExp NOTIFY endRegExpChanged)
    Q_PROPERTY(int endRegExpIndex READ endRegExpIndex WRITE setEndRegExpIndex NOTIFY endRegExpIndexChanged)
    Q_PROPERTY(QVariant allow READ allowedRules WRITE setAllowedRules NOTIFY allowedRulesChanged)

public:
    explicit QchSyntaxHighlightRule(QObject *parent = 0);
    explicit QchSyntaxHighlightRule(const QRegExp &regExp, const QRegExp &endRegExp, QObject *parent = 0);
    ~QchSyntaxHighlightRule();

    QchTextCharFormat* format();
    void setFormat(QchTextCharFormat *format);
    void resetFormat();

    bool isEnabled() const;
    void setEnabled(bool enabled);

    int priority() const;
    void setPriority(int priority);
    void resetPriority();

    QRegExp regExp() const;
    void setRegExp(const QRegExp &re);
    void resetRegExp();

    int regExpIndex() const;
    void setRegExpIndex(int index);

    QRegExp endRegExp() const;
    void setEndRegExp(const QRegExp &re);
    void resetEndRegExp();

    int endRegExpIndex() const;
    void setEndRegExpIndex(int index);

    QVariant allowedRules() const;
    void setAllowedRules(const QVariant &rules);

Q_SIGNALS:
    void changed();
    void formatChanged();
    void enabledChanged();
    void exclusiveChanged();
    void priorityChanged();
    void regExpChanged();
    void regExpIndexChanged();
    void endRegExpChanged();
    void endRegExpIndexChanged();
    void allowedRulesChanged();

private:
    QScopedPointer<QchSyntaxHighlightRulePrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_removeAllowedRule(QObject*))
    
    Q_DECLARE_PRIVATE(QchSyntaxHighlightRule)
    Q_DISABLE_COPY(QchSyntaxHighlightRule)

    friend class QchSyntaxHighlighter;
    friend class QchSyntaxHighlighterPrivate;
};

class QchSyntaxHighlighterPrivate;

class QchSyntaxHighlighter : public QSyntaxHighlighter, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QTextDocument* textDocument READ document WRITE setDocument RESET resetDocument)
    Q_PROPERTY(bool autoRehighlight READ autoRehighlight WRITE setAutoRehighlight NOTIFY autoRehighlightChanged)
    Q_PROPERTY(int currentBlockState READ currentBlockState WRITE setCurrentBlockState)
    Q_PROPERTY(int previousBlockState READ previousBlockState)
    Q_PROPERTY(QDeclarativeListProperty<QchSyntaxHighlightRule> rules READ rules)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "rules")

public:
    explicit QchSyntaxHighlighter(QObject *parent = 0);
    ~QchSyntaxHighlighter();

    void resetDocument();

    bool autoRehighlight() const;
    void setAutoRehighlight(bool enabled);

    QDeclarativeListProperty<QchSyntaxHighlightRule> rules();

public Q_SLOTS:
    QchSyntaxHighlightRule* addRule(const QRegExp &regExp, const QRegExp &endRegExp = QRegExp());
    void addRule(QchSyntaxHighlightRule *rule);
    void removeRule(QchSyntaxHighlightRule *rule);

    void rehighlightText(int position, int length);

    void setFormat(int start, int count, QchTextCharFormat *format);

Q_SIGNALS:
    void autoRehighlightChanged();
    void highlightText(const QString &text);

private:
    virtual void highlightBlock(const QString &text);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<QchSyntaxHighlighterPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_enabledChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_moveRule());
    Q_PRIVATE_SLOT(d_func(), void _q_removeRule(QObject*))

    Q_DECLARE_PRIVATE(QchSyntaxHighlighter)
    Q_DISABLE_COPY(QchSyntaxHighlighter)
};

QML_DECLARE_TYPE(QchSyntaxHighlightRule)
QML_DECLARE_TYPE(QchSyntaxHighlighter)

#endif // QCHSYNTAXHIGHLIGHTER_H


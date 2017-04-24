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

#include "qchsyntaxhighlighter.h"
#include "qchtextcharformat.h"
#include <QTextDocument>
#include <QTimer>

class QchSyntaxHighlightRulePrivate
{

public:
    QchSyntaxHighlightRulePrivate(QchSyntaxHighlightRule *parent) :
        q_ptr(parent),
        format(0),
        ownFormat(false),
        enabled(true),
        regExpIndex(0),
        endRegExpIndex(0),
        priority(0),
        blockState(-1)
    {
    }

    void _q_removeAllowedRule(QObject *obj) {
        if (QchSyntaxHighlightRule *rule = qobject_cast<QchSyntaxHighlightRule*>(obj)) {
            Q_Q(QchSyntaxHighlightRule);
            allowedRules.removeOne(rule);
            q->disconnect(rule, SIGNAL(destroyed(QObject*)), q, SLOT(_q_removeAllowedRule(QObject*)));

            if (allowedRulesVariant.type() == QVariant::List) {
                QVariantList list = allowedRulesVariant.toList();
                list.removeOne(QVariant::fromValue(rule));
                allowedRulesVariant = list;
            }
            else {
                allowedRulesVariant = QVariant();
            }

            emit q->allowedRulesChanged();
            emit q->changed();
        }
    }

    QchSyntaxHighlightRule *q_ptr;

    QchTextCharFormat *format;

    bool ownFormat;
    bool enabled;

    QRegExp regExp;
    QRegExp endRegExp;

    int regExpIndex;
    int endRegExpIndex;
    int priority;
    int blockState;

    QVariant allowedRulesVariant;
    QList<QchSyntaxHighlightRule*> allowedRules;

    Q_DECLARE_PUBLIC(QchSyntaxHighlightRule)
};

/*!
 * \class SyntaxHighlightRule
 * \ingroup components
 * \brief Defines a rule for highlighting text.
 *
 * The SyntaxHighlightRule class is used to define a rule used by a SyntaxHighlighter when highlighting text.
 * 
 * \sa SyntaxHighlighter
 */
QchSyntaxHighlightRule::QchSyntaxHighlightRule(QObject *parent) :
    QObject(parent),
    d_ptr(new QchSyntaxHighlightRulePrivate(this))
{
}

QchSyntaxHighlightRule::QchSyntaxHighlightRule(const QRegExp &regExp, const QRegExp &endRegExp, QObject *parent) :
    QObject(parent),
    d_ptr(new QchSyntaxHighlightRulePrivate(this))
{
    setRegExp(regExp);
    setEndRegExp(endRegExp);
}

QchSyntaxHighlightRule::~QchSyntaxHighlightRule() {}

/*!
 * The TextCharFormat used by the rule.
 *
 * \sa TextCharFormat
 */
QchTextCharFormat* QchSyntaxHighlightRule::format() {
    Q_D(QchSyntaxHighlightRule);

    if (!d->format) {
        d->format = new QchTextCharFormat(this);
        d->ownFormat = true;
        connect(d->format, SIGNAL(changed()), this, SIGNAL(changed()));
    }

    return d->format;
}

void QchSyntaxHighlightRule::setFormat(QchTextCharFormat *format) {
    Q_D(QchSyntaxHighlightRule);

    if (format != d->format) {
        if (d->format) {
            disconnect(d->format, SIGNAL(changed()), this, SIGNAL(changed()));

            if (d->ownFormat) {
                delete d->format;
            }
        }

        if (format) {
            d->format = format;
            d->ownFormat = false;
        }
        else {
            d->format = new QchTextCharFormat(this);
            d->ownFormat = true;
        }

        connect(d->format, SIGNAL(changed()), this, SIGNAL(changed()));
        emit formatChanged();
        emit changed();
    }
}

void QchSyntaxHighlightRule::resetFormat() {
    setFormat(0);
}

/*!
 * Whether the rule is enabled.
 *
 * A disabled rule will not be used to match text.
 *
 * The default value is \c true.
 */
bool QchSyntaxHighlightRule::isEnabled() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->enabled;
}

void QchSyntaxHighlightRule::setEnabled(bool enabled) {
    Q_D(QchSyntaxHighlightRule);

    if (enabled != d->enabled) {
        d->enabled = enabled;
        emit enabledChanged();
        emit changed();
    }
}

/*!
 * The priority of the rule.
 *
 * Where there is a conflict between two or more rules, the rule with the
 * highest priority will be used.
 *
 * The default value is \c 0.
 */
int QchSyntaxHighlightRule::priority() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->priority;
}

void QchSyntaxHighlightRule::setPriority(int priority) {
    Q_D(QchSyntaxHighlightRule);

    if (priority != d->priority) {
        d->priority = priority;
        emit priorityChanged();
        emit changed();
    }
}

void QchSyntaxHighlightRule::resetPriority() {
    setPriority(0);
}

/*!
 * The regular expression used to match text.
 *
 * \sa endRegExp
 */
QRegExp QchSyntaxHighlightRule::regExp() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->regExp;
}

void QchSyntaxHighlightRule::setRegExp(const QRegExp &regExp) {
    Q_D(QchSyntaxHighlightRule);

    if (regExp != d->regExp) {
        d->regExp = regExp;
        emit regExpChanged();
        emit changed();
    }
}

void QchSyntaxHighlightRule::resetRegExp() {
    setRegExp(QRegExp());
}

/*!
 * The index of the regExp captured text to be highlighted.
 *
 * The default value is \c 0, meaning the entire match is highlighted.
 *
 * \sa regExp, endRegExpIndex
 */
int QchSyntaxHighlightRule::regExpIndex() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->regExpIndex;
}

void QchSyntaxHighlightRule::setRegExpIndex(int index) {
    Q_D(QchSyntaxHighlightRule);

    if (index != d->regExpIndex) {
        d->regExpIndex = index;
        emit regExpIndexChanged();
        emit changed();
    }
}

/*!
 * The regular expression used to match the end of the text to be highlighted.
 *
 * This property is used mostly for rules that match text across two or more text blocks.
 *
 * \sa regExp
 */
QRegExp QchSyntaxHighlightRule::endRegExp() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->endRegExp;
}

void QchSyntaxHighlightRule::setEndRegExp(const QRegExp &regExp) {
    Q_D(QchSyntaxHighlightRule);

    if (regExp != d->endRegExp) {
        d->endRegExp = regExp;
        emit endRegExpChanged();
        emit changed();
    }
}

void QchSyntaxHighlightRule::resetEndRegExp() {
    setEndRegExp(QRegExp());
}

/*!
 * The index of the endRegExp captured text to be highlighted.
 *
 * The default value is \c 0, meaning the entire match is highlighted.
 *
 * \sa endRegExp, regExpIndex
 */
int QchSyntaxHighlightRule::endRegExpIndex() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->endRegExpIndex;
}

void QchSyntaxHighlightRule::setEndRegExpIndex(int index) {
    Q_D(QchSyntaxHighlightRule);

    if (index != d->endRegExpIndex) {
        d->endRegExpIndex = index;
        emit endRegExpIndexChanged();
        emit changed();
    }
}

/*!
 * One or more rules that may be applied even when they conflict with this rule.
 *
 * The value of this property may be either a single instance of an existing SyntaxHighlightRule, or a list.
 */
QVariant QchSyntaxHighlightRule::allowedRules() const {
    Q_D(const QchSyntaxHighlightRule);
    return d->allowedRulesVariant;
}

void QchSyntaxHighlightRule::setAllowedRules(const QVariant &rules) {
    Q_D(QchSyntaxHighlightRule);

    foreach (QchSyntaxHighlightRule *rule, d->allowedRules) {
        disconnect(rule, SIGNAL(destroyed(QObject*)), this, SLOT(_q_removeAllowedRule(QObject*)));
    }

    d->allowedRules.clear();
    d->allowedRulesVariant = rules;
    QVariantList list;

    if (rules.type() == QVariant::List) {
        list = rules.toList();
    }
    else {
        list << rules;
    }

    foreach (const QVariant &r, list) {
        if (QObject *obj = qvariant_cast<QObject*>(r)) {
            if (QchSyntaxHighlightRule *rule = qobject_cast<QchSyntaxHighlightRule*>(obj)) {
                d->allowedRules << rule;
                connect(rule, SIGNAL(destroyed(QObject*)), this, SLOT(_q_removeAllowedRule(QObject*)));
            }
        }
    }

    emit allowedRulesChanged();
    emit changed();
}

struct RuleMatch
{
    RuleMatch(QchSyntaxHighlightRule *r, int s, int e) :
        rule(r),
        start(s),
        end(e)
    {
    }

    QchSyntaxHighlightRule *rule;
    int start;
    int end;
};

typedef QList<RuleMatch> RuleMatchList;

class QchSyntaxHighlighterPrivate
{

public:
    QchSyntaxHighlighterPrivate(QchSyntaxHighlighter *parent) :
        q_ptr(parent),
        autoRehighlight(true),
        complete(false)
    {
        timer.setInterval(100);
        timer.setSingleShot(true);
        parent->connect(&timer, SIGNAL(timeout()), parent, SLOT(rehighlight()));
    }

    void addRule(QchSyntaxHighlightRule *rule) {
        if (rules.contains(rule)) {
            return;
        }

        Q_Q(QchSyntaxHighlighter);
        rule->d_func()->blockState = ++blockState;
        rules << rule;
        insertRule(rule);
        q->connect(rule, SIGNAL(priorityChanged()), q, SLOT(_q_moveRule()));
        q->connect(rule, SIGNAL(destroyed(QObject*)), q, SLOT(_q_removeRule(QObject*)));

        if (autoRehighlight) {
            q->connect(rule, SIGNAL(changed()), &timer, SLOT(start()));
            q->connect(rule, SIGNAL(enabledChanged()), q, SLOT(_q_enabledChanged()));

            if (complete) {
                q->rehighlight();
            }
        }
    }

    void insertRule(QchSyntaxHighlightRule *rule) {
        for (int i = 0; i < sortedRules.size(); i++) {
            if (rule->priority() > sortedRules.at(i)->priority()) {
                sortedRules.insert(i, rule);
                return;
            }
        }

        sortedRules << rule;
    }

    void removeRule(QchSyntaxHighlightRule *rule) {
        const int i = rules.indexOf(rule);

        if (i == -1) {
            return;
        }

        Q_Q(QchSyntaxHighlighter);
        rules.removeAt(i);
        sortedRules.removeOne(rule);
        q->disconnect(rule, SIGNAL(changed()), &timer, SLOT(start()));
        q->disconnect(rule, SIGNAL(enabledChanged()), q, SLOT(_q_enabledChanged()));
        q->disconnect(rule, SIGNAL(priorityChanged()), q, SLOT(_q_moveRule()));
        q->disconnect(rule, SIGNAL(destroyed(QObject*)), q, SLOT(_q_removeRule(QObject*)));

        if ((autoRehighlight) && (complete)) {
            q->rehighlight();
        }
    }

    void _q_enabledChanged() {
        Q_Q(QchSyntaxHighlighter);

        if (QchSyntaxHighlightRule *rule = qobject_cast<QchSyntaxHighlightRule*>(q->sender())) {
            if (rule->isEnabled()) {
                q->connect(rule, SIGNAL(changed()), &timer, SLOT(start()));
            }
            else {
                q->disconnect(rule, SIGNAL(changed()), &timer, SLOT(start()));
            }
        }
    }

    void _q_moveRule() {
        if (sortedRules.size() < 2) {
            return;
        }

        Q_Q(QchSyntaxHighlighter);

        if (QchSyntaxHighlightRule *rule = qobject_cast<QchSyntaxHighlightRule*>(q->sender())) {
            sortedRules.removeOne(rule);
            insertRule(rule);
        }
    }

    void _q_removeRule(QObject *obj) {
        if (QchSyntaxHighlightRule *rule = qobject_cast<QchSyntaxHighlightRule*>(obj)) {
            removeRule(rule);
        }
    }

    static bool ruleIsAllowed(QchSyntaxHighlightRule *rule, int index, const RuleMatchList &matches) {
        for (int i = 0; i < matches.size(); i++) {
            const RuleMatch &match = matches.at(i);

            if ((index >= match.start) && (index <= match.end) && (match.rule)
                    && (match.rule->d_func()->allowedRules.indexOf(rule) == -1)) {
                return false;
            }
        }

        return true;
    }

    static void rulesAppend(QDeclarativeListProperty<QchSyntaxHighlightRule> *list,
            QchSyntaxHighlightRule *rule) {
        if (!rule) {
            return;
        }

        if (QchSyntaxHighlighter *highlighter = qobject_cast<QchSyntaxHighlighter*>(list->object)) {
            highlighter->d_func()->addRule(rule);
        }
    }

    static QchSyntaxHighlightRule* rulesAt(QDeclarativeListProperty<QchSyntaxHighlightRule> *list, int index) {
        if (QchSyntaxHighlighter *highlighter = qobject_cast<QchSyntaxHighlighter*>(list->object)) {
            if ((index >= 0) && (index < highlighter->d_func()->rules.size())) {
                return highlighter->d_func()->rules.at(index);
            }
        }

        return 0;
    }

    static int rulesCount(QDeclarativeListProperty<QchSyntaxHighlightRule> *list) {
        if (QchSyntaxHighlighter *highlighter = qobject_cast<QchSyntaxHighlighter*>(list->object)) {
            return highlighter->d_func()->rules.size();
        }

        return 0;
    }

    QchSyntaxHighlighter *q_ptr;

    QList<QchSyntaxHighlightRule*> rules;
    QList<QchSyntaxHighlightRule*> sortedRules;

    QTimer timer;

    bool autoRehighlight;
    bool complete;

    static int blockState;

    Q_DECLARE_PUBLIC(QchSyntaxHighlighter)
};

int QchSyntaxHighlighterPrivate::blockState = 0;

/*!
 * \class SyntaxHighlighter
 * \ingroup components
 * \brief Applies syntax highlighting rules to a text document.
 *
 * The SyntaxHighlighter class applies highlighting rules defined by SyntaxHighlightRule to a text document.
 *
 * \sa SyntaxHighlightRule
 */
QchSyntaxHighlighter::QchSyntaxHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent),
    d_ptr(new QchSyntaxHighlighterPrivate(this))
{
}

QchSyntaxHighlighter::~QchSyntaxHighlighter() {}

void QchSyntaxHighlighter::resetDocument() {
    setDocument(0);
}

/*!
 * Whether the highlighting will be reapplied when a rules is added, removed or changed.
 *
 * The default value is \c true.
 */
bool QchSyntaxHighlighter::autoRehighlight() const {
    Q_D(const QchSyntaxHighlighter);
    return d->autoRehighlight;
}

void QchSyntaxHighlighter::setAutoRehighlight(bool enabled) {
    Q_D(QchSyntaxHighlighter);

    if (enabled != d->autoRehighlight) {
        d->autoRehighlight = enabled;
        emit autoRehighlightChanged();

        if (enabled) {
            foreach (const QchSyntaxHighlightRule *rule, d->rules) {
                connect(rule, SIGNAL(changed()), &d->timer, SLOT(start()));
                connect(rule, SIGNAL(enabledChanged()), this, SLOT(_q_enabledChanged()));
            }
        }
        else {
            foreach (const QchSyntaxHighlightRule *rule, d->rules) {
                disconnect(rule, SIGNAL(changed()), &d->timer, SLOT(start()));
                disconnect(rule, SIGNAL(enabledChanged()), this, SLOT(_q_enabledChanged()));
            }
        }
    }
}

QDeclarativeListProperty<QchSyntaxHighlightRule> QchSyntaxHighlighter::rules() {
    return QDeclarativeListProperty<QchSyntaxHighlightRule>(this, 0, QchSyntaxHighlighterPrivate::rulesAppend,
            QchSyntaxHighlighterPrivate::rulesCount, QchSyntaxHighlighterPrivate::rulesAt);
}

/*!
 * Adds a rule using the specified RegExp's \a regExp and \a endRegExp and returns it.
 */
QchSyntaxHighlightRule* QchSyntaxHighlighter::addRule(const QRegExp &regExp, const QRegExp &endRegExp) {
    QchSyntaxHighlightRule *rule = new QchSyntaxHighlightRule(regExp, endRegExp, this);
    addRule(rule);
    return rule;
}

/*!
 * Adds the specified \a rule.
 *
 * The highlighter does not take ownership of the rule.
 */
void QchSyntaxHighlighter::addRule(QchSyntaxHighlightRule *rule) {
    Q_D(QchSyntaxHighlighter);
    d->addRule(rule);
}

/*!
 * Removes the specified \a rule.
 *
 * The rule is not deleted.
 */
void QchSyntaxHighlighter::removeRule(QchSyntaxHighlightRule *rule) {
    Q_D(QchSyntaxHighlighter);
    d->removeRule(rule);
}

/*!
 * Reapplies the highlighting to the section of the document starting at \a position for \a length.
 *
 * \sa rehighlight()
 */
void QchSyntaxHighlighter::rehighlightText(int position, int length) {
    if (!document()) {
        return;
    }

    const int end = position + length;
    QTextBlock block = document()->findBlock(position);

    while (block.isValid()) {
        rehighlightBlock(block);
        
        if (block.contains(end)) {
            break;
        }

        block = block.next();
    }
}

/*!
 * Applies the specified \a format to the highlighter's current text block.
 */
void QchSyntaxHighlighter::setFormat(int start, int count, QchTextCharFormat *format) {
    if (format) {
        QSyntaxHighlighter::setFormat(start, count, format->format);
    }
    else {
        QSyntaxHighlighter::setFormat(start, count, QTextCharFormat());
    }
}

/*!
 * \internal
 *
 * Re-implementation of QSyntaxHighlighter::highlightBlock()
 */
void QchSyntaxHighlighter::highlightBlock(const QString &text) {
    Q_D(const QchSyntaxHighlighter);
    setCurrentBlockState(0);
    RuleMatchList matches;

    foreach (QchSyntaxHighlightRule *rule, d->sortedRules) {
        if (rule->isEnabled()) {
            int startIndex = 0;
            int length = 0;
            const QRegExp regExp = rule->regExp();
            const QRegExp endRegExp = rule->endRegExp();
            const int regExpIndex = rule->regExpIndex();

            if (!endRegExp.isEmpty()) {
                const int endRegExpIndex = rule->endRegExpIndex();
                const int blockState = rule->d_func()->blockState;

                if (previousBlockState() != blockState) {
                    startIndex = regExp.indexIn(text);

                    if (startIndex >= 0) {
                        startIndex = regExp.pos(regExpIndex);
                        length = qMax(1, regExp.cap(regExpIndex).length());
                    }
                }

                while ((startIndex >= 0) && (QchSyntaxHighlighterPrivate::ruleIsAllowed(rule, startIndex, matches))) {
                    int endIndex = -1;
                    
                    if (endRegExp.indexIn(text, startIndex + length) >= 0) {
                        endIndex = endRegExp.pos(endRegExpIndex);
                    }

                    if (endIndex == -1) {
                        setCurrentBlockState(blockState);
                        length = text.length() - startIndex;
                        matches << RuleMatch(rule, startIndex, startIndex + length);
                        setFormat(startIndex, length, rule->format());
                        break;
                    }

                    length = endIndex - startIndex + qMax(1, endRegExp.cap(endRegExpIndex).length());
                    matches << RuleMatch(rule, startIndex, startIndex + length);
                    setFormat(startIndex, length, rule->format());
                    startIndex = regExp.indexIn(text, startIndex + length);

                    if (startIndex >= 0) {
                        startIndex = regExp.pos(regExpIndex);
                    }
                }
            }
            else {
                startIndex = regExp.indexIn(text, startIndex);

                if (startIndex >= 0) {
                    startIndex = regExp.pos(regExpIndex);
                }

                while ((startIndex >= 0) && (QchSyntaxHighlighterPrivate::ruleIsAllowed(rule, startIndex, matches))) {
                    length = qMax(1, regExp.cap(regExpIndex).length());
                    matches << RuleMatch(rule, startIndex, startIndex + length);
                    setFormat(startIndex, length, rule->format());
                    startIndex = regExp.indexIn(text, startIndex + length);

                    if (startIndex >= 0) {
                        startIndex = regExp.pos(regExpIndex);
                    }
                }
            }
        }
    }

    emit highlightText(text);
}

void QchSyntaxHighlighter::classBegin() {}

void QchSyntaxHighlighter::componentComplete() {
    Q_D(QchSyntaxHighlighter);
    d->complete = true;
}

#include "moc_qchsyntaxhighlighter.cpp"


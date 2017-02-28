/*
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

#include "qchwebelement.h"
#include <QScriptEngine>
#include <QScriptValue>

QchWebElement::QchWebElement(QObject *parent) :
    QObject(parent)
{
}

bool QchWebElement::hasAttributes() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->hasAttributes();
    }
    
    return false;
}

QStringList QchWebElement::attributeNames() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->attributeNames();
    }
    
    QStringList();
}

QString QchWebElement::attribute(const QString &name, const QString &defaultValue) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->attribute(name, defaultValue);
    }
    
    return QString();
}

QString QchWebElement::attributeNS(const QString &namespaceUri, const QString &name, const QString &defaultValue) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->attributeNS(namespaceUri, name, defaultValue);
    }
    
    return QString();
}

bool QchWebElement::hasAttribute(const QString &name) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->hasAttribute(name);
    }
    
    return false;
}

bool QchWebElement::hasAttributeNS(const QString &namespaceUri, const QString &name) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->hasAttributeNS(namespaceUri, name);
    }
    
    return false;
}

void QchWebElement::removeAttribute(const QString &name) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->removeAttribute(name);
    }
}

void QchWebElement::removeAttributeNS(const QString &namespaceUri, const QString &name) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->removeAttributeNS(namespaceUri, name);
    }
}

void QchWebElement::setAttribute(const QString &name, const QString &value) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->setAttribute(name, value);
    }
}

void QchWebElement::setAttributeNS(const QString &namespaceUri, const QString &name, const QString &value) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->setAttributeNS(namespaceUri, name, value);
    }
}

QStringList QchWebElement::classes() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->classes();
    }
    
    return QStringList();
}

bool QchWebElement::hasClass(const QString &name) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->hasClass(name);
    }
    
    return false;
}

void QchWebElement::addClass(const QString &name) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->addClass(name);
    }
}

void QchWebElement::removeClass(const QString &name) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->removeClass(name);
    }
}

void QchWebElement::toggleClass(const QString &name) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->toggleClass(name);
    }
}

QWebElement QchWebElement::clone() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->clone();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::documentElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->document();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::firstChildElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->firstChild();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::lastChildElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->lastChild();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::nextSiblingElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->nextSibling();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::parentElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->parent();
    }
    
    return QWebElement();
}

QWebElement QchWebElement::previousSiblingElement() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->previousSibling();
    }
    
    return QWebElement();
}

void QchWebElement::encloseContentsWith(const QWebElement &el) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->encloseContentsWith(el);
    }
}

void QchWebElement::encloseContentsWith(const QString &markup) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->encloseContentsWith(markup);
    }
}

void QchWebElement::encloseWith(const QWebElement &el) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->encloseWith(el);
    }
}

void QchWebElement::encloseWith(const QString &markup) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->encloseWith(markup);
    }
}

QVariant QchWebElement::evaluateJavaScript(const QString &sourceScript) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->evaluateJavaScript(sourceScript);
    }
    
    return QVariant();
}

QList<QWebElement> QchWebElement::findAll(const QString &selectorQuery) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->findAll(selectorQuery).toList();
    }
    
    return QList<QWebElement>();
}

QWebElement QchWebElement::findFirst(const QString &selectorQuery) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->findFirst(selectorQuery);
    }
    
    return QWebElement();
}

QRect QchWebElement::geometry() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->geometry();
    }
    
    return QRect();
}

bool QchWebElement::hasFocus() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->hasFocus();
    }
    
    return false;
}

bool QchWebElement::isNull() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->isNull();
    }
    
    return true;
}

QString QchWebElement::localName() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->localName();
    }
    
    return QString();
}

QString QchWebElement::namespaceUri() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->namespaceUri();
    }
    
    return QString();
}

QString QchWebElement::prefix() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->prefix();
    }
    
    return QString();
}

QString QchWebElement::styleProperty(const QString &name, int strategy) const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->styleProperty(name, QWebElement::StyleResolveStrategy(strategy));
    }
    
    return QString();
}

void QchWebElement::setStyleProperty(const QString &name, const QString &value) {
    if (QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        element->setStyleProperty(name, value);
    }
}

QString QchWebElement::tagName() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->tagName();
    }
    
    return QString();
}

QString QchWebElement::toInnerXml() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->toInnerXml();
    }
    
    return QString();
}

QString QchWebElement::toOuterXml() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->toOuterXml();
    }
    
    return QString();
}

QString QchWebElement::toPlainText() const {
    if (const QWebElement *element = qscriptvalue_cast<QWebElement*>(thisObject())) {
        return element->toPlainText();
    }
    
    return QString();
}

QScriptValue QchWebElement::newInstance(QScriptContext *, QScriptEngine *engine) {
    return engine->toScriptValue(QWebElement());
}

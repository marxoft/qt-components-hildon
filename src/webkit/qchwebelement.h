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

#ifndef QCHWEBELEMENT_H
#define QCHWEBELEMENT_H

#include <QObject>
#include <QScriptable>
#include <QWebElement>

class QchWebElement : public QObject, public QScriptable
{
    Q_OBJECT
    
    Q_PROPERTY(bool hasAttributes READ hasAttributes)
    Q_PROPERTY(QStringList attributeNames READ attributeNames)
    Q_PROPERTY(QStringList classes READ classes)
    Q_PROPERTY(QWebElement document READ documentElement)
    Q_PROPERTY(QWebElement firstChild READ firstChildElement)
    Q_PROPERTY(QWebElement lastChild READ lastChildElement)
    Q_PROPERTY(QWebElement nextSibling READ nextSiblingElement)
    Q_PROPERTY(QWebElement parent READ parentElement)
    Q_PROPERTY(QWebElement previousSibling READ previousSiblingElement)
    Q_PROPERTY(QRect geometry READ geometry)
    Q_PROPERTY(bool focus READ hasFocus)
    Q_PROPERTY(QString innerXml READ toInnerXml)
    Q_PROPERTY(bool isNull READ isNull)
    Q_PROPERTY(QString localName READ localName)
    Q_PROPERTY(QString namespaceUri READ namespaceUri)
    Q_PROPERTY(QString outerXml READ toOuterXml)
    Q_PROPERTY(QString prefix READ prefix)
    Q_PROPERTY(QString tagName READ tagName)
    Q_PROPERTY(QString text READ toPlainText)
    
    Q_ENUMS(QWebElement::StyleResolveStrategy)

public:
    explicit QchWebElement(QObject *parent = 0);
    
    bool hasAttributes() const;
    QStringList attributeNames() const;
    Q_INVOKABLE QString attribute(const QString &name, const QString &defaultValue = QString()) const;
    Q_INVOKABLE QString attributeNS(const QString &namespaceUri, const QString &name,
                                    const QString &defaultValue = QString()) const;
    Q_INVOKABLE bool hasAttribute(const QString &name) const;
    Q_INVOKABLE bool hasAttributeNS(const QString &namespaceUri, const QString &name) const;
    Q_INVOKABLE void removeAttribute(const QString &name);
    Q_INVOKABLE void removeAttributeNS(const QString &namespaceUri, const QString &name);
    Q_INVOKABLE void setAttribute(const QString &name, const QString &value);
    Q_INVOKABLE void setAttributeNS(const QString &namespaceUri, const QString &name, const QString &value);
    
    QStringList classes() const;
    Q_INVOKABLE bool hasClass(const QString &name) const;
    Q_INVOKABLE void addClass(const QString &name);
    Q_INVOKABLE void removeClass(const QString &name);
    Q_INVOKABLE void toggleClass(const QString &name);
    
    Q_INVOKABLE QWebElement clone() const;
    
    QWebElement documentElement() const;
    QWebElement firstChildElement() const;
    QWebElement lastChildElement() const;
    QWebElement nextSiblingElement() const;
    QWebElement parentElement() const;
    QWebElement previousSiblingElement() const;
    
    Q_INVOKABLE void encloseContentsWith(const QWebElement &el);
    Q_INVOKABLE void encloseContentsWith(const QString &markup);
    
    Q_INVOKABLE void encloseWith(const QWebElement &el);
    Q_INVOKABLE void encloseWith(const QString &markup);
    
    Q_INVOKABLE QVariant evaluateJavaScript(const QString &scriptSource);
    
    Q_INVOKABLE QList<QWebElement> findAll(const QString &selectoQuery) const;
    Q_INVOKABLE QWebElement findFirst(const QString &selectorQuery) const;
    
    QRect geometry() const;
    
    bool hasFocus() const;
    
    bool isNull() const;
    
    QString localName() const;
    
    QString namespaceUri() const;
    
    QString prefix() const;
    
    Q_INVOKABLE void prependInside(const QWebElement &el);
    Q_INVOKABLE void prependInside(const QString &markup);
    
    Q_INVOKABLE void prependOutside(const QWebElement &el);
    Q_INVOKABLE void prependOutside(const QString &markup);
    
    Q_INVOKABLE void removeAllChildren();
    
    Q_INVOKABLE QString styleProperty(const QString &name, int strategy) const;
    Q_INVOKABLE void setStyleProperty(const QString &name, const QString &value);
    
    QString tagName() const;
    
    QString toInnerXml() const;
    QString toOuterXml() const;
    QString toPlainText() const;
    
    static QScriptValue newInstance(QScriptContext *context, QScriptEngine *engine);

private:
    Q_DISABLE_COPY(QchWebElement)
};

Q_DECLARE_METATYPE(QchWebElement*)
Q_DECLARE_METATYPE(QWebElement*)
Q_DECLARE_METATYPE(QList<QWebElement>)
    
#endif // QCHWEBELEMENT_H

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

#ifndef TEXTFIELD_P_H
#define TEXTFIELD_P_H

#include "anchors_p.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class TextFieldPrivate;

class TextField : public QLineEdit, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin NOTIFY marginsChanged)
    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin NOTIFY marginsChanged)
    Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin NOTIFY marginsChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY marginsChanged)
    Q_PRIVATE_PROPERTY(TextField::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(TextField::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(TextField::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(TextField::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(TextField::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(TextField::d_func(), QValidator* validator READ validator WRITE setValidator)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    void setFocus(bool focus);

    int leftMargin() const;
    void setLeftMargin(int margin);
    int topMargin() const;
    void setTopMargin(int margin);
    int rightMargin() const;
    void setRightMargin(int margin);
    int bottomMargin() const;
    void setBottomMargin(int margin);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();
    void marginsChanged();

protected:
    TextField(TextFieldPrivate &dd, QWidget *parent = 0);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<TextFieldPrivate> d_ptr;

    Q_DECLARE_PRIVATE(TextField)

private:
    Q_DISABLE_COPY(TextField)
};

QML_DECLARE_TYPE(TextField)
QML_DECLARE_TYPE(QValidator)
QML_DECLARE_TYPE(QIntValidator)
QML_DECLARE_TYPE(QDoubleValidator)
QML_DECLARE_TYPE(QRegExpValidator)

#endif // TEXTFIELD_P_H

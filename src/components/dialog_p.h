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

#ifndef DIALOG_P_H
#define DIALOG_P_H

#include "anchors_p.h"
#include "screen_p.h"
#include <QDialog>
#include <QIcon>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class DialogPrivate;

class Dialog : public QDialog, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(bool showProgressIndicator READ showingProgressIndicator WRITE showProgressIndicator)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(Dialog::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(Dialog::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(Dialog::d_func(), QDeclarativeListProperty<QObject> content READ content)
    Q_PRIVATE_PROPERTY(Dialog::d_func(), QDeclarativeListProperty<QObject> buttons READ buttons)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    bool showingProgressIndicator() const;
    void showProgressIndicator(bool show);

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

protected:
    Dialog(DialogPrivate &dd, QWidget *parent = 0);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<DialogPrivate> d_ptr;

    Q_DISABLE_COPY(Dialog)
    Q_DECLARE_PRIVATE(Dialog)

    Q_PRIVATE_SLOT(d_func(), void _q_onOrientationChanged(Screen::Orientation))
};

QML_DECLARE_TYPE(Dialog)

#endif // DIALOG_P_H

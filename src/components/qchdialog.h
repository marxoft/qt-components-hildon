/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHDIALOG_H
#define QCHDIALOG_H

#include "qchdialogstatus.h"
#include <QDialog>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeItem;

class QchDialogPrivate;

class QchDialog : public QDialog, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(bool showProgressIndicator READ showProgressIndicator WRITE setShowProgressIndicator
               NOTIFY showProgressIndicatorChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString styleSheet READ styleSheet CONSTANT FINAL)
    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchDialog(QWidget *parent = 0);
    ~QchDialog();
    
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    bool showProgressIndicator() const;
    void setShowProgressIndicator(bool enabled);
    
    QchDialogStatus::Status status() const;

Q_SIGNALS:
    void showProgressIndicatorChanged();
    void sizeChanged();
    void statusChanged();
    void titleChanged();
    void visibleChanged();
    
protected:    
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void changeEvent(QEvent *e);

    QScopedPointer<QchDialogPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchDialog)

private:
    Q_DISABLE_COPY(QchDialog)
};

QML_DECLARE_TYPE(QchDialog)
    
#endif // QCHDIALOG_H

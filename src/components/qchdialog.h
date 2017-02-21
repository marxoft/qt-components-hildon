/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

class QchDialogWidgetPrivate;

class QchDialogWidget : public QDialog, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(QDeclarativeItem* contentItem READ contentItem CONSTANT)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(bool showProgressIndicator READ showProgressIndicator WRITE setShowProgressIndicator
               NOTIFY showProgressIndicatorChanged)
    Q_PROPERTY(int result READ result WRITE setResult NOTIFY statusChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString styleSheet READ styleSheet CONSTANT FINAL)
    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    
    Q_ENUMS(DialogCode)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchDialogWidget(QWidget *parent = 0);
    ~QchDialogWidget();
    
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    QDeclarativeItem* contentItem() const;
    
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

    QScopedPointer<QchDialogWidgetPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchDialogWidget)

private:
    Q_DISABLE_COPY(QchDialogWidget)
    
    friend class QchDialog;
};

class QchDialog : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(QDeclarativeItem* contentItem READ contentItem CONSTANT)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY sizeChanged)
    Q_PROPERTY(bool modal READ isModal WRITE setModal NOTIFY modalChanged)
    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(bool showProgressIndicator READ showProgressIndicator WRITE setShowProgressIndicator
               NOTIFY showProgressIndicatorChanged)
    Q_PROPERTY(int result READ result WRITE setResult NOTIFY statusChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY sizeChanged)
    
    Q_ENUMS(QDialog::DialogCode)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit QchDialog(QObject *parent = 0);
    ~QchDialog();
        
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    QDeclarativeItem* contentItem() const;
    
    int height() const;
    void setHeight(int h);
        
    bool isModal() const;
    void setModal(bool m);
    
    bool showProgressIndicator() const;
    void setShowProgressIndicator(bool enabled);
    
    int result() const;
    void setResult(int r);
    
    QchDialogStatus::Status status() const;
    
    QString title() const;
    void setTitle(const QString &t);
    
    bool isVisible() const;
    void setVisible(bool v);
    
    int width() const;
    void setWidth(int w);

public Q_SLOTS:
    void accept();
    void close();
    void done(int r);
    int exec();
    void hide();
    void open();
    void reject();
    void show();

Q_SIGNALS:
    void accepted();
    void finished(int result);
    void modalChanged();
    void parentChanged();
    void rejected();
    void showProgressIndicatorChanged();
    void sizeChanged();
    void statusChanged();
    void titleChanged();
    void visibleChanged();

private:    
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual bool event(QEvent *e);
    
    QchDialogWidget *m_dialog;
    
    Q_DISABLE_COPY(QchDialog)
};

QML_DECLARE_TYPE(QchDialog)
    
#endif // QCHDIALOG_H

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

#ifndef QCHINFORMATIONBOX_H
#define QCHINFORMATIONBOX_H

#include "qchdialogstatus.h"
#include <QMaemo5InformationBox>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeItem;

class QchInformationBoxWidgetPrivate;

class QchInformationBoxWidget : public QMaemo5InformationBox, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(QDeclarativeItem* contentItem READ contentItem CONSTANT)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchInformationBoxWidget(QWidget *parent = 0);
    ~QchInformationBoxWidget();
    
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    QDeclarativeItem* contentItem() const;
    
    QchDialogStatus::Status status() const;

Q_SIGNALS:
    void sizeChanged();
    void statusChanged();
    void visibleChanged();
    
protected:    
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

    QScopedPointer<QchInformationBoxWidgetPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchInformationBoxWidget)

private:
    Q_DISABLE_COPY(QchInformationBoxWidget)
    
    friend class QchInformationBox;
};

class QchInformationBox : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(QDeclarativeItem* contentItem READ contentItem CONSTANT)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY sizeChanged)
    Q_PROPERTY(bool modal READ isModal WRITE setModal NOTIFY modalChanged)
    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int result READ result WRITE setResult NOTIFY statusChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY sizeChanged)
    
    Q_ENUMS(Timeout)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    enum Timeout {
        NoTimeout = 0,
        DefaultTimeout = 3000
    };
    
    explicit QchInformationBox(QObject *parent = 0);
    ~QchInformationBox();
        
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
    QDeclarativeItem* contentItem() const;
    
    int height() const;
    void setHeight(int h);
    
    bool isModal() const;
    void setModal(bool m);
    
    int result() const;
    void setResult(int r);
        
    QchDialogStatus::Status status() const;
    
    int timeout() const;
    void setTimeout(int t);
        
    bool isVisible() const;
    void setVisible(bool v);
    
    int width() const;
    void setWidth(int w);

public Q_SLOTS:
    void accept();
    void done(int r);
    int exec();
    void open();
    void reject();

Q_SIGNALS:
    void accepted();
    void clicked();
    void finished(int result);
    void modalChanged();
    void parentChanged();
    void rejected();
    void sizeChanged();
    void statusChanged();
    void timeoutChanged();
    void visibleChanged();

private:    
    virtual void classBegin();
    virtual void componentComplete();
    
    virtual bool event(QEvent *e);
    
    QchInformationBoxWidget *m_box;
};

QML_DECLARE_TYPE(QchInformationBox)
    
#endif // QCHINFORMATIONBOX_H

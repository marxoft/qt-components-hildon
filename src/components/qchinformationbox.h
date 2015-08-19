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

#ifndef QCHINFORMATIONBOX_H
#define QCHINFORMATIONBOX_H

#include "qchdialogstatus.h"
#include <QMaemo5InformationBox>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeItem;

class QchInformationBoxPrivate;

class QchInformationBox : public QMaemo5InformationBox, public QDeclarativeParserStatus
{
    Q_OBJECT
    
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeItem> children READ children)
    Q_PROPERTY(QDeclarativeListProperty<QObject> data READ data)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY sizeChanged)
    Q_PROPERTY(QchDialogStatus::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY sizeChanged)
    
    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")
    
public:
    explicit QchInformationBox(QWidget *parent = 0);
    ~QchInformationBox();
    
    QDeclarativeListProperty<QDeclarativeItem> children();
    QDeclarativeListProperty<QObject> data();
    
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

    QScopedPointer<QchInformationBoxPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchInformationBox)

private:
    Q_DISABLE_COPY(QchInformationBox)
};

QML_DECLARE_TYPE(QchInformationBox)
    
#endif // QCHINFORMATIONBOX_H

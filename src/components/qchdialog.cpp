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

#include "qchdialog.h"
#include "qchgraphicsview.h"
#include <QDeclarativeItem>
#include <QVBoxLayout>
#include <QEvent>

class QchDialogPrivate
{

public:
    QchDialogPrivate(QchDialog *parent) :
        q_ptr(parent),
        view(0),
        root(0),
        status(QchDialogStatus::Closed)
    {
    }
    
    static void children_append(QDeclarativeListProperty<QDeclarativeItem> *list, QDeclarativeItem *item) {        
        if (!item) {
            return;
        }
        
        if (QchDialog *dialog = qobject_cast<QchDialog*>(list->object)) {
            if (QDeclarativeItem *root = dialog->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchDialog *dialog = qobject_cast<QchDialog*>(list->object)) {
            if (obj->isWidgetType()) {
                obj->setParent(dialog);
            }
            else if (QDeclarativeItem *root = dialog->d_func()->root) {
                obj->setParent(root);
                
                if (QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(obj)) {
                    item->setParentItem(root);
                }
            }
        }
    }
    
    void init() {
        Q_Q(QchDialog);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        root->setParent(view);
        view->addItem(root);
        
        QVBoxLayout *vbox = new QVBoxLayout(q);
        vbox->addWidget(view);
    }
        
    QchDialog *q_ptr;
    
    QchGraphicsView *view;
    QDeclarativeItem *root;
        
    QchDialogStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchDialog)
};

/*!
    \class Dialog
    \brief The base class for popup dialogs.
    
    \ingroup components
*/
QchDialog::QchDialog(QWidget *parent) :
    QDialog(parent),
    d_ptr(new QchDialogPrivate(this))
{
    Q_D(QchDialog);
    d->init();
}

QchDialog::~QchDialog() {}

/*!
    \brief The visual children of the dialog.
*/
QDeclarativeListProperty<QDeclarativeItem> QchDialog::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchDialogPrivate::children_append);
}

/*!
    \brief The children of the dialog.
*/
QDeclarativeListProperty<QObject> QchDialog::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchDialogPrivate::data_append);
}

/*!
    \brief Whether the progress indicator should be visible.
    
    The default value is \c false.
*/
bool QchDialog::showProgressIndicator() const {
    return testAttribute(Qt::WA_Maemo5ShowProgressIndicator);
}

void QchDialog::setShowProgressIndicator(bool enabled) {
    if (enabled != showProgressIndicator()) {
        setAttribute(Qt::WA_Maemo5ShowProgressIndicator, enabled);
        emit showProgressIndicatorChanged();
    }
}

/*!
    \brief The current status of the dialog.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>DialogStatus.Closed</td>
            <td>The dialog is closed (default).</td>
        </tr>
        <tr>
            <td>DialogStatus.Opening</td>
            <td>The dialog is opening.</td>
        </tr>
        <tr>
            <td>DialogStatus.Open</td>
            <td>The dialog is open.</td>
        </tr>
        <tr>
            <td>DialogStatus.Closing</td>
            <td>The dialog is closing.</td>
        </tr>
    </table>
*/
QchDialogStatus::Status QchDialog::status() const {
    Q_D(const QchDialog);
    return d->status;
}

void QchDialog::classBegin() {}

void QchDialog::componentComplete() {
    if (parentWidget()) {
        setWindowFlags(Qt::Dialog);
    }
}

void QchDialog::showEvent(QShowEvent *e) {
    Q_D(QchDialog);
    d->status = QchDialogStatus::Opening;
    emit statusChanged();
    QDialog::showEvent(e);
    d->status = QchDialogStatus::Open;
    emit statusChanged();
    emit visibleChanged();
}

void QchDialog::hideEvent(QHideEvent *e) {
    Q_D(QchDialog);
    d->status = QchDialogStatus::Closing;
    emit statusChanged();
    QDialog::hideEvent(e);
    d->status = QchDialogStatus::Closed;
    emit statusChanged();
    emit visibleChanged();
}

void QchDialog::resizeEvent(QResizeEvent *e) {
    QDialog::resizeEvent(e);
    emit sizeChanged();
}

void QchDialog::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    
    if (e->type() == QEvent::WindowTitleChange) {
        emit titleChanged();
    }
}

#include "moc_qchdialog.cpp"

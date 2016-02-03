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

#include "qchdialog.h"
#include "qchgraphicsview.h"
#include <QDeclarativeItem>
#include <QVBoxLayout>
#include <QEvent>

class QchDialogWidgetPrivate
{

public:
    QchDialogWidgetPrivate(QchDialogWidget *parent) :
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
        
        if (QchDialogWidget *dialog = qobject_cast<QchDialogWidget*>(list->object)) {
            if (QDeclarativeItem *root = dialog->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchDialogWidget *dialog = qobject_cast<QchDialogWidget*>(list->object)) {
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
        Q_Q(QchDialogWidget);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        root->setParent(view);
        view->addItem(root);
        
        QVBoxLayout *vbox = new QVBoxLayout(q);
        vbox->addWidget(view);
    }
        
    QchDialogWidget *q_ptr;
    
    QchGraphicsView *view;
    QDeclarativeItem *root;
        
    QchDialogStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchDialogWidget)
};

QchDialogWidget::QchDialogWidget(QWidget *parent) :
    QDialog(parent),
    d_ptr(new QchDialogWidgetPrivate(this))
{
    Q_D(QchDialogWidget);
    d->init();
}

QchDialogWidget::~QchDialogWidget() {}

QDeclarativeListProperty<QDeclarativeItem> QchDialogWidget::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchDialogWidgetPrivate::children_append);
}

QDeclarativeListProperty<QObject> QchDialogWidget::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchDialogWidgetPrivate::data_append);
}

bool QchDialogWidget::showProgressIndicator() const {
    return testAttribute(Qt::WA_Maemo5ShowProgressIndicator);
}

void QchDialogWidget::setShowProgressIndicator(bool enabled) {
    if (enabled != showProgressIndicator()) {
        setAttribute(Qt::WA_Maemo5ShowProgressIndicator, enabled);
        emit showProgressIndicatorChanged();
    }
}

QchDialogStatus::Status QchDialogWidget::status() const {
    Q_D(const QchDialogWidget);
    return d->status;
}

void QchDialogWidget::classBegin() {}

void QchDialogWidget::componentComplete() {
    if (parentWidget()) {
        setWindowFlags(Qt::Dialog);
    }
}

void QchDialogWidget::showEvent(QShowEvent *e) {
    Q_D(QchDialogWidget);
    d->status = QchDialogStatus::Opening;
    emit statusChanged();
    QDialog::showEvent(e);
    d->status = QchDialogStatus::Open;
    emit statusChanged();
    emit visibleChanged();
}

void QchDialogWidget::hideEvent(QHideEvent *e) {
    Q_D(QchDialogWidget);
    d->status = QchDialogStatus::Closing;
    emit statusChanged();
    QDialog::hideEvent(e);
    d->status = QchDialogStatus::Closed;
    emit statusChanged();
    emit visibleChanged();
}

void QchDialogWidget::resizeEvent(QResizeEvent *e) {
    QDialog::resizeEvent(e);
    emit sizeChanged();
}

void QchDialogWidget::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    
    if (e->type() == QEvent::WindowTitleChange) {
        emit titleChanged();
    }
}

/*!
    \class Dialog
    \brief The base class for popup dialogs.
    
    \ingroup components
*/
QchDialog::QchDialog(QObject *parent) :
    QObject(parent),
    m_dialog(new QchDialogWidget)
{
    connect(m_dialog, SIGNAL(accepted()), this, SIGNAL(accepted()));
    connect(m_dialog, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
    connect(m_dialog, SIGNAL(rejected()), this, SIGNAL(rejected()));
    connect(m_dialog, SIGNAL(showProgressIndicatorChanged()),
            this, SIGNAL(showProgressIndicatorChanged()));
    connect(m_dialog, SIGNAL(sizeChanged()), this, SIGNAL(sizeChanged()));
    connect(m_dialog, SIGNAL(statusChanged()), this, SIGNAL(statusChanged()));
    connect(m_dialog, SIGNAL(titleChanged()), this, SIGNAL(titleChanged()));
    connect(m_dialog, SIGNAL(visibleChanged()), this, SIGNAL(visibleChanged()));
}

QchDialog::~QchDialog() {
    delete m_dialog;
    m_dialog = 0;
}

/*!
    \brief The visual children of the dialog.
*/
QDeclarativeListProperty<QDeclarativeItem> QchDialog::children() {
    return m_dialog->children();
}

/*!
    \brief The children of the dialog.
*/
QDeclarativeListProperty<QObject> QchDialog::data() {
    return m_dialog->data();
}

/*!
    \brief The height of the dialog.
*/
int QchDialog::height() const {
    return m_dialog->height();
}

void QchDialog::setHeight(int h) {
    m_dialog->setFixedHeight(h);
}

/*!
    \brief Whether the dialog is modal.
*/
bool QchDialog::isModal() const {
    return m_dialog->isModal();
}

void QchDialog::setModal(bool m) {
    if (m != isModal()) {
        m_dialog->setModal(m);
        emit modalChanged();
    }
}

/*!
    \brief Whether the progress indicator should be visible.
    
    The default value is \c false.
*/
bool QchDialog::showProgressIndicator() const {
    return m_dialog->showProgressIndicator();
}

void QchDialog::setShowProgressIndicator(bool enabled) {
    m_dialog->setShowProgressIndicator(enabled);
}

/*!
    \brief The result code of the dialog.
*/
int QchDialog::result() const {
    return m_dialog->result();
}

void QchDialog::setResult(int r) {
    m_dialog->setResult(r);
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
    return m_dialog->status();
}

/*!
    \brief The title of the dialog.
*/
QString QchDialog::title() const {
    return m_dialog->windowTitle();
}

void QchDialog::setTitle(const QString &t) {
    m_dialog->setWindowTitle(t);
}

/*!
    \brief Whether the dialog is visible.
*/
bool QchDialog::isVisible() const {
    return m_dialog->isVisible();
}

void QchDialog::setVisible(bool v) {
    m_dialog->setVisible(v);
}

/*!
    \brief Closes the dialog with result code Dialog.Accepted.
*/
void QchDialog::accept() {
    m_dialog->accept();
}

/*!
    \brief Closes the dialog with result code \a r.
*/
void QchDialog::done(int r) {
    m_dialog->done(r);
}

/*!
    \brief Opens the dialog as a modal dialog, blocking until the user closes it.
    
    Returns the result code.
*/
int QchDialog::exec() {
    return m_dialog->exec();
}

/*!
    \brief Opens the dialog as a non-modal dialog.
*/
void QchDialog::open() {
    m_dialog->open();
}

/*!
    \brief Closes the dialog with result code Dialog.Rejected.
*/
void QchDialog::reject() {
    m_dialog->reject();
}

void QchDialog::classBegin() {
    m_dialog->classBegin();
}

void QchDialog::componentComplete() {
    QObject *p = parent();
    
    while (p) {
        if (p->isWidgetType()) {
            if (QWidget *w = qobject_cast<QWidget*>(p)) {
                m_dialog->setParent(w);
                break;
            }
        }
        
        p = p->parent();
    }
    
    m_dialog->componentComplete();
}

bool QchDialog::event(QEvent *e) {
    if (e->type() == QEvent::ParentChange) {
        QObject *p = parent();
        
        while (p) {
            if (p->isWidgetType()) {
                if (QWidget *w = qobject_cast<QWidget*>(p)) {
                    m_dialog->setParent(w);
                    break;
                }
            }
            
            p = p->parent();
        }
        
        emit parentChanged();
    }
    
    return QObject::event(e);
}

#include "moc_qchdialog.cpp"

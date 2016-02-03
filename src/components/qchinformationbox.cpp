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

#include "qchinformationbox.h"
#include "qchgraphicsview.h"
#include <QDeclarativeItem>
#include <QVBoxLayout>
#include <QEvent>

class QchInformationBoxWidgetPrivate
{

public:
    QchInformationBoxWidgetPrivate(QchInformationBoxWidget *parent) :
        q_ptr(parent),
        view(0),
        root(0),
        status(QchDialogStatus::Closed)
    {
    }
    
    ~QchInformationBoxWidgetPrivate() {
        delete root;
    }
    
    static void children_append(QDeclarativeListProperty<QDeclarativeItem> *list, QDeclarativeItem *item) {        
        if (!item) {
            return;
        }
        
        if (QchInformationBoxWidget *informationbox = qobject_cast<QchInformationBoxWidget*>(list->object)) {
            if (QDeclarativeItem *root = informationbox->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchInformationBoxWidget *informationbox = qobject_cast<QchInformationBoxWidget*>(list->object)) {
            if (obj->isWidgetType()) {
                obj->setParent(informationbox);
            }
            else if (QDeclarativeItem *root = informationbox->d_func()->root) {
                obj->setParent(root);
                
                if (QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(obj)) {
                    item->setParentItem(root);
                }
            }
        }
    }
    
    void init() {
        Q_Q(QchInformationBoxWidget);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        view->setStyleSheet("background: transparent");
        view->addItem(root);
        q->setWidget(view);
    }
        
    QchInformationBoxWidget *q_ptr;
    
    QchGraphicsView *view;
    QDeclarativeItem *root;
        
    QchDialogStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchInformationBoxWidget)
};

QchInformationBoxWidget::QchInformationBoxWidget(QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(new QchInformationBoxWidgetPrivate(this))
{
    Q_D(QchInformationBoxWidget);
    d->init();
}

QchInformationBoxWidget::~QchInformationBoxWidget() {}

QDeclarativeListProperty<QDeclarativeItem> QchInformationBoxWidget::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchInformationBoxWidgetPrivate::children_append);
}

QDeclarativeListProperty<QObject> QchInformationBoxWidget::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchInformationBoxWidgetPrivate::data_append);
}

QchDialogStatus::Status QchInformationBoxWidget::status() const {
    Q_D(const QchInformationBoxWidget);
    return d->status;
}

void QchInformationBoxWidget::classBegin() {}

void QchInformationBoxWidget::componentComplete() {
    if (parentWidget()) {
        setWindowFlags(Qt::Dialog);
    }
}

void QchInformationBoxWidget::showEvent(QShowEvent *e) {
    Q_D(QchInformationBoxWidget);
    d->status = QchDialogStatus::Opening;
    emit statusChanged();
    QMaemo5InformationBox::showEvent(e);
    d->status = QchDialogStatus::Open;
    emit statusChanged();
    emit visibleChanged();
}

void QchInformationBoxWidget::hideEvent(QHideEvent *e) {
    Q_D(QchInformationBoxWidget);
    d->status = QchDialogStatus::Closing;
    emit statusChanged();
    QMaemo5InformationBox::hideEvent(e);
    d->status = QchDialogStatus::Closed;
    emit statusChanged();
    emit visibleChanged();
}

void QchInformationBoxWidget::resizeEvent(QResizeEvent *e) {
    QMaemo5InformationBox::resizeEvent(e);
    emit sizeChanged();
}

/*!
    \class InformationBox
    \brief Displays a Hildon-style popup information banner.
    
    \ingroup components
    
    \sa Notification
*/
QchInformationBox::QchInformationBox(QObject *parent) :
    QObject(parent),
    m_box(new QchInformationBoxWidget)
{
    connect(m_box, SIGNAL(accepted()), this, SIGNAL(accepted()));
    connect(m_box, SIGNAL(clicked()), this, SIGNAL(clicked()));
    connect(m_box, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
    connect(m_box, SIGNAL(rejected()), this, SIGNAL(rejected()));
    connect(m_box, SIGNAL(sizeChanged()), this, SIGNAL(sizeChanged()));
    connect(m_box, SIGNAL(statusChanged()), this, SIGNAL(statusChanged()));
    connect(m_box, SIGNAL(visibleChanged()), this, SIGNAL(visibleChanged()));
}

QchInformationBox::~QchInformationBox() {
    delete m_box;
    m_box = 0;
}

/*!
    \brief The visual children of the dialog.
*/
QDeclarativeListProperty<QDeclarativeItem> QchInformationBox::children() {
    return m_box->children();
}

/*!
    \brief The children of the dialog.
*/
QDeclarativeListProperty<QObject> QchInformationBox::data() {
    return m_box->data();
}

/*!
    \brief The height of the dialog.
*/
int QchInformationBox::height() const {
    return m_box->height();
}

void QchInformationBox::setHeight(int h) {
    m_box->setFixedHeight(h);
}

/*!
    \brief Whether the information box is modal.
*/
bool QchInformationBox::isModal() const {
    return m_box->isModal();
}

void QchInformationBox::setModal(bool m) {
    if (m != isModal()) {
        m_box->setModal(m);
        emit modalChanged();
    }
}

/*!
    \brief The result code of the information box.
*/
int QchInformationBox::result() const {
    return m_box->result();
}

void QchInformationBox::setResult(int r) {
    m_box->setResult(r);
}

/*!
    \brief The current status of the information box.
    
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
QchDialogStatus::Status QchInformationBox::status() const {
    return m_box->status();
}

/*!
    \brief The timeout for the information box.
*/
int QchInformationBox::timeout() const {
    return m_box->timeout();
}

void QchInformationBox::setTimeout(int t) {
    if (t != timeout()) {
        m_box->setTimeout(t);
        emit timeoutChanged();
    }
}

/*!
    \brief Whether the information box is visible.
*/
bool QchInformationBox::isVisible() const {
    return m_box->isVisible();
}

void QchInformationBox::setVisible(bool v) {
    m_box->setVisible(v);
}

/*!
    \brief Closes the information box with result code Dialog.Accepted.
*/
void QchInformationBox::accept() {
    m_box->accept();
}

/*!
    \brief Closes the information box with result code \a r.
*/
void QchInformationBox::done(int r) {
    m_box->done(r);
}

/*!
    \brief Opens the information box as a modal dialog, blocking until the user closes it.
    
    Returns the result code.
*/
int QchInformationBox::exec() {
    return m_box->exec();
}

/*!
    \brief Opens the information box.
*/
void QchInformationBox::open() {
    m_box->open();
}

/*!
    \brief Closes the information box with result code Dialog.Rejected.
*/
void QchInformationBox::reject() {
    m_box->reject();
}

void QchInformationBox::classBegin() {
    m_box->classBegin();
}

void QchInformationBox::componentComplete() {
    m_box->componentComplete();
}

bool QchInformationBox::event(QEvent *e) {
    if (e->type() == QEvent::ParentChange) {
        QObject *p = parent();
        
        while (p) {
            if (p->isWidgetType()) {
                if (QWidget *w = qobject_cast<QWidget*>(p)) {
                    m_box->setParent(w);
                    break;
                }
            }
            
            p = p->parent();
        }
        
        emit parentChanged();
    }
    
    return QObject::event(e);
}

#include "moc_qchinformationbox.cpp"

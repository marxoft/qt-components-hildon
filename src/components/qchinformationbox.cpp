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

#include "qchinformationbox.h"
#include "qchgraphicsview.h"
#include <QDeclarativeItem>
#include <QVBoxLayout>
#include <QEvent>

class QchInformationBoxPrivate
{

public:
    QchInformationBoxPrivate(QchInformationBox *parent) :
        q_ptr(parent),
        view(0),
        root(0),
        status(QchDialogStatus::Closed)
    {
    }
    
    ~QchInformationBoxPrivate() {
        delete root;
    }
    
    static void children_append(QDeclarativeListProperty<QDeclarativeItem> *list, QDeclarativeItem *item) {        
        if (!item) {
            return;
        }
        
        if (QchInformationBox *informationbox = qobject_cast<QchInformationBox*>(list->object)) {
            if (QDeclarativeItem *root = informationbox->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchInformationBox *informationbox = qobject_cast<QchInformationBox*>(list->object)) {
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
        Q_Q(QchInformationBox);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        view->setStyleSheet("background: transparent");
        view->addItem(root);
        q->setWidget(view);
    }
        
    QchInformationBox *q_ptr;
    
    QchGraphicsView *view;
    QDeclarativeItem *root;
        
    QchDialogStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchInformationBox)
};

/*!
    \class InformationBox
    \brief Displays a Hildon-style popup information banner.
    
    \ingroup components
    
    \sa Notification
*/
QchInformationBox::QchInformationBox(QWidget *parent) :
    QMaemo5InformationBox(parent),
    d_ptr(new QchInformationBoxPrivate(this))
{
    Q_D(QchInformationBox);
    d->init();
}

QchInformationBox::~QchInformationBox() {}

/*!
    \brief The visual children of the information box.
*/
QDeclarativeListProperty<QDeclarativeItem> QchInformationBox::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchInformationBoxPrivate::children_append);
}

/*!
    \brief The visual children of the information box.
*/
QDeclarativeListProperty<QObject> QchInformationBox::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchInformationBoxPrivate::data_append);
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
            <td>The information box is closed (default).</td>
        </tr>
        <tr>
            <td>DialogStatus.Opening</td>
            <td>The information box is opening.</td>
        </tr>
        <tr>
            <td>DialogStatus.Open</td>
            <td>The information box is open.</td>
        </tr>
        <tr>
            <td>DialogStatus.Closing</td>
            <td>The information box is closing.</td>
        </tr>
    </table>
*/
QchDialogStatus::Status QchInformationBox::status() const {
    Q_D(const QchInformationBox);
    return d->status;
}

void QchInformationBox::classBegin() {}

void QchInformationBox::componentComplete() {
    if (parentWidget()) {
        setWindowFlags(Qt::Dialog);
    }
}

void QchInformationBox::showEvent(QShowEvent *e) {
    Q_D(QchInformationBox);
    d->status = QchDialogStatus::Opening;
    emit statusChanged();
    QMaemo5InformationBox::showEvent(e);
    d->status = QchDialogStatus::Open;
    emit statusChanged();
    emit visibleChanged();
}

void QchInformationBox::hideEvent(QHideEvent *e) {
    Q_D(QchInformationBox);
    d->status = QchDialogStatus::Closing;
    emit statusChanged();
    QMaemo5InformationBox::hideEvent(e);
    d->status = QchDialogStatus::Closed;
    emit statusChanged();
    emit visibleChanged();
}

void QchInformationBox::resizeEvent(QResizeEvent *e) {
    QMaemo5InformationBox::resizeEvent(e);
    emit sizeChanged();
}

#include "moc_qchinformationbox.cpp"

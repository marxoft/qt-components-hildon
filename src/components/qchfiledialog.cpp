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

#include "qchfiledialog.h"
#include <QFileDialog>

class QchFileDialogPrivate
{

public:
    QchFileDialogPrivate(QchFileDialog *parent) :
        q_ptr(parent),
        folder("/home/user/MyDocs/"),
        selectFolder(false)
    {
    }
    
    QWidget *findParentWidget() const {
        Q_Q(const QchFileDialog);
        QObject *p = q->parent();
        
        while (p) {
            if (p->isWidgetType()) {
                return qobject_cast<QWidget*>(p);
            }
            
            p = p->parent();
        }
        
        return 0;
    }
    
    QchFileDialog *q_ptr;
    
    QString filePath;
    QString folder;
    
    QStringList nameFilters;
    
    bool selectFolder;
    
    Q_DECLARE_PUBLIC(QchFileDialog)
};

QchFileDialog::QchFileDialog(QObject *parent) :
    QObject(parent),
    d_ptr(new QchFileDialogPrivate(this))
{
}

QchFileDialog::~QchFileDialog() {}

QString QchFileDialog::filePath() const {
    Q_D(const QchFileDialog);
    return d->filePath;
}

QString QchFileDialog::folder() const {
    Q_D(const QchFileDialog);
    return d->folder;
}

void QchFileDialog::setFolder(const QString &f) {
    if (f != folder()) {
        Q_D(QchFileDialog);
        d->folder = f;
        emit folderChanged();
    }
}

QStringList QchFileDialog::nameFilters() const {
    Q_D(const QchFileDialog);
    return d->nameFilters;
}

void QchFileDialog::setNameFilters(const QStringList &f) {
    Q_D(QchFileDialog);
    d->nameFilters = f;
    emit nameFiltersChanged();
}

bool QchFileDialog::selectFolder() const {
    Q_D(const QchFileDialog);
    return d->selectFolder;
}

void QchFileDialog::setSelectFolder(bool s) {
    if (s != selectFolder()) {
        Q_D(QchFileDialog);
        d->selectFolder = s;
        emit selectFolderChanged();
    }
}

void QchFileDialog::open() {
    Q_D(QchFileDialog);
    
    QString result;
    
    if (selectFolder()) {
        result = QFileDialog::getExistingDirectory(d->findParentWidget(), QString(), folder());
        
        if (!result.isEmpty()) {
            d->filePath = result;
            setFolder(result);
            emit accepted();
        }
        else {
            emit rejected();
        }
    }
    else {
        result = QFileDialog::getOpenFileName(d->findParentWidget(), QString(), folder(),
                                              nameFilters().isEmpty() ? QString() : QString("Files (%1)")
                                              .arg(nameFilters().join(" ")));
        
        if (!result.isEmpty()) {
            d->filePath = result;
            setFolder(result.left(result.lastIndexOf('/')));
            emit accepted();
        }
        else {
            emit rejected();
        }
    }
}

#include "moc_qchfiledialog.cpp"

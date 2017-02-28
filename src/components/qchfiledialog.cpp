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

#include "qchfiledialog.h"
#include <QFileDialog>

class QchFileDialogPrivate
{

public:
    QchFileDialogPrivate(QchFileDialog *parent) :
        q_ptr(parent),
        folder("/home/user/MyDocs/"),
        selectFolder(false),
        status(QchDialogStatus::Closed)
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
    
    QchDialogStatus::Status status;
    
    Q_DECLARE_PUBLIC(QchFileDialog)
};

/*!
    \class FileDialog
    \brief A file dialog with native appearance.
    
    \ingroup components
    
    The FileDialog component is used to display a native file dialog.
*/
QchFileDialog::QchFileDialog(QObject *parent) :
    QObject(parent),
    d_ptr(new QchFileDialogPrivate(this))
{
}

QchFileDialog::~QchFileDialog() {}

/*!
    \brief The current chosen filepath.
    
    \sa accepted()
*/
QString QchFileDialog::filePath() const {
    Q_D(const QchFileDialog);
    return d->filePath;
}

/*!
    \brief The current folder.
    
    The folder can be changed either programatically or by the user.
*/
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

/*!
    \brief A list of wildcard filters used to filter filenames.
*/
QStringList QchFileDialog::nameFilters() const {
    Q_D(const QchFileDialog);
    return d->nameFilters;
}

void QchFileDialog::setNameFilters(const QStringList &f) {
    Q_D(QchFileDialog);
    d->nameFilters = f;
    emit nameFiltersChanged();
}

/*!
    \brief Whether the dialog should be used to choose a folder.
    
    The default value is \c false.
*/
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
QchDialogStatus::Status QchFileDialog::status() const {
    Q_D(const QchFileDialog);
    return d->status;
}

/*!
    \fn void FileDialog::accepted()
    \brief Emitted when the user chooses a file/folder.    
*/

/*!
    \fn void FileDialog::rejected()
    \brief Emitted when the user closes the dialog without choosing a file/folder.
*/

/*!
    \brief Opens the dialog in accordance with the currently set properties.
    
    If a file/folder is chosen, the accepted() signal will be emitted, otherwise the rejected() signal will be emitted.
    
    \sa accepted(), rejected()
*/
void QchFileDialog::open() {
    Q_D(QchFileDialog);
    d->status = QchDialogStatus::Open;
    emit statusChanged();
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
    
    d->status = QchDialogStatus::Closed;
    emit statusChanged();
}

#include "moc_qchfiledialog.cpp"

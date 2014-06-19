#include "filedialog_p.h"
#include "filedialog_p_p.h"

FileDialog::FileDialog(QWidget *parent) :
    QObject(parent),
    d_ptr(new FileDialogPrivate(this))
{
}

FileDialog::FileDialog(FileDialogPrivate &dd, QWidget *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

FileDialog::~FileDialog() {}

QString FileDialog::caption() const {
    Q_D(const FileDialog);

    return d->caption;
}

void FileDialog::setCaption(const QString &caption) {
    if (caption != this->caption()) {
        Q_D(FileDialog);
        d->caption = caption;
        emit captionChanged();
    }
}

QString FileDialog::directory() const {
    Q_D(const FileDialog);

    return d->directory;
}

void FileDialog::setDirectory(const QString &directory) {
    if (directory != this->directory()) {
        Q_D(FileDialog);
        d->directory = directory;
        emit directoryChanged();
    }
}

QStringList FileDialog::nameFilters() const {
    Q_D(const FileDialog);

    return d->nameFilters;
}

void FileDialog::setNameFilters(const QStringList &filters) {
    if (filters != this->nameFilters()) {
        Q_D(FileDialog);
        d->nameFilters = filters;
        emit nameFiltersChanged();
    }
}

QStringList FileDialog::selectedFiles() const {
    Q_D(const FileDialog);

    return d->selectedFiles;
}

void FileDialog::getExistingDirectory() {
    Q_D(FileDialog);

    if (d->isOpen) {
        return;
    }

    d->isOpen = true;

    QWidget *parentWidget = 0;

    if (this->parent()->isWidgetType()) {
        parentWidget = qobject_cast<QWidget*>(this->parent());
    }

    QString dir = QFileDialog::getExistingDirectory(parentWidget, this->caption(), this->directory());
    d->isOpen = false;

    if (dir.isEmpty()) {
        emit rejected();
    }
    else {
        d->selectedFiles.clear();
        d->selectedFiles.append(dir);
        emit selectedFilesChanged();
        emit accepted();
    }
}

void FileDialog::getOpenFileName() {
    Q_D(FileDialog);

    if (d->isOpen) {
        return;
    }

    d->isOpen = true;

    QWidget *parentWidget = 0;

    if (this->parent()->isWidgetType()) {
        parentWidget = qobject_cast<QWidget*>(this->parent());
    }

    QString file = QFileDialog::getOpenFileName(parentWidget, this->caption(), this->directory(), this->nameFilters().join(" "));
    d->isOpen = false;

    if (file.isEmpty()) {
        emit rejected();
    }
    else {
        d->selectedFiles.clear();
        d->selectedFiles.append(file);
        emit selectedFilesChanged();
        emit accepted();
    }
}

void FileDialog::getOpenFileNames() {
    Q_D(FileDialog);

    if (d->isOpen) {
        return;
    }

    d->isOpen = true;

    QWidget *parentWidget = 0;

    if (this->parent()->isWidgetType()) {
        parentWidget = qobject_cast<QWidget*>(this->parent());
    }

    QStringList files = QFileDialog::getOpenFileNames(parentWidget, this->caption(), this->directory(), this->nameFilters().join(" "));
    d->isOpen = false;

    if (files.isEmpty()) {
        emit rejected();
    }
    else {
        d->selectedFiles = files;
        emit selectedFilesChanged();
        emit accepted();
    }
}

void FileDialog::getSaveFileName() {
    Q_D(FileDialog);

    if (d->isOpen) {
        return;
    }

    d->isOpen = true;

    QWidget *parentWidget = 0;

    if (this->parent()->isWidgetType()) {
        parentWidget = qobject_cast<QWidget*>(this->parent());
    }

    QString file = QFileDialog::getSaveFileName(parentWidget, this->caption(), this->directory(), this->nameFilters().join(" "));
    d->isOpen = false;

    if (file.isEmpty()) {
        emit rejected();
    }
    else {
        d->selectedFiles.clear();
        d->selectedFiles.append(file);
        emit selectedFilesChanged();
        emit accepted();
    }
}

#include "moc_filedialog_p.cpp"

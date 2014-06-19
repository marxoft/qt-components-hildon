#ifndef FILEDIALOG_P_P_H
#define FILEDIALOG_P_P_H

#include "filedialog_p.h"

class FileDialogPrivate
{

public:
    FileDialogPrivate(FileDialog *parent) :
        q_ptr(parent),
        isOpen(false)
    {
    }

    virtual ~FileDialogPrivate() {}

    FileDialog *q_ptr;

    QString caption;

    QString directory;

    QStringList nameFilters;

    bool isOpen;

    QStringList selectedFiles;
};

#endif // FILEDIALOG_P_P_H

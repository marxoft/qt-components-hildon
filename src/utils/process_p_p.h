#ifndef PROCESS_P_P_H
#define PROCESS_P_P_H

#include "process_p.h"

class ProcessPrivate
{

public:
    ProcessPrivate(Process *parent);
    virtual ~ProcessPrivate();

    Process *q_ptr;

    Process *outputProcess;

    QProcess *process;

    QString command;

    QVariantMap envMap;

    QString errorFile;
    QString inputFile;
    QString outputFile;
};

#endif // PROCESS_P_P_H

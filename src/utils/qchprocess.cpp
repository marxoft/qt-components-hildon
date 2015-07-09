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

#include "qchprocess.h"

class QchProcessPrivate
{

public:
    QchProcessPrivate(QchProcess *parent) :
        q_ptr(parent),
        outputProcess(0),
        process(0)
    {
    }

    QchProcess *q_ptr;

    QchProcess *outputProcess;

    QProcess *process;

    QString command;

    QVariantMap envMap;

    QString errorFile;
    QString inputFile;
    QString outputFile;
    
    Q_DECLARE_PUBLIC(QchProcess)
};

QchProcess::QchProcess(QObject *parent) :
    QObject(parent),
    d_ptr(new QchProcessPrivate(this))
{
    Q_D(QchProcess);

    d->process = new QProcess(this);
    connect(d->process, SIGNAL(started()), this, SIGNAL(started()));
    connect(d->process, SIGNAL(finished(int)), this, SIGNAL(finished()));
    connect(d->process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SIGNAL(stateChanged()));
    connect(d->process, SIGNAL(readyReadStandardError()), this, SIGNAL(standardErrorChanged()));
    connect(d->process, SIGNAL(readyReadStandardOutput()), this, SIGNAL(standardOutputChanged()));
}

QchProcess::QchProcess(QchProcessPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    Q_D(QchProcess);

    if (!d->process) {
        d->process = new QProcess(this);
    }

    connect(d->process, SIGNAL(started()), this, SIGNAL(started()));
    connect(d->process, SIGNAL(finished(int)), this, SIGNAL(finished()));
    connect(d->process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SIGNAL(stateChanged()));
    connect(d->process, SIGNAL(readyReadStandardError()), this, SIGNAL(standardErrorChanged()));
    connect(d->process, SIGNAL(readyReadStandardOutput()), this, SIGNAL(standardOutputChanged()));
}

QchProcess::~QchProcess() {}

QString QchProcess::command() const {
    Q_D(const QchProcess);

    return d->command;
}

void QchProcess::setCommand(const QString &command) {
    if (command != this->command()) {
        Q_D(QchProcess);
        d->command = command;
        emit commandChanged();
    }
}

QString QchProcess::workingDirectory() const {
    Q_D(const QchProcess);

    return d->process->workingDirectory();
}

void QchProcess::setWorkingDirectory(const QString &directory) {
    if (directory != workingDirectory()) {
        Q_D(QchProcess);
        d->process->setWorkingDirectory(directory);
        emit workingDirectoryChanged();
    }
}

Q_PID QchProcess::pid() const {
    Q_D(const QchProcess);

    return d->process->pid();
}

QchProcess::ProcessError QchProcess::error() const {
    Q_D(const QchProcess);

    return ProcessError(d->process->error());
}

QchProcess::ProcessState QchProcess::state() const {
    Q_D(const QchProcess);

    return ProcessState(d->process->state());
}

int QchProcess::exitCode() const {
    Q_D(const QchProcess);

    return d->process->exitCode();
}

QchProcess::ExitStatus QchProcess::exitStatus() const {
    Q_D(const QchProcess);

    return ExitStatus(d->process->exitStatus());
}

QchProcess::ProcessChannelMode QchProcess::processChannelMode() const {
    Q_D(const QchProcess);

    return ProcessChannelMode(d->process->processChannelMode());
}

void QchProcess::setProcessChannelMode(ProcessChannelMode mode) {
    if (mode != processChannelMode()) {
        Q_D(QchProcess);
        d->process->setProcessChannelMode(QProcess::ProcessChannelMode(mode));
        emit processChannelModeChanged();
    }
}

QVariantMap QchProcess::processEnvironment() const {
    Q_D(const QchProcess);

    return d->envMap;
}

void QchProcess::setProcessEnvironment(const QVariantMap &environment) {
    if (environment != processEnvironment()) {
        Q_D(QchProcess);
        d->envMap = environment;

        QProcessEnvironment env;

        QMapIterator<QString, QVariant> iterator(environment);

        while (iterator.hasNext()) {
            iterator.next();
            env.insert(iterator.key(), iterator.value().toString());
        }

        emit processEnvironmentChanged();
    }
}

void QchProcess::resetProcessEnvironment() {
    setProcessEnvironment(QVariantMap());
}

QchProcess::ProcessChannel QchProcess::readChannel() const {
    Q_D(const QchProcess);

    return ProcessChannel(d->process->readChannel());
}

void QchProcess::setReadChannel(ProcessChannel channel) {
    if (channel != readChannel()) {
        Q_D(QchProcess);
        d->process->setReadChannel(QProcess::ProcessChannel(channel));
        emit readChannelChanged();
    }
}

QString QchProcess::standardError() {
    Q_D(QchProcess);

    return d->process->readAllStandardError();
}

QString QchProcess::standardOutput() {
    Q_D(QchProcess);

    return d->process->readAllStandardOutput();
}

QString QchProcess::standardErrorFile() const {
    Q_D(const QchProcess);

    return d->errorFile;
}

void QchProcess::setStandardErrorFile(const QString &path) {
    if (path != standardErrorFile()) {
        Q_D(QchProcess);
        d->errorFile = path;
        d->process->setStandardErrorFile(path);
        emit standardErrorFileChanged();
    }
}

QString QchProcess::standardInputFile() const {
    Q_D(const QchProcess);

    return d->inputFile;
}

void QchProcess::setStandardInputFile(const QString &path) {
    if (path != standardInputFile()) {
        Q_D(QchProcess);
        d->inputFile = path;
        d->process->setStandardInputFile(path);
        emit standardInputFileChanged();
    }
}

QString QchProcess::standardOutputFile() const {
    Q_D(const QchProcess);

    return d->outputFile;
}

void QchProcess::setStandardOutputFile(const QString &path) {
    if (path != standardOutputFile()) {
        Q_D(QchProcess);
        d->outputFile = path;
        d->process->setStandardOutputFile(path);
        emit standardOutputFileChanged();
    }
}

QchProcess* QchProcess::standardOutputProcess() const {
    Q_D(const QchProcess);

    return d->outputProcess;
}

void QchProcess::setStandardOutputProcess(QchProcess *process) {
    if (process != standardOutputProcess()) {
        Q_D(QchProcess);
        d->outputProcess = process;
        d->process->setStandardOutputProcess(process->d_func()->process);
        emit standardOutputProcessChanged();
    }
}

void QchProcess::resetStandardOutputProcess() {
    setStandardOutputProcess(0);
}

void QchProcess::start() {
    Q_D(QchProcess);

    d->process->start(command());
}

void QchProcess::abort() {
    Q_D(QchProcess);

    d->process->kill();
}

#include "moc_qchprocess.cpp"

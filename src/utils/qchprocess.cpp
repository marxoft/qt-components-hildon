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

/*!
    \class Process
    \brief Used to start external programs and communicate with them.

    \ingroup utils
    
    \include process.qml
*/
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

/*!
    \brief The command to be executed by the process.
*/
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

/*!
    \brief The directory from which \link command\endlink is executed.
*/
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

/*!
    \brief The unique process id.
*/
Q_PID QchProcess::pid() const {
    Q_D(const QchProcess);

    return d->process->pid();
}

/*!
    \brief The error that last occurred.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Process.FailedToStart</td>
            <td>The process failed to start.</td>
        </tr>
        <tr>
            <td>Process.Crashed</td>
            <td>The process crashed some time after starting successfully.</td>
        </tr>
        <tr>
            <td>Process.WriteError</td>
            <td>An error occurred when attempting to write to the process.</td>
        </tr>
        <tr>
            <td>Process.ReadError</td>
            <td>An error occurred when attempting to read from the process.</td>
        </tr>
        <tr>
            <td>Process.UnknownError</td>
            <td>An unknown error occurred (default).</td>
        </tr>
    </table>
*/
QchProcess::ProcessError QchProcess::error() const {
    Q_D(const QchProcess);

    return ProcessError(d->process->error());
}

/*!
    \brief The current state of the process.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Process.NotRunning</td>
            <td>The process is not running (default).</td>
        </tr>
        <tr>
            <td>Process.Starting</td>
            <td>The process is starting, but the program has not yet been invoked.</td>
        </tr>
        <tr>
            <td>Process.Running</td>
            <td>The process is running and is ready for reading and writing.</td>
        </tr>
    </table>
*/
QchProcess::ProcessState QchProcess::state() const {
    Q_D(const QchProcess);

    return ProcessState(d->process->state());
}

/*!
    \brief The last exit code of the process.
    
    \sa exitStatus
*/
int QchProcess::exitCode() const {
    Q_D(const QchProcess);

    return d->process->exitCode();
}

/*!
    \brief The last exit status of the process.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Process.NormalExit</td>
            <td>The process exited normally.</td>
        </tr>
        <tr>
            <td>Process.CrashExit</td>
            <td>The process crashed.</td>
        </tr>
    </table>
    
    \sa exitCode
*/
QchProcess::ExitStatus QchProcess::exitStatus() const {
    Q_D(const QchProcess);

    return ExitStatus(d->process->exitStatus());
}

/*!
    \brief The channel mode of the process standard output and standard error channels.

    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Process.SeparateChannels</td>
            <td>Process manages the output of the running process, keeping standard output and standard error data in 
            separate internal buffers (default).</td>
        </tr>
        <tr>
            <td>Process.MergedChannels</td>
            <td>Process merges the output of the running process into the standard output channel (stdout). 
            The standard error channel (stderr) will not receive any data.</td>
        </tr>
        <tr>
            <td>Process.ForwardedChannels</td>
            <td>Process forwards the output of the running process onto the main process.</td>
        </tr>
    </table>
    
    \sa readChannel
*/
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

/*!
    \brief The environment variables of the process.
*/
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

/*!
    \brief The read channel of the process.
    
    Possible values are:
    
    <table>
        <tr>
            <th>Value</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>Process.StandardOutput</td>
            <td>The standard output (stdout) of the running process (default).</td>
        </tr>
        <tr>
            <td>Process.StandardError</td>
            <td>The standard error (stderr) of the running process.</td>
        </tr>
    </table>
*/
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

/*!
    \brief The output from standard error (stderr).
*/
QString QchProcess::standardError() {
    Q_D(QchProcess);

    return d->process->readAllStandardError();
}

/*!
    \brief The output from standard output (stdout).
*/
QString QchProcess::standardOutput() {
    Q_D(QchProcess);

    return d->process->readAllStandardOutput();
}

/*!
    \brief The file to which standard error output is redirected.
    
    \sa standardError
*/
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

/*!
    \brief The file to which standard input is redirected.
*/
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

/*!
    \brief The file to which standard output is redirected.
    
    \sa standardOutput
*/
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

/*!
    \brief The Process to which standard output is redirected.
    
    Setting this property to a valid Process is the equivalent of
    
    \code
    $ process1 | process2
    \endcode
    
    Set the property to \c null to reset.
    
    \sa standardOutput, standardOutputFile
*/
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

/*!    
    Starts the process. The started() signal will be emitted if the process was started successfully.
    
    \sa started(), state
*/
void QchProcess::start() {
    Q_D(QchProcess);

    d->process->start(command());
}

/*!    
    Aborts a running process.
*/
void QchProcess::abort() {
    Q_D(QchProcess);

    d->process->kill();
}

/*!
    \fn void Process::started()
    
    This signal is emitted when the process is started.
    
    \sa start(), state
*/

#include "moc_qchprocess.cpp"

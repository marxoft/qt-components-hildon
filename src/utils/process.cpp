#include "process_p.h"
#include "process_p_p.h"

Process::Process(QObject *parent) :
    QObject(parent),
    d_ptr(new ProcessPrivate(this))
{
    Q_D(Process);

    d->process = new QProcess(this);
    this->connect(d->process, SIGNAL(started()), this, SIGNAL(started()));
    this->connect(d->process, SIGNAL(finished(int)), this, SIGNAL(finished()));
    this->connect(d->process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SIGNAL(stateChanged()));
    this->connect(d->process, SIGNAL(readyReadStandardError()), this, SIGNAL(standardErrorChanged()));
    this->connect(d->process, SIGNAL(readyReadStandardOutput()), this, SIGNAL(standardOutputChanged()));
}

Process::Process(ProcessPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    Q_D(Process);

    if (!d->process) {
        d->process = new QProcess(this);
    }

    this->connect(d->process, SIGNAL(started()), this, SIGNAL(started()));
    this->connect(d->process, SIGNAL(finished(int)), this, SIGNAL(finished()));
    this->connect(d->process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SIGNAL(stateChanged()));
    this->connect(d->process, SIGNAL(readyReadStandardError()), this, SIGNAL(standardErrorChanged()));
    this->connect(d->process, SIGNAL(readyReadStandardOutput()), this, SIGNAL(standardOutputChanged()));
}

Process::~Process() {}

QString Process::command() const {
    Q_D(const Process);

    return d->command;
}

void Process::setCommand(const QString &command) {
    if (command != this->command()) {
        Q_D(Process);
        d->command = command;
        emit commandChanged();
    }
}

QString Process::workingDirectory() const {
    Q_D(const Process);

    return d->process->workingDirectory();
}

void Process::setWorkingDirectory(const QString &directory) {
    if (directory != this->workingDirectory()) {
        Q_D(Process);
        d->process->setWorkingDirectory(directory);
        emit workingDirectoryChanged();
    }
}

Q_PID Process::pid() const {
    Q_D(const Process);

    return d->process->pid();
}

Process::ProcessError Process::error() const {
    Q_D(const Process);

    return ProcessError(d->process->error());
}

Process::ProcessState Process::state() const {
    Q_D(const Process);

    return ProcessState(d->process->state());
}

int Process::exitCode() const {
    Q_D(const Process);

    return d->process->exitCode();
}

Process::ExitStatus Process::exitStatus() const {
    Q_D(const Process);

    return ExitStatus(d->process->exitStatus());
}

Process::ProcessChannelMode Process::processChannelMode() const {
    Q_D(const Process);

    return ProcessChannelMode(d->process->processChannelMode());
}

void Process::setProcessChannelMode(ProcessChannelMode mode) {
    if (mode != this->processChannelMode()) {
        Q_D(Process);
        d->process->setProcessChannelMode(QProcess::ProcessChannelMode(mode));
        emit processChannelModeChanged();
    }
}

QVariantMap Process::processEnvironment() const {
    Q_D(const Process);

    return d->envMap;
}

void Process::setProcessEnvironment(const QVariantMap &environment) {
    if (environment != this->processEnvironment()) {
        Q_D(Process);
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

void Process::resetProcessEnvironment() {
    this->setProcessEnvironment(QVariantMap());
}

Process::ProcessChannel Process::readChannel() const {
    Q_D(const Process);

    return ProcessChannel(d->process->readChannel());
}

void Process::setReadChannel(ProcessChannel channel) {
    if (channel != this->readChannel()) {
        Q_D(Process);
        d->process->setReadChannel(QProcess::ProcessChannel(channel));
        emit readChannelChanged();
    }
}

QString Process::standardError() {
    Q_D(Process);

    return d->process->readAllStandardError();
}

QString Process::standardOutput() {
    Q_D(Process);

    return d->process->readAllStandardOutput();
}

QString Process::standardErrorFile() const {
    Q_D(const Process);

    return d->errorFile;
}

void Process::setStandardErrorFile(const QString &path) {
    if (path != this->standardErrorFile()) {
        Q_D(Process);
        d->errorFile = path;
        d->process->setStandardErrorFile(path);
        emit standardErrorFileChanged();
    }
}

QString Process::standardInputFile() const {
    Q_D(const Process);

    return d->inputFile;
}

void Process::setStandardInputFile(const QString &path) {
    if (path != this->standardInputFile()) {
        Q_D(Process);
        d->inputFile = path;
        d->process->setStandardInputFile(path);
        emit standardInputFileChanged();
    }
}

QString Process::standardOutputFile() const {
    Q_D(const Process);

    return d->outputFile;
}

void Process::setStandardOutputFile(const QString &path) {
    if (path != this->standardOutputFile()) {
        Q_D(Process);
        d->outputFile = path;
        d->process->setStandardOutputFile(path);
        emit standardOutputFileChanged();
    }
}

Process* Process::standardOutputProcess() const {
    Q_D(const Process);

    return d->outputProcess;
}

void Process::setStandardOutputProcess(Process *process) {
    if (process != this->standardOutputProcess()) {
        Q_D(Process);
        d->outputProcess = process;
        d->process->setStandardOutputProcess(process->d_func()->process);
        emit standardOutputProcessChanged();
    }
}

void Process::resetStandardOutputProcess() {
    this->setStandardOutputProcess(0);
}

void Process::start() {
    Q_D(Process);

    d->process->start(this->command());
}

void Process::abort() {
    Q_D(Process);

    d->process->kill();
}

ProcessPrivate::ProcessPrivate(Process *parent) :
    q_ptr(parent),
    outputProcess(0),
    process(0)
{
}

ProcessPrivate::~ProcessPrivate() {}

#include "moc_process_p.cpp"

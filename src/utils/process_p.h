#ifndef PROCESS_P_H
#define PROCESS_P_H

#include <QProcess>
#include <QVariantMap>
#include <qdeclarative.h>

class ProcessPrivate;

class Process : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QString workingDirectory READ workingDirectory WRITE setWorkingDirectory NOTIFY workingDirectoryChanged)
    Q_PROPERTY(Q_PID pid READ pid NOTIFY pidChanged)
    Q_PROPERTY(ProcessError error READ error NOTIFY finished)
    Q_PROPERTY(ProcessState state READ state NOTIFY stateChanged)
    Q_PROPERTY(int exitCode READ exitCode NOTIFY finished)
    Q_PROPERTY(ExitStatus exitStatus READ exitStatus NOTIFY finished)
    Q_PROPERTY(ProcessChannelMode processChannelMode READ processChannelMode WRITE setProcessChannelMode NOTIFY processChannelModeChanged)
    Q_PROPERTY(QVariantMap processEnvironment READ processEnvironment WRITE setProcessEnvironment RESET resetProcessEnvironment NOTIFY processEnvironmentChanged)
    Q_PROPERTY(ProcessChannel readChannel READ readChannel WRITE setReadChannel NOTIFY readChannelChanged)
    Q_PROPERTY(QString standardError READ standardError NOTIFY standardErrorChanged)
    Q_PROPERTY(QString standardOutput READ standardOutput NOTIFY standardOutputChanged)
    Q_PROPERTY(QString standardErrorFile READ standardErrorFile WRITE setStandardErrorFile NOTIFY standardErrorFileChanged)
    Q_PROPERTY(QString standardInputFile READ standardInputFile WRITE setStandardInputFile NOTIFY standardInputFileChanged)
    Q_PROPERTY(QString standardOutputFile READ standardOutputFile WRITE setStandardOutputFile NOTIFY standardOutputFileChanged)
    Q_PROPERTY(Process* standardOutputProcess READ standardOutputProcess WRITE setStandardOutputProcess RESET resetStandardOutputProcess NOTIFY standardOutputProcessChanged)

    Q_ENUMS(ExitStatus
            ProcessChannel
            ProcessChannelMode
            ProcessError
            ProcessState)

public:
    enum ExitStatus {
        NormalExit = QProcess::NormalExit,
        CrashExit = QProcess::CrashExit
    };

    enum ProcessChannel {
        StandardOutput = QProcess::StandardOutput,
        StandardError = QProcess::StandardError
    };

    enum ProcessChannelMode {
        SeparateChannels = QProcess::SeparateChannels,
        MergedChannels = QProcess::MergedChannels,
        ForwardedChannels = QProcess::ForwardedChannels
    };

    enum ProcessError {
        FailedToStart = QProcess::FailedToStart,
        Crashed = QProcess::Crashed,
        Timedout = QProcess::Timedout,
        WriteError = QProcess::WriteError,
        ReadError = QProcess::ReadError,
        UnknownError = QProcess::UnknownError
    };

    enum ProcessState {
        NotRunning = QProcess::NotRunning,
        Starting = QProcess::Starting,
        Running = QProcess::Running
    };

    explicit Process(QObject *parent = 0);
    ~Process();

    QString command() const;
    void setCommand(const QString &command);

    QString workingDirectory() const;
    void setWorkingDirectory(const QString &directory);

    Q_PID pid() const;

    ProcessError error() const;

    ProcessState state() const;

    int exitCode() const;

    ExitStatus exitStatus() const;

    ProcessChannelMode processChannelMode() const;
    void setProcessChannelMode(ProcessChannelMode mode);

    QVariantMap processEnvironment() const;
    void setProcessEnvironment(const QVariantMap &environment);
    void resetProcessEnvironment();

    ProcessChannel readChannel() const;
    void setReadChannel(ProcessChannel channel);

    QString standardError();
    QString standardOutput();

    QString standardErrorFile() const;
    void setStandardErrorFile(const QString &path);

    QString standardInputFile() const;
    void setStandardInputFile(const QString &path);

    QString standardOutputFile() const;
    void setStandardOutputFile(const QString &path);

    Process* standardOutputProcess() const;
    void setStandardOutputProcess(Process *process);
    void resetStandardOutputProcess();

public slots:
    void start();
    void abort();

signals:
    void commandChanged();
    void workingDirectoryChanged();
    void pidChanged();
    void stateChanged();
    void started();
    void finished();
    void processChannelModeChanged();
    void processEnvironmentChanged();
    void readChannelChanged();
    void standardErrorChanged();
    void standardOutputChanged();
    void standardErrorFileChanged();
    void standardInputFileChanged();
    void standardOutputFileChanged();
    void standardOutputProcessChanged();

protected:
    Process(ProcessPrivate &dd, QObject *parent = 0);

    QScopedPointer<ProcessPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Process)

private:
    Q_DISABLE_COPY(Process)
};

QML_DECLARE_TYPE(Process)

#endif // PROCESS_P_H

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

#ifndef QCHPROCESS_H
#define QCHPROCESS_H

#include <QProcess>
#include <QVariantMap>
#include <qdeclarative.h>

class QchProcessPrivate;

class QchProcess : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QString workingDirectory READ workingDirectory WRITE setWorkingDirectory NOTIFY workingDirectoryChanged)
    Q_PROPERTY(Q_PID pid READ pid NOTIFY pidChanged)
    Q_PROPERTY(ProcessError error READ error NOTIFY finished)
    Q_PROPERTY(ProcessState state READ state NOTIFY stateChanged)
    Q_PROPERTY(int exitCode READ exitCode NOTIFY finished)
    Q_PROPERTY(ExitStatus exitStatus READ exitStatus NOTIFY finished)
    Q_PROPERTY(ProcessChannelMode processChannelMode READ processChannelMode WRITE setProcessChannelMode
               NOTIFY processChannelModeChanged)
    Q_PROPERTY(QVariantMap processEnvironment READ processEnvironment WRITE setProcessEnvironment
               RESET resetProcessEnvironment NOTIFY processEnvironmentChanged)
    Q_PROPERTY(ProcessChannel readChannel READ readChannel WRITE setReadChannel NOTIFY readChannelChanged)
    Q_PROPERTY(QString standardError READ standardError NOTIFY standardErrorChanged)
    Q_PROPERTY(QString standardOutput READ standardOutput NOTIFY standardOutputChanged)
    Q_PROPERTY(QString standardErrorFile READ standardErrorFile WRITE setStandardErrorFile
               NOTIFY standardErrorFileChanged)
    Q_PROPERTY(QString standardInputFile READ standardInputFile WRITE setStandardInputFile
               NOTIFY standardInputFileChanged)
    Q_PROPERTY(QString standardOutputFile READ standardOutputFile WRITE setStandardOutputFile
               NOTIFY standardOutputFileChanged)
    Q_PROPERTY(QchProcess* standardOutputProcess READ standardOutputProcess WRITE setStandardOutputProcess
               RESET resetStandardOutputProcess NOTIFY standardOutputProcessChanged)

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

    explicit QchProcess(QObject *parent = 0);
    ~QchProcess();

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

    QchProcess* standardOutputProcess() const;
    void setStandardOutputProcess(QchProcess *process);
    void resetStandardOutputProcess();

public Q_SLOTS:
    void start();
    void start(const QString &command);
    void abort();

    static bool startDetached(const QString &command);

Q_SIGNALS:
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
    QchProcess(QchProcessPrivate &dd, QObject *parent = 0);

    QScopedPointer<QchProcessPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchProcess)

private:
    Q_DISABLE_COPY(QchProcess)
};

QML_DECLARE_TYPE(QchProcess)

#endif // QCHPROCESS_H

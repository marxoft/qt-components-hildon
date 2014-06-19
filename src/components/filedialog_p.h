#ifndef FILEDIALOG_P_H
#define FILEDIALOG_P_H

#include <QObject>
#include <QFileDialog>
#include <qdeclarative.h>

class FileDialogPrivate;

class FileDialog : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory NOTIFY directoryChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    Q_PROPERTY(QStringList selectedFiles READ selectedFiles NOTIFY selectedFilesChanged)

public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();

    QString caption() const;
    void setCaption(const QString &caption);

    QString directory() const;
    void setDirectory(const QString &directory);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &filters);

    QStringList selectedFiles() const;

public slots:
    void getExistingDirectory();
    void getOpenFileName();
    void getOpenFileNames();
    void getSaveFileName();

signals:
    void captionChanged();
    void directoryChanged();
    void nameFiltersChanged();
    void selectedFilesChanged();
    void accepted();
    void rejected();

private:
    FileDialog(FileDialogPrivate &dd, QWidget *parent = 0);

    QScopedPointer<FileDialogPrivate> d_ptr;

    Q_DECLARE_PRIVATE(FileDialog)
};

QML_DECLARE_TYPE(FileDialog)

#endif // FILEDIALOG_P_H

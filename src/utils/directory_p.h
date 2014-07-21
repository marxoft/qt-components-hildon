#ifndef DIRECTORY_P_H
#define DIRECTORY_P_H

#include <QObject>
#include <QDir>
#include <qdeclarative.h>

class Directory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString absolutePath READ absolutePath NOTIFY pathChanged)
    Q_PROPERTY(QString canonicalPath READ canonicalPath NOTIFY pathChanged)
    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QString homePath READ homePath CONSTANT FINAL)
    Q_PROPERTY(QString rootPath READ rootPath CONSTANT FINAL)
    Q_PROPERTY(QString tempPath READ tempPath CONSTANT FINAL)
    Q_PROPERTY(uint count READ count NOTIFY pathChanged)
    Q_PROPERTY(QString dirName READ dirName NOTIFY pathChanged)
    Q_PROPERTY(bool exists READ exists NOTIFY pathChanged)
    Q_PROPERTY(Filters filter READ filter WRITE setFilter RESET resetFilter NOTIFY filterChanged)
    Q_PROPERTY(bool absolute READ isAbsolute NOTIFY pathChanged)
    Q_PROPERTY(bool readable READ isReadable NOTIFY pathChanged)
    Q_PROPERTY(bool relative READ isRelative NOTIFY pathChanged)
    Q_PROPERTY(bool root READ isRoot NOTIFY pathChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters NOTIFY nameFiltersChanged)
    Q_PROPERTY(SortFlags sorting READ sorting WRITE setSorting RESET resetSorting NOTIFY sortingChanged)

    Q_ENUMS(Filter SortFlag)

public:
    enum Filter {
        Dirs = QDir::Dirs,
        AllDirs = QDir::AllDirs,
        Drives = QDir::Drives,
        NoSymLinks = QDir::NoSymLinks,
        NoDotAndDotDot = QDir::NoDotAndDotDot,
        NoDot = QDir::NoDot,
        NoDotDot = QDir::NoDotDot,
        AllEntries = QDir::AllEntries,
        Readable = QDir::Readable,
        Writable = QDir::Writable,
        Executable = QDir::Executable,
        Modified = QDir::Modified,
        Hidden = QDir::Hidden,
        System = QDir::System,
        CaseSensitive = QDir::CaseSensitive
    };

    enum SortFlag {
        Name = QDir::Name,
        Time = QDir::Time,
        Size = QDir::Size,
        Type = QDir::Type,
        Unsorted = QDir::Unsorted,
        NoSort = QDir::NoSort,
        DirsFirst = QDir::DirsFirst,
        DirsLast = QDir::DirsLast,
        Reversed = QDir::Reversed,
        IgnoreCase = QDir::IgnoreCase,
        LocaleAware = QDir::LocaleAware
    };

    Q_DECLARE_FLAGS(Filters, Filter)
    Q_DECLARE_FLAGS(SortFlags, SortFlag)

    explicit Directory(QObject *parent = 0);
    ~Directory();

    QString path() const;
    void setPath(const QString &path);

    QString absolutePath() const;
    QString canonicalPath() const;

    QString currentPath();
    void setCurrentPath(const QString &path);
    QString homePath();
    QString rootPath();
    QString tempPath();

    uint count() const;

    QString dirName() const;

    bool exists() const;

    Filters filter() const;
    void setFilter(Filters filter);
    void resetFilter();

    bool isAbsolute() const;
    bool isReadable() const;
    bool isRelative() const;
    bool isRoot() const;

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    SortFlags sorting() const;
    void setSorting(SortFlags sorting);
    void resetSorting();

    Q_INVOKABLE QString absoluteFilePath(const QString &fileName) const;
    Q_INVOKABLE QString filePath(const QString &fileName) const;
    Q_INVOKABLE QString relativeFilePath(const QString &fileName) const;

    Q_INVOKABLE bool cd(const QString &dirName);
    Q_INVOKABLE bool cdUp();

    Q_INVOKABLE QStringList entryList() const;

    Q_INVOKABLE bool makeAbsolute();

    Q_INVOKABLE bool mkdir(const QString &dirName) const;
    Q_INVOKABLE bool mkPath(const QString &dirPath) const;
    Q_INVOKABLE bool remove(const QString &fileName);
    Q_INVOKABLE bool rename(const QString &oldName, const QString &newName);
    Q_INVOKABLE bool rmdir(const QString &dirName) const;
    Q_INVOKABLE bool rmpath(const QString &dirPath) const;

    Q_INVOKABLE void refresh();

    Q_INVOKABLE static QString cleanPath(const QString &path);

    Q_INVOKABLE static QString fromNativeSeparators(const QString &pathName);
    Q_INVOKABLE static QString toNativeSeparators(const QString &pathName);

    Q_INVOKABLE static bool match(const QString &filter, const QString &fileName);
    Q_INVOKABLE static bool match(const QStringList &filters, const QString &fileName);

    Q_INVOKABLE static QStringList searchPaths(const QString &prefix);
    Q_INVOKABLE static void addSearchPath(const QString &prefix, const QString &path);
    Q_INVOKABLE static void setSearchPaths(const QString &prefix, const QStringList &searchPaths);

signals:
    void pathChanged();
    void currentPathChanged();
    void filterChanged();
    void nameFiltersChanged();
    void sortingChanged();

private:
    QDir m_dir;

    Q_DISABLE_COPY(Directory)
};

QML_DECLARE_TYPE(Directory)

Q_DECLARE_OPERATORS_FOR_FLAGS(Directory::Filters)
Q_DECLARE_OPERATORS_FOR_FLAGS(Directory::SortFlags)

#endif // DIRECTORY_P_H

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

#ifndef QCHSCREENSHOT_H
#define QCHSCREENSHOT_H

#include <QObject>
#include <qdeclarative.h>

class QchScreenShotPrivate;

class QchScreenShot : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject *target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool overwriteExistingFile READ overwriteExistingFile WRITE setOverwriteExistingFile
               NOTIFY overwriteExistingFileChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight NOTIFY heightChanged)
    Q_PROPERTY(int targetX READ targetX WRITE setTargetX RESET resetTargetX NOTIFY targetXChanged)
    Q_PROPERTY(int targetY READ targetY WRITE setTargetY RESET resetTargetY NOTIFY targetYChanged)
    Q_PROPERTY(int targetWidth READ targetWidth WRITE setTargetWidth RESET resetTargetWidth NOTIFY targetWidthChanged)
    Q_PROPERTY(int targetHeight READ targetHeight WRITE setTargetHeight RESET resetTargetHeight
               NOTIFY targetHeightChanged)

public:
    explicit QchScreenShot(QObject *parent = 0);
    ~QchScreenShot();

    QObject* target() const;
    void setTarget(QObject *obj);
    void resetTarget();

    QString fileName() const;
    void setFileName(const QString &name);

    bool overwriteExistingFile() const;
    void setOverwriteExistingFile(bool o);

    bool smooth() const;
    void setSmooth(bool s);

    int width() const;
    void setWidth(int w);
    void resetWidth();

    int height() const;
    void setHeight(int h);
    void resetHeight();

    int targetX() const;
    void setTargetX(int x);
    void resetTargetX();

    int targetY() const;
    void setTargetY(int y);
    void resetTargetY();

    int targetWidth() const;
    void setTargetWidth(int w);
    void resetTargetWidth();

    int targetHeight() const;
    void setTargetHeight(int h);
    void resetTargetHeight();



public slots:
    bool grab();

signals:
    void targetChanged();
    void fileNameChanged();
    void overwriteExistingFileChanged();
    void smoothChanged();
    void widthChanged();
    void heightChanged();
    void targetXChanged();
    void targetYChanged();
    void targetWidthChanged();
    void targetHeightChanged();

protected:
    QchScreenShot(QchScreenShotPrivate &dd, QObject *parent = 0);

    QScopedPointer<QchScreenShotPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QchScreenShot)

private:
    Q_DISABLE_COPY(QchScreenShot)
};

QML_DECLARE_TYPE(QchScreenShot)

#endif // QCHSCREENSHOT_H

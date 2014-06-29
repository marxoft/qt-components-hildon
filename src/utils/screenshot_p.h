/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SCREENSHOT_P_H
#define SCREENSHOT_P_H

#include <QObject>
#include <qdeclarative.h>

class QWidget;
class ScreenShotPrivate;

class ScreenShot : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QWidget *target READ target WRITE setTarget RESET resetTarget NOTIFY targetChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool overwriteExistingFile READ overwriteExistingFile WRITE setOverwriteExistingFile NOTIFY overwriteExistingFileChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PROPERTY(int width READ width WRITE setWidth RESET resetWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight RESET resetHeight NOTIFY heightChanged)
    Q_PROPERTY(int targetX READ targetX WRITE setTargetX RESET resetTargetX NOTIFY targetXChanged)
    Q_PROPERTY(int targetY READ targetY WRITE setTargetY RESET resetTargetY NOTIFY targetYChanged)
    Q_PROPERTY(int targetWidth READ targetWidth WRITE setTargetWidth RESET resetTargetWidth NOTIFY targetWidthChanged)
    Q_PROPERTY(int targetHeight READ targetHeight WRITE setTargetHeight RESET resetTargetHeight NOTIFY targetHeightChanged)

public:
    explicit ScreenShot(QObject *parent = 0);
    ~ScreenShot();

    QWidget* target() const;
    void setTarget(QWidget *target);
    void resetTarget();

    QString fileName() const;
    void setFileName(const QString &fileName);

    bool overwriteExistingFile() const;
    void setOverwriteExistingFile(bool overwrite);

    bool smooth() const;
    void setSmooth(bool smooth);

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

private:
    ScreenShot(ScreenShotPrivate &dd, QObject *parent = 0);

    QScopedPointer<ScreenShotPrivate> d_ptr;

    Q_DISABLE_COPY(ScreenShot)
    Q_DECLARE_PRIVATE(ScreenShot)
};

QML_DECLARE_TYPE(ScreenShot)

#endif // SCREENSHOT_P_H

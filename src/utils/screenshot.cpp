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

#include "screenshot_p.h"
#include "screenshot_p_p.h"
#include <QFile>
#include <QApplication>
#include <QDesktopWidget>

ScreenShot::ScreenShot(QObject *parent) :
    QObject(parent),
    d_ptr(new ScreenShotPrivate(this))
{
}

ScreenShot::ScreenShot(ScreenShotPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

ScreenShot::~ScreenShot() {}

QWidget* ScreenShot::target() const {
    Q_D(const ScreenShot);

    return d->target;
}

void ScreenShot::setTarget(QWidget *target) {
    if (target != this->target()) {
        Q_D(ScreenShot);
        d->target = target;
        emit targetChanged();
    }
}

void ScreenShot::resetTarget() {
    this->setTarget(0);
}

QString ScreenShot::fileName() const {
    Q_D(const ScreenShot);

    return d->fileName;
}

void ScreenShot::setFileName(const QString &fileName) {
    if (fileName != this->fileName()) {
        Q_D(ScreenShot);
        d->fileName = fileName;
        emit fileNameChanged();
    }
}

bool ScreenShot::overwriteExistingFile() const {
    Q_D(const ScreenShot);

    return d->overwrite;
}

void ScreenShot::setOverwriteExistingFile(bool overwrite) {
    if (overwrite != this->overwriteExistingFile()) {
        Q_D(ScreenShot);
        d->overwrite = overwrite;
        emit overwriteExistingFileChanged();
    }
}

bool ScreenShot::smooth() const {
    Q_D(const ScreenShot);

    return d->smooth;
}

void ScreenShot::setSmooth(bool smooth) {
    if (smooth != this->smooth()) {
        Q_D(ScreenShot);
        d->smooth = smooth;
        emit smoothChanged();
    }
}

int ScreenShot::width() const {
    Q_D(const ScreenShot);

    return d->width;
}

void ScreenShot::setWidth(int w) {
    if (w != this->width()) {
        Q_D(ScreenShot);
        d->width = w;
        emit widthChanged();
    }
}

void ScreenShot::resetWidth() {
    this->setWidth(-1);
}

int ScreenShot::height() const {
    Q_D(const ScreenShot);

    return d->height;
}

void ScreenShot::setHeight(int h) {
    if (h != this->height()) {
        Q_D(ScreenShot);
        d->height = h;
        emit heightChanged();
    }
}

void ScreenShot::resetHeight() {
    this->setHeight(-1);
}

int ScreenShot::targetX() const {
    Q_D(const ScreenShot);

    return d->targetX;
}

void ScreenShot::setTargetX(int x) {
    if (x != this->targetX()) {
        Q_D(ScreenShot);
        d->targetX = x;
        emit targetXChanged();
    }
}

void ScreenShot::resetTargetX() {
    this->setTargetX(0);
}

int ScreenShot::targetY() const {
    Q_D(const ScreenShot);

    return d->targetY;
}

void ScreenShot::setTargetY(int y) {
    if (y != this->targetY()) {
        Q_D(ScreenShot);
        d->targetY = y;
        emit targetYChanged();
    }
}

void ScreenShot::resetTargetY() {
    this->setTargetY(0);
}

int ScreenShot::targetWidth() const {
    Q_D(const ScreenShot);

    return d->targetWidth;
}

void ScreenShot::setTargetWidth(int w) {
    if (w != this->targetWidth()) {
        Q_D(ScreenShot);
        d->targetWidth = w;
        emit targetWidthChanged();
    }
}

void ScreenShot::resetTargetWidth() {
    this->setTargetWidth(-1);
}

int ScreenShot::targetHeight() const {
    Q_D(const ScreenShot);

    return d->targetHeight;
}

void ScreenShot::setTargetHeight(int h) {
    if (h != this->targetHeight()) {
        Q_D(ScreenShot);
        d->targetHeight = h;
        emit targetHeightChanged();
    }
}

void ScreenShot::resetTargetHeight() {
    this->setHeight(-1);
}

bool ScreenShot::grab() {
    Q_D(ScreenShot);

    d->pixmap = QPixmap();

    if (this->target()) {
        d->pixmap = QPixmap::grabWidget(this->target(),
                                    this->targetX(),
                                    this->targetY(),
                                    this->targetWidth(),
                                    this->targetHeight());
    }
    else {
        d->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),
                                        this->targetX(),
                                        this->targetY(),
                                        this->targetWidth(),
                                        this->targetHeight());
    }

    if (!d->pixmap.isNull()) {
        QString name = d->getFileName();

        if (!name.isEmpty()) {
            this->setFileName(name);

            if ((this->width() > 0) && (this->height() > 0)) {
                d->pixmap = d->pixmap.scaled(this->width(),
                                             this->height(),
                                             Qt::IgnoreAspectRatio,
                                             this->smooth() ? Qt::SmoothTransformation : Qt::FastTransformation);
            }

            return d->pixmap.save(name);
        }
    }

    return false;
}

ScreenShotPrivate::ScreenShotPrivate(ScreenShot *parent) :
    q_ptr(parent),
    target(0),
    overwrite(false),
    smooth(false),
    width(-1),
    height(-1),
    targetX(0),
    targetY(0),
    targetWidth(-1),
    targetHeight(-1)
{
}

ScreenShotPrivate::~ScreenShotPrivate() {}

QString ScreenShotPrivate::getFileName() {
    if (overwrite) {
        return fileName;
    }

    QString name = fileName.remove(QRegExp("\\(\\d+\\)(?=(\\.\\w+|$))"));

    if (!name.contains(QRegExp("\\.\\w{3,4}$"))) {
        name.append(".png");
    }

    int i = 1;

    while ((QFile::exists(name)) && (i < 100)) {
        int lastDot = fileName.lastIndexOf('.');
        name = QString("%1(%2)%3").arg(fileName.left(lastDot)).arg(i).arg(fileName.mid(lastDot));
        i++;
    }

    return name;
}

#include "moc_screenshot_p.cpp"

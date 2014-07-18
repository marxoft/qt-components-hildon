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

#ifndef LOADER_P_H
#define LOADER_P_H

#include <QObject>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class QDeclarativeComponent;
class QWidget;
class LoaderPrivate;

class Loader : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QObject* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QDeclarativeComponent* sourceComponent READ sourceComponent WRITE setSourceComponent RESET resetSourceComponent NOTIFY sourceChanged)
    Q_PROPERTY(QWidget* item READ item NOTIFY itemChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)

    Q_ENUMS(Status)

    Q_INTERFACES(QDeclarativeParserStatus)

public:
    enum Status {
        Null = 0,
        Ready,
        Loading,
        Error
    };

    explicit Loader(QObject *parent = 0);
    ~Loader();

    QUrl source() const;
    void setSource(const QUrl &url);

    QDeclarativeComponent* sourceComponent() const;
    void setSourceComponent(QDeclarativeComponent *component);
    void resetSourceComponent();

    Status status() const;

    qreal progress() const;

    QWidget* item() const;

signals:
    void parentChanged();
    void itemChanged();
    void sourceChanged();
    void statusChanged();
    void progressChanged();
    void loaded();

private:
    Loader(LoaderPrivate &dd, QObject *parent = 0);

    void classBegin();
    void componentComplete();

    bool event(QEvent *event);

    QScopedPointer<LoaderPrivate> d_ptr;

    Q_DISABLE_COPY(Loader)
    Q_DECLARE_PRIVATE(Loader)
    Q_PRIVATE_SLOT(d_func(), void _q_sourceLoaded())
};

QML_DECLARE_TYPE(Loader)

#endif // LOADER_P_H

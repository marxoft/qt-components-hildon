/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "settings_p.h"
#include <qcoreevent.h>
#include <qsettings.h>
#include <qpointer.h>
#include <qdebug.h>
#include <qhash.h>

// #define SETTINGS_DEBUG

static const int settingsWriteDelay = 500;

class SettingsPrivate
{
    Q_DECLARE_PUBLIC(Settings)

public:
    SettingsPrivate();

    QSettings *instance() const;

    void init();
    void reset();

    void load();
    void store();

    void _q_propertyChanged();

    Settings *q_ptr;
    int timerId;
    bool initialized;
    QString fileName;
    QString category;
    mutable QPointer<QSettings> settings;
    QHash<const char *, QVariant> changedProperties;
};

SettingsPrivate::SettingsPrivate()
    : q_ptr(0), timerId(0), initialized(false)
{
}

QSettings* SettingsPrivate::instance() const {
    if (!settings) {
        Settings *q = const_cast<Settings*>(q_func());
        settings = fileName.isEmpty() ? new QSettings(q)
                                      : new QSettings(fileName, QSettings::NativeFormat, q);

        if (!category.isEmpty()) {
            settings->beginGroup(category);
        }

        if (initialized) {
            q->d_func()->load();
        }
    }

    return settings;
}

void SettingsPrivate::init() {
    if (!initialized) {
#ifdef SETTINGS_DEBUG
        qDebug() << "Settings: stored at" << instance()->fileName();
#endif
        load();
        initialized = true;
    }
}

void SettingsPrivate::reset() {
    if (initialized && settings && !changedProperties.isEmpty()) {
        store();
    }

    delete settings;
}

void SettingsPrivate::load() {
    Q_Q(Settings);

    const QMetaObject *mo = q->metaObject();
    const int offset = mo->propertyOffset();
    const int count = mo->propertyCount();

    for (int i = offset; i < count; ++i) {
        QMetaProperty property = mo->property(i);

        const QVariant previousValue = property.read(q);
        const QVariant currentValue = instance()->value(property.name(), previousValue);

        if (!currentValue.isNull() && (!previousValue.isValid()
                || (currentValue.canConvert(previousValue.type()) && previousValue != currentValue))) {
            property.write(q, currentValue);
#ifdef SETTINGS_DEBUG
            qDebug() << "Settings: load" << property.name() << "setting:" << currentValue << "default:" << previousValue;
#endif
        }

        // ensure that a non-existent setting gets written
        // even if the property wouldn't change later
        if (!instance()->contains(property.name())) {
            _q_propertyChanged();
        }

        // setup change notifications on first load
        if (!initialized && property.hasNotifySignal()) {
            static const int propertyChangedIndex = mo->indexOfSlot("_q_propertyChanged()");
            QMetaObject::connect(q, property.notifySignalIndex(), q, propertyChangedIndex);
        }
    }
}

void SettingsPrivate::store() {
    QHash<const char *, QVariant>::iterator it = changedProperties.begin();

    while (it != changedProperties.end()) {
        instance()->setValue(it.key(), it.value());
#ifdef SETTINGS_DEBUG
        qDebug() << "Settings: store" << it.key() << ":" << it.value();
#endif
        it = changedProperties.erase(it);
    }
}

void SettingsPrivate::_q_propertyChanged() {
    Q_Q(Settings);

    const QMetaObject *mo = q->metaObject();
    const int offset = mo->propertyOffset();
    const int count = mo->propertyCount();

    for (int i = offset; i < count; ++i) {
        const QMetaProperty &property = mo->property(i);
        changedProperties.insert(property.name(), property.read(q));
#ifdef SETTINGS_DEBUG
        qDebug() << "Settings: cache" << property.name() << ":" << property.read(q);
#endif
    }

    if (timerId != 0) {
        q->killTimer(timerId);
    }

    timerId = q->startTimer(settingsWriteDelay);
}

/*!
    \class Settings
    \ingroup org-hildon-settings
*/

Settings::Settings(QObject *parent)
    : QObject(parent), d_ptr(new SettingsPrivate)
{
    Q_D(Settings);
    d->q_ptr = this;
}

Settings::~Settings()
{
    Q_D(Settings);
    d->reset(); // flush pending changes
}

QString Settings::fileName() const {
    Q_D(const Settings);
    
    return d->fileName;
}

void Settings::setFileName(const QString &fileName) {
    Q_D(Settings);
    
    if (d->fileName != fileName) {
        d->reset();
        d->fileName = fileName;
        
        if (d->initialized) {
            d->load();
        }
    }
}

QString Settings::category() const {
    Q_D(const Settings);

    return d->category;
}

void Settings::setCategory(const QString &category) {
    Q_D(Settings);

    if (d->category != category) {
        d->reset();
        d->category = category;

        if (d->initialized) {
            d->load();
        }
    }
}

void Settings::classBegin() {}

void Settings::componentComplete() {
    Q_D(Settings);

    d->init();
}

void Settings::timerEvent(QTimerEvent *event) {
    Q_D(Settings);

    if (event->timerId() == d->timerId) {
        if (d->changedProperties.isEmpty()) {
            killTimer(d->timerId);
            d->timerId = 0;
        }
        else {
            d->store();
        }
    }

    QObject::timerEvent(event);
}

#include "moc_settings_p.cpp"

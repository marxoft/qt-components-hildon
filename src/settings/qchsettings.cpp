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

#include "qchsettings.h"
#include <qcoreevent.h>
#include <qsettings.h>
#include <qpointer.h>
#include <qdebug.h>
#include <qhash.h>

// #define SETTINGS_DEBUG

static const int settingsWriteDelay = 500;

class QchSettingsPrivate
{
    Q_DECLARE_PUBLIC(QchSettings)

public:
    QchSettingsPrivate();

    QSettings *instance() const;

    void init();
    void reset();

    void load();
    void store();

    void _q_propertyChanged();

    QchSettings *q_ptr;
    int timerId;
    bool initialized;
    QString fileName;
    QString category;
    mutable QPointer<QSettings> settings;
    QHash<const char *, QVariant> changedProperties;
};

QchSettingsPrivate::QchSettingsPrivate()
    : q_ptr(0), timerId(0), initialized(false)
{
}

QSettings* QchSettingsPrivate::instance() const {
    if (!settings) {
        QchSettings *q = const_cast<QchSettings*>(q_func());
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

void QchSettingsPrivate::init() {
    if (!initialized) {
#ifdef SETTINGS_DEBUG
        qDebug() << "QchSettings: stored at" << instance()->fileName();
#endif
        load();
        initialized = true;
    }
}

void QchSettingsPrivate::reset() {
    if (initialized && settings && !changedProperties.isEmpty()) {
        store();
    }

    delete settings;
}

void QchSettingsPrivate::load() {
    Q_Q(QchSettings);

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
            qDebug() << "QchSettings: load" << property.name() << "setting:" << currentValue << "default:" << previousValue;
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

void QchSettingsPrivate::store() {
    QHash<const char *, QVariant>::iterator it = changedProperties.begin();

    while (it != changedProperties.end()) {
        instance()->setValue(it.key(), it.value());
#ifdef SETTINGS_DEBUG
        qDebug() << "QchSettings: store" << it.key() << ":" << it.value();
#endif
        it = changedProperties.erase(it);
    }
}

void QchSettingsPrivate::_q_propertyChanged() {
    Q_Q(QchSettings);

    const QMetaObject *mo = q->metaObject();
    const int offset = mo->propertyOffset();
    const int count = mo->propertyCount();

    for (int i = offset; i < count; ++i) {
        const QMetaProperty &property = mo->property(i);
        changedProperties.insert(property.name(), property.read(q));
#ifdef SETTINGS_DEBUG
        qDebug() << "QchSettings: cache" << property.name() << ":" << property.read(q);
#endif
    }

    if (timerId != 0) {
        q->killTimer(timerId);
    }

    timerId = q->startTimer(settingsWriteDelay);
}

/*!
    \class Settings
    \brief Exposes the QSettings API to QML.
    
    \ingroup settings
    
    Each Settings instance can have a \link fileName\endlink and a \link category\endlink.
    Properties declared in QML will be automatically (re)stored.
    
    \include settings.qml
*/
QchSettings::QchSettings(QObject *parent)
    : QObject(parent), d_ptr(new QchSettingsPrivate)
{
    Q_D(QchSettings);
    d->q_ptr = this;
}

QchSettings::~QchSettings()
{
    Q_D(QchSettings);
    d->reset(); // flush pending changes
}

/*!
    \brief The location of the file where the settings will be stored.
    
    By default, this property is an empty string, meaning that the location will be determined by 
    QApplication::organizationName() and QApplication::applicationName().
*/
QString QchSettings::fileName() const {
    Q_D(const QchSettings);
    
    return d->fileName;
}

void QchSettings::setFileName(const QString &fileName) {
    Q_D(QchSettings);
    
    if (d->fileName != fileName) {
        d->reset();
        d->fileName = fileName;
        
        if (d->initialized) {
            d->load();
        }
    }
}

/*!
    \brief The category under which settings will be (re)stored.
*/
QString QchSettings::category() const {
    Q_D(const QchSettings);

    return d->category;
}

void QchSettings::setCategory(const QString &category) {
    Q_D(QchSettings);

    if (d->category != category) {
        d->reset();
        d->category = category;

        if (d->initialized) {
            d->load();
        }
    }
}

void QchSettings::classBegin() {}

void QchSettings::componentComplete() {
    Q_D(QchSettings);

    d->init();
}

void QchSettings::timerEvent(QTimerEvent *event) {
    Q_D(QchSettings);

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

#include "moc_qchsettings.cpp"

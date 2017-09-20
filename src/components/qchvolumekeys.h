/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

#ifndef QCHVOLUMEKEYS_H
#define QCHVOLUMEKEYS_H

#include <QObject>
#include <qdeclarative.h>

class QchVolumeKeys : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit QchVolumeKeys(QObject *parent = 0);
    ~QchVolumeKeys();

    bool isEnabled() const;

    static QchVolumeKeys* qmlAttachedProperties(QObject *obj);

public Q_SLOTS:
    void setEnabled(bool enabled);

Q_SIGNALS:
    void enabledChanged(bool enabled);

private:
    virtual bool eventFilter(QObject *obj, QEvent *event);

    bool m_enabled;
    bool m_complete;

    Q_DISABLE_COPY(QchVolumeKeys)
};

QML_DECLARE_TYPE(QchVolumeKeys)
QML_DECLARE_TYPEINFO(QchVolumeKeys, QML_HAS_ATTACHED_PROPERTIES)

#endif // QCHVOLUMEKEYS_H

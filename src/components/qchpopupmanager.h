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

#ifndef QCHPOPUPMANAGER_H
#define QCHPOPUPMANAGER_H

#include <QObject>
#include <qdeclarative.h>

class QchPopupManagerPrivate;

class QchPopupManager : public QObject
{
    Q_OBJECT

public:
    explicit QchPopupManager(QDeclarativeEngine *engine);
    ~QchPopupManager();
    
public Q_SLOTS:
    QObject* open(const QVariant &popup, QObject *parent = 0, const QVariantMap &properties = QVariantMap());

private:
    QScopedPointer<QchPopupManagerPrivate> d_ptr;
    
    Q_PRIVATE_SLOT(d_func(), void _q_onPopupStatusChanged());
    
    Q_DECLARE_PRIVATE(QchPopupManager)
    Q_DISABLE_COPY(QchPopupManager)
};

QML_DECLARE_TYPE(QchPopupManager)

#endif // QCHPOPUPMANAGER_H

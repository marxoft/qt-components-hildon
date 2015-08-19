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

#include "qchplugin.h"
#include "qchcloseevent.h"
#include "qchhomescreenwidget.h"
#include "qchnotification.h"

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.desktop"));
    
    qRegisterMetaType<QchCloseEvent*>("QchCloseEvent*");
    
    qmlRegisterType<QchHomescreenWidget>(uri, 1, 0, "HomescreenWidget");
    qmlRegisterType<QchNotification>(uri, 1, 0, "Notification");
    
    qmlRegisterUncreatableType<QchCloseEvent>(uri, 1, 0, "CloseEvent", "");
}

Q_EXPORT_PLUGIN2(qchdesktop, QchPlugin)

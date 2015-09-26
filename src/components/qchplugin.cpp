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
#include "qchaction.h"
#include "qchcloseevent.h"
#include "qchdialog.h"
#include "qchexclusivegroup.h"
#include "qchfiledialog.h"
#include "qchimageproviders.h"
#include "qchinformationbox.h"
#include "qchmenu.h"
#include "qchmenubar.h"
#include "qchmenuitem.h"
#include "qchnavigationmode.h"
#include "qchscreen.h"
#include "qchstyle.h"
#include "qchvaluelayout.h"
#include "qchwindow.h"
#include "qchwindowstack.h"
#include "qchwindowstatus.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void QchPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));
    
    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);
    
    if (!engine->imageProvider("theme")) {
        engine->addImageProvider("icon", new QchIconImageProvider);
        engine->addImageProvider("theme", new QchThemeImageProvider);
        
        QDeclarativeContext *context = engine->rootContext();
        context->setContextProperty("platformStyle", new QchStyle(engine));
        context->setContextProperty("screen", new QchScreen(engine));
    }   
}

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));
    
    qRegisterMetaType<QchCloseEvent*>("QchCloseEvent*");
    
    qmlRegisterType<QchAction>(uri, 1, 0, "Action");
    qmlRegisterType<QchDialog>(uri, 1, 0, "Dialog");
    qmlRegisterType<QchExclusiveGroup>(uri, 1, 0, "ExclusiveGroup");
    qmlRegisterType<QchFileDialog>(uri, 1, 0, "FileDialog");
    qmlRegisterType<QchInformationBox>(uri, 1, 0, "InformationBox");
    qmlRegisterType<QchMenu>(uri, 1, 0, "Menu");
    qmlRegisterType<QchMenuBar>(uri, 1, 0, "MenuBar");
    qmlRegisterType<QchMenuItem>(uri, 1, 0, "MenuItem");
    qmlRegisterType<QchWindow>(uri, 1, 0, "Window");
    qmlRegisterType<QchWindowStack>(uri, 1, 0, "WindowStack");
    
    qmlRegisterUncreatableType<QchCloseEvent>(uri, 1, 0, "CloseEvent", "");
    qmlRegisterUncreatableType<QchDialogStatus>(uri, 1, 0, "DialogStatus", "");
    qmlRegisterUncreatableType<QchNavigationMode>(uri, 1, 0, "NavigationMode", "");
    qmlRegisterUncreatableType<QchValueLayout>(uri, 1, 0, "ValueLayout", "");
    qmlRegisterUncreatableType<QchWindowStatus>(uri, 1, 0, "WindowStatus", "");
}

Q_EXPORT_PLUGIN2(qchcomponents, QchPlugin)

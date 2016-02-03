/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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
#include "qchdatetime.h"
#include "qchdialog.h"
#include "qchexclusivegroup.h"
#include "qchfiledialog.h"
#include "qchfontmetrics.h"
#include "qchimageproviders.h"
#include "qchinformationbox.h"
#include "qchinsertpolicy.h"
#include "qchmenu.h"
#include "qchmenubar.h"
#include "qchmenuitem.h"
#include "qchnavigationmode.h"
#include "qchscreen.h"
#include "qchsortfilterproxymodel.h"
#include "qchstyle.h"
#include "qchtextmetrics.h"
#include "qchtheme.h"
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
        context->setContextProperty("dateTime", new QchDateTime(engine));
        context->setContextProperty("platformStyle", new QchStyle(engine));
        context->setContextProperty("screen", new QchScreen(engine));
        context->setContextProperty("theme", new QchTheme(engine));
    }   
}

void QchPlugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));
    
    qRegisterMetaType<QchCloseEvent*>("QchCloseEvent*");
    
    qmlRegisterType<QchAction>(uri, 1, 0, "Action");
    qmlRegisterType<QchDialog>(uri, 1, 0, "Dialog");
    qmlRegisterType<QchExclusiveGroup>(uri, 1, 0, "ExclusiveGroup");
    qmlRegisterType<QchFileDialog>(uri, 1, 0, "FileDialog");
    qmlRegisterType<QchFontMetrics>(uri, 1, 0, "FontMetrics");
    qmlRegisterType<QchInformationBox>(uri, 1, 0, "InformationBox");
    qmlRegisterType<QchMenu>(uri, 1, 0, "Menu");
    qmlRegisterType<QchMenuBar>(uri, 1, 0, "MenuBar");
    qmlRegisterType<QchMenuItem>(uri, 1, 0, "MenuItem");
    qmlRegisterType<QchSortFilterProxyModel>(uri, 1, 0, "SortFilterProxyModel");
    qmlRegisterType<QchTextMetrics>(uri, 1, 0, "TextMetrics");
    qmlRegisterType<QchWindow>(uri, 1, 0, "Window");
    qmlRegisterType<QchWindowStack>(uri, 1, 0, "WindowStack");
    
    qmlRegisterUncreatableType<QchCloseEvent>(uri, 1, 0, "CloseEvent", "");
    qmlRegisterUncreatableType<QchDialogStatus>(uri, 1, 0, "DialogStatus", "");
    qmlRegisterUncreatableType<QchInsertPolicy>(uri, 1, 0, "InsertPolicy", "");
    qmlRegisterUncreatableType<QchNavigationMode>(uri, 1, 0, "NavigationMode", "");
    qmlRegisterUncreatableType<QchValueLayout>(uri, 1, 0, "ValueLayout", "");
    qmlRegisterUncreatableType<QchWindowStatus>(uri, 1, 0, "WindowStatus", "");
}

Q_EXPORT_PLUGIN2(qchcomponents, QchPlugin)

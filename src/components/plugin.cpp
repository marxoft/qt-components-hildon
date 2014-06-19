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

#include "plugin_p.h"
#include "action_p.h"
#include "actiongroup_p.h"
#include "action_p.h"
#include "anchors_p_p.h"
#include "button_p.h"
#include "buttonrow_p.h"
#include "checkbox_p.h"
#include "column_p.h"
#include "dateselector_p.h"
#include "dialog_p.h"
#include "editbar_p.h"
#include "filedialog_p.h"
#include "flickable_p.h"
#include "flow_p.h"
#include "grid_p.h"
#include "informationbox_p.h"
#include "item_p.h"
//#include "itemdelegate_p.h"
//#include "itemdelegatetext_p.h"
#include "label_p.h"
#include "listselector_p.h"
#include "listview_p.h"
#include "loader_p.h"
#include "menu_p.h"
#include "mousearea_p.h"
#include "platformstyle_p.h"
#include "progressbar_p.h"
#include "radiobutton_p.h"
#include "row_p.h"
#include "screen_p.h"
#include "separator_p.h"
#include "slider_p.h"
#include "spinbox_p.h"
#include "tabgroup_p.h"
#include "text_p.h"
#include "textedit_p.h"
#include "textfield_p.h"
#include "timer_p.h"
#include "timeselector_p.h"
#include "toolbar_p.h"
#include "toolbutton_p.h"
#include "valuebutton_p.h"
#include "valueselector_p.h"
#include "window_p.h"
#include "windowstack_p_p.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

void Plugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);

    if (engine->rootContext()->contextProperty("platformStyle").isNull()) {
        engine->rootContext()->setContextProperty("platformStyle", new PlatformStyle);
        engine->rootContext()->setContextProperty("screen", Screen::instance());
        engine->rootContext()->setContextProperty("windowStack", WindowStack::instance());

        qmlRegisterUncreatableType<PlatformStyle>(uri, 1, 0, "PlatformStyle", "");
        qmlRegisterUncreatableType<Screen>(uri, 1, 0, "Screen", "");
        qmlRegisterUncreatableType<WindowStack>(uri, 1, 0, "WindowStack", "");
    }
}

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));

    qRegisterMetaType<AnchorLine>("AnchorLine");

    qmlRegisterUncreatableType<QWidget>(uri, 1, 0, "Widget", "");

    qmlRegisterType<Action>(uri, 1, 0, "Action");
    qmlRegisterType<ActionGroup>(uri, 1, 0, "ActionGroup");
    qmlRegisterType<Anchors>(uri, 1, 0, "Anchors");
    qmlRegisterType<Button>(uri, 1, 0, "Button");
    qmlRegisterType<ButtonRow>(uri, 1, 0, "ButtonRow");
    qmlRegisterType<CheckBox>(uri, 1, 0, "CheckBox");
    qmlRegisterType<Column>(uri, 1, 0, "Column");
    qmlRegisterType<DateSelector>(uri, 1, 0, "DateSelector");
    qmlRegisterType<Dialog>(uri, 1, 0, "Dialog");
    qmlRegisterType<EditBar>(uri, 1, 0, "EditBar");
    qmlRegisterType<FileDialog>(uri, 1, 0, "FileDialog");
    qmlRegisterType<Flickable>(uri, 1, 0, "Flickable");
    qmlRegisterType<Flow>(uri, 1, 0, "Flow");
    qmlRegisterType<Grid>(uri, 1, 0, "Grid");
    qmlRegisterType<InformationBox>(uri, 1, 0, "InformationBox");
    qmlRegisterType<Item>(uri, 1, 0, "Item");
//    qmlRegisterType<ItemDelegate>(uri, 1, 0, "ItemDelegate");
//    qmlRegisterType<ItemDelegateText>(uri, 1, 0, "ItemDelegateText");
    qmlRegisterType<Label>(uri, 1, 0, "Label");
    qmlRegisterType<ListSelector>(uri, 1, 0, "ListSelector");
    qmlRegisterType<ListView>(uri, 1, 0, "ListView");
    qmlRegisterType<Loader>(uri, 1, 0, "Loader");
    qmlRegisterType<Menu>(uri, 1, 0, "Menu");
    qmlRegisterType<MouseArea>(uri, 1, 0, "MouseArea");
    qmlRegisterType<MouseDrag>(uri, 1, 0, "Drag");
    qmlRegisterType<ProgressBar>(uri, 1, 0, "ProgressBar");
//    qmlRegisterType<QDeclarativeComponent>(uri, 1, 0, "Component");
    qmlRegisterType<QDoubleValidator>(uri, 1, 0, "DoubleValidator");
    qmlRegisterType<QIntValidator>(uri, 1, 0, "IntValidator");
    qmlRegisterType<QRegExpValidator>(uri, 1, 0, "RegExpValidator");
    qmlRegisterType<QObject>(uri, 1, 0, "QtObject");
    qmlRegisterType<RadioButton>(uri, 1, 0, "RadioButton");
    qmlRegisterType<Row>(uri, 1, 0, "Row");
    qmlRegisterType<Separator>(uri, 1, 0, "Separator");
    qmlRegisterType<Slider>(uri, 1, 0, "Slider");
    qmlRegisterType<SpinBox>(uri, 1, 0, "SpinBox");
    qmlRegisterType<TabGroup>(uri, 1, 0, "TabGroup");
    qmlRegisterType<Text>(uri, 1, 0, "Text");
    qmlRegisterType<TextEdit>(uri, 1, 0, "TextEdit");
    qmlRegisterType<TextField>(uri, 1, 0, "TextField");
    qmlRegisterType<Timer>(uri, 1, 0, "Timer");
    qmlRegisterType<TimeSelector>(uri, 1, 0, "TimeSelector");
    qmlRegisterType<ToolBar>(uri, 1, 0, "ToolBar");
    qmlRegisterType<ToolButton>(uri, 1, 0, "ToolButton");
    qmlRegisterType<ValueButton>(uri, 1, 0, "ValueButton");
    qmlRegisterType<ValueSelector>(uri, 1, 0, "ValueSelector");
    qmlRegisterType<Window>(uri, 1, 0, "Window");
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildoncomponents, Plugin)

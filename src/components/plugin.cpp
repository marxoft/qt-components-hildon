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
#include "borderimage_p.h"
#include "button_p.h"
#include "buttonrow_p.h"
#include "checkbox_p.h"
#include "column_p.h"
#include "dateselector_p.h"
#include "dialog_p.h"
#include "doublespinbox_p.h"
#include "editbar_p.h"
#include "filesystemmodel_p.h"
#include "flickable_p.h"
#include "flow_p.h"
#include "grid_p.h"
#include "headerview_p.h"
#include "image_p.h"
#include "imageborder_p.h"
#include "imageproviders_p.h"
#include "informationbox_p.h"
#include "item_p.h"
#include "itemaction_p.h"
#include "keys_p.h"
#include "label_p.h"
//#include "listelement_p.h"
#include "listitem_p.h"
#include "listitemborderimage_p.h"
#include "listitemimage_p.h"
#include "listitemlabel_p.h"
#include "listitemmousearea_p.h"
#include "listitemprogressbar_p.h"
#include "listitemrectangle_p.h"
#include "listitemtext_p.h"
#include "listmodel_p.h"
#include "listselector_p.h"
#include "listview_p.h"
#include "loader_p.h"
#include "menu_p.h"
#include "modelindex_p.h"
#include "mousearea_p.h"
#include "multilistselector_p.h"
#include "page_p.h"
#include "pagestack_p.h"
#include "platformstyle_p.h"
#include "progressbar_p.h"
#include "qdeclarativebind_p.h"
#include "qdeclarativeconnections_p.h"
#include "qdeclarativetimer_p.h"
#include "radiobutton_p.h"
#include "rectangle_p.h"
#include "repeater_p.h"
#include "row_p.h"
#include "screen_p.h"
#include "separator_p.h"
#include "slider_p.h"
#include "spinbox_p.h"
#include "sortfilterproxymodel_p.h"
#include "style_p.h"
#include "tabbar_p.h"
#include "tabgroup_p.h"
#include "tableview_p.h"
#include "text_p.h"
#include "textbrowser_p.h"
#include "textedit_p.h"
#include "textfield_p.h"
#include "timeselector_p.h"
#include "toolbar_p.h"
#include "toolbutton_p.h"
#include "valuebutton_p.h"
#include "valueselector_p.h"
#include "window_p.h"
#include "zoomarea_p.h"
#include "private/qdeclarativecomponent_p.h"
#include <QDeclarativeContext>

void Plugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));

    QDeclarativeExtensionPlugin::initializeEngine(engine, uri);

    if (engine->rootContext()->contextProperty("platformStyle").isNull()) {
        engine->rootContext()->setContextProperty("platformStyle", new PlatformStyle(engine));
        engine->rootContext()->setContextProperty("screen", new Screen(engine));
        engine->rootContext()->setContextProperty("QModelIndex", new ModelIndex(engine));

        engine->addImageProvider("theme", new ThemeImageProvider);

        engine->setContextForObject(Screen::instance(), engine->rootContext());

        qmlRegisterUncreatableType<PlatformStyle>(uri, 1, 0, "PlatformStyle", "");
        qmlRegisterUncreatableType<Screen>(uri, 1, 0, "Screen", "");
    }
}

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("org.hildon.components"));

    qRegisterMetaType<AnchorLine>("AnchorLine");
    qRegisterMetaType<KeyEvent*>("KeyEvent*");

    qmlRegisterUncreatableType<Anchors>(uri, 1, 0, "Anchors", "");
    qmlRegisterUncreatableType<Border>(uri, 1, 0, "Border", "");
    qmlRegisterUncreatableType<ImageBorder>(uri, 1, 0, "ImageBorder", "");
    qmlRegisterUncreatableType<Keys>(uri, 1, 0, "Keys", "");
    qmlRegisterUncreatableType<KeyEvent>(uri, 1, 0, "KeyEvent", "");
    qmlRegisterUncreatableType<MouseDrag>(uri, 1, 0, "Drag", "");
    qmlRegisterUncreatableType<PageStack>(uri, 1, 0, "PageStack", "");
    qmlRegisterUncreatableType<QWidget>(uri, 1, 0, "Widget", "");
    qmlRegisterUncreatableType<QAbstractButton>(uri, 1, 0, "AbstractButton", "");
    qmlRegisterUncreatableType<QHeaderView>(uri, 1, 0, "QHeaderView", "");

    qmlRegisterType<Action>(uri, 1, 0, "Action");
    qmlRegisterType<ActionGroup>(uri, 1, 0, "ActionGroup");
    qmlRegisterType<BorderImage>(uri, 1, 0, "BorderImage");
    qmlRegisterType<Button>(uri, 1, 0, "Button");
    qmlRegisterType<ButtonRow>(uri, 1, 0, "ButtonRow");
    qmlRegisterType<CheckBox>(uri, 1, 0, "CheckBox");
    qmlRegisterType<Column>(uri, 1, 0, "Column");
    qmlRegisterType<DateSelector>(uri, 1, 0, "DateSelector");
    qmlRegisterType<Dialog>(uri, 1, 0, "Dialog");
    qmlRegisterType<DoubleSpinBox>(uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType<EditBar>(uri, 1, 0, "EditBar");
    qmlRegisterType<FileSystemModel>(uri, 1, 0, "FileSystemModel");
    qmlRegisterType<Flickable>(uri, 1, 0, "Flickable");
    qmlRegisterType<Flow>(uri, 1, 0, "Flow");
    qmlRegisterType<Gradient>(uri, 1, 0, "Gradient");
    qmlRegisterType<GradientStop>(uri, 1, 0, "GradientStop");
    qmlRegisterType<Grid>(uri, 1, 0, "Grid");
    qmlRegisterType<HeaderSection>(uri, 1, 0, "HeaderSection");
    qmlRegisterType<HeaderView>(uri, 1, 0, "HeaderView");
    qmlRegisterType<Image>(uri, 1, 0, "Image");
    qmlRegisterType<InformationBox>(uri, 1, 0, "InformationBox");
    qmlRegisterType<Item>(uri, 1, 0, "Item");
    qmlRegisterType<ItemAction>(uri, 1, 0, "ItemAction");
    qmlRegisterType<Label>(uri, 1, 0, "Label");
    qmlRegisterType<ListItem>(uri, 1, 0, "ListItem");
    qmlRegisterType<ListItemBorderImage>(uri, 1, 0, "ListItemBorderImage");
    qmlRegisterType<ListItemImage>(uri, 1, 0, "ListItemImage");
    qmlRegisterType<ListItemLabel>(uri, 1, 0, "ListItemLabel");
    qmlRegisterType<ListItemMouseArea>(uri, 1, 0, "ListItemMouseArea");
    qmlRegisterType<ListItemProgressBar>(uri, 1, 0, "ListItemProgressBar");
    qmlRegisterType<ListItemRectangle>(uri, 1, 0, "ListItemRectangle");
    qmlRegisterType<ListItemText>(uri, 1, 0, "ListItemText");
    qmlRegisterType<ListModel>(uri, 1, 0, "ListModel");
    qmlRegisterType<ListSelector>(uri, 1, 0, "ListSelector");
    qmlRegisterType<ListView>(uri, 1, 0, "ListView");
    qmlRegisterType<Loader>(uri, 1, 0, "Loader");
    qmlRegisterType<Menu>(uri, 1, 0, "Menu");
    qmlRegisterType<MouseArea>(uri, 1, 0, "MouseArea");
    qmlRegisterType<MultiListSelector>(uri, 1, 0, "MultiListSelector");
    qmlRegisterType<Page>(uri, 1, 0, "Page");
    qmlRegisterType<ProgressBar>(uri, 1, 0, "ProgressBar");
    qmlRegisterType<QDeclarativeBind>(uri, 1, 0, "Binding");
    qmlRegisterType<QDeclarativeComponent>(uri, 1, 0, "Component");
    qmlRegisterType<QDeclarativeTimer>(uri, 1, 0, "Timer");
    qmlRegisterType<QDoubleValidator>(uri, 1, 0, "DoubleValidator");
    qmlRegisterType<QIntValidator>(uri, 1, 0, "IntValidator");
    qmlRegisterType<QRegExpValidator>(uri, 1, 0, "RegExpValidator");
    qmlRegisterType<QObject>(uri, 1, 0, "QtObject");
    qmlRegisterType<RadioButton>(uri, 1, 0, "RadioButton");
    qmlRegisterType<Rectangle>(uri, 1, 0, "Rectangle");
    qmlRegisterType<Repeater>(uri, 1, 0, "Repeater");
    qmlRegisterType<Row>(uri, 1, 0, "Row");
    qmlRegisterType<Separator>(uri, 1, 0, "MenuSeparator");
    qmlRegisterType<Slider>(uri, 1, 0, "Slider");
    qmlRegisterType<SortFilterProxyModel>(uri, 1, 0, "SortFilterProxyModel");
    qmlRegisterType<SpinBox>(uri, 1, 0, "SpinBox");
    qmlRegisterType<Style>(uri, 1, 0, "Style");
    qmlRegisterType<TabBar>(uri, 1, 0, "TabBar");
    qmlRegisterType<TabButton>(uri, 1, 0, "TabButton");
    qmlRegisterType<TabGroup>(uri, 1, 0, "TabGroup");
    qmlRegisterType<TableView>(uri, 1, 0, "TableView");
    qmlRegisterType<Text>(uri, 1, 0, "Text");
    qmlRegisterType<TextBrowser>(uri, 1, 0, "TextBrowser");
    qmlRegisterType<TextEdit>(uri, 1, 0, "TextEdit");
    qmlRegisterType<TextField>(uri, 1, 0, "TextField");
    qmlRegisterType<TimeSelector>(uri, 1, 0, "TimeSelector");
    qmlRegisterType<ToolBar>(uri, 1, 0, "ToolBar");
    qmlRegisterType<ToolButton>(uri, 1, 0, "ToolButton");
    qmlRegisterType<ValueButton>(uri, 1, 0, "ValueButton");
    qmlRegisterType<ValueSelector>(uri, 1, 0, "ValueSelector");
    qmlRegisterType<Window>(uri, 1, 0, "Window");
    qmlRegisterType<ZoomArea>(uri, 1, 0, "ZoomArea");
    
    //qmlRegisterCustomType<ListElement>(uri, 1, 0, "ListElement", new ListElementParser);
    qmlRegisterCustomType<QDeclarativeConnections>(uri, 1, 0, "Connections", new QDeclarativeConnectionsParser);
}

#include "moc_plugin_p.cpp"

Q_EXPORT_PLUGIN2(hildoncomponents, Plugin)

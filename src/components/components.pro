TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus maemo5 script

TARGET = qchcomponents

HEADERS += \
    qchaction.h \
    qchcloseevent.h \
    qchdatetime.h \
    qchdeclarativelistmodelproxy.h \
    qchdialog.h \
    qchdialogstatus.h \
    qcheventtypes.h \
    qchexclusivegroup.h \
    qchfiledialog.h \
    qchfontmetrics.h \
    qchgraphicsview.h \
    qchimageproviders.h \
    qchinformationbox.h \
    qchinputmode.h \
    qchinsertpolicy.h \
    qchitemaction.h \
    qchmenu.h \
    qchmenubar.h \
    qchmenuitem.h \
    qchnavigationmode.h \
    qchscreen.h \
    qchsortfilterproxymodel.h \
    qchstandardbutton.h \
    qchstyle.h \
    qchtextmetrics.h \
    qchtheme.h \
    qchvaluelayout.h \
    qchvariantlistmodel.h \
    qchwindow.h \
    qchwindowstack.h \
    qchwindowstatus.h \
    qchplugin.h

SOURCES += \
    qchaction.cpp \
    qchdatetime.cpp \
    qchdeclarativelistmodelproxy.cpp \
    qchdialog.cpp \
    qchexclusivegroup.cpp \
    qchfiledialog.cpp \
    qchfontmetrics.cpp \
    qchgraphicsview.cpp \
    qchimageproviders.cpp \
    qchinformationbox.cpp \
    qchitemaction.cpp \
    qchmenu.cpp \
    qchmenubar.cpp \
    qchmenuitem.cpp \
    qchscreen.cpp \
    qchsortfilterproxymodel.cpp \
    qchstyle.cpp \
    qchtextmetrics.cpp \
    qchtheme.cpp \
    qchvariantlistmodel.cpp \
    qchwindow.cpp \
    qchwindowstack.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir \
    qml/AbstractButton.qml \
    qml/AbstractPickSelector.qml \
    qml/AcceptButtonStyle.qml \
    qml/AcceptThumbButtonStyle.qml \
    qml/AppletCloseButtonStyle.qml \
    qml/AppletConfigureButtonStyle.qml \
    qml/ApplicationShortcutButtonStyle.qml \
    qml/ApplicationWindow.qml \
    qml/BiDirectionalSlider.qml \
    qml/BiDirectionalSliderStyle.qml \
    qml/Button.qml \
    qml/ButtonRow.qml \
    qml/ButtonStyle.qml \
    qml/CheckBox.qml \
    qml/CheckBoxStyle.qml \
    qml/ColumnLayout.qml \
    qml/ComboBox.qml \
    qml/ComboBoxStyle.qml \
    qml/DatePickSelector.qml \
    qml/DialogButtonBox.qml \
    qml/DialogButtonStyle.qml \
    qml/DoubleSpinBox.qml \
    qml/EditBar.qml \
    qml/EditButtonStyle.qml \
    qml/Flickable.qml \
    qml/FlickableStyle.qml \
    qml/FlowLayout.qml \
    qml/GridLayout.qml \
    qml/InputDialog.qml \
    qml/Label.qml \
    qml/LabelStyle.qml \
    qml/ListItem.qml \
    qml/ListItemStyle.qml \
    qml/ListPickSelector.qml \
    qml/ListView.qml \
    qml/ListViewStyle.qml \
    qml/MessageBox.qml \
    qml/MultiListPickSelector.qml \
    qml/OssoCheckBoxStyle.qml \
    qml/OssoComboBoxStyle.qml \
    qml/OssoFlickableStyle.qml \
    qml/OssoListItemStyle.qml \
    qml/OssoListViewStyle.qml \
    qml/OssoRadioButtonStyle.qml \
    qml/OssoTextAreaStyle.qml \
    qml/OssoTextFieldStyle.qml \
    qml/PortraitButtonStyle.qml \
    qml/ProgressBar.qml \
    qml/ProgressBarStyle.qml \
    qml/ProgressDialog.qml \
    qml/RadioButton.qml \
    qml/RadioButtonStyle.qml \
    qml/RejectButtonStyle.qml \
    qml/RejectThumbButtonStyle.qml \
    qml/RowLayout.qml \
    qml/ScrollBar.qml \
    qml/ScrollBarStyle.qml \
    qml/ScrollDecorator.qml \
    qml/ScrollDecoratorStyle.qml \
    qml/Slider.qml \
    qml/SliderStyle.qml \
    qml/SmallProgressBarStyle.qml \
    qml/SpinBox.qml \
    qml/SpinBoxStyle.qml \
    qml/Style.qml \
    qml/StylusButtonStyle.qml \
    qml/Tab.qml \
    qml/TabBar.qml \
    qml/TabButtonStyle.qml \
    qml/TabView.qml \
    qml/TextArea.qml \
    qml/TextAreaStyle.qml \
    qml/TextField.qml \
    qml/TextFieldStyle.qml \
    qml/ThumbButtonStyle.qml \
    qml/ThumbScrollBarStyle.qml \
    qml/TimePickSelector.qml \
    qml/ToolBar.qml \
    qml/ToolBarStyle.qml \
    qml/ToolButton.qml \
    qml/ToolButtonStyle.qml \
    qml/ValueButton.qml \
    qml/ValueButtonStyle.qml

qml.path = /opt/lib/qt4/imports/org/hildon/components
target.path = /opt/lib/qt4/imports/org/hildon/components

INSTALLS += qml target

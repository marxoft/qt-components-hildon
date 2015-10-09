TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus maemo5

TARGET = qchcomponents

HEADERS += \
    qchaction.h \
    qchcloseevent.h \
    qchdialog.h \
    qchdialogstatus.h \
    qchexclusivegroup.h \
    qchfiledialog.h \
    qchfontmetrics.h \
    qchgraphicsview.h \
    qchimageproviders.h \
    qchinformationbox.h \
    qchitemaction.h \
    qchmenu.h \
    qchmenubar.h \
    qchmenuitem.h \
    qchnavigationmode.h \
    qchscreen.h \
    qchstyle.h \
    qchtextmetrics.h \
    qchvaluelayout.h \
    qchwindow.h \
    qchwindowstack.h \
    qchwindowstatus.h \
    qchplugin.h

SOURCES += \
    qchaction.cpp \
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
    qchstyle.cpp \
    qchtextmetrics.cpp \
    qchwindow.cpp \
    qchwindowstack.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir \
    qml/AbstractButton.qml \
    qml/AbstractPickSelector.qml \
    qml/ApplicationWindow.qml \
    qml/BiDirectionalSlider.qml \
    qml/BiDirectionalSliderStyle.qml \
    qml/Button.qml \
    qml/ButtonStyle.qml \
    qml/CheckBox.qml \
    qml/CheckBoxStyle.qml \
    qml/DatePickSelector.qml \
    qml/DialogButtonStyle.qml \
    qml/DoubleSpinBox.qml \
    qml/EditBar.qml \
    qml/EditButtonStyle.qml \
    qml/Flickable.qml \
    qml/Label.qml \
    qml/LabelStyle.qml \
    qml/ListItem.qml \
    qml/ListItemStyle.qml \
    qml/ListPickSelector.qml \
    qml/ListView.qml \
    qml/ProgressBar.qml \
    qml/ProgressBarStyle.qml \
    qml/RadioButton.qml \
    qml/ScrollBar.qml \
    qml/ScrollBarStyle.qml \
    qml/Slider.qml \
    qml/SliderStyle.qml \
    qml/SpinBox.qml \
    qml/SpinBoxStyle.qml \
    qml/Style.qml \
    qml/Tab.qml \
    qml/TabBar.qml \
    qml/TabButtonStyle.qml \
    qml/TabView.qml \
    qml/TextArea.qml \
    qml/TextAreaStyle.qml \
    qml/TextField.qml \
    qml/TextFieldStyle.qml \
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

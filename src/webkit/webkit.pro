TEMPLATE = lib
CONFIG = qt plugin
QT += declarative webkit network script

TARGET = qchwebkit

INCLUDEPATH += ../script

HEADERS += \
    ../script/qchscriptengineacquirer.h \
    qchnetworkrequest.h \
    qchwebelement.h \
    qchwebhistory.h \
    qchwebhistoryinterface.h \
    qchwebhittestresult.h \
    qchwebpage.h \
    qchwebsettings.h \
    qchwebview.h \
    qchplugin.h

SOURCES += \
    ../script/qchscriptengineacquirer.cpp \
    qchnetworkrequest.cpp \
    qchwebelement.cpp \
    qchwebhistory.cpp \
    qchwebhistoryinterface.cpp \
    qchwebhittestresult.cpp \
    qchwebpage.cpp \
    qchwebsettings.cpp \
    qchwebview.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/webkit
target.path = /opt/lib/qt4/imports/org/hildon/webkit

INSTALLS += qml target

TEMPLATE = lib
CONFIG = qt plugin
QT += declarative webkit network

TARGET = hildonwebkit

HEADERS += \
    qchwebhistory.h \
    qchwebhistoryinterface.h \
    qchwebpage.h \
    qchwebsettings.h \
    qchwebview.h \
    qchplugin.h

SOURCES += \
    qchwebhistory.cpp \
    qchwebhistoryinterface.cpp \
    qchwebpage.cpp \
    qchwebsettings.cpp \
    qchwebview.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/webkit
target.path = /opt/lib/qt4/imports/org/hildon/webkit

INSTALLS += qml target

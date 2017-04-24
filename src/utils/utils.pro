TEMPLATE = lib
CONFIG = qt plugin
QT += declarative script

TARGET = qchutils

INCLUDEPATH += ../script

HEADERS += \
    ../script/qchscriptengineacquirer.h \
    qchclipboard.h \
    qchdirectory.h \
    qchfile.h \
    qchfileinfo.h \
    qchprocess.h \
    qchscreensaver.h \
    qchscreenshot.h \
    qchplugin.h

SOURCES += \
    ../script/qchscriptengineacquirer.cpp \
    qchclipboard.cpp \
    qchdirectory.cpp \
    qchfile.cpp \
    qchfileinfo.cpp \
    qchprocess.cpp \
    qchscreensaver.cpp \
    qchscreenshot.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/utils
target.path = /opt/lib/qt4/imports/org/hildon/utils

INSTALLS += qml target

TEMPLATE = lib
CONFIG = qt plugin
QT += declarative

TARGET = qchutils

HEADERS += \
    qchclipboard.h \
    qchdirectory.h \
    qchfile.h \
    qchprocess.h \
    qchscreensaver.h \
    qchscreenshot.h \
    qchplugin.h

SOURCES += \
    qchclipboard.cpp \
    qchdirectory.cpp \
    qchfile.cpp \
    qchprocess.cpp \
    qchscreensaver.cpp \
    qchscreenshot.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/utils
target.path = /opt/lib/qt4/imports/org/hildon/utils

INSTALLS += qml target

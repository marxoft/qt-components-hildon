TEMPLATE = lib
CONFIG = qt plugin
QT += declarative

TARGET = hildonutils

HEADERS += \
    qchclipboard.h \
    qchdirectory.h \
    qchprocess.h \
    qchscreensaver.h \
    qchplugin.h

SOURCES += \
    qchclipboard.cpp \
    qchdirectory.cpp \
    qchprocess.cpp \
    qchscreensaver.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/utils
target.path = /opt/lib/qt4/imports/org/hildon/utils

INSTALLS += qml target

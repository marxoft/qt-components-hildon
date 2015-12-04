TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus

TARGET = qchdbus

HEADERS += \
    qchdbus.h \
    qchdbusconnections.h \
    qchdbusmessage.h \
    qchdbusutils.h \
    qchplugin.h

SOURCES += \
    qchdbusconnections.cpp \
    qchdbusmessage.cpp \
    qchdbusutils.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/dbus
target.path = /opt/lib/qt4/imports/org/hildon/dbus

INSTALLS += qml target

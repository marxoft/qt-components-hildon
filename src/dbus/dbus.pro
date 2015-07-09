TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus

TARGET = hildondbus

HEADERS += \
    qchdbusadaptor.h \
    qchdbusmessage.h \
    qchdbusutils.h \
    qdbusutil_p.h \
    qchplugin.h

SOURCES += \
    qchdbusadaptor.cpp \
    qchdbusmessage.cpp \
    qchdbusutils.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/dbus
target.path = /opt/lib/qt4/imports/org/hildon/dbus

INSTALLS += qml target

TEMPLATE = lib
CONFIG = qt plugin
QT += declarative
INCLUDEPATH += /usr/include/gq
LIBS += -lgq-gconf

TARGET = qchsettings

HEADERS += \
    qchgconfitem.h \
    qchsettings.h \
    qchplugin.h

SOURCES += \
    qchgconfitem.cpp \
    qchsettings.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/settings
target.path = /opt/lib/qt4/imports/org/hildon/settings

INSTALLS += qml target

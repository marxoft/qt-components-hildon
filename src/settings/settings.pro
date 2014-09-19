TEMPLATE = lib
CONFIG = qt plugin
QT += declarative
INCLUDEPATH += /usr/include/gq
LIBS += -lgq-gconf

TARGET = hildonsettings

HEADERS += \
    qmlgconfitem_p.h \
    settings_p.h \
    plugin_p.h

SOURCES += \
    qmlgconfitem.cpp \
    settings.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/settings
target.path = /opt/lib/qt4/imports/org/hildon/settings

INSTALLS += qdeclarativesources target

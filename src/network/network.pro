TEMPLATE = lib
CONFIG = qt plugin
QT += declarative network

TARGET = hildonnetwork

HEADERS += \
    networkrequest_p.h \
    networkrequest_p_p.h \
    plugin_p.h

SOURCES += \
    networkrequest.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/network
target.path = /opt/lib/qt4/imports/org/hildon/network

INSTALLS += qdeclarativesources target

TEMPLATE = lib
CONFIG = qt plugin
QT += declarative webkit network

TARGET = hildonwebkit

INCLUDEPATH += ../components

HEADERS += \
    ../components/anchorline_p.h \
    ../components/anchors_p.h \
    ../components/anchors_p_p.h \
    ../components/item_p.h \
    ../components/item_p_p.h \
    ../components/style_p.h \
    ../components/style_p_p.h \
    webhistory_p.h \
    webhistoryinterface_p.h \
    webpage_p.h \
    websettings_p.h \
    webview_p.h \
    webview_p_p.h \
    plugin_p.h

SOURCES += \
    ../components/anchors.cpp \
    ../components/item.cpp \
    ../components/style.cpp \
    webhistory.cpp \
    webhistoryinterface.cpp \
    webpage.cpp \
    websettings.cpp \
    webview.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/webkit
target.path = /opt/lib/qt4/imports/org/hildon/webkit

INSTALLS += qdeclarativesources target

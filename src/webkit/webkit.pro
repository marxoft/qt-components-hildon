TEMPLATE = lib
CONFIG = qt plugin
QT += declarative webkit

TARGET = hildonwebkit

INCLUDEPATH += ../components

HEADERS += \
    webview_p.h \
    webview_p_p.h \
    plugin_p.h

SOURCES += \
    webview.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/webkit
target.path = /opt/lib/qt4/imports/org/hildon/webkit

INSTALLS += qdeclarativesources target

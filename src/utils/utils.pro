TEMPLATE = lib
CONFIG = qt plugin
QT += declarative

TARGET = hildonutils

HEADERS += \
    process_p.h \
    process_p_p.h \
    screensaver_p.h \
    screensaver_p_p.h \
    screenshot_p.h \
    screenshot_p_p.h \
    settings_p.h \
    plugin_p.h

SOURCES += \
    process.cpp \
    screensaver.cpp \
    screenshot.cpp \
    settings.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/utils
target.path = /opt/lib/qt4/imports/org/hildon/utils

INSTALLS += qdeclarativesources target

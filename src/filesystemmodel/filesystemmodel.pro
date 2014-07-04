TEMPLATE = lib
CONFIG = qt plugin
QT += declarative

TARGET = hildonfilesystemmodel

HEADERS += \
    filesystemmodel_p.h \
    plugin_p.h

SOURCES += \
    filesystemmodel.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/filesystemmodel
target.path = /opt/lib/qt4/imports/org/hildon/filesystemmodel

INSTALLS += qdeclarativesources target

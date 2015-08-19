TEMPLATE = lib
CONFIG = qt plugin
QT += declarative

TARGET = qchdesktop

CONFIG += link_pkgconfig
PKGCONFIG += hildon-notify

INCLUDEPATH += ../components

HEADERS += \
    ../components/qchcloseevent.h \
    ../components/qchgraphicsview.h \
    qchhomescreenwidget.h \
    qchnotification.h \
    qchplugin.h

SOURCES += \
    ../components/qchgraphicsview.cpp \
    qchhomescreenwidget.cpp \
    qchnotification.cpp \
    qchplugin.cpp

qml.files = qml/qmldir
qml.path = /opt/lib/qt4/imports/org/hildon/desktop
target.path = /opt/lib/qt4/imports/org/hildon/desktop

INSTALLS += qml target

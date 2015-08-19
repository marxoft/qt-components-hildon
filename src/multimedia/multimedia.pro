TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus

CONFIG += link_pkgconfig
PKGCONFIG += mafw mafw-shared glib-2.0 libplayback-1 gnome-vfs-2.0

LIBS += -lgq-gconf

DEFINES += MAFW_WORKAROUNDS

TARGET = qchmultimedia

INCLUDEPATH += \
    /usr/include/gq

HEADERS += \
    mafw/mafwrenderersignalhelper.h \
    mafw/mafwrendereradapter.h \
    mafw/mafwsourceadapter.h \
    mafw/mafwplaylistadapter.h \
    mafw/mafwplaylistmanageradapter.h \
    mafw/mafwregistryadapter.h \
    metadatawatcher.h \
    missioncontrol.h \
    playlistquerymanager.h \
    qchaudioplayer.h \
    qchmediastatus.h \
    qchmediatype.h \
    qchnowplayingmodel.h \
    qchplugin.h

SOURCES += \
    mafw/mafwrenderersignalhelper.cpp \
    mafw/mafwsourceadapter.cpp \
    mafw/mafwrendereradapter.cpp \
    mafw/mafwplaylistadapter.cpp \
    mafw/mafwplaylistmanageradapter.cpp \
    mafw/mafwregistryadapter.cpp \
    metadatawatcher.cpp \
    missioncontrol.cpp \
    playlistquerymanager.cpp \
    qchaudioplayer.cpp \
    qchnowplayingmodel.cpp \
    qchplugin.cpp

qml.files += \
    qml/qmldir

qml.path = /opt/lib/qt4/imports/org/hildon/multimedia
target.path = /opt/lib/qt4/imports/org/hildon/multimedia

INSTALLS += qml target

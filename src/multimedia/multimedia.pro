TEMPLATE = lib
CONFIG = qt plugin
QT += declarative dbus

CONFIG += link_pkgconfig
PKGCONFIG += mafw mafw-shared glib-2.0 libplayback-1 gnome-vfs-2.0

LIBS += -lgq-gconf

DEFINES += MAFW_WORKAROUNDS

TARGET = hildonmultimedia

INCLUDEPATH += ../components \
    /usr/include/gq

HEADERS += \
    ../components/anchorline_p.h \
    ../components/anchors_p.h \
    ../components/anchors_p_p.h \
    ../components/item_p.h \
    ../components/item_p_p.h \
    ../components/modelindex_p.h \
    ../components/style_p.h \
    ../components/style_p_p.h \
    mafw/mafwrenderersignalhelper.h \
    mafw/mafwrendereradapter.h \
    mafw/mafwsourceadapter.h \
    mafw/mafwplaylistadapter.h \
    mafw/mafwplaylistmanageradapter.h \
    mafw/mafwregistryadapter.h \
    metadatawatcher_p.h \
    missioncontrol_p.h \
    playlistquerymanager_p.h \
    audioplayer_p.h \
    mediastatus_p.h \
    mediatype_p.h \
    playbackmodel_p.h \
    videoplayer_p.h \
    plugin_p.h

SOURCES += \
    ../components/anchors.cpp \
    ../components/item.cpp \
    ../components/style.cpp \
    mafw/mafwrenderersignalhelper.cpp \
    mafw/mafwsourceadapter.cpp \
    mafw/mafwrendereradapter.cpp \
    mafw/mafwplaylistadapter.cpp \
    mafw/mafwplaylistmanageradapter.cpp \
    mafw/mafwregistryadapter.cpp \
    metadatawatcher.cpp \
    missioncontrol.cpp \
    playlistquerymanager.cpp \
    audioplayer.cpp \
    playbackmodel.cpp \
    videoplayer.cpp \
    plugin.cpp

qdeclarativesources.files += \
    qml/qmldir

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/multimedia
target.path = /opt/lib/qt4/imports/org/hildon/multimedia

INSTALLS += qdeclarativesources target

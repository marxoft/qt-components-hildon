TEMPLATE = app
TARGET = process

QT += declarative

SOURCES += src/main.cpp

RESOURCES += src/resources.qrc

OTHER_FILES += src/*.qml

target.path = /opt/qt-components-hildon/bin

desktopfile.files = qt-components-hildon-process.desktop
desktopfile.path = /usr/share/applications/hildon

icon.files = qt-components-hildon-process.png
icon.path = /usr/share/icons/hicolor/64x64/apps

INSTALLS += target desktopfile icon

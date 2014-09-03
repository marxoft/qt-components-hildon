TEMPLATE = app
TARGET = dbus

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/dbus/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/dbus/qml

INSTALLS += target qml

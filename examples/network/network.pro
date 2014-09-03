TEMPLATE = app
TARGET = network

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/network/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/network/qml

INSTALLS += target qml

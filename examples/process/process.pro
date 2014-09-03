TEMPLATE = app
TARGET = process

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/process/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/process/qml

INSTALLS += target qml

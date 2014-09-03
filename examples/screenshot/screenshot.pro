TEMPLATE = app
TARGET = screenshot

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/screenshot/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/screenshot/qml

INSTALLS += target qml

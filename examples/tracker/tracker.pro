TEMPLATE = app
TARGET = tracker

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/tracker/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/tracker/qml

INSTALLS += target qml

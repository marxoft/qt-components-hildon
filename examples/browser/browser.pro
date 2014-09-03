TEMPLATE = app
TARGET = browser

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/browser/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/browser/qml

INSTALLS += target qml

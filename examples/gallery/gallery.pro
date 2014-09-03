TEMPLATE = app
TARGET = browser

QT += declarative

SOURCES += src/main.cpp

target.path = /opt/qt-components-hildon/examples/gallery/bin

qml.files += $$files(src/qml/*.*)
qml.path = /opt/qt-components-hildon/examples/gallery/qml

INSTALLS += target qml

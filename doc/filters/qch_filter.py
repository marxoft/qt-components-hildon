#!/usr/bin/env python

import os.path

# This filter is used to 'QML-ize' class names and property types.

FILTER = [
    ('AudioPlayer', 'Audio'),
    ('Clipboard', 'clipboard'),
    ('const ', ''),
    ('DBusAdaptor::BusType ', 'enumeration '),
    ('DBusMessage::BusType ', 'enumeration '),
    ('DialogStatus::Status ', 'enumeration '),
    ('Directory::Filters ', 'flags '),
    ('Directory::SortFlags ', 'flags '),
    ('File::OpenMode ', 'enumeration '),
    ('File::Permissions ', 'flags '),
    ('MediaStatus::Status ', 'enumeration '),
    ('MetadataWatcher* ', 'variant '),
    ('Menu* ', 'Menu '),
    ('MenuItem* ', 'MenuItem '),
    ('qint64 ', 'int '),
    ('qreal ', 'real '),
    ('Q_INVOKABLE ', ''),
    ('QByteArray ', 'string '),
    ('Qch', ''),
    ('QColor ', 'color '),
    ('QDeclarativeComponent* ', 'Component '),
    ('QDeclarativeItem* ', 'Item '),
    ('QDeclarativeListProperty', 'list'),
    ('QFont ', 'font '),
    ('QObject* ', 'object '),
    ('QObject *', 'object '),
    ('QPoint ', 'point '),
    ('QRect ', 'rect '),
    ('QString ', 'string '),
    ('QStringList', 'list<string>'),
    ('Qt::TextElideMode ', 'enumeration '),
    ('Qt::WindowStates ', 'flags '),
    ('QUrl ', 'url '),
    ('QVariant ', 'variant '),
    ('QVariantList', 'list<variant>'),
    ('QVariantMap()', 'null'),
    ('QVariantMap', 'dict'),
    ('Screen', 'screen'),
    ('screenSaver', 'ScreenSaver'),
    ('screenShot', 'ScreenShot'),
    ('static ', ''),
    ('Style', 'platformStyle'),
    ('uint ', 'int '),
    ('Window* ', 'Window '),
    ('Window *', 'Window '),
    ('WindowStatus::Status ', 'enumeration '),
    ('<QObject>', '<object>'),
    ('&', ''),
    ('BusType ', 'enumeration '),
    ('Error ', 'enumeration '),
    ('Filters ', 'flags '),
    ('MessageType ', 'enumeration '),
    ('OpenMode ', 'enumeration '),
    ('Permissions ', 'flags '),
    ('SortFlags ', 'flags '),
    ('Status ', 'enumeration ')
]

def filter_source(source):
    with open(os.path.abspath(source)) as sf:
        s = sf.read()
    
    for before, after in FILTER:
        s = s.replace(before, after)
    
    print s

if __name__ == '__main__':
    import sys
    sys.exit(filter_source(sys.argv[1]))
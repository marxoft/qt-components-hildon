TEMPLATE = subdirs

qdeclarativesources.files += \
    qmldir \
    Tracker.js \
    TrackerContainsFilter.qml \
    TrackerEndsWithFilter.qml \
    TrackerEqualsFilter.qml \
    TrackerFilterIntersection.qml \
    TrackerFilterUnion.qml \
    TrackerGreaterThanFilter.qml \
    TrackerItemRequest.qml \
    TrackerLessThanFilter.qml \
    TrackerPropertyModel.qml \
    TrackerPropertyRequest.qml \
    TrackerQueryModel.qml \
    TrackerQueryRequest.qml \
    TrackerStartsWithFilter.qml \
    TrackerWildcardFilter.qml

qdeclarativesources.path = /opt/lib/qt4/imports/org/hildon/tracker

INSTALLS += qdeclarativesources

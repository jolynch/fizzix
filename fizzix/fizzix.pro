TEMPLATE = app
TARGET = fizzix
target.path = /usr/local/bin
DEPENDPATH += .
PKGCONFIG += xmms2-client xmms2-client-cpp
CONFIG += link_pkgconfig debug
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

MOC_DIR = moc
OBJECTS_DIR = build

# Fizzix

HEADERS+=
SOURCES+=

TEMPLATE = app
TARGET = fizzix
target.path = /usr/local/bin
DEPENDPATH += .
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

MOC_DIR = moc
OBJECTS_DIR = build
RESOURCES = fizzix.qrc

# Fizzix

HEADERS+=src/*.h
SOURCES+=src/*.cpp

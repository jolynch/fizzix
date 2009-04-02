TEMPLATE = app
TARGET = fizzix
target.path = /usr/local/bin
DEPENDPATH += .
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
CONFIG = qt opengl thread resources exceptions warn_on stl rtti
MOC_DIR = moc
OBJECTS_DIR = build
RESOURCES = fizzix.qrc

# Fizzix

HEADERS+=src/about.h \
src/buttonpanel.h \
src/forcepanel.h \
src/macropanel.h \
src/mainwindow.h \
src/objectpanel.h \
src/propertypanel.h \


SOURCES+=src/main.cpp \
src/about.cpp \
src/buttonpanel.cpp \
src/forcepanel.cpp \
src/macropanel.cpp \
src/mainwindow.cpp \
src/objectpanel.cpp \
src/propertypanel.cpp \


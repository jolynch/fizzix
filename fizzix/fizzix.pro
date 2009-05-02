TEMPLATE = app
TARGET = fizzix
target.path = /usr/local/bin
INCLUDEPATH += /usr/local/include
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
CONFIG = qt opengl thread resources exceptions warn_on stl rtti
MOC_DIR = moc
OBJECTS_DIR = build
RESOURCES = fizzix.qrc
QT += opengl
LIBS +=  -lfizzix -L/usr/local/lib


# Fizzix

HEADERS+=src/forcepanel.h \
src/macropanel.h \
src/mainwindow.h \
src/objectpanel.h \
src/propertypanel.h \
src/databrowser.h \
src/dataeditor.h \
src/simulationcontrol.h \
src/drawableobject.h \
src/GLdrawpane.h \


SOURCES+=src/main.cpp \
src/forcepanel.cpp \
src/macropanel.cpp \
src/mainwindow.cpp \
src/objectpanel.cpp \
src/propertypanel.cpp \
src/databrowser.cpp \
src/dataeditor.cpp \
src/simulationcontrol.cpp \
src/drawableobject.cpp \
src/GLdrawpane.cpp \

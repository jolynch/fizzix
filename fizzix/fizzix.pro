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

HEADERS+=src/mainwindow.h \
src/databrowser.h \
src/dataeditor.h \
src/databackend/databackend.h \
src/simulationcontrol.h \
src/drawableobject.h \
src/GLdrawpane.h \
src/databackend/mapkeylistmodel.h \


SOURCES+=src/main.cpp \
src/mainwindow.cpp \
src/databrowser.cpp \
src/dataeditor.cpp \
src/databackend/databackend.cpp \
src/simulationcontrol.cpp \
src/drawableobject.cpp \
src/GLdrawpane.cpp \

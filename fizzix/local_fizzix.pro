TEMPLATE = app
TARGET = fizzix
target.path = ../local_install
INCLUDEPATH = ../local_install/include
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
CONFIG = qt opengl thread resources exceptions warn_on stl rtti
MOC_DIR = moc
OBJECTS_DIR = build
RESOURCES = fizzix.qrc
QT += opengl
LIBS += -L../local_install/lib -lfizzix


# Fizzix

HEADERS+=src/mainwindow.h \
src/databrowser.h \
src/dataeditor.h \
src/constanteditor.h \
src/objecteditor.h \
src/forceeditor.h \
src/formulaeditor.h \
src/shapeeditor.h \
src/propertylisteditor.h \
src/databackend/databackend.h \
src/simulationcontrol.h \
src/databackend/drawableobject.h \
src/GLdrawpane.h \
src/databackend/mapkeylistmodel.h \
src/databackend/changefactory.h \
src/databackend/maputil.h \
src/databackend/parser.h \
src/editpropertydialog.h \

SOURCES+=src/main.cpp \
src/mainwindow.cpp \
src/databrowser.cpp \
src/dataeditor.cpp \
src/constanteditor.cpp \
src/objecteditor.cpp \
src/forceeditor.cpp \
src/formulaeditor.cpp \
src/shapeeditor.cpp \
src/propertylisteditor.cpp \
src/databackend/databackend.cpp \
src/simulationcontrol.cpp \
src/databackend/drawableobject.cpp \
src/GLdrawpane.cpp \
src/databackend/changefactory.cpp \
src/editpropertydialog.cpp \

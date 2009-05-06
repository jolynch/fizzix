SUBDIRS=fizformoperators
lib_LTLIBRARIES = libfizzix.la
libfizzix_la_LIBADD = fizformoperators/libfizformoperators.la
fizzix_includedir=$(includedir)/libfizzix/


#The following will be installed in /usr/local/libfizzix/ by default.
fizzix_include_HEADERS= \
fizformoperator.h \
fizstack.h \
fizengine.h  \
fizformanonconst.h  \
matrix.h \
gen_structs.h \
fizforce.h  \
fizformnode.h   \
fizformula.h   \
fizobject.h  \
quaternion.h \
fizformget.h \
getters.h \
fizcylinder.h \
fizprism.h \
fizsphere.h 

#This is everything that's getting compiled.
libfizzix_la_SOURCES = \
fizengine.cpp \
fizformanonconst.cpp \
fizformoperator.h \
fizstack.h   \
fizengine.h  \
fizformanonconst.h \
fizformvariable.h  \
gen_structs.cpp \
matrix.h \
fizforce.cpp \
fizformnode.cpp \
fizformula.cpp \
fizobject.cpp  \
gen_structs.h  \
quaternion.cpp \
fizforce.h  \
fizformnode.h  \
fizformula.h \
fizobject.h \
quaternion.h \
fizformgetconst.cpp \
fizformgetforce.cpp \
fizformgetmacro.cpp \
fizformget.h \
fizformget.cpp \
fizcylinder.cpp \
fizprism.cpp \
fizsphere.cpp \
fizformgetprop.cpp

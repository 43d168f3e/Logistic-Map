#$$PWD is the path of current .pro file

#############	begin	   IMPORTANT	if additional file copy is required   ###################
#modified from
#https://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt/42840533:
#answered Apr 5 '16 at 22:55 by Paglian

#copydata0.commands = $(COPY_DIR) $$PWD/required_files/* $$OUT_PWD
#copydata1.commands= $(COPY_FILE) $$PWD/glPointVert2Color1.glsl $$OUT_PWD
#copydata2.commands= $(COPY_FILE) $$PWD/glPointFrag.glsl $$OUT_PWD
#first.depends = $(first) copydata0 copydata1 copydata2
#export(first.depends)
#export(copydata0.commands)
#export(copydata1.commands)
#export(copydata2.commands)
#QMAKE_EXTRA_TARGETS += first copydata0 copydata1 copydata2

#############	end	   IMPORTANT	   ###################

#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T07:32:44
#
#-----------------------------ldl locale---------------------

CONFIG += c++2a

INCLUDEPATH += /usr/include/c++/9  #for <stdlib.h>, if compiler cannot find "stdlib.h"
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local/include  #for nlohmann/json
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include

LIBS += -lgmp -lmpfr -lgmpxx  -lpng -lstdc++fs -ldl  -latomic -lm -lpthread
#unix:LIBS += -L/usr/lib64 -lgmpxx
#win32:LIBS += "c:/mylibs/gmpxx.lib"

#For Qt build, QMAKE_CXXFLAGS, ... , are initialized in $(QTDIR)\mkspecs<your compiler>\qmake.conf
#/usr/lib64/qt5/mkspecs/linux-clang-libc++/
QMAKE_CFLAGS+= -I/usr/include -I/usr/local/include
#QMAKE_CFLAGS+= -isystem /usr/include
QMAKE_CXXFLAGS += -std=c++2a
#QMAKE_CXXFLAGS += -isystem /usr/include
QMAKE_CXXFLAGS += -I/usr/include  -I/usr/local/include
QMAKE_CXXFLAGS += -g -Wall -Wextra -Wunreachable-code -Wpedantic -Wmissing-declarations

QMAKE_CFLAGS_RELEASE +=  -I/usr/include -I/usr/local/include -O3
QMAKE_CXXFLAGS_RELEASE +=   -std=c++2a -I/usr/include -I/usr/local/include -O3


contains( QMAKE_CXX , g++ ) {
      message("-lstdc++")
LIBS += -lstdc++
  }
contains( QMAKE_CXX , clang++ ){
      message("-lc++")
LIBS += -lc++
  }

message('Compiled with Qt Version '$$QT_VERSION)
message('INCLUDEPATH='$$INCLUDEPATH)
message('QMAKE_CXX='$$QMAKE_CXX)
message('QMAKE_CXXFLAGS='$$QMAKE_CXXFLAGS)
message('QMAKE_LINK='$$QMAKE_LINK)
message('QMAKE_LIBS='$$QMAKE_LIBS)
message('LIBS='$$LIBS)
##################################################################################
#preprocessors stringify operation:
#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)
#define RECORD_00(X) message(STRINGIFY(X)'='$$X)
#define RECORD_(X) RECORD_00(X)
#RECORD_(QMAKE_LFLAGS_RPATH)
##################################################################################


QT       += core gui widgets
#QT += multimedia

TARGET = Logistic_Map
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#CONFIG += c++2a

SOURCES += \
        QJsonModel/qjsonmodel.cpp \
        QJsonModel/qjsontreeview.cpp \
        dialogForRATE.cpp \
        main.cpp \
        lmap.cpp \
        global.cpp \
        mycentralwidget.cpp \
        src/assemble_block.cpp \
        src/data.cpp \
        src/datum.cpp \
        src/fill_in_vector.cpp \
        src/generateTemplate.cpp \
        src/oglframe.cpp \
        src/oglwidget.cpp \
        src/playRows.cpp \
        src/toot.cpp

HEADERS += \
        QJsonModel/qjsonmodel.h \
        QJsonModel/qjsontreeview.h \
        dialogForRATE.h \
        global.h \
        include/CXX14Support.h \
        include/rxqt.hpp \
        include/rxqt_event.hpp \
        include/rxqt_run_loop.hpp \
        include/rxqt_signal.hpp \
        include/rxqt_util.hpp \
        lmap.h \
        logisticMap_4.ui.inc \
        mycentralwidget.h \
        src/assemble_block.h \
        src/colorize_map.h \
        src/colormap.h \
        src/data.h \
        src/datum.h \
        src/fill_in_vector.h \
        src/generateTemplate.h \
        src/logisticMapBoundaryPostOnsetOfChaos.h \
        src/notes.h \
        src/oglframe.h \
        src/oglwidget.h \
        src/playRows.h \
        src/toot.h \
        src/utility.h \
        src/worker_thread.h

#FORMS += \
#        lmap.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialogForRATE.ui

DISTFILES += \
    declarations_logisticMap_4.inc \
    definitions_logisticMap_4.inc \
    player/player \
    player/player.pro__

QT += webkit \
    network
LIBS += -lpng -lfreetype -lz -lgthread-2.0
HEADERS = mainwindow.h \
    buttonfactory.h \
    buttonlaunch.h \
    customstyle.h \
    menupage.h \
    osdmanager.h \
    matrixcontrol.h
TARGET = matrix_gui
SOURCES += main.cpp \
    mainwindow.cpp \
    buttonfactory.cpp \
    buttonlaunch.cpp \
    customstyle.cpp \
    menupage.cpp \
    osdmanager.cpp \
    matrixcontrol.cpp

# install
target.path = .
INSTALLS += target

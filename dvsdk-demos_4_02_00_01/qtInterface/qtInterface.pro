HEADERS += messageserver.h \
 configwindow.h \
 controlwindow.h \
 osdmanager.h \
 qtinterface.h
SOURCES += messageserver.cpp \
 controlwindow.cpp \
 configwindow.cpp \
 main.cpp \
 osdmanager.cpp 
RESOURCES += qtinterface.qrc

#install
target.path = /$(EXEC_DIR)
INSTALLS += target

QMAKE_CXXFLAGS_RELEASE += -DPlatform_$(PLATFORM)
QMAKE_CXXFLAGS_DEBUG += -DPlatform_$(PLATFORM)

CONFIG += thread link_pkgconfig

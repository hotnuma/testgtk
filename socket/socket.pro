TEMPLATE = app
TARGET = testgtk
CONFIG = c++11 link_pkgconfig
PKGCONFIG = gtk+-3.0
DEFINES = GTK
INCLUDEPATH = /home/hotnuma/DevFiles/scintilla/include

HEADERS += \
#    MainWindow.h \
    CSingleInstance.h \
    MainWindow.h \
    libsocket.h

SOURCES = \
    0Temp.cpp \
#    MainWindow.cpp \
    CSingleInstance.cpp \
    MainActions.cpp \
    MainWindow.cpp \
    libsocket.cpp \
    main.cpp

DISTFILES = \
    install.sh \
    meson.build \


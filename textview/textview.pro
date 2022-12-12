TEMPLATE = app
TARGET = testgtk
CONFIG = c++11 link_pkgconfig
PKGCONFIG = gtk+-3.0
DEFINES = GTK
INCLUDEPATH = /home/hotnuma/DevFiles/scintilla/include

HEADERS += \
#    MainWindow.h \
    MainWindow.h

SOURCES = \
    0Temp.cpp \
#    MainWindow.cpp \
    MainActions.cpp \
    MainWindow.cpp \
    main.cpp \

DISTFILES = \
    License.txt \
    Readme.txt \
    install.sh \
    meson.build \


TEMPLATE = app
TARGET = testgtk
CONFIG = c++11 link_pkgconfig
PKGCONFIG = gtk+-3.0
DEFINES = GTK
INCLUDEPATH = /usr/local/include/scintilla

HEADERS = \
    MainWindow.h \

SOURCES = \
    0Temp.cpp \
    MainActions.cpp \
    MainWindow.cpp \
    main.cpp \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.txt \


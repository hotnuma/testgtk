TEMPLATE = app
TARGET = testgtk
CONFIG = c11 link_pkgconfig
PKGCONFIG = gtk+-3.0

#DEFINES = GTK
#INCLUDEPATH = /home/hotnuma/DevFiles/scintilla/include

HEADERS = \
    application.h \
    config.h

SOURCES = \
    0Temp.c \
    application.c \
    main.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



TEMPLATE = app
TARGET = testgtk
CONFIG = c99 link_pkgconfig
PKGCONFIG = gtk+-3.0
DEFINES = GTK
INCLUDEPATH = /usr/local/include/scintilla

HEADERS = \

SOURCES = \
    0Temp.c \
    main.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.txt \


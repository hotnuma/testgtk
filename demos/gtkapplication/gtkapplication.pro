TEMPLATE = app
TARGET = gtkapplication
CONFIG = c11 link_pkgconfig
PKGCONFIG = gtk+-3.0 tinyc

HEADERS = \
    application.h \
    appwindow.h \
    config.h \
    preferences.h \

SOURCES = \
    0Temp.c \
    application.c \
    appwindow.c \
    main.c \
    preferences.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



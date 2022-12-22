TEMPLATE = app
TARGET = testgtk
CONFIG = c11 link_pkgconfig
PKGCONFIG = gtk+-3.0 tinyc

HEADERS = \
    application.h \
    config.h \
    preferences.h \
    window.h \

SOURCES = \
    0Temp.c \
    application.c \
    main.c \
    preferences.c \
    window.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



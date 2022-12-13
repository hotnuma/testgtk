TEMPLATE = app
TARGET = testgtk
CONFIG = c11 link_pkgconfig
PKGCONFIG = gtk+-3.0

HEADERS = \
    application.h \
    config.h \
    window.h \

SOURCES = \
    0Temp.c \
    application.c \
    main.c \
    window.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



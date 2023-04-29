TEMPLATE = app
TARGET = testgtk
CONFIG = c99 link_pkgconfig
DEFINES = _GNU_SOURCE
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc

HEADERS = \
    appwindow.h \
    libargs.h

SOURCES = \
    0Temp.c \
    appactions.c \
    appwindow.c \
    libargs.c \
    main.c \

DISTFILES = \
    install.sh \
    meson.build \



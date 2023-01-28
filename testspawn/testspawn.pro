TEMPLATE = app
TARGET = testspawn
CONFIG = c99 link_pkgconfig
DEFINES = SPAWN_TEST
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc

SOURCES = \
    0Temp.c \
    main.c \
    spawn.c

DISTFILES += \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \

HEADERS += \
    spawn.h



TEMPLATE = app
TARGET = testgtk
CONFIG = c99 link_pkgconfig
DEFINES =
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
#PKGCONFIG += tinyc
#PKGCONFIG += glib-2.0
#PKGCONFIG += gudev-1.0
#PKGCONFIG += dbus-1
#PKGCONFIG += libxml-2.0

SOURCES = \
    0Temp.c \
    main.c \
    samples/001_grid.c

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



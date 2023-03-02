TEMPLATE = app
TARGET = testroot
CONFIG = c99 link_pkgconfig
DEFINES =
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc
#PKGCONFIG += glib-2.0
#PKGCONFIG += dbus-1
#PKGCONFIG += libxml-2.0

HEADERS = \

SOURCES = \
    0Temp.c \
    main.c \

DISTFILES = \
    data/testroot.desktop \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



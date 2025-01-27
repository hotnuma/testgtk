TEMPLATE = app
TARGET = gtkappsimple
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
    application.h \
    appwindow.h \

SOURCES = \
    0Temp.c \
    application.c \
    appwindow.c \
    main.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



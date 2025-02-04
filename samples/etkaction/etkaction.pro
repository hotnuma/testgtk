TEMPLATE = app
TARGET = testui
CONFIG = c99 link_pkgconfig

DEFINES =
INCLUDEPATH =
PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyui
#PKGCONFIG += glib-2.0
#PKGCONFIG += dbus-1
#PKGCONFIG += libxml-2.0

HEADERS = \
    appwindow.h \
    config.h \

SOURCES = \
    0Temp.c \
    appwindow.c \
    main.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



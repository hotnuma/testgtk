TEMPLATE = app
TARGET = etkaction
CONFIG = c99 link_pkgconfig
DEFINES =
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc
#PKGCONFIG += glib-2.0
#PKGCONFIG += dbus-1
#PKGCONFIG += libxml-2.0

HEADERS += \
    appwindow.h \
    config.h \

SOURCES = \
    0Temp.c \
    appwindow.c \
    main.c \

DISTFILES += \
    data/applist.desktop \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



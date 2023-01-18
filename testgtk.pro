TEMPLATE = app
TARGET = testgtk
CONFIG = c99 link_pkgconfig
DEFINES =
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc
#PKGCONFIG += glib-2.0
#PKGCONFIG += dbus-1
#PKGCONFIG += libxml-2.0

SOURCES = \
    0Temp.c \
    main.c \
    samples/gio_app_info.c \
    samples/gtk_appchooser.c \
    samples/iconlist.c \
    samples/iconview.c \
    samples/image.c \
    samples/image2.c \
    samples/listbox-dnd.c \
    samples/listview.c

DISTFILES += \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



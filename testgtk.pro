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
    samples/gio_app_info.c \
    samples/gmenu.c \
    samples/gtk_appchooser.c \
    samples/iconview.c \
    samples/image.c \
    samples/image_saturate.c \
    samples/listbox_dnd.c \
    samples/listview.c \
    samples/redirect_widget.c \
    samples/single_instance.c \
    samples/sys_gudev.c \
    zetcode/010-version.c \
    zetcode/020-simple.c \
    zetcode/021-center.c \
    zetcode/022-icon.c \
    zetcode/023-toolltip.c \
    zetcode/024-mnemonic.c \
    zetcode/030-simplemenu.c \
    zetcode/031-submenu.c \
    zetcode/100-simpletextview.c \
    0Temp.c \
    main.c \

DISTFILES += \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



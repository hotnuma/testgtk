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
    samples/01_widgets.c \
    samples/02_toolbar.c \
    samples/cairo_draw.c \
    samples/object_set.c \
    samples/object_set_data_full.c \
    samples/socket_path.c \
    zetcode/010_version.c \
    zetcode/020_simple.c \
    zetcode/021_center.c \
    zetcode/022_icon.c \
    zetcode/023_toolltip.c \
    zetcode/024_mnemonic.c \
    zetcode/030_simplemenu.c \
    zetcode/031_submenu.c \
    zetcode/032_imagemenu.c \
    zetcode/033_checkmenuitem.c \
    zetcode/034_popupmenu.c \
    zetcode/035_toolbar.c \
    zetcode/036_undoredo.c \
    zetcode/040_fixed.c \
    zetcode/041_vbox.c \
    zetcode/042_grid.c \
    zetcode/043_windows.c \
    zetcode/050_buttonclick.c \
    zetcode/051_moveevent.c \
    zetcode/052_entersignal.c \
    zetcode/053_disconnect.c \
    zetcode/054_dragdrop.c \
    zetcode/055_timer.c \
    zetcode/060_messagedialogs.c \
    zetcode/061_aboutdialog.c \
    zetcode/062_fontdialog.c \
    zetcode/063_colordialog.c \
    zetcode/070_button.c \
    zetcode/071_checkbutton.c \
    zetcode/072_frames.c \
    zetcode/073_hscale.c \
    zetcode/074_label.c \
    zetcode/075_markup.c \
    zetcode/080_combobox.c \
    zetcode/081_separator.c \
    zetcode/082_entry.c \
    zetcode/083_image.c \
    zetcode/084_statusbar.c \
    zetcode/085_iconview.c \
    zetcode/090_listview.c \
    zetcode/091_dynamiclistview.c \
    zetcode/092_treeview.c \
    zetcode/100_simpletextview.c \
    zetcode/101_linescols.c \
    zetcode/102_search.c

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \



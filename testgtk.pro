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
    samples/cairo_draw.c \
    samples/dialog_fontchooser.c \
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
    zetcode/010_version.c \
    zetcode/020_simple.c \
    zetcode/021-center.c \
    zetcode/022-icon.c \
    zetcode/023-toolltip.c \
    zetcode/024-mnemonic.c \
    zetcode/030-simplemenu.c \
    zetcode/031-submenu.c \
    zetcode/032-imagemenu.c \
    zetcode/033-checkmenuitem.c \
    zetcode/034-popupmenu.c \
    zetcode/035-toolbar.c \
    zetcode/036-undoredo.c \
    zetcode/040-fixed.c \
    zetcode/041-vbox.c \
    zetcode/042-grid.c \
    zetcode/043-windows.c \
    zetcode/050-buttonclick.c \
    zetcode/051-moveevent.c \
    zetcode/052-entersignal.c \
    zetcode/053-disconnect.c \
    zetcode/054-dragdrop.c \
    zetcode/055-timer.c \
    zetcode/060-messagedialogs.c \
    zetcode/061-aboutdialog.c \
    zetcode/062-fontdialog.c \
    zetcode/063-colordialog.c \
    zetcode/070-button.c \
    zetcode/071-checkbutton.c \
    zetcode/072-frames.c \
    zetcode/073-hscale.c \
    zetcode/074-label.c \
    zetcode/075-markup.c \
    zetcode/080-combobox.c \
    zetcode/081-separator.c \
    zetcode/082-entry.c \
    zetcode/083-image.c \
    zetcode/084-statusbar.c \
    zetcode/085-iconview.c \
    zetcode/090-listview.c \
    zetcode/091-dynamiclistview.c \
    zetcode/092-treeview.c \
    zetcode/100-simpletextview.c \
    0Temp.c \
    main.c \
    zetcode/101-linescols.c \
    zetcode/102-search.c \
    zetcode/mycpu/main.c \
    zetcode/mycpu/mycpu.c

DISTFILES += \
    install.sh \
    License.txt \
    meson.build \
    Readme.md \

HEADERS += \
    zetcode/mycpu/mycpu.h



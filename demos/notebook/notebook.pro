TEMPLATE = app
TARGET = testgtk
CONFIG = c99 link_pkgconfig
DEFINES =
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += gtk+-3.0
PKGCONFIG += tinyc

HEADERS = \
    appwindow.h \
    etkwidget.h

SOURCES = \
    0Temp.c \
    appactions.c \
    appwindow.c \
    etkwidget.c \
    main.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.txt \



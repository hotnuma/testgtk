#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "config.h"
#include <gtk/gtk.h>
#include <etype.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

#endif // APPWINDOW_H



#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtk/gtk.h>
#include <etype.h>
#include <stdbool.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

#endif // APPWINDOW_H


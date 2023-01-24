#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <etype.h>
#include <gtk/gtk.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

#endif // APPWINDOW_H



#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <etktype.h>
#include <gtk/gtk.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

typedef enum
{
    APP_WINDOW_ACTION_FILE_MENU = 1,
    APP_WINDOW_ACTION_FILE_OPEN,

} AppWindowAction;

#endif // APPWINDOW_H



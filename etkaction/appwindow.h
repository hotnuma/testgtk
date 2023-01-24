#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtk/gtk.h>
#include <etype.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

typedef enum
{
    APP_WINDOW_ACTION_FILE_MENU,
    APP_WINDOW_ACTION_NEW_TAB,

    APP_WINDOW_N_ACTIONS,

} AppWindowAction;

#endif // APPWINDOW_H



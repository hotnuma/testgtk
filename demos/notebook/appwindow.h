#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <etype.h>

struct _AppWindow
{
    GtkWindow __parent__;

    GtkWidget *notebook;
};

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkWindow)

void _window_action_new(AppWindow *window);
void _window_action_open(AppWindow *window);
void _window_action_close_tab(AppWindow *window);

#endif // APPWINDOW_H



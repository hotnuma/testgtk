#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "application.h"
#include <etype.h>

#define TYPE_APPWINDOW (window_get_type())
E_DECLARE_FINAL_TYPE(AppWindow, window, APPWINDOW, GtkApplicationWindow)

AppWindow* window_new(Application *app);
void window_open(AppWindow *win, GFile *file);

#endif // APPWINDOW_H



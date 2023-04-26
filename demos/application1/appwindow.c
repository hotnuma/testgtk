#include "appwindow.h"

struct _AppWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AppWindow, window, GTK_TYPE_APPLICATION_WINDOW);

static void window_init(AppWindow *window)
{
    (void) window;
}

static void window_class_init(AppWindowClass *klass)
{
    (void) klass;
}

AppWindow* window_new(Application *application)
{
    return g_object_new(TYPE_APPWINDOW, "application", application, NULL);
}

void window_open(AppWindow *window, GFile *file)
{
    (void) window;
    (void) file;
}



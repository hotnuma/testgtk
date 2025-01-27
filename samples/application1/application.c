#include <gtk/gtk.h>

#include "application.h"
#include "appwindow.h"

struct _Application
{
    GtkApplication parent;
};

G_DEFINE_TYPE(Application, application, GTK_TYPE_APPLICATION);

static void application_init(Application *application)
{
    (void) application;
}

static void application_activate(GApplication *application)
{
    AppWindow *win = window_new(APPLICATION(application));

    gtk_window_present(GTK_WINDOW(win));
}

static void application_open(GApplication *app, GFile **files, gint n_files,
                             const gchar *hint)
{
    (void) hint;

    AppWindow *win;

    GList *windows = gtk_application_get_windows(GTK_APPLICATION(app));

    if (windows)
        win = APPWINDOW(windows->data);
    else
        win = window_new(APPLICATION(app));

    for (int i = 0; i < n_files; ++i)
        window_open(win, files[i]);

    gtk_window_present(GTK_WINDOW(win));
}

static void application_class_init(ApplicationClass *klass)
{
    GApplicationClass *gapplication_class = G_APPLICATION_CLASS(klass);
    gapplication_class->activate = application_activate;
    gapplication_class->open = application_open;
}

Application* application_new()
{
    return g_object_new(TYPE_APPLICATION,
                        "application-id", "org.gtk.exampleapp",
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}



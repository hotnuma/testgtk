#include "application.h"
#include "config.h"

#include "window.h"
#include <gtk/gtk.h>

static void _application_finalize(GObject *object);
static void _application_startup(GApplication *application);
static void _application_shutdown(GApplication *application);
static void _application_activate(GApplication *application);
static int _application_command_line(GApplication *application,
                                     GApplicationCommandLine *command_line);

GtkWidget* application_window_open(Application *application);
static void _application_window_take(Application *application, GtkWindow *window);

struct _ApplicationClass
{
    GtkApplicationClass __parent__;
};

struct _Application
{
    GtkApplication __parent__;
};

G_DEFINE_TYPE(Application, application, GTK_TYPE_APPLICATION)

static void application_class_init(ApplicationClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->finalize = _application_finalize;

    GApplicationClass *gapplication_class = G_APPLICATION_CLASS(klass);
    gapplication_class->startup = _application_startup;
    gapplication_class->shutdown = _application_shutdown;

    gapplication_class->activate = _application_activate;
    gapplication_class->command_line = _application_command_line;
}

static void application_init(Application *application)
{
    g_application_set_flags(G_APPLICATION(application),
                            G_APPLICATION_HANDLES_COMMAND_LINE);
}

static void _application_finalize(GObject *object)
{
    G_OBJECT_CLASS(application_parent_class)->finalize(object);
}

static void _application_startup(GApplication *gapp)
{
    G_APPLICATION_CLASS(application_parent_class)->startup(gapp);
}

static void _application_shutdown(GApplication *gapp)
{
    G_APPLICATION_CLASS(application_parent_class)->shutdown(gapp);
}

Application* application_get()
{
    GApplication *default_app = g_application_get_default();

    if (default_app)
        return APPLICATION(g_object_ref(default_app));
    else
        return g_object_ref_sink(g_object_new(APPLICATION_TYPE,
                                              "application-id",
                                              "org.hotnuma.Application",
                                              NULL));
}

static void _application_activate(GApplication *gapp)
{
    //g_print("application_activate\n");
    //application_open_window(APPLICATION(gapp));

    G_APPLICATION_CLASS(application_parent_class)->activate(gapp);
}

static int _application_command_line(GApplication *gapp,
                                     GApplicationCommandLine *command_line)
{
    UNUSED(gapp);
    UNUSED(command_line);

    g_print("application_command_line\n");

    //Application *application  = APPLICATION(gapp);

    application_window_open(APPLICATION(gapp));

    return 0;
}

GtkWidget* application_window_open(Application *application)
{
    g_return_val_if_fail(IS_APPLICATION(application), NULL);

    GtkWidget *window = g_object_new(TYPE_WINDOW, NULL);

    _application_window_take(application, GTK_WINDOW(window));

    gtk_widget_show(window);

    return window;
}

void _application_window_take(Application *application, GtkWindow *window)
{
    g_return_if_fail(IS_APPLICATION(application));
    g_return_if_fail(GTK_IS_WINDOW(window));

    // only windows without a parent get a new window group
    if (gtk_window_get_transient_for(window) == NULL && !gtk_window_has_group(window))
    {
        GtkWindowGroup *group = gtk_window_group_new();
        gtk_window_group_add_window(group, window);
        g_object_weak_ref(G_OBJECT(window),
                          (GWeakNotify) (void(*)(void)) g_object_unref,
                          group);
    }

    gtk_window_set_application(window, GTK_APPLICATION(application));
}



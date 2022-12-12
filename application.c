#include <application.h>
#include <config.h>
#include <gtk/gtk.h>

static void application_get_property(GObject *object, guint prop_id, GValue *value,
                                     GParamSpec *pspec);
static void application_set_property(GObject *object, guint prop_id, const GValue *value,
                                     GParamSpec *pspec);
static void application_finalize(GObject *object);

static void application_startup(GApplication *application);
static void application_shutdown(GApplication *application);
static void application_activate(GApplication *application);
static int application_command_line(GApplication *application,
                                    GApplicationCommandLine *command_line);

GtkWidget* application_open_window(Application *application);
void application_take_window(Application *application, GtkWindow *window);

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
    GApplicationClass *gapplication_class = G_APPLICATION_CLASS(klass);

    gobject_class->get_property = application_get_property;
    gobject_class->set_property = application_set_property;
    gobject_class->finalize = application_finalize;

    //gapplication_class->startup = application_startup;
    gapplication_class->activate = application_activate;
    gapplication_class->shutdown = application_shutdown;
    gapplication_class->command_line = application_command_line;
}

static void application_init(Application *application)
{
    UNUSED(application);

    g_application_set_flags(G_APPLICATION(application), G_APPLICATION_HANDLES_COMMAND_LINE);
    //g_application_add_main_option_entries(G_APPLICATION(application), option_entries);
}

static void application_get_property(GObject *object, guint prop_id, GValue *value,
                                     GParamSpec *pspec)
{
    UNUSED(object);
    UNUSED(value);

    switch (prop_id)
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void application_set_property(GObject      *object,
                                            guint         prop_id,
                                            const GValue *value,
                                            GParamSpec   *pspec)
{
    UNUSED(object);
    UNUSED(value);

    switch (prop_id)
    {

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void application_startup(GApplication *gapp)
{
    G_APPLICATION_CLASS(application_parent_class)->startup(gapp);
}

static void application_shutdown(GApplication *gapp)
{
    G_APPLICATION_CLASS(application_parent_class)->shutdown(gapp);
}

static void application_finalize(GObject *object)
{
    (*G_OBJECT_CLASS(application_parent_class)->finalize)(object);
}

static int application_command_line(GApplication *gapp,
                                    GApplicationCommandLine *command_line)
{
    UNUSED(gapp);
    UNUSED(command_line);

    g_print("application_command_line\n");

    //Application *application  = APPLICATION(gapp);

    application_open_window(APPLICATION(gapp));

    return EXIT_SUCCESS;
}

static void application_activate(GApplication *gapp)
{
    /* TODO */

    g_print("application_activate\n");

    //application_open_window(APPLICATION(gapp));

    G_APPLICATION_CLASS(application_parent_class)->activate(gapp);
}


Application* application_get()
{
    GApplication *default_app = g_application_get_default();

    if (default_app)
        return APPLICATION(g_object_ref(default_app));
    else
        return g_object_ref_sink(g_object_new(TYPE_APPLICATION,
                                              "application-id",
                                              "org.hotnuma.Application",
                                              NULL));
}

void application_take_window(Application *application, GtkWindow *window)
{
    g_return_if_fail(GTK_IS_WINDOW(window));
    g_return_if_fail(IS_APPLICATION(application));

    /* only windows without a parent get a new window group */
    if (gtk_window_get_transient_for(window) == NULL && !gtk_window_has_group(window))
    {
        GtkWindowGroup *group = gtk_window_group_new();
        gtk_window_group_add_window(group, window);
        g_object_weak_ref(G_OBJECT(window),
                          (GWeakNotify) (void(*)(void)) g_object_unref,
                          group);
    }

    // add ourselves to the window
    gtk_window_set_application(window, GTK_APPLICATION(application));
}

GtkWidget* application_open_window(Application *application)
{
    g_return_val_if_fail(IS_APPLICATION(application), NULL);

    GtkWidget *window = g_object_new(GTK_TYPE_WINDOW, NULL);

    /* hook up the window */
    application_take_window(application, GTK_WINDOW(window));

    /* show the new window */
    gtk_widget_show(window);

    return window;
}



#include "appwindow.h"
#include <etkwidget.h>

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);
static void _window_create_view(AppWindow *window);


struct _AppWindow
{
    GtkWindow __parent__;
};

G_DEFINE_TYPE(AppWindow, window, GTK_TYPE_WINDOW)

static void window_class_init(AppWindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = _window_dispose;
    gobject_class->finalize = _window_finalize;
}

static void _window_dispose(GObject *object)
{

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void _window_finalize(GObject *object)
{

    G_OBJECT_CLASS(window_parent_class)->finalize(object);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    (void) event;
    (void) data;

    GtkWindow *window = GTK_WINDOW(widget);

    if (etk_window_is_last(window))
        gtk_main_quit();

    return false;
}

static void window_init(AppWindow *window)
{
    gtk_window_set_title(GTK_WINDOW(window), "Gtk App Simple");
    gtk_window_set_default_size(GTK_WINDOW(window),
                                300,
                                200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    g_signal_connect(window, "delete-event",
                     G_CALLBACK(_window_on_delete), NULL);

    _window_create_view(window);
}

static void _window_create_view(AppWindow *window)
{
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll),
                                        GTK_SHADOW_IN);
}



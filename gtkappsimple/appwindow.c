#include "appwindow.h"

#include <libmacros.h>
#include <stdbool.h>

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);

static void _window_create_view(AppWindow *window);

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);

enum
{
    COL_INFO = 0,
    COL_ICON,
    COL_TITLE,
    COL_FILE,
    NUM_COLS
};

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
    //AppWindow *window = APPWINDOW(object);

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void _window_finalize(GObject *object)
{
    //AppWindow *window = APPWINDOW(object);

    G_OBJECT_CLASS(window_parent_class)->finalize(object);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    UNUSED(widget);
    UNUSED(event);
    UNUSED(data);

#if 0
    Preferences *prefs = get_preferences();
    GtkWindow *window = GTK_WINDOW(widget);

    if (gtk_widget_get_visible(GTK_WIDGET(widget)))
    {
        GdkWindowState state = gdk_window_get_state(
                                            gtk_widget_get_window(widget));

        prefs->window_maximized = ((state & (GDK_WINDOW_STATE_MAXIMIZED
                                             | GDK_WINDOW_STATE_FULLSCREEN))
                                    != 0);

        if (!prefs->window_maximized)
        {
            gtk_window_get_size(window,
                                &prefs->window_width,
                                &prefs->window_height);
        }
    }
#endif

    gtk_main_quit();

    return false;
}

static void window_init(AppWindow *window)
{

#if 0
    Preferences *prefs = get_preferences();

    gtk_window_set_default_size(GTK_WINDOW(window),
                                prefs->window_width,
                                prefs->window_height);

    if (G_UNLIKELY(prefs->window_maximized))
        gtk_window_maximize(GTK_WINDOW(window));
#endif

    gtk_window_set_title(GTK_WINDOW(window), "Gtk App Simple");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

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



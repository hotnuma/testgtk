#include "appwindow.h"

#include "preferences.h"

static void window_dispose(GObject *object);
static void window_finalize(GObject *object);
static void window_realize(GtkWidget *widget);
static void window_unrealize(GtkWidget *widget);

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);

struct _AppWindow
{
    GtkWindow __parent__;
};

G_DEFINE_TYPE(AppWindow, window, GTK_TYPE_WINDOW)

static void window_class_init(AppWindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = window_dispose;
    gobject_class->finalize = window_finalize;

    GtkWidgetClass *gtkwidget_class = GTK_WIDGET_CLASS(klass);
    gtkwidget_class->realize = window_realize;
    gtkwidget_class->unrealize = window_unrealize;
}

static void window_dispose(GObject *object)
{
    // do something...

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void window_finalize(GObject *object)
{
    // do something...

    G_OBJECT_CLASS(window_parent_class)->finalize(object);
}

static void window_realize(GtkWidget *widget)
{
    GTK_WIDGET_CLASS(window_parent_class)->realize(widget);

    // do something...
}

static void window_unrealize(GtkWidget *widget)
{
    // do something...

    GTK_WIDGET_CLASS(window_parent_class)->unrealize(widget);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    (void) event;
    (void) data;

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

    return false;
}


static void window_init(AppWindow *window)
{
    g_signal_connect(window, "delete-event",
                     G_CALLBACK(_window_on_delete), NULL);

    Preferences *prefs = get_preferences();

    gtk_window_set_default_size(GTK_WINDOW(window),
                                prefs->window_width,
                                prefs->window_height);

    if (G_UNLIKELY(prefs->window_maximized))
        gtk_window_maximize(GTK_WINDOW(window));
}



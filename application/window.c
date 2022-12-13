#include "window.h"
#include "config.h"

#include <gtk/gtk.h>

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);
static void window_realize(GtkWidget *widget);
static void window_unrealize(GtkWidget *widget);

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);

struct _WindowClass
{
    GtkWindowClass __parent__;
};

struct _Window
{
    GtkWindow __parent__;
};

G_DEFINE_TYPE(Window, window, GTK_TYPE_WINDOW)

static void window_class_init(WindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = _window_dispose;
    gobject_class->finalize = _window_finalize;

    GtkWidgetClass *gtkwidget_class = GTK_WIDGET_CLASS(klass);
    gtkwidget_class->realize = window_realize;
    gtkwidget_class->unrealize = window_unrealize;
}

static void window_init(Window *window)
{
    g_signal_connect(window, "delete-event", G_CALLBACK(_window_on_delete), NULL);

    gint last_window_width = 640;
    gint last_window_height = 480;

    gtk_window_set_default_size(GTK_WINDOW(window),
                                last_window_width,
                                last_window_height);

    gboolean last_window_maximized = FALSE;

    if (G_UNLIKELY(last_window_maximized))
        gtk_window_maximize(GTK_WINDOW(window));

    // Create widgets...

}

static void _window_dispose(GObject *object)
{
    //Window  *window = WINDOW(object);

    // do something...

    (*G_OBJECT_CLASS(window_parent_class)->dispose)(object);
}

static void _window_finalize(GObject *object)
{
    //Window *window = WINDOW(object);

    // do something...

    (*G_OBJECT_CLASS(window_parent_class)->finalize)(object);
}

static void window_realize(GtkWidget *widget)
{
    (*GTK_WIDGET_CLASS(window_parent_class)->realize)(widget);

    //Window *window = WINDOW(widget);

    // do something...
}

static void window_unrealize(GtkWidget *widget)
{
    //Window *window = WINDOW(widget);

    // do something...

    (*GTK_WIDGET_CLASS(window_parent_class)->unrealize)(widget);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    UNUSED(widget);
    UNUSED(event);
    UNUSED(data);

    return FALSE;
}



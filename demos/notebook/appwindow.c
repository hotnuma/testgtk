#include "appwindow.h"
#include "etkwidget.h"

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);

// toolbar helper -------------------------------------------------------------

GtkToolItem* toolbar_append_item(GtkWidget *toolbar, const char *icon_name,
                                 GCallback callback, GtkWindow *window)
{
    GtkWidget *img = gtk_image_new_from_icon_name(
                                icon_name,
                                GTK_ICON_SIZE_SMALL_TOOLBAR);

    if (!img)
        return NULL;

    GtkToolItem *item = gtk_tool_button_new(img, NULL);

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);
    g_signal_connect_swapped(G_OBJECT(item), "clicked", callback, window);

    return item;
}

void toolbar_append_separator(GtkWidget *toolbar)
{
    GtkToolItem *sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
}

// app window -----------------------------------------------------------------

G_DEFINE_TYPE(AppWindow, window, GTK_TYPE_WINDOW)

static void window_class_init(AppWindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = _window_dispose;
    gobject_class->finalize = _window_finalize;
}

static void _window_dispose(GObject *object)
{
    // do something

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void _window_finalize(GObject *object)
{
    // do something

    G_OBJECT_CLASS(window_parent_class)->finalize(object);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    (void) widget;
    (void) event;
    (void) data;

    gtk_main_quit();

    return false; // close the window
}

static void _window_on_quit(GtkWidget *widget)
{
    gtk_window_close(GTK_WINDOW(widget));
}

static void window_init(AppWindow *window)
{
    gtk_window_set_title(GTK_WINDOW(window), "Gtk App Simple");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    gtk_window_set_default_size(GTK_WINDOW(window),
                                400,
                                300);

    g_signal_connect(window, "delete-event",
                     G_CALLBACK(_window_on_delete), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkWidget *_toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(_toolbar), GTK_TOOLBAR_ICONS);

    toolbar_append_item(_toolbar, "gtk-new",
                        G_CALLBACK(_window_action_new), GTK_WINDOW(window));
    toolbar_append_item(_toolbar, "gtk-open",
                        G_CALLBACK(_window_action_open), GTK_WINDOW(window));
    //toolbar_append_item(_toolbar, "gtk-save",
    //                    G_CALLBACK(_window_action_open), GTK_WINDOW(window));
    toolbar_append_separator(_toolbar);
    toolbar_append_item(_toolbar, "gtk-quit",
                        G_CALLBACK(_window_on_quit), GTK_WINDOW(window));

    gtk_grid_attach(GTK_GRID(grid), _toolbar, 0, row, 1, 1);
    ++row;

    window->notebook = gtk_notebook_new();
    gtk_widget_set_hexpand(window->notebook, true);
    gtk_widget_set_vexpand(window->notebook, true);
    gtk_grid_attach(GTK_GRID(grid), window->notebook, 0, row, 1, 1);
    ++row;

    _window_action_new(window);
}



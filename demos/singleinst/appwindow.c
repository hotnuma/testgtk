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

#if 0

#include <libsocket.h>
#include <sys/socket.h>
#include <netinet/in.h>

void MainWindow::_createWindow()
{
    _wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(_wnd), "App Title");
    gtk_window_set_default_size(GTK_WINDOW(_wnd), 400, 300);
    gtk_window_set_position(GTK_WINDOW(_wnd), GTK_WIN_POS_CENTER);
    setWindowObject(_wnd, this);

    _grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(_wnd), _grid);

    _createMenu();

    GtkWidget *scrolled_w = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_hexpand(scrolled_w, true);
    gtk_widget_set_vexpand(scrolled_w, true);
    gtk_grid_attach(GTK_GRID(_grid), scrolled_w, 0, _gridrow, 1, 1);
    ++_gridrow;

    GtkWidget *view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_w), view);

    //GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    //GtkTextIter iter;
    //gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    //gtk_text_buffer_insert(buffer, &iter, "sample text\n", -1);

    _statusbar = gtk_statusbar_new();
    gtk_grid_attach(GTK_GRID(_grid), _statusbar, 0, _gridrow, 1, 1);
    ++_gridrow;

    g_signal_connect(_wnd, "destroy", G_CALLBACK(_onDestroyCB), this);
}

#endif



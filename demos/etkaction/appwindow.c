#include "config.h"
#include "appwindow.h"

#include <stdbool.h>
#include "etkaction.h"

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);
static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);

static void _window_create_view(AppWindow *window);
static void _window_create_menubar(AppWindow *window);
static void _window_create_toolbar(AppWindow *window);

static void _window_action_test(AppWindow *window, gpointer data);


struct _AppWindow
{
    GtkWindow       __parent__;

    GtkAccelGroup   *accel_group;

    GtkWidget       *menubar;
    gboolean        menubar_visible;
    GtkWidget       *toolbar;
    GtkWidget       *grid;
};

G_DEFINE_TYPE(AppWindow, window, GTK_TYPE_WINDOW)

static EtkActionEntry _window_actions[] =
{
    {APP_WINDOW_ACTION_FILE_MENU,
     "<Actions>/AppWindow/file-menu",
     "",
     ETK_MENU_ITEM,
     N_("_File"),
     NULL,
     NULL,
     NULL},

    {APP_WINDOW_ACTION_FILE_OPEN,
     "<Actions>/AppWindow/file-open",
     "<Primary>o",
     ETK_IMAGE_MENU_ITEM,
     N_("_Open"),
     N_("Open file"),
     "document-open",
     G_CALLBACK(_window_action_test)},

    {0},
};

static void window_class_init(AppWindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = _window_dispose;
    gobject_class->finalize = _window_finalize;

    //etk_actions_translate(_window_actions);
}

static void _window_dispose(GObject *object)
{
    AppWindow *window = APPWINDOW(object);

    etk_actions_dispose(GTK_WINDOW(window), window->accel_group);
    window->accel_group = NULL;

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void _window_finalize(GObject *object)
{
    // do something

    G_OBJECT_CLASS(window_parent_class)->finalize(object);
}

static void window_init(AppWindow *window)
{
    gtk_window_set_title(GTK_WINDOW(window), "Test Gtk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    window->accel_group = etk_actions_init(GTK_WINDOW(window), _window_actions);

    g_signal_connect(window, "delete-event",
                     G_CALLBACK(_window_on_delete), NULL);

    _window_create_view(window);
}

static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    (void) widget;
    (void) event;
    (void) data;

    gtk_main_quit();

    return false;
}

static void _window_create_view(AppWindow *window)
{
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll),
                                        GTK_SHADOW_IN);

    window->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scroll), window->grid);
    gtk_widget_show_all(GTK_WIDGET(window));

    // build the application menubar
    _window_create_menubar(window);

    _window_create_toolbar(window);

    // menubar visibility
    window->menubar_visible = true;
    if (window->menubar_visible == false)
        gtk_widget_hide(window->menubar);

    gtk_grid_attach(GTK_GRID(window->grid), window->menubar, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(window->grid), window->toolbar, 0, 1, 1, 1);
}

static void _window_create_menubar(AppWindow *window)
{
    // build the application menubar
    window->menubar = gtk_menu_bar_new();
    gtk_widget_set_hexpand(window->menubar, true);

    GtkWidget *item = NULL;
    GtkWidget *submenu = NULL;

    item = etk_menu_item_new_from_action(GTK_MENU_SHELL(window->menubar),
                                         APP_WINDOW_ACTION_FILE_MENU,
                                         _window_actions,
                                         G_OBJECT(window));
    submenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), GTK_WIDGET(submenu));
    gtk_menu_set_accel_group(GTK_MENU(submenu), window->accel_group);

    etk_menu_item_new_from_action(GTK_MENU_SHELL(submenu),
                                  APP_WINDOW_ACTION_FILE_OPEN,
                                  _window_actions,
                                  G_OBJECT(window));

    gtk_widget_show_all(window->menubar);
}

static void _window_create_toolbar(AppWindow *window)
{
    window->toolbar = gtk_toolbar_new();

    etk_tool_button_new_from_action(GTK_TOOLBAR(window->toolbar),
                                                APP_WINDOW_ACTION_FILE_OPEN,
                                                _window_actions,
                                                G_OBJECT(window));

    gtk_widget_show_all(window->toolbar);
}

static void _window_action_test(AppWindow *window, gpointer data)
{
    (void) window;

    g_print("%s\n", G_OBJECT_TYPE_NAME(data));

    g_print("bla\n");
}



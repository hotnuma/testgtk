#include "config.h"
#include "appwindow.h"

#include <libmacros.h>
#include <stdbool.h>
#include "etkaction.h"

static void _window_dispose(GObject *object);
static void _window_finalize(GObject *object);

static void _window_create_view(AppWindow *window);
static gboolean _window_on_delete(GtkWidget *widget, GdkEvent *event, gpointer data);
static void _window_action_test(AppWindow *window);

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
    GtkWindow       __parent__;

    GtkAccelGroup   *accel_group;

    GtkWidget       *grid;
    GtkWidget       *menubar;
    gboolean        menubar_visible;
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

    {APP_WINDOW_ACTION_NEW_TAB,
     "<Actions>/AppWindow/new-tab",
     "<Primary>t",
     ETK_IMAGE_MENU_ITEM,
     N_("New _Tab"),
     N_("Open a new tab for the displayed location"),
     "tab-new",
     G_CALLBACK(_window_action_test)},
};

#define get_action_entry(id) \
    etk_get_action_entry_by_id(_window_actions, G_N_ELEMENTS(_window_actions), id)

static void window_class_init(AppWindowClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->dispose = _window_dispose;
    gobject_class->finalize = _window_finalize;

    etk_translate_action_entries(_window_actions, G_N_ELEMENTS(_window_actions));
}

static void _window_dispose(GObject *object)
{
    AppWindow *window = APPWINDOW(object);

    if (window->accel_group != NULL)
    {
        gtk_accel_group_disconnect(window->accel_group, NULL);
        gtk_window_remove_accel_group(GTK_WINDOW (window), window->accel_group);
        g_object_unref(window->accel_group);
        window->accel_group = NULL;
    }

    G_OBJECT_CLASS(window_parent_class)->dispose(object);
}

static void _window_finalize(GObject *object)
{
    //AppWindow *window = APPWINDOW(object);
    //UNUSED(window);

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

    window->accel_group = gtk_accel_group_new();
    etk_accel_map_add_entries(_window_actions, G_N_ELEMENTS(_window_actions));
    etk_accel_group_connect_action_entries(window->accel_group,
                                           _window_actions,
                                           G_N_ELEMENTS(_window_actions),
                                           window);

    gtk_window_add_accel_group(GTK_WINDOW(window), window->accel_group);

    gtk_window_set_title(GTK_WINDOW(window), "Test Gtk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    g_signal_connect(window, "delete-event",
                     G_CALLBACK(_window_on_delete), NULL);

    _window_create_view(window);
}

static GtkWidget* _window_create_menu(AppWindow *window, AppWindowAction action)
{
    g_return_val_if_fail(IS_APPWINDOW(window), NULL);

    GtkWidget *item;
    item = etk_menu_item_new_from_action_entry(get_action_entry(action),
                                               G_OBJECT(window),
                                               GTK_MENU_SHELL(window->menubar));

    GtkWidget *submenu = gtk_menu_new();
    gtk_menu_set_accel_group(GTK_MENU(submenu), window->accel_group);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), GTK_WIDGET(submenu));

    return submenu;
}

static void _window_create_view(AppWindow *window)
{
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scroll);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroll),
                                        GTK_SHADOW_IN);

    window->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(scroll), window->grid);
    gtk_widget_show(window->grid);

    /* build the menubar */
    window->menubar = gtk_menu_bar_new();

    GtkWidget *submenu = _window_create_menu(window, APP_WINDOW_ACTION_FILE_MENU);

    etk_menu_item_new_from_action_entry(get_action_entry(APP_WINDOW_ACTION_NEW_TAB),
                                        G_OBJECT(window),
                                        GTK_MENU_SHELL(submenu));

    gtk_widget_show_all(window->menubar);

    window->menubar_visible = true;
    if (window->menubar_visible == false)
        gtk_widget_hide (window->menubar);

    gtk_widget_set_hexpand (window->menubar, TRUE);
    gtk_grid_attach (GTK_GRID (window->grid), window->menubar, 0, 0, 1, 1);
}

static void _window_action_test(AppWindow *window)
{
    UNUSED(window);

    g_print("bla\n");
}



#include <gtk/gtk.h>
#include <stdbool.h>
#include <cstring.h>
#include <libpath.h>
#include <libapp.h>

enum
{
    COL_ICON = 0,
    COL_TEXT,
    NUM_COLS
};

static GtkListStore* treeview_create(GtkWidget *window)
{
    c_autounref GtkListStore *store;
    store = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

    GtkWidget *view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    GtkTreeViewColumn *col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "Title");

    GtkCellRenderer *renderer = gtk_cell_renderer_pixbuf_new();
    gtk_tree_view_column_pack_start(col, renderer, FALSE);
    gtk_tree_view_column_set_attributes(col, renderer,
                                        "pixbuf", COL_ICON,
                                        NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_set_attributes(col, renderer,
                                        "text", COL_TEXT,
                                        NULL);

    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    gtk_container_add(GTK_CONTAINER(window), view);

    return store;
}

static bool _append_line(GtkListStore *store, const gchar *filename,
                         const gchar *text)
{
    CStringAuto *dir = cstr_new("/usr/share/icons/hicolor/48x48/apps/");
    CStringAuto *filepath = cstr_new_size(64);

    path_join(filepath, c_str(dir), filename);

    if (!file_exists(c_str(filepath)))
        return false;

    c_autounref GdkPixbuf *pix = gdk_pixbuf_new_from_file(c_str(filepath), NULL);

    if (!pix)
        return false;

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_ICON, pix,
                       COL_TEXT, text,
                       -1);

    return true;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    GtkListStore *store = treeview_create(window);

    _append_line(store, "geany.png", "Geany");

    c_refcount(store);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



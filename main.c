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

static GtkListStore *_store;

static bool _append_line(const gchar *filename, const gchar *text)
{
    if (!_store)
        return false;

    CStringAuto *dir = cstr_new("/usr/share/icons/hicolor/48x48/apps/");
    CStringAuto *filepath = cstr_new_size(64);

    path_join(filepath, c_str(dir), filename);

    if (!file_exists(c_str(filepath)))
        return false;

    GdkPixbuf *pix = gdk_pixbuf_new_from_file(c_str(filepath), NULL);

    if (!pix)
        return false;

    GtkTreeIter iter;
    gtk_list_store_append(_store, &iter);
    gtk_list_store_set(_store, &iter,
                       COL_ICON, pix,
                       COL_TEXT, text,
                       -1);

    g_object_unref(pix);

    return true;
}

GtkWidget* create_treeview()
{
    _store = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

    GtkWidget *view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(_store));

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

    gtk_widget_show_all(view);

    return view;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    GtkWidget *view = create_treeview();
    gtk_container_add(GTK_CONTAINER(window), view);

    _append_line("geany.png", "Geany");

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



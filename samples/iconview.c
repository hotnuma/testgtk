#include <libpath.h>
#include <libapp.h>
#include <gtk/gtk.h>

enum
{
    COL_DISPLAY_NAME,
    COL_PIXBUF,
    NUM_COLS
};

static bool _append_icon(GtkListStore *store, const gchar *filename,
                         const gchar *dispname)
{
    CStringAuto *dir = cstr_new("/usr/share/icons/hicolor/48x48/apps/");
    CStringAuto *filepath = cstr_new_size(64);

    path_join(filepath, c_str(dir), filename);

    if (!file_exists(c_str(filepath)))
        return false;

    GdkPixbuf *pix = gdk_pixbuf_new_from_file(c_str(filepath), NULL);

    if (!pix)
        return false;

    GtkTreeIter iter;

    gtk_list_store_append(GTK_LIST_STORE(store), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store), &iter,
                       COL_DISPLAY_NAME, dispname,
                       COL_PIXBUF, pix,
                       -1);

    g_object_unref(pix);

    return true;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "IconView");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);

    GtkWidget *scrwnd = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrwnd);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrwnd),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrwnd),
                                        GTK_SHADOW_IN);

    GtkListStore *store = gtk_list_store_new(NUM_COLS,
                                             G_TYPE_STRING,
                                             GDK_TYPE_PIXBUF);

    _append_icon(store, "firefox.png", "Firefox");
    _append_icon(store, "gimp.png", "Gimp");
    _append_icon(store, "geany.png", "Geany");

    GtkWidget *view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_container_add(GTK_CONTAINER(scrwnd), view);

    gtk_icon_view_set_text_column(GTK_ICON_VIEW(view),
                                  COL_DISPLAY_NAME);
    gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(view), COL_PIXBUF);
    gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(view),
                                     GTK_SELECTION_MULTIPLE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}



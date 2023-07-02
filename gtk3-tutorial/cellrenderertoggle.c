#include <gtk/gtk.h>

static void destroy(GtkWidget *widget, gpointer data)
{
    (void) widget;
    (void) data;

    gtk_main_quit();
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Center");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkListStore *liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_BOOLEAN);
    GtkTreeIter treeiter;

    gtk_list_store_append(liststore, &treeiter);
    gtk_list_store_set(liststore, &treeiter, 0, "Michael", 1, FALSE, -1);
    gtk_list_store_append(liststore, &treeiter);
    gtk_list_store_set(liststore, &treeiter, 0, "Rebecca", 1, TRUE, -1);
    gtk_list_store_append(liststore, &treeiter);
    gtk_list_store_set(liststore, &treeiter, 0, "Paul", 1, TRUE, -1);
    gtk_list_store_append(liststore, &treeiter);
    gtk_list_store_set(liststore, &treeiter, 0, "Jessica", 1, FALSE, -1);
    gtk_list_store_append(liststore, &treeiter);
    gtk_list_store_set(liststore, &treeiter, 0, "Lucy", 1, TRUE, -1);

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));
    gtk_container_add(GTK_CONTAINER(window), treeview);

    GtkTreeViewColumn *treeviewcolumn;
    GtkCellRenderer *cellrenderer;

    cellrenderer = gtk_cell_renderer_text_new();
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Student",
                                                              cellrenderer,
                                                              "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), treeviewcolumn);
    cellrenderer = gtk_cell_renderer_toggle_new();
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Present",
                                                              cellrenderer,
                                                              "active", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), treeviewcolumn);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



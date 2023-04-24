#include <gtk/gtk.h>
#include <stdbool.h>

enum
{
    LIST_ITEM = 0,
    N_COLUMNS
};

void list_init(GtkWidget *list)
{
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
                                        "List Items",
                                        renderer,
                                        "text",
                                        LIST_ITEM,
                                        NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    GtkListStore *store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list),
                            GTK_TREE_MODEL(store));

    g_object_unref(store);
}

void list_append(GtkWidget *list, const gchar *str)
{
    GtkListStore *store = GTK_LIST_STORE(
                            gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

void on_changed(GtkWidget *widget, gpointer label)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(
                GTK_TREE_SELECTION(widget), &model, &iter))
    {
        gchar *value;

        gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
        gtk_label_set_text(GTK_LABEL(label), value);
        g_free(value);
    }
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "List view");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    GtkWidget *list = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), false);
    gtk_widget_set_hexpand(list, true);
    gtk_widget_set_vexpand(list, true);

    GtkWidget *label = gtk_label_new("");

    //GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_box_pack_start(GTK_BOX(vbox), list, true, true, 5);
    //gtk_box_pack_start(GTK_BOX(vbox), label, false, false, 5);
    //gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    gtk_grid_attach(GTK_GRID(grid), list, 0, row, 1, 1);
    ++row;
    gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
    ++row;

    list_init(list);
    list_append(list, "Aliens");
    list_append(list, "Leon");
    list_append(list, "The Verdict");
    list_append(list, "North Face");
    list_append(list, "Der Untergang");

    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(selection, "changed",
                     G_CALLBACK(on_changed), label);

    g_signal_connect(G_OBJECT (window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



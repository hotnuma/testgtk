#include <gtk/gtk.h>

enum
{
    LIST_ITEM = 0,
    N_COLUMNS
};

static void _list_init(GtkWidget *list)
{
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column =
        gtk_tree_view_column_new_with_attributes("List Items",
                                                 renderer,
                                                 "text",
                                                 LIST_ITEM,
                                                 NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    GtkListStore *store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);
}

void _list_append(GtkWidget *list, const gchar *str)
{
    GtkListStore *store =
        GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

static void _on_changed(GtkWidget *widget, gpointer label)
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
    GtkWidget *list = gtk_tree_view_new();

    gtk_window_set_title(GTK_WINDOW(window), "List view");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_box_pack_start(GTK_BOX(box), list, TRUE, TRUE, 5);

    GtkWidget *label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), box);

    _list_init(list);
    _list_append(list, "Aliens");
    _list_append(list, "Leon");
    _list_append(list, "The Verdict");
    _list_append(list, "North Face");
    _list_append(list, "Der Untergang");

    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(selection, "changed",
                     G_CALLBACK(_on_changed), label);

    g_signal_connect(G_OBJECT (window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



#include <gtk/gtk.h>

enum
{
    LIST_ITEM = 0,
    N_COLUMNS
};

GtkWidget *list;

void append_item(GtkWidget *widget, gpointer entry)
{
    (void) widget;

    const gchar *str = gtk_entry_get_text(entry);

    GtkListStore *store = GTK_LIST_STORE(
                gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);

    gtk_entry_set_text(entry, "");
}

void remove_item(GtkWidget *widget, gpointer selection)
{
    (void) widget;

    GtkListStore *store;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    GtkTreeIter iter;
    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
                                        &model, &iter))
    {
        gtk_list_store_remove(store, &iter);
    }
}

void remove_all(GtkWidget *widget, gpointer selection)
{
    (void) widget;
    (void) selection;

    GtkListStore *store;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

    GtkTreeIter iter;

    if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
    {
        return;
    }

    gtk_list_store_clear(store);
}

void list_init(GtkWidget *list)
{
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            "List Item",
            renderer,
            "text", LIST_ITEM,
            NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

    GtkListStore *store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

    g_object_unref(store);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "List view");
    gtk_widget_set_size_request(window, 370, 270);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    GtkWidget *sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
                                        GTK_SHADOW_ETCHED_IN);

    list = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
    gtk_container_add(GTK_CONTAINER(sw), list);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);

    GtkWidget *add = gtk_button_new_with_label("Add");
    gtk_box_pack_start(GTK_BOX(hbox), add, FALSE, TRUE, 3);

    GtkWidget *remove = gtk_button_new_with_label("Remove");
    gtk_box_pack_start(GTK_BOX(hbox), remove, FALSE, TRUE, 3);

    GtkWidget *removeAll = gtk_button_new_with_label("Remove All");
    gtk_box_pack_start(GTK_BOX(hbox), removeAll, FALSE, TRUE, 3);

    GtkWidget *entry = gtk_entry_new();
    gtk_widget_set_size_request(entry, 120, -1);
    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, TRUE, 3);

    list_init(list);

    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

    g_signal_connect(G_OBJECT(add), "clicked",
                     G_CALLBACK(append_item), entry);
    g_signal_connect(G_OBJECT(remove), "clicked",
                     G_CALLBACK(remove_item), selection);
    g_signal_connect(G_OBJECT(removeAll), "clicked",
                     G_CALLBACK(remove_all), selection);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



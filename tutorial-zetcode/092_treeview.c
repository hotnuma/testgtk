#include <gtk/gtk.h>

enum
{
    COLUMN = 0,
    NUM_COLS
};

void on_changed(GtkWidget *widget, gpointer statusbar)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(
                GTK_TREE_SELECTION(widget), &model, &iter))
    {
        gchar *value;

        gtk_tree_model_get(model, &iter, COLUMN, &value,  -1);
        gtk_statusbar_push(GTK_STATUSBAR(statusbar),
                           gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
                                                        value),
                           value);
        g_free(value);
    }
}

GtkTreeModel *create_and_fill_model()
{
    GtkTreeStore *treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);

    GtkTreeIter toplevel;
    GtkTreeIter child;

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,
                       COLUMN, "Scripting languages",
                       -1);

    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "Python",
                       -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "Perl",
                       -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "PHP",
                       -1);

    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,
                       COLUMN, "Compiled languages",
                       -1);

    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "C",
                       -1);

    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "C++",
                       -1);

    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child,
                       COLUMN, "Java",
                       -1);

    return GTK_TREE_MODEL(treestore);
}

GtkWidget *create_view_and_model(void)
{
    GtkWidget *view = gtk_tree_view_new();

    GtkTreeViewColumn *col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "Programming languages");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer,
                                       "text", COLUMN);

    GtkTreeModel *model = create_and_fill_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);

    return view;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Tree view");
    gtk_widget_set_size_request(window, 350, 300);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *view = create_view_and_model();
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);

    GtkWidget *statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);

    g_signal_connect(selection, "changed",
                     G_CALLBACK(on_changed), statusbar);

    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



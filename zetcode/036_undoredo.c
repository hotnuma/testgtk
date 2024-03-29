#include <gtk/gtk.h>

void undo_redo(GtkWidget *widget,  gpointer item)
{
    static gint count = 2;
    const gchar *name = gtk_widget_get_name(widget);

    if (g_strcmp0(name, "undo"))
        ++count;
    else
        --count;

    if (count < 0)
    {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(item, TRUE);
    }

    if (count > 5)
    {
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(item, TRUE);
    }
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Undo redo");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
    GtkToolItem *undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(GTK_WIDGET(undo), "undo");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, -1);

    GtkToolItem *redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), redo, -1);

    g_signal_connect(G_OBJECT(undo), "clicked",
                     G_CALLBACK(undo_redo), redo);
    g_signal_connect(G_OBJECT(redo), "clicked",
                     G_CALLBACK(undo_redo), undo);

    GtkToolItem *item = NULL;

    item = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(gtk_main_quit), NULL);
    G_GNUC_END_IGNORE_DEPRECATIONS;

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



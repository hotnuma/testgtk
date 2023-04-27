#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "toolbar");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

    GtkToolItem *item = NULL;

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
    item = gtk_tool_button_new_from_stock("gtk-new");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_tool_button_new_from_stock("gtk-open");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_tool_button_new_from_stock("gtk-save");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item = gtk_tool_button_new_from_stock("gtk-quit");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);
    g_signal_connect(G_OBJECT(item), "clicked",
                     G_CALLBACK(gtk_main_quit), NULL);
    G_GNUC_END_IGNORE_DEPRECATIONS;

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



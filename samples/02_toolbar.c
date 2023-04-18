#include <gtk/gtk.h>

GtkWidget* create_menu()
{
    GtkWidget *menu = gtk_menu_new();

    GtkWidget *item = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    g_signal_connect(G_OBJECT(item), "activate",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(menu);

    return menu;
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "toolbar");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

    GtkToolItem *item = NULL;

    item = gtk_menu_tool_button_new_from_stock("gtk-open");
    GtkWidget *menu = create_menu();
    gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(item), menu);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    item  = gtk_tool_item_new();
    GtkWidget *entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(item), entry);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), item, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



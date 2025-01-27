#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Submenu");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    GtkWidget *menu = NULL;
    GtkWidget *submenu = NULL;
    GtkWidget *item = NULL;

    menu = gtk_menu_item_new_with_label("File");
    submenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu), submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);

    GtkWidget *impmenu = gtk_menu_item_new_with_label("Import");
    GtkWidget *impsubmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(impmenu), impsubmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), impmenu);

    item = gtk_menu_item_new_with_label("Import news feed...");
    gtk_menu_shell_append(GTK_MENU_SHELL(impsubmenu), item);

    item = gtk_menu_item_new_with_label("Import bookmarks...");
    gtk_menu_shell_append(GTK_MENU_SHELL(impsubmenu), item);

    item = gtk_menu_item_new_with_label("Import mail...");
    gtk_menu_shell_append(GTK_MENU_SHELL(impsubmenu), item);

    item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), item);

    item = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), item);
    g_signal_connect(G_OBJECT(item), "activate",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



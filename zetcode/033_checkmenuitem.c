#include <gtk/gtk.h>

void toggle_statusbar(GtkWidget *widget, gpointer statusbar)
{
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)))
        gtk_widget_show(statusbar);
    else
        gtk_widget_hide(statusbar);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkCheckMenuItem");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    GtkWidget *statusbar = gtk_statusbar_new();
    gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 0);
    const char *str = "Status";
    gtk_statusbar_push(GTK_STATUSBAR(statusbar),
                       gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), str),
                       str);

    GtkWidget *menu = gtk_menu_item_new_with_label("View");
    GtkWidget *submenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu), submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);

    GtkWidget *item = gtk_check_menu_item_new_with_label("View statusbar");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu), item);
    g_signal_connect(G_OBJECT(item), "activate",
                     G_CALLBACK(toggle_statusbar), statusbar);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



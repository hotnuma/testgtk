#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Images");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    GtkAccelGroup *accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *submenu = NULL;
    GtkWidget *menu = NULL;
    GtkWidget *item = NULL;

    submenu = gtk_menu_item_new_with_mnemonic("_File");
    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(submenu), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), submenu);

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;

    item = gtk_image_menu_item_new_from_stock("gtk-new", NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_image_menu_item_new_from_stock("gtk-open", NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), gtk_separator_menu_item_new());

    item = gtk_image_menu_item_new_from_stock("gtk-quit", accel_group);
    gtk_widget_add_accelerator(item, "activate", accel_group,
                               GDK_KEY_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(G_OBJECT(item), "activate",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    G_GNUC_END_IGNORE_DEPRECATIONS;

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



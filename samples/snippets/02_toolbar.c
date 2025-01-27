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
    GtkToolItem *toolitem = NULL;
    GtkWidget *item = NULL;
    GtkWidget *menu = NULL;

    // GtkMenuToolButton
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
    toolitem = gtk_menu_tool_button_new_from_stock("gtk-open");
    G_GNUC_END_IGNORE_DEPRECATIONS;
    menu = create_menu();
    gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(toolitem), menu);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolitem, -1);

    // GtkMenuButton
    toolitem  = gtk_tool_item_new();
    item = gtk_menu_button_new();
    GtkWidget *image = gtk_image_new_from_icon_name("media-playback-start",
                                                    GTK_ICON_SIZE_BUTTON);
    gtk_button_set_image(GTK_BUTTON(item), image);
    gtk_button_set_relief(GTK_BUTTON(item), GTK_RELIEF_NONE);
    gtk_container_add(GTK_CONTAINER(toolitem), item);
    menu = create_menu();
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(item), menu);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolitem, -1);

    // GtkEntry
    toolitem  = gtk_tool_item_new();
    item = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(toolitem), item);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolitem, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);


    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



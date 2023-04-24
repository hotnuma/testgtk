#if 0

GtkWidget* menuCreateSub(GtkWidget *parent, const char *label)
{
    // File menu
    GtkWidget *item = gtk_menu_item_new_with_label(label);
    GtkWidget *menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(parent), item);

    return menu;
}

GtkWidget* menuAppendItem(GtkWidget *parent, const char *label,
                          GCallback func, CWindow *wnd)
{
    GtkWidget *item = gtk_menu_item_new_with_label(label);
    gtk_menu_shell_append(GTK_MENU_SHELL(parent), item);
    g_signal_connect(G_OBJECT(item), "activate", func, wnd);

    return item;
}

#endif



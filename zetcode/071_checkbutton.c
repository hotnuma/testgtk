#include <gtk/gtk.h>

void toggle_title(GtkWidget *widget, gpointer window)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
        gtk_window_set_title(window, "GtkCheckButton");
    else
        gtk_window_set_title(window, "");
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkCheckButton");
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkWidget *item = NULL;

    item = gtk_check_button_new_with_label("Show title");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(item), TRUE);
    gtk_widget_set_can_focus(item, FALSE);
    gtk_grid_attach(GTK_GRID(grid), item, 0, row, 1, 1);
    ++row;
    g_signal_connect(item, "clicked",
                     G_CALLBACK(toggle_title), (gpointer) window);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



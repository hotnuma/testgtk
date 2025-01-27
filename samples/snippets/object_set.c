#include <gtk/gtk.h>

static void destroy(GtkWidget *widget, gpointer data)
{
    (void) widget;
    (void) data;

    gtk_main_quit();
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *button = gtk_button_new();
    g_object_set(button, "label", "Quit", NULL);
    g_signal_connect(GTK_BUTTON(button), "clicked",
                     G_CALLBACK(destroy), NULL);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}



#include <gtk/gtk.h>

void print_msg(GtkWidget *widget, gpointer window)
{
    (void) widget;
    (void) window;

    printf("Button clicked\n");
    fflush(stdout);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mnemonic");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *button = gtk_button_new_with_mnemonic("_Button");

    g_signal_connect(button, "clicked",
                     G_CALLBACK(print_msg), NULL);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}



#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_container_add(GTK_CONTAINER(window), grid);
    int row = 0;

    GtkWidget *label = NULL;
    GtkWidget *entry = NULL;

    label = gtk_label_new("Name");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, row, 1, 1);
    ++row;

    label = gtk_label_new("Age");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, row, 1, 1);
    ++row;

    label = gtk_label_new("Occupation");
    gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, row, 1, 1);
    ++row;

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



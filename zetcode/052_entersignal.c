#include <gtk/gtk.h>

void enter_button(GtkWidget *widget, gpointer data)
{
    (void) data;

    GdkColor col = {0, 27000, 30000, 35000};
    gtk_widget_modify_bg(widget, GTK_STATE_PRELIGHT, &col);
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_title(GTK_WINDOW(window), "Enter signal");

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *btn = gtk_button_new_with_label("Button");
    gtk_widget_set_size_request(btn, 70, 30);

    gtk_grid_attach(GTK_GRID(grid), btn, 0, 0, 1, 1);

    g_signal_connect(G_OBJECT(btn), "enter",
                     G_CALLBACK(enter_button), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



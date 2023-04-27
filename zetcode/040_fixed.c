#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    GtkWidget *item = NULL;

    item = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), item, 150, 50);
    gtk_widget_set_size_request(item, 80, 30);

    item = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), item, 15, 15);
    gtk_widget_set_size_request(item, 80, 30);

    item = gtk_button_new_with_label("Button");
    gtk_fixed_put(GTK_FIXED(fixed), item, 100, 100);
    gtk_widget_set_size_request(item, 80, 30);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}



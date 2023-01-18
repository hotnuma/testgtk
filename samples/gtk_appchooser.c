#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    GtkWidget *view = gtk_app_chooser_widget_new("");

    gtk_app_chooser_widget_set_show_all(GTK_APP_CHOOSER_WIDGET(view), TRUE);

    gtk_container_add(GTK_CONTAINER(window), view);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}


